#ifndef WINDOWS_H
#define WINDOWS_H

#include <windows.h>
#include <stdbool.h>

bool create_rename_dialog(HWND h_parent, char* output_buffer, int buffer_size);
bool open_text_editor(HWND hParent, const char* filePath);

#endif // WINDOWS_H