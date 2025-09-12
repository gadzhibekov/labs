#ifndef LIST_H
#define LIST_H

#include <windows.h>
#include <commctrl.h>
#include <stdbool.h>

struct ListObj
{
    char* name;
    char* type;
    char* size;
};

void            add_obj_to_list(struct ListObj obj, int *count, LVITEM *lvi, HWND *hListView);
void            open_dir(const char* path, int* list_obj_count, LVITEM *lvi, HWND *hListView);
int             count_objs_in_dir(const char *path);
void            free_dir_objs(struct ListObj* objs, int count);
struct ListObj* get_dir_objs(const char* path, int* count);
bool            is_file(const char *path); 
bool            is_dir(const char *path);
void            free_list(HWND *hListView, int* list_obj_count);
bool            delete_selected_list_item(HWND *hListView, int* list_obj_count);
char*           read_file(const char* path);

#endif // LIST_H