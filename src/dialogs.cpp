#ifndef DIALOGS_CPP
#define DIALOGS_CPP

#include <windows.h>
#include <commdlg.h>
// #include <shobjidl.h>

#include "dialogs.h"

std::string openAudioFileDialog() {
    OPENFILENAMEA dialog;
    char szFile[256];
    HWND hwnd;
    HANDLE hf;

    // Initialize ofn
    ZeroMemory(&dialog, sizeof(dialog));
    dialog.lStructSize = sizeof(dialog);
    dialog.hwndOwner = NULL;
    dialog.lpstrFile = szFile;
    dialog.lpstrFile[0] = '\0'; // So it doesn't initialize with garbage data
    dialog.nMaxFile = sizeof(szFile);
    dialog.lpstrFilter = "Wave\0*.wav*\0";
    dialog.nFilterIndex = 1;
    dialog.lpstrFileTitle = NULL;
    dialog.nMaxFileTitle = 0;
    dialog.lpstrInitialDir = NULL;
    dialog.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    // Display open dialog box
    printf("boutta open file dialog\n");
    if (GetOpenFileNameA(&dialog) == TRUE) {
        char filename[strlen(dialog.lpstrFile)];
        strcpy(filename, dialog.lpstrFile);
        return std::string(filename);
    }
    printf("did not find it.\n");
    return "";
}

#endif /* DIALOGS_CPP */
