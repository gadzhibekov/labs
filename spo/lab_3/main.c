#include "list.h"
#include "utils.h"
#include "windows.h"

#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <string.h>

#define ID_BUTTON_BACK                          101
#define ID_BUTTON_FORWARD                       102
#define ID_BUTTON_RENAME                        103
#define ID_BUTTON_DELETE                        104
#define ID_BUTTON_COPY                          105
#define ID_BUTTON_PASTE                         106
#define ID_BUTTON_CUT                           107
#define ID_BUTTON_HELP                          108
#define ID_LISTVIEW                             201
#define ID_ACCEL_COPY                           ID_BUTTON_COPY
#define ID_ACCEL_PASTE                          ID_BUTTON_PASTE

#define START_DIR                               "test_dir/"
#define LOG

int     list_obj_count                          = 0;
int     last_dirs_count                         = 0;
char    current_dir[MAX_PATH]                   = START_DIR;
char    last_dir[MAX_PATH * 2]                  = "";
char    current_obj[MAX_PATH * 2]               = "";
char    last_dirs[MAX_PATH * 2][MAX_PATH * 2]       ;


static ACCEL accelTable[] = 
{
    { FVIRTKEY | FCONTROL, 'C', ID_ACCEL_COPY   },
    { FVIRTKEY | FCONTROL, 'V', ID_ACCEL_PASTE  },
};

static HWND     hListView;
static HACCEL   hAccel = NULL;

