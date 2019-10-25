#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "types.h"
#include "tokenizer.cpp"

OM_INTERNAL string
ReadEntireFileIntoMemory(char *FileName)
{
    string Result = {};

    FILE *File = fopen(FileName, "r");
    if (File)
    {
        fseek(File, 0, SEEK_END);
        Result.Count = ftell(File);
        fseek(File, 0, SEEK_SET);

        Result.Data = (u8 *)malloc(Result.Count);
        fread(Result.Data, Result.Count, 1, File);

        fclose(File);
    }

    return (Result);
}

int 
main (int ArgCount, char **Args)
{
    printf("                          ud$$$**$$$$$$$bc,\n");
    printf("                       u@**^        4$$$$$$$Nu\n");
    printf("                     J                ^^#$$$$$$r\n");
    printf("                    @                       $$$$b\n");
    printf("                  ,F                        ^*3$$$\n");
    printf("                 :# 4                         J$$$N\n");
    printf("                 $  :F                       :$$$$$\n");
    printf("                4F  9                       J$$$$$$$\n");
    printf("                4$   k             4$$$$bed$$$$$$$$$\n");
    printf("                $$r  ,F            $$$$$$$$$$$$$$$$$r\n");
    printf("                $$$   b,           $$$$$$$$$$$$$$$$$N\n");
    printf("                $$$$$k 3eeed$$b    $$$Euec,^$$$$$$$$$\n");
    printf(" ,@$**N,        $$$$$^ $$$$$$F,L $$$$$$$$$$$  $$$$$$$\n");
    printf(" :$$L  ,L       $$$$$ 4$$$$$$  * $$$$$$$$$$F  $$$$$$F         edNc\n");
    printf("@$$$$N  ^k      $$$$$  3$$$$*#   $F4$$$$$$$   $$$$$^        d^  z$N\n");
    printf("$$$$$$   ^k     ,$$$^   #$$$F   ,$  $$$$$c,u@$$$          J^  @$$$$r\n");
    printf("$$$$$$$b   *u    ^$L            $$  $$$$$$$$$$$$u@       $$  d$$$$$$\n");
    printf(" ^$$$$$$,    ^NL   ^N, z@*     $$$  $$$$$$$$$$$$$P      $P  d$$$$$$$\n");
    printf("    ^^*$$$$b   ,*L   9$E      4$$$  d$$$$$$$$$$$^     d*   J$$$$$r\n");
    printf("         ^$$$$u  ,$,  $$$L     ^#^ d$$$$$$^,@$$    ,@$^  z$$$$*^\n");
    printf("           ^$$$$, ^$N,3$$$       4u$$$$$$$ 4$$$  u$*^ z$$$^\n");
    printf("             ,*$$$$$$$$ *$b      J$$$$$$$b u$$P $^  d$$P\n");
    printf("                #$$$$$$ 4$ 3*$^$*$ $^$,c@@$$$$ ,u@$$$P\n");
    printf("                  ^$$$$  ^^F~$ $uNr$$$^&J$$$$F $$$$#\n");
    printf("                    ^$$    ^$$$bd$,$W$$$$$$$$F $$^\n");
    printf("                      ?k         ?$$$$$$$$$$$F,*\n");
    printf("                       9$$bL     z$$$$$$$$$$$F\n");
    printf("                        $$$$    $$$$$$$$$$$$$\n");
    printf("                         ,#$$c  ,$$$$$$$$$^\n");
    printf("                          ,@^#$$$$$$$$$$$$b\n");
    printf("                        z*      $$$$$$$$$$$$N,\n");
    printf("                      e^      z$$^  #$$$k  ,*$$,\n");
    printf("                  ,u*      u@$P^      ,#$$c   ^$$c\n");
    printf("           u@$*^^^       d$$^            ^$$$u  ^*$$b,\n");
    printf("         :$F           J$P^                ^$$$c   ,^$$$$$$bL\n");
    printf("        d$$  ,,      @$#                      #$$b         ,#$\n");
    printf("        9$$$$$$b   4$$                          ^$$k         ,$\n");
    printf("         ^$$6^^$b u$$                             ,$    d$$$$$P\n");
    printf("           ,$F $$$$$^                              ^b  ^$$$$b$\n");
    printf("            ,$W$$$$^                                ,b@$$$$^\n");
    printf("                                                     ^$$$*\n");
    printf("Oskar Mendels Class to DTO Converter. Welcome to hell.");
    char *FileNames[] = 
    {
        ""
    };

    for(u32 FileIndex = 0; FileIndex < OM_ARRAYCOUNT(FileNames); ++FileIndex)
    {
        string FileContents = ReadEntireFileIntoMemory(FileNames[FileIndex]);
        tokenizer Tokenizer = Tokenize(FileContents, FileNames[FileIndex]);

        b32 Parsing = true;
        while(Parsing)
        {
            token Token = GetToken(&Tokenizer);
            switch(Token.Type)
            {
                case Token_EndOfStream:
                {
                    Parsing = false;
                } break;
            }
        }
    }

    return (0);
}