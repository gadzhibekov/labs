#include "windows.h"

#include <commctrl.h>
#include <stdio.h>

static BOOL     dialogResult = FALSE;
static char*    dialogOutputBuffer = NULL;
static int      dialogBufferSize = 0;
static HWND     hEditControl = NULL;
static char*    currentFilePath = NULL;

LRESULT CALLBACK DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
                case 1002:
                {
                    HWND hEdit = GetDlgItem(hwnd, 1001);
                    GetWindowText(hEdit, dialogOutputBuffer, dialogBufferSize);
                    dialogResult = TRUE;
                    DestroyWindow(hwnd);
                    return 0;
                }
                
                case 1003:
                {
                    dialogResult = FALSE;
                    DestroyWindow(hwnd);
                    return 0;
                }
            }

            break;
        }
        
        case WM_CLOSE:
        {
            dialogResult = FALSE;
            DestroyWindow(hwnd);
            return 0;
        }
        
        case WM_DESTROY:    return 0;
    }
    
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK EditorProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CREATE:
        {
            hEditControl = CreateWindowEx(
                WS_EX_CLIENTEDGE,
                "EDIT",
                "",
                WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_WANTRETURN,
                10, 10, 560, 300,
                hwnd,
                (HMENU)1001,
                GetModuleHandle(NULL),
                NULL
            );
            
            HFONT hFont = CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                                   DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                   DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Courier New");
            SendMessage(hEditControl, WM_SETFONT, (WPARAM)hFont, TRUE);
            
            if (currentFilePath)
            {
                FILE* file = fopen(currentFilePath, "r");
                if (file)
                {
                    fseek(file, 0, SEEK_END);
                    long fileSize = ftell(file);
                    fseek(file, 0, SEEK_SET);
                    
                    char* buffer = malloc(fileSize + 1);
                    if (buffer)
                    {
                        fread(buffer, 1, fileSize, file);
                        buffer[fileSize] = '\0';
                        SetWindowText(hEditControl, buffer);
                        free(buffer);
                    }
                    fclose(file);
                }
            }
            
            CreateWindow(
                "BUTTON",
                "Save",
                WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
                400, 320, 80, 30,
                hwnd,
                (HMENU)1002,
                GetModuleHandle(NULL),
                NULL
            );
            
            CreateWindow(
                "BUTTON",
                "Close",
                WS_CHILD | WS_VISIBLE,
                490, 320, 80, 30,
                hwnd,
                (HMENU)1003,
                GetModuleHandle(NULL),
                NULL
            );
            
            SetFocus(hEditControl);
            return 0;
        }
        
        case WM_SIZE:
        {
            if (hEditControl)
            {
                RECT rc;
                GetClientRect(hwnd, &rc);
                SetWindowPos(hEditControl, NULL, 10, 10, rc.right - 20, rc.bottom - 50, SWP_NOZORDER);
                
                HWND hSaveBtn = GetDlgItem(hwnd, 1002);
                HWND hCloseBtn = GetDlgItem(hwnd, 1003);
                if (hSaveBtn && hCloseBtn)
                {
                    SetWindowPos(hSaveBtn, NULL, rc.right - 180, rc.bottom - 40, 80, 30, SWP_NOZORDER);
                    SetWindowPos(hCloseBtn, NULL, rc.right - 90, rc.bottom - 40, 80, 30, SWP_NOZORDER);
                }
            }
            return 0;
        }
        
        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
                case 1002:
                {
                    if (currentFilePath)
                    {
                        int textLength = GetWindowTextLength(hEditControl);
                        if (textLength > 0)
                        {
                            char* buffer = malloc(textLength + 1);
                            if (buffer)
                            {
                                GetWindowText(hEditControl, buffer, textLength + 1);
                                
                                FILE* file = fopen(currentFilePath, "w");
                                if (file)
                                {
                                    fwrite(buffer, 1, textLength, file);
                                    fclose(file);
                                }
                                else
                                {
                                    MessageBox(hwnd, "Failes to save file", "Error", MB_OK | MB_ICONERROR);
                                }
                                
                                free(buffer);
                            }
                        }
                    }
                    DestroyWindow(hwnd);
                    return 0;
                }
                
                case 1003:
                {
                    DestroyWindow(hwnd);
                    return 0;
                }
            }
            break;
        }
        
        case WM_CLOSE:
        {
            DestroyWindow(hwnd);
            return 0;
        }
        
        case WM_DESTROY:
        {
            if (currentFilePath)
            {
                free(currentFilePath);
                currentFilePath = NULL;
            }
            hEditControl = NULL;
            return 0;
        }
    }
    
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

