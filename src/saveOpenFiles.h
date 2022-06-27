#ifndef SAVE_OPEN_FILES_H
#define SAVE_OPEN_FILES_H

// Provides a simple interface for Windows open/save dialog boxes for a single file type
// Requires comdlg32.lib

#include<string>
#include<fstream>
#include<windows.h>

void setOpenFilenameObject(OPENFILENAMEA* ofn, std::string& filterString, std::string& fileExtension, std::string& fileTypeName, HWND hwnd, char* szFileName);
std::string openFilename(std::string fileExtension, std::string fileTypeName, HWND hwnd);
std::string saveFilename(std::string fileExtension, std::string fileTypeName, HWND hwnd);

#endif // SAVE_OPEN_FILES_H
