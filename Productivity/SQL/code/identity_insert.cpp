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

struct string_list
{
    int Count;
    char **Strings;
};

OM_INTERNAL string_list
LoadStringList(char *FileName)
{
    string_list Result = { };

    FILE *File = fopen(FileName, "r");
    if (File == NULL)
    {
        // TODO(Oskar): Propper logging.
        printf("Error: couldn't open file.");
        return (Result);
    }

    // NOTE(Oskar): Get file length
    fseek(File, 0, SEEK_END);
    u32 FileSize = ftell(File);
    fseek(File, 0, SEEK_SET);

    char Buffer[4096];
    int ExpectedCount = 0;
    while (!feof(File))
    {
        fgets(Buffer, sizeof(Buffer), File);
        ++ExpectedCount;
    }

    Result.Strings = (char **)malloc(ExpectedCount* sizeof(char*));
    fseek(File, 0, SEEK_SET);
    while (!feof(File))
    {
        fgets(Buffer, sizeof(Buffer), File);
        size_t Length = strlen(Buffer);
        
        for (size_t Clean = 0; Clean < Length; ++Clean)
        {
            if ((Buffer[Clean] == '\n') || Buffer[Clean] == '\r')
            {
                Buffer[Clean] = 0;
            }
        }
        char **Dest = &Result.Strings[Result.Count++];
        *Dest = (char *) malloc(Length + 1);
        memcpy(*Dest, Buffer, Length + 1);
    }

    fclose(File);
    return (Result);
}

struct sql_identifiers
{
    char *Name;
    int Count;
    char **Identifiers;
};

OM_INTERNAL sql_identifiers
ConvertStringListToSqlIdentifiers(string_list *List)
{
    // TODO(Oskar): Currently doesn't take ID into account

    sql_identifiers Result = {};
    Result.Identifiers = (char **)malloc(List->Count * sizeof(char*));

    for (int Index = 0; Index < List->Count; ++Index)
    {
        char *Current = List->Strings[Index];
        while(isspace(*Current)) ++Current;
        
        if (StringContains(Current, "public"))
        {
            Current += strlen("public") + 1;
            if (!StringContains(Current, "virtual"))
            {

                // NOTE(Oskar): If Current is a class
                if (StringContains(Current, "class"))
                {
                    Current += strlen("class") + 1;
                    char *Temp = Current;
                    while(!isspace(*Temp)) ++Temp;
                    *Temp = 0;

                    Result.Name = Current;
                }
                else
                {
                    char *Temp = Current;
                    while(!isspace(*Temp)) ++Temp;
                    while (isspace(*Temp)) ++Temp;
                    Current = Temp;

                    while(!isspace(*Temp)) ++Temp;
                    *Temp = 0;

                    char **Dest = &Result.Identifiers[Result.Count++];
                    *Dest = (char *) malloc(strlen(Current) + 1);
                    memcpy(*Dest, Current, strlen(Current) + 1);
                }
            }
        }
    }

    return (Result);
}

OM_INTERNAL void
GenerateEntityFrameworkIdentityInsert(sql_identifiers *Identifiers)
{
    char Buffer[8192];
    char IdentifierBuffer[4096] = "";
    
    for(int Index = 0; Index < Identifiers->Count; ++Index)
    {
        strcat(IdentifierBuffer, "[");
        strcat(IdentifierBuffer, Identifiers->Identifiers[Index]);   
        strcat(IdentifierBuffer, "]");
        strcat(IdentifierBuffer, ", ");
    }
    
    u32 IdentifiersLength = strlen(IdentifierBuffer) - 2;
    IdentifierBuffer[IdentifiersLength] = 0;

    sprintf(Buffer, 
        "SET IDENTITY_INSERT %s ON \n"
        "INSERT INTO %s\n"
        "(%s)\n"
        "SELECT %s\n"
        "FROM %s\n"
        "SET IDENTITY_INSERT %s OFF \n", 
        "[wst].[dbo].[Orders]", 
        "[wst].[dbo].[Orders]", 
        IdentifierBuffer,
        IdentifierBuffer,
        "[111wst].[dbo].[Orders]",
        "[wst].[dbo].[Orders]");

    printf("%s\n", Buffer);
}

int
main (int argc, char **args)
{

    // TODO(Oskar): Take 3 args, a file, source & target database.

    string_list List = LoadStringList("Order.cs");
    // TODO(Oskar): Free list
    sql_identifiers Identifiers = ConvertStringListToSqlIdentifiers(&List);
    GenerateEntityFrameworkIdentityInsert(&Identifiers);

    return (0);
}