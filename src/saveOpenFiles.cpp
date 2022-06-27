#include "saveOpenFiles.h"

void setOpenFilenameObject(OPENFILENAMEA* ofn, std::string& filterString, std::string& fileExtension, std::string& fileTypeName, HWND hwnd, char* szFileName)
{
    const std::string filterPartA(" (*", 3);
    const std::string filterPartB(")\0*", 3);
    const std::string filterPartC("\0All Files (*.*)\0*.*\0\0", 22);

    filterString = fileTypeName + filterPartA + fileExtension + filterPartB + fileExtension + filterPartC;

    ZeroMemory(ofn, sizeof(*ofn));
    ofn->lStructSize = sizeof(*ofn);
    ofn->hwndOwner = hwnd;
    ofn->lpstrFilter = (LPCSTR)filterString.c_str();
    ofn->lpstrFile = (LPSTR)szFileName;
    ofn->nMaxFile = MAX_PATH;
    ofn->lpstrDefExt = (LPCSTR)fileExtension.c_str();
    ofn->Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
}

std::string openFilename(std::string fileExtension, std::string fileTypeName, HWND hwnd)
{
    std::string filterString;
    char szFilename[MAX_PATH] = { 0 };
    OPENFILENAMEA ofn;
    setOpenFilenameObject(&ofn, filterString, fileExtension, fileTypeName, hwnd, szFilename);

    std::string output = "";

    if(GetOpenFileNameA(&ofn))
        output = szFilename;
    return output;
}

std::string saveFilename(std::string fileExtension, std::string fileTypeName, HWND hwnd)
{
    std::string filterString;
    char szFilename[MAX_PATH] = { 0 };
    OPENFILENAMEA ofn;
    setOpenFilenameObject(&ofn, filterString, fileExtension, fileTypeName, hwnd, szFilename);

    std::string output = "";

    if(GetSaveFileNameA(&ofn))
    {
        std::ifstream readFile(szFilename, std::ios::in | std::ios::binary);
        if(!readFile || MessageBoxA(hwnd, (LPCSTR)"This file exists.  Overwrite?", (LPCSTR)"Save As", MB_OKCANCEL) == IDOK)
            output = szFilename;

        readFile.close();
    }
    return output;
}