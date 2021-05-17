#pragma comment(lib, "kernel32.lib") 
#pragma comment(lib, "user32.lib") 
#pragma comment(lib, "gdi32.lib") 
#pragma comment(lib, "winspool.lib") 
#pragma comment(lib, "comdlg32.lib") 
#pragma comment(lib, "advapi32.lib") 
#pragma comment(lib, "shell32.lib") 
#pragma comment(lib, "ole32.lib") 
#pragma comment(lib, "oleaut32.lib") 
#pragma comment(lib, "uuid.lib") 
#pragma comment(lib, "odbc32.lib") 
#pragma comment(lib, "odbccp32.lib")

#include "microsoft_craziness.h"
#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{

    wchar_t Architecture[4] = L"x64";
    if (argc <= 1)
    {
        printf("No arguments passed, assuming x64 ...\n");
    }
    else
    {
        char *Argument = argv[1];
        if (strcmp(Argument, "x86") == 0)
        {
            wcscpy(Architecture, L"x86");
        }
        else if (strcmp(Argument, "x64") == 0)
        {
            wcscpy(Architecture, L"x64");
        }
        else
        {
            printf("Unknown architecture, use either x86 or x64 ... \n");
            return 0;
        }
    }

    Find_Result Result = find_visual_studio_and_windows_sdk();

    if (Result.vs_varsall_path != NULL)
    {
        char CBuffer[2048];
        wchar_t Buffer[2048];
        wcscpy(Buffer, L"CALL \"");
        wcscat(Buffer, Result.vs_varsall_path);
        wcscat(Buffer, L"vcvarsall.bat\" ");
        wcscat(Buffer, Architecture);

        sprintf(CBuffer, "%ws", Buffer);
        system(CBuffer);
    }
    else
    {
        printf("ERROR: vcvars not found! \n");
        printf("Please submit an issue at: https://github.com/brokenprogrammer/tools");
    }

    free_resources(&Result);
    return 0;
}