bool create_rename_dialog(HWND h_parent, char* output_buffer, int buffer_size)
{
    const char DIALOG_CLASS[] = "RenameDialogClass";
    
    WNDCLASS wc = {0};
    wc.lpfnWndProc = DialogProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = DIALOG_CLASS;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    
    RegisterClass(&wc);

    HWND h_dialog = CreateWindowEx(
        WS_EX_DLGMODALFRAME,
        DIALOG_CLASS,
        "Rename",
        WS_POPUP | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT,
        300, 150,
        h_parent,
        NULL,
        GetModuleHandle(NULL),
        NULL
    );

    if (!h_dialog) return FALSE;

    dialogOutputBuffer = output_buffer;
    dialogBufferSize = buffer_size;
    dialogResult = FALSE;

    HWND hText = CreateWindow(
        "STATIC",
        "Enter new name:",
        WS_CHILD | WS_VISIBLE | SS_CENTER,
        10, 15, 280, 20,
        h_dialog,
        NULL,
        GetModuleHandle(NULL),
        NULL
    );

    HWND hEdit = CreateWindow(
        "EDIT",
        "",
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
        50, 40, 200, 25,
        h_dialog,
        (HMENU)1001,
        GetModuleHandle(NULL),
        NULL
    );

    HWND hOkBtn = CreateWindow(
        "BUTTON",
        "OK",
        WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
        70, 75, 75, 25,
        h_dialog,
        (HMENU)1002,
        GetModuleHandle(NULL),
        NULL
    );

    HWND hCancelBtn = CreateWindow(
        "BUTTON",
        "Cancel",
        WS_CHILD | WS_VISIBLE,
        155, 75, 75, 25,
        h_dialog,
        (HMENU)1003,
        GetModuleHandle(NULL),
        NULL
    );

    RECT rcOwner, rcDlg;
    GetWindowRect(h_parent, &rcOwner);
    GetWindowRect(h_dialog, &rcDlg);
    
    int x = rcOwner.left + (rcOwner.right - rcOwner.left - (rcDlg.right - rcDlg.left)) / 2;
    int y = rcOwner.top + (rcOwner.bottom - rcOwner.top - (rcDlg.bottom - rcDlg.top)) / 2;
    
    SetWindowPos(h_dialog, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

    ShowWindow(h_dialog, SW_SHOW);
    SetFocus(hEdit);

    MSG msg;
    BOOL bRet;
    
    while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
    {
        if      (bRet == -1)                        break;
        else if (!IsWindow(h_dialog))               break;
        else if (!IsDialogMessage(h_dialog, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    UnregisterClass(DIALOG_CLASS, GetModuleHandle(NULL));
    
    return dialogResult;
}

bool open_text_editor(HWND hParent, const char* filePath)
{
    const char EDITOR_CLASS[]   = "TextEditorClass";
    
    WNDCLASS wc                 = {0};
    wc.lpfnWndProc              = EditorProc;
    wc.hInstance                = GetModuleHandle(NULL);
    wc.lpszClassName            = EDITOR_CLASS;
    wc.hbrBackground            = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor                  = LoadCursor(NULL, IDC_ARROW);
    
    RegisterClass(&wc);

    if (currentFilePath) free(currentFilePath);
    currentFilePath             = _strdup(filePath);

    HWND hEditor = CreateWindowEx(
        WS_EX_DLGMODALFRAME,
        EDITOR_CLASS,
        "Text Editor",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT,
        600, 400,
        hParent,
        NULL,
        GetModuleHandle(NULL),
        NULL
    );

    if (!hEditor) 
    {
        if (currentFilePath) free(currentFilePath);

        currentFilePath = NULL;
        return FALSE;
    }

    RECT rcOwner, rcEditor;
    GetWindowRect(hParent, &rcOwner);
    GetWindowRect(hEditor, &rcEditor);
    
    int x = rcOwner.left + (rcOwner.right  - rcOwner.left - (rcEditor.right  - rcEditor.left)) / 2;
    int y = rcOwner.top  + (rcOwner.bottom - rcOwner.top  - (rcEditor.bottom - rcEditor.top))  / 2;
    
    SetWindowPos(hEditor, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

    ShowWindow(hEditor, SW_SHOW);

    MSG msg;
    BOOL bRet;
    
    while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
    {
        if      (bRet == -1)            break;
        else if (!IsWindow(hEditor))    break;
        else if (!IsDialogMessage(hEditor, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    UnregisterClass(EDITOR_CLASS, GetModuleHandle(NULL));
    
    return TRUE;
}