void UpdateListViewSize(HWND hwnd);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
    const char CLASS_NAME[] = "FileManagerWindowClass";

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "File Manager",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        800, 600,
        NULL, NULL, hInstance, NULL
    );

    if (!hwnd) return 0;

    ShowWindow(hwnd, nCmdShow);

    hAccel = CreateAcceleratorTable(accelTable, sizeof(accelTable) / sizeof(ACCEL));

    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (!TranslateAccelerator(hwnd, hAccel, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return 0;
}

void UpdateListViewSize(HWND hwnd)
{
    RECT rcClient;
    GetClientRect(hwnd, &rcClient);
    int clientWidth     = rcClient.right    - rcClient.left;
    int clientHeight    = rcClient.bottom   - rcClient.top;

    int listTop         = 50;
    int listLeft        = 10;
    int listRight       = clientWidth       - 10;
    int listBottom      = clientHeight      - 10;
    
    SetWindowPos(hListView, NULL, listLeft, listTop, 
                 listRight - listLeft, listBottom - listTop, SWP_NOZORDER);

    int listViewWidth = listRight - listLeft;
    ListView_SetColumnWidth(hListView, 0, listViewWidth - 210);
    ListView_SetColumnWidth(hListView, 1, 100);
    ListView_SetColumnWidth(hListView, 2, 100);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
    switch (uMsg) 
    {
        case WM_CREATE: 
        {
            INITCOMMONCONTROLSEX icex = { sizeof(icex), ICC_LISTVIEW_CLASSES | ICC_STANDARD_CLASSES };
            InitCommonControlsEx(&icex);

            HINSTANCE hInst = GetModuleHandle(NULL);
            
            CreateWindow("BUTTON", "Back",    WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_DEFPUSHBUTTON,
                        10,10,  80,30, hwnd, (HMENU)ID_BUTTON_BACK,    hInst, NULL);
            CreateWindow("BUTTON", "Forward", WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_DEFPUSHBUTTON,
                        100,10, 80,30, hwnd, (HMENU)ID_BUTTON_FORWARD, hInst, NULL);
            CreateWindow("BUTTON", "Rename",  WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_DEFPUSHBUTTON,
                        190,10,100,30, hwnd, (HMENU)ID_BUTTON_RENAME,  hInst, NULL);
            CreateWindow("BUTTON", "Delete",  WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_DEFPUSHBUTTON,
                        300,10, 80,30, hwnd, (HMENU)ID_BUTTON_DELETE,  hInst, NULL);
            CreateWindow("BUTTON", "Copy",    WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_DEFPUSHBUTTON,
                        390,10, 90,30, hwnd, (HMENU)ID_BUTTON_COPY,    hInst, NULL);
            CreateWindow("BUTTON", "Paste",   WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_DEFPUSHBUTTON,
                        490,10, 80,30, hwnd, (HMENU)ID_BUTTON_PASTE,   hInst, NULL);
            CreateWindow("BUTTON", "Cut",     WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_DEFPUSHBUTTON,
                        580,10, 80,30, hwnd, (HMENU)ID_BUTTON_CUT,     hInst, NULL);
            CreateWindow("BUTTON", "Help",    WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_DEFPUSHBUTTON,
                        670,10, 80,30, hwnd, (HMENU)ID_BUTTON_HELP,    hInst, NULL);

            hListView = CreateWindowEx(
                0, WC_LISTVIEW, "",
                WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS,
                10,50, 760,400,
                hwnd, (HMENU)ID_LISTVIEW, hInst, NULL
            );

            LVCOLUMN lvc = {0};
            lvc.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;

            lvc.iSubItem = 0;
            lvc.cx       = 250;
            lvc.pszText  = "Name";
            ListView_InsertColumn(hListView, 0, &lvc);

            lvc.iSubItem = 1;
            lvc.cx       = 100;
            lvc.pszText  = "Size";
            ListView_InsertColumn(hListView, 1, &lvc);

            lvc.iSubItem = 2;
            lvc.cx       = 100;
            lvc.pszText  = "Type";
            ListView_InsertColumn(hListView, 2, &lvc);

            LVITEM lvi = {0};
            lvi.mask = LVIF_TEXT;

            open_dir(START_DIR, &list_obj_count, &lvi, &hListView);

            break;
        }

        case WM_SIZE:
        {
            UpdateListViewSize(hwnd);
            break;
        }

        case WM_NOTIFY:
        {
            LPNMHDR nmhdr = (LPNMHDR)lParam;
            if (nmhdr->idFrom == ID_LISTVIEW) 
            {
                if (nmhdr->code == NM_CLICK) 
                {
                    LPNMLISTVIEW pnmv = (LPNMLISTVIEW)lParam;
                    int idx = ListView_GetNextItem(hListView, -1, LVNI_SELECTED);
                    
                    if (idx != -1) 
                    {
                        char buf[MAX_PATH];
                        ListView_GetItemText(hListView, idx, 0, buf, MAX_PATH);
                        snprintf(current_obj, sizeof(current_obj), "%s%s", current_dir, buf);
                    }
                }
                else if (nmhdr->code == NM_DBLCLK) 
                {
                    PostMessage(hwnd, WM_COMMAND, (WPARAM)ID_BUTTON_FORWARD, 0);
                }
            }

            break;
        }

        case WM_COMMAND: 
        {
            switch (LOWORD(wParam)) 
            {
                case ID_BUTTON_BACK:
                {
                    if (last_dirs_count != 0)
                    {
                        free_list(&hListView, &list_obj_count);

                        LVITEM new_item = {0};
                        new_item.mask = LVIF_TEXT;

                        strcpy(current_dir, last_dirs[last_dirs_count - 1]);
                        strcpy(last_dirs[last_dirs_count - 1], " ");
                        last_dirs_count--;

                        open_dir(current_dir, &list_obj_count, &new_item, &hListView);

                        #ifdef LOG
                        printf("<--\n");
                        for (int i = 0; i < last_dirs_count; ++i)
                        {
                            printf("[%d]\tlast_dir:\t%s\n", i + 1, last_dirs[i]);
                        }
                        printf("[+]\tcurrent_dir:\t%s\n\n", current_dir);
                        #endif // LOG
                    }

                    break;
                }

                case ID_BUTTON_FORWARD:
                {
                    if (is_dir(current_obj))
                    {
                        free_list(&hListView, &list_obj_count);

                        LVITEM new_item = {0};
                        new_item.mask = LVIF_TEXT;

                        open_dir(current_obj, &list_obj_count, &new_item, &hListView);
                        snprintf(current_obj + strlen(current_obj), (MAX_PATH * 2) - strlen(current_obj), "/");

                        strncpy(last_dir, current_dir, MAX_PATH - 1);
                        last_dir[MAX_PATH - 1] = '\0';

                        strncpy(current_dir, current_obj, MAX_PATH - 1);
                        current_dir[MAX_PATH - 1] = '\0';
                        
                        strcpy(last_dirs[last_dirs_count], last_dir);
                        last_dirs_count++;

                        #ifdef LOG
                        printf("-->\n");
                        for (int i = 0; i < last_dirs_count; ++i)
                        {
                            printf("[%d]\tlast_dir:\t%s\n", i + 1, last_dirs[i]);
                        }
                        printf("[+]\tcurrent_dir:\t%s\n\n", current_dir);
                        #endif // LOG
                    }
                    else
                    {
                        open_text_editor(hwnd, current_obj);
                    }

                    break;
                }

                case ID_BUTTON_RENAME: 
                {
                    int selectedIndex = ListView_GetNextItem(hListView, -1, LVNI_SELECTED);
    
                    if (selectedIndex == -1) 
                    {
                        MessageBox(NULL, "Please select an item to rename", "Error", MB_OK | MB_ICONERROR);
                        break;
                    }
                    
                    char old_name[MAX_PATH];
                    ListView_GetItemText(hListView, selectedIndex, 0, old_name, MAX_PATH);
                    
                    char full_path[MAX_PATH * 2];
                    snprintf(full_path, sizeof(full_path), "%s%s", current_dir, old_name);

                    char new_name[MAX_PATH] = {0};
                    if (create_rename_dialog(hwnd, new_name, MAX_PATH))
                    {
                        if (strlen(new_name) > 0)
                        {
                            if (!rename_obj(full_path, new_name))
                            {
                                MessageBox(NULL, "Rename error", "Failed to rename", MB_OK);
                            }

                            free_list(&hListView, &list_obj_count);

                            LVITEM new_item = {0};
                            new_item.mask = LVIF_TEXT;

                            open_dir(current_dir, &list_obj_count, &new_item, &hListView);
                        }
                    }
                    
                    break;
                }

                case ID_BUTTON_DELETE:
                {
                    int selectedIndex = ListView_GetNextItem(hListView, -1, LVNI_SELECTED);
                    
                    if (selectedIndex != -1)
                    {
                        char buffer[MAX_PATH];
                        ListView_GetItemText(hListView, selectedIndex, 0, buffer, MAX_PATH);
                        
                        char full_path[MAX_PATH * 2];
                        snprintf(full_path, sizeof(full_path), "%s%s", current_dir, buffer);
                        
                        for (char* p = full_path; *p; p++) 
                        {
                            if (*p == '/') *p = '\\';
                        }
                        
                        printf("Deleting: %s\n", full_path);
                        
                        DWORD attrib = GetFileAttributes(full_path);

                        if (attrib == INVALID_FILE_ATTRIBUTES) 
                        {
                            printf("File not found\n");
                            break;
                        }
                        
                        if (attrib & FILE_ATTRIBUTE_DIRECTORY) 
                        {
                            if (delete_directory_recursive(full_path)) 
                            {
                                printf("Folder deleted successfully\n");
                                delete_selected_list_item(&hListView, &list_obj_count);
                            }
                            else                            
                            {
                                printf("Failed to delete folder. Error: %d\n", GetLastError());
                                MessageBox(hwnd, "Failed to delete directory. It may not be empty or you don't have permissions.", "Error", MB_OK | MB_ICONERROR);
                            }
                        } 
                        else 
                        {
                            if (DeleteFile(full_path))  
                            {
                                printf("File deleted successfully\n");
                                delete_selected_list_item(&hListView, &list_obj_count);
                            }
                            else                        
                            {
                                printf("Failed to delete file. Error: %d\n", GetLastError());
                                MessageBox(hwnd, "Failed to delete file. It may be in use or you don't have permissions.", "Error", MB_OK | MB_ICONERROR);
                            }
                        }
                    }

                    break;
                }

                case ID_BUTTON_COPY:
                {
                    int selectedIndex = ListView_GetNextItem(hListView, -1, LVNI_SELECTED);
    
                    if (selectedIndex != -1)
                    {
                        char buffer[MAX_PATH];
                        ListView_GetItemText(hListView, selectedIndex, 0, buffer, MAX_PATH);
                        
                        char full_path[MAX_PATH * 2];
                        snprintf(full_path, sizeof(full_path), "%s%s", current_dir, buffer);
                        
                        if (copy_file_or_directory(full_path, TRUE))
                        {
                            char msg[256];
                            snprintf(msg, sizeof(msg), "Prepared for copying:\n%s", full_path);
                            MessageBox(hwnd, msg, "Copy", MB_OK | MB_ICONINFORMATION);
                        }
                    }
                    else
                    {
                        MessageBox(hwnd, "Please select an item first", "Error", MB_OK | MB_ICONERROR);
                    }
                    break;
                }

                case ID_BUTTON_PASTE:
                {
                    if (!has_content_to_paste()) 
                    {
                        MessageBox(hwnd, "Nothing to paste", "Error", MB_OK | MB_ICONERROR);

                        break;
                    }
                
                    if (paste_file_or_directory(current_dir)) 
                    {
                        free_list(&hListView, &list_obj_count);
                        LVITEM new_item = {0};
                        new_item.mask = LVIF_TEXT;
                        open_dir(current_dir, &list_obj_count, &new_item, &hListView);
                    } 
                    else 
                    {
                        MessageBox(hwnd, "Paste operation failed", "Error", MB_OK | MB_ICONERROR);
                    }

                    break;
                }

                case ID_BUTTON_CUT:
                {
                    int selectedIndex = ListView_GetNextItem(hListView, -1, LVNI_SELECTED);
    
                    if (selectedIndex != -1)
                    {
                        char buffer[MAX_PATH];
                        ListView_GetItemText(hListView, selectedIndex, 0, buffer, MAX_PATH);
                        
                        char full_path[MAX_PATH * 2];
                        snprintf(full_path, sizeof(full_path), "%s%s", current_dir, buffer);
                        
                        if (copy_file_or_directory(full_path, FALSE))
                        {
                            char msg[256];
                            snprintf(msg, sizeof(msg), "Prepared for moving (cut):\n%s", full_path);
                            MessageBox(hwnd, msg, "Cut", MB_OK | MB_ICONINFORMATION);
                        }
                    }
                    else
                    {
                        MessageBox(hwnd, "Please select an item first", "Error", MB_OK | MB_ICONERROR);
                    }

                    break;
                }

                case ID_BUTTON_HELP:
                {
                    MessageBox(hwnd, "This is a \"Help\" window", "Help", MB_OK);
                    break;
                }
            }
            
            break;
        }

        case WM_DESTROY:
        {
            PostQuitMessage(0);
            break;
        }

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}