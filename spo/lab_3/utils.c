#include "utils.h"

#include <stdio.h>
#include <shlobj.h>
#include <string.h>

static char copiedPath[MAX_PATH * 2]    = {0};
static BOOL isCopyOperation             = FALSE;

bool rename_obj(const char* old_path, const char* new_name)
{
    if (!old_path || !new_name || strlen(old_path) == 0 || strlen(new_name) == 0) 
    {
        printf("Error: Invalid input parameters\n");
        return false;
    }
    
    char normalized_old_path[2 * MAX_PATH];
    strcpy(normalized_old_path, old_path);

    for (char* p = normalized_old_path; *p; p++) 
    {
        if (*p == '/') *p = '\\';
    }
    
    char directory[MAX_PATH];
    char old_file_name[MAX_PATH];
    
    char* last_backslash = strrchr(normalized_old_path, '\\');
    if (last_backslash) 
    {
        size_t dirLength = last_backslash - normalized_old_path;
        strncpy(directory, normalized_old_path, dirLength);
        directory[dirLength] = '\0';
        
        strcpy(old_file_name, last_backslash + 1);
    } 
    else 
    {
        strcpy(directory, ".");
        strcpy(old_file_name, normalized_old_path);
    }
    
    char new_path[MAX_PATH * 2];
    snprintf(new_path, sizeof(new_path), "%s\\%s", directory, new_name);
    
    if (MoveFile(normalized_old_path, new_path)) 
    {
        printf("Successfully renamed\n");
        return true;
    } 
    else 
    {
        DWORD error = GetLastError();
        printf("Failed to rename. Windows error code: %d\n", error);
        
        if      (error == ERROR_FILE_NOT_FOUND) printf("File not found: %s\n", normalized_old_path);
        else if (error == ERROR_ACCESS_DENIED)  printf("Access denied\n");
        else if (error == ERROR_ALREADY_EXISTS) printf("File with new name already exists\n");
        
        return false;
    }
}

BOOL copy_file_or_directory(const char* path, BOOL copyOperation)
{
    if (!path || strlen(path) == 0) 
    {
        MessageBox(NULL, "No file/directory to copy", "Error", MB_OK | MB_ICONERROR);
        return FALSE;
    }

    char normalizedPath[MAX_PATH * 2];
    strcpy(normalizedPath, path);
    
    for (char* p = normalizedPath; *p; p++) 
    {
        if (*p == '/') *p = '\\';
    }

    DWORD attrib = GetFileAttributes(normalizedPath);

    if (attrib == INVALID_FILE_ATTRIBUTES) 
    {
        char errorMsg[256];
        snprintf(errorMsg, sizeof(errorMsg), "File/directory does not exist:\n%s", normalizedPath);
        MessageBox(NULL, errorMsg, "Error", MB_OK | MB_ICONERROR);
        return FALSE;
    }

    strncpy(copiedPath, normalizedPath, MAX_PATH * 2 - 1);
    copiedPath[MAX_PATH * 2 - 1] = '\0';
    isCopyOperation = copyOperation;

    printf("Prepared for %s: %s\n", copyOperation ? "copy" : "cut", copiedPath);

    return TRUE;
}

BOOL paste_file_or_directory(const char* targetDir)
{
    if (strlen(copiedPath) == 0) 
    {
        MessageBox(NULL, "Nothing to paste", "Error", MB_OK | MB_ICONERROR);
        return FALSE;
    }

    if (!targetDir || strlen(targetDir) == 0) 
    {
        MessageBox(NULL, "No target directory specified", "Error", MB_OK | MB_ICONERROR);
        return FALSE;
    }

    char normalizedTargetDir[MAX_PATH * 2];
    strcpy(normalizedTargetDir, targetDir);
    
    for (char* p = normalizedTargetDir; *p; p++) 
    {
        if (*p == '/') *p = '\\';
    }

    char* fileName = strrchr(copiedPath, '\\');

    if (!fileName)  fileName = (char*) copiedPath;
    else            fileName++;

    char targetPath[MAX_PATH * 2];
    snprintf(targetPath, sizeof(targetPath), "%s\\%s", normalizedTargetDir, fileName);

    printf("Pasting %s to %s\n", copiedPath, targetPath);

    if (isCopyOperation) 
    {
        SHFILEOPSTRUCT fileOp   = {0};
        fileOp.hwnd             = NULL;
        fileOp.wFunc            = FO_COPY;
        fileOp.pFrom            = copiedPath;
        fileOp.pTo              = targetPath;
        fileOp.fFlags           = FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_SILENT;

        int result              = SHFileOperation(&fileOp);

        if (result == 0) 
        {
            printf("Successfully copied: %s -> %s\n", copiedPath, targetPath);
            return TRUE;
        } 
        else 
        {
            printf("Failed to copy. Error: %d\n", result);
            return FALSE;
        }
    } 
    else 
    {
        SHFILEOPSTRUCT fileOp   = {0};
        fileOp.hwnd             = NULL;
        fileOp.wFunc            = FO_MOVE;
        fileOp.pFrom            = copiedPath;
        fileOp.pTo              = targetPath;
        fileOp.fFlags           = FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_SILENT;

        int result              = SHFileOperation(&fileOp);
        
        if (result == 0) 
        {
            printf("Successfully moved: %s -> %s\n", copiedPath, targetPath);
            copiedPath[0] = '\0';
            return TRUE;
        } 
        else 
        {
            printf("Failed to move. Error: %d\n", result);
            return FALSE;
        }
    }
}

const char* get_copied_path()
{
    return copiedPath;
}

BOOL has_content_to_paste()
{
    return strlen(copiedPath) > 0;
}

void clear_copy_buffer()
{
    copiedPath[0] = '\0';
    isCopyOperation = FALSE;
}

BOOL delete_directory_recursive(const char* path)
{
    if (!path || strlen(path) == 0) 
    {
        return FALSE;
    }

    char normalizedPath[MAX_PATH * 2];
    strcpy(normalizedPath, path);
    
    for (char* p = normalizedPath; *p; p++) 
    {
        if (*p == '/') *p = '\\';
    }

    char searchPath[MAX_PATH * 2 + 3];
    snprintf(searchPath, sizeof(searchPath), "%s\\*", normalizedPath);

    WIN32_FIND_DATA findData;
    HANDLE hFind = FindFirstFile(searchPath, &findData);
    
    if (hFind == INVALID_HANDLE_VALUE) 
    {
        return RemoveDirectory(normalizedPath);
    }

    BOOL success = TRUE;
    
    do 
    {
        if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0) continue;

        char filePath[MAX_PATH * 2];
        snprintf(filePath, sizeof(filePath), "%s\\%s", normalizedPath, findData.cFileName);

        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
        {  
            if (!delete_directory_recursive(filePath)) 
            {
                success = FALSE;
            }
        } 
        else 
        {
            if (!DeleteFile(filePath)) success = FALSE;
        }

    } 
    while (FindNextFile(hFind, &findData));

    FindClose(hFind);

    if (success) success = RemoveDirectory(normalizedPath);

    return success;
}