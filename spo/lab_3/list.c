#include "list.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

void add_obj_to_list(struct ListObj obj, int *count, LVITEM *lvi, HWND *hListView)
{
    (*lvi).iItem    = *count;
    (*lvi).iSubItem = 0;
    (*lvi).pszText  = obj.name;
    ListView_InsertItem(*hListView, lvi);

    (*lvi).iSubItem = 1;
    (*lvi).pszText  = obj.size;
    ListView_SetItem(*hListView, lvi);

    (*lvi).iSubItem = 2;
    (*lvi).pszText  = obj.type;
    ListView_SetItem(*hListView, lvi);

    (*count)++;
}

int count_objs_in_dir(const char *path) 
{
    struct dirent *entry;
    DIR *dir;
    int count = 0;
    dir = opendir(path);

    if (dir == NULL) return -1;
     
    while ((entry = readdir(dir)) != NULL) 
    {
        if (entry->d_name[0] != '.')  count++;
    }

    closedir(dir);

    return count;
}

struct ListObj* get_dir_objs(const char* path, int* count)
{
    DIR* dir;
    struct dirent* entry;
    struct stat file_stat;
    struct ListObj* result = NULL;
    int capacity = 0;
    int actual_count = 0;
    
    dir = opendir(path);
    if (dir == NULL) 
    {
        perror("Ошибка открытия директории");
        *count = 0;
        return NULL;
    }
    
    while ((entry = readdir(dir)) != NULL) 
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
        
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        
        if (stat(full_path, &file_stat) == -1)  continue;
        
        if (actual_count >= capacity) 
        {
            capacity = (capacity == 0) ? 10 : capacity * 2;
            struct ListObj* temp = realloc(result, capacity * sizeof(struct ListObj));

            if (temp == NULL) 
            {
                perror("Ошибка выделения памяти");
                closedir(dir);
                *count = 0;
                return NULL;
            }

            result = temp;
        }
        
        result[actual_count].name = strdup(entry->d_name);
        
        if (S_ISREG(file_stat.st_mode)) 
        {
            result[actual_count].type = strdup("file");
        } 
        else if (S_ISDIR(file_stat.st_mode)) 
        {
            result[actual_count].type = strdup("directory");
        } 
        else 
        {
            result[actual_count].type = strdup("other");
        }
        
        char size_str[64];
        
        if (S_ISREG(file_stat.st_mode)) 
        {
            snprintf(size_str, sizeof(size_str), "%ld", (long)file_stat.st_size);
        } 
        else 
        {
            snprintf(size_str, sizeof(size_str), "-");
        }

        result[actual_count].size = strdup(size_str);
        
        actual_count++;
    }
    
    closedir(dir);
    *count = actual_count;

    return result;
}

void free_dir_objs(struct ListObj* objs, int count)
{
    if (objs == NULL) return;
    
    for (int i = 0; i < count; i++) 
    {
        free(objs[i].name);
        free(objs[i].type);
        free(objs[i].size);
    }

    free(objs);
}

void open_dir(const char* path, int* list_obj_count, LVITEM *lvi, HWND *hListView)
{
    int count = count_objs_in_dir(path);
            
    struct ListObj* contents = get_dir_objs(path, &count);
    
    if (contents != NULL) 
    {
        for (int i = 0; i < count; i++) 
        { 
            struct ListObj obj = {contents[i].name, contents[i].type, contents[i].size};
            add_obj_to_list(obj, list_obj_count, lvi, hListView);
        }
        
        free_dir_objs(contents, count);
    }
}

bool is_file(const char *path) 
{
    struct stat file_stat;
    
    if (stat(path, &file_stat) != 0) return false;
    
    return S_ISREG(file_stat.st_mode);
}

bool is_dir(const char *path) 
{
    struct stat file_stat;
    
    if (stat(path, &file_stat) != 0) return false;
    
    return S_ISDIR(file_stat.st_mode);
}

void free_list(HWND *hListView, int* list_obj_count) 
{
    ListView_DeleteAllItems(*hListView);

    (*list_obj_count) = 0;
}

bool delete_selected_list_item(HWND *hListView, int* list_obj_count) 
{
    if (*hListView == NULL) return false;
    
    int selectedIndex = ListView_GetNextItem(*hListView, -1, LVNI_SELECTED);
    
    if (selectedIndex == -1) return false;
    
    (*list_obj_count)--;

    return ListView_DeleteItem(*hListView, selectedIndex);
}

char* read_file(const char* path) 
{
    FILE* file      = NULL;
    char* buffer    = NULL;
    long file_size  = 0;
    
    file            = fopen(path, "rb");
    
    if (file == NULL) return NULL;

    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    if (file_size == 0) 
    {
        fclose(file);
        char message[256];
        return NULL;
    }
    
    buffer = (char*)malloc(file_size + 1);

    if (buffer == NULL) 
    {
        fclose(file);
        return NULL;
    }
    
    size_t bytes_read = fread(buffer, 1, file_size, file);
    
    if (bytes_read != file_size) 
    {
        fclose(file);
        free(buffer);
        return NULL;
    }
    
    buffer[file_size] = '\0';

    fclose(file);

    return buffer;
}