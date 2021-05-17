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

int main()
{
    // TODO(Oskar): Cli args to specify x64 or x86, x64 default.

    Find_Result Result = find_visual_studio_and_windows_sdk();

    if (Result.vs_varsall_path != NULL)
    {
        char CBuffer[2048];
        wchar_t Buffer[2048];
        wcscpy(Buffer, L"CALL \"");
        wcscat(Buffer, Result.vs_varsall_path);
        wcscat(Buffer, L"vcvarsall.bat\" x64");

        sprintf(CBuffer, "%ws", Buffer);
        system(CBuffer);
    }
    else
    {
        printf("ERROR: vcvars not found! \n");
        pritnf("Please submit an issue at: https://github.com/brokenprogrammer/tools");
    }

    free_resources(&Result);
    return 0;
}