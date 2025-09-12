#ifndef UTILS_H
#define UTILS_H

#include <windows.h>
#include <stdbool.h>

bool        rename_obj(const char* old_path, const char* new_name);
BOOL        copy_file_or_directory(const char* path, BOOL copyOperation);
BOOL        paste_file_or_directory(const char* targetDir);
BOOL        delete_directory_recursive(const char* path);
BOOL        has_content_to_paste();
void        clear_copy_buffer();
const char* get_copied_path();

#endif // UTILS_H