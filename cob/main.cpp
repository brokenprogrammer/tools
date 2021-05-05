#include <stdio.h>
#include <locale.h>

void
PrintUsage()
{
    // TODO(Oskar): Print usage.
    printf("Instructions..\n");
}

int main(int argc, char *argv[])
{
    // NOTE(Oskar): Allow special characters such as åäö
    setlocale(LC_ALL, "");
    
    if (argc == 2)
    {
        // NOTE(Oskar): Show word
        printf("%s - Word explanation", argv[1]);
        // printf("Number of args: %d\n", argc);
        // printf("%s\n", argv[0]);
        // printf("%s\n", argv[1]);
    }
    else if (argc == 3)
    {
        // NOTE(Oskar): Save word
        printf("Savind the following words: \n");
        printf("%s - %s\n", argv[1], argv[2]);
    }
    else
    {
        PrintUsage();
    }

    return 0;
}