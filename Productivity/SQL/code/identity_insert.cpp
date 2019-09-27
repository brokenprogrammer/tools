#include "stdio.h"
#include "malloc.h"
#include "string.h"
#include "ctype.h"
#include "types.h"

OM_INTERNAL b32
IsEmptyString(char *String)
{
    b32 Result = false;

    if (*String == '\0')
    {
        Result = true;
    } 

    return (Result);
}

OM_INTERNAL u32
StringLength(char *String)
{
    u32 Count = 0;

    if (String)
    {
        while(*String++)
        {
            ++Count;
        }
    }

    return (Count);
}

OM_INTERNAL void
StringCopy(u32 Size, char *SourceInit, char *DestinationInit)
{
    u8 *Source = (u8 *)SourceInit; 
    u8 *Destination = (u8 *)DestinationInit;

    while (Size--)
    {
        *Destination++ = *Source++;
    }
}

OM_INTERNAL b32
StringsAreEqual(char *A, char *B)
{
    b32 Result = (A == B);

    if (A && B)
    {
        while (*A && *B && (*A == *B))
        {
            ++A;
            ++B;
        }

        Result = ((*A == 0) && (*B == 0));
    }

    return (Result);
}

OM_INTERNAL b32
StringCompare(char *A, char *B)
{
    b32 Result = false;

    while (*A && *B)
    {
        if (*A != *B)
        {
            return (Result);
        }
        A++;
        B++;
    }

    if (*B == '\0')
    {
        Result = true;
    }

    return (Result);
}

OM_INTERNAL b32
StringContains(char *A, char *B)
{
    b32 Result = false;

    if (A && B)
    {
        while (*A != '\0')
        {
            if ((*A == *B) && StringCompare(A, B))
            {
                Result = true;
                break;
            }
            A++;
        }
    }

    return (Result);
}

OM_INTERNAL char *
StringGetSubstring(char *A, char *B)
{
    while (*A != '\0')
    {
        if ((*A == *B) && StringCompare(A, B))
        {
            return (A);
        }
        A++;
    }

    return (NULL);
}

struct entity
{
    char *Name;
    char* Identifiers[1024];
};

void
ReadFileIdentifiers(char *FileName)
{
    entity Entity = { };

    FILE *File = fopen(FileName, "r");
    if (File == NULL)
    {
        // TODO(Oskar): Propper logging.
        printf("Error: couldn't open file.");
        return;
    }

    // NOTE(Oskar): Get file length
    fseek(File, 0, SEEK_END);
    u32 FileSize = ftell(File);
    fseek(File, 0, SEEK_SET);

    char *Buffer = (char *) malloc(FileSize * sizeof(char)) + 1;

    int c;
    for (u64 Index = 0; (c = fgetc(File)) != EOF; ++Index)
    {
        Buffer[Index] = (char) c;
    }

    // TODO(Oskar): Close File

    const char NewLine = '\n';
    char *Lines = strtok(Buffer, &NewLine);

    int Line = 0;
    while (Lines != NULL)
    {
        ++Line;

        if (StringContains(Lines, "public"))
        {
            while (isspace(*Lines)) ++Lines;
            Lines += strlen("public") + 1;

            if (StringContains(Lines, "class"))
            {
                Lines += strlen("class") + 1;

            }

            if (StringContains(Lines, "virtual"))
            {
                Lines = strtok(NULL, &NewLine);
                continue;
            }

            // TODO(Oskar): Handle normal identifier
            while (!isspace(*Lines)) ++Lines;

            printf("%d:%s\n", Line, Lines);
        }
        Lines = strtok(NULL, &NewLine);
    }

    fclose(File);
    //free(Buffer);
}

int
main (int argc, char **args)
{
    ReadFileIdentifiers("Order.cs");

    return (0);
}