#include <windows.h>
#include <stdio.h>

int main(void)
{
    WIN32_FIND_DATAA findData;
    HANDLE hFind;

    hFind = FindFirstFileA("*.*", &findData);

    if (hFind == INVALID_HANDLE_VALUE) {
        printf("FindFirstFileA failed: %lu\n", GetLastError());
        return 1;
    }

    do {
        printf("File: %s\n", findData.cFileName);

        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            printf("  Type: Directory\n");
        else
            printf("  Type: File\n");

    } while (FindNextFileA(hFind, &findData));

    FindClose(hFind);
    return 0;
}