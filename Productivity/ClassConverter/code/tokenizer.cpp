#include "tokenizer.h"

OM_INTERNAL void
Refill(tokenizer *Tokenizer)
{
    if (Tokenizer->Input.Count == 0)
    {
        Tokenizer->At[0] = 0;
        Tokenizer->At[1] = 0;
    }
    else if (Tokenizer->Input.Count == 1)
    {
        Tokenizer->At[0] = Tokenizer->Input.Data[0];
        Tokenizer->At[1] = 0;
    }
    else
    {
        Tokenizer->At[0] = Tokenizer->Input.Data[0];
        Tokenizer->At[1] = Tokenizer->Input.Data[1];
    }
}

OM_INTERNAL void
AdvanceChars(tokenizer *Tokenizer, u32 Count)
{
    
}

OM_INTERNAL token
GetTokenRaw(tokenizer *Tokenizer)
{
    token Token = {};
    Token.FileName = Tokenizer->FileName;
    Token.ColumnNumber = Tokenizer->ColumnNuber;
    Token.LineNumber = Tokenizer->LineNumber;
    Token.Text = Tokenizer->Input;

    char C = Tokenizer->At[0];
    AdvanceChars(Tokenizer, 1);
    switch (C)
    {
        case '\0': {Token.Type = Token_EndOfStream;} break;
        case '(':  {Token.Type = Token_OpenParen;} break;
        case ')':  {Token.Type = Token_CloseParen;} break;
        case ':':  {Token.Type = Token_Colon;} break;
        case ';':  {Token.Type = Token_Semicolon;} break;
        case '*':  {Token.Type = Token_Asterisk;} break;
        case '[':  {Token.Type = Token_OpenBrace;} break;
        case ']':  {Token.Type = Token_CloseBrace;} break;
        case '{':  {Token.Type = Token_OpenBracket;} break;
        case '}':  {Token.Type = Token_CloseBracket;} break;
        case '=':  {Token.Type = Token_Equals;} break;
        case ',':  {Token.Type = Token_Comma;} break;
        case '|':  {Token.Type = Token_Or;} break;
        case '#':  {Token.Type = Token_Pound;} break;

        case '"':
        {
            Token.Type = Token_String;

            while (Tokenizer->At[0] &&
                   Tokenizer->At[0] != '"')
            {
                if ((Tokenizer->At[0] == '\\') && Tokenizer->At[1])
                {
                    AdvanceChars(Tokenizer, 1);
                }
                AdvanceChars(Tokenizer, 1);
            }

            if (Tokenizer->At[0] == '"')
            {
                AdvanceChars(Tokenizer, 1);
            }
        } break;

        default:
        {
            if (IsSpace(C))
            {
                Token.Type = Token_Space;
                while (Tokenizer->At[0])
                {
                    AdvanceChars(Tokenizer, 1);
                }
            }
            else if (IsEndOfLine(C))
            {
                Token.Type = Token_EndOfLine;
                
                if (((C == '\r') &&
                    (Tokenizer->At[0] == '\n')) ||
                   ((C == '\n') &&
                    (Tokenizer->At[0] == '\r')))
                {
                    AdvanceChars(Tokenizer, 1);
                }

                Tokenizer->ColumnNumber = 1;
                ++Tokenizer->LineNumber;
            }
            else if ((C == '/') &&
                    (Tokenizer->At[0] == '/'))
            {
                Token.Type = Token_Comment;

                AdvanceChars(Tokenizer, 2);
                while (Tokenizer->At[0] && !IsEndOfLine(Tokenizer->At[0]))
                {
                    AdvanceChars(Tokenizer, 1);
                }
            }
            else if ((C == '/') &&
                    (Tokenizer->At[0] == '*'))
            {
                Token.Type = Token_Comment;

                AdvanceChars(Tokenizer, 2);
                while (Tokenizer->At[0] &&
                      !((Tokenizer->At[0] == '*') &&
                        (Tokenizer->At[1] == '/')))
                {
                    if (((Tokenizer->At[0] == '\r') &&
                        (Tokenizer->At[1] == '\n')) ||
                       ((Tokenizer->At[0] == '\n') &&
                        (Tokenizer->At[1] == '\r')))
                    {
                        AdvanceChars(Tokenizer, 1);
                    }

                    if (IsEndOfLine(Tokenizer->At[0]))
                    {
                        ++Tokenizer->LineNumber;
                    }

                    AdvanceChars(Tokenizer, 1);
                }

                if(Tokenizer->At[0] == '*')
                {
                    AdvanceChars(Tokenizer, 2);
                }
            }
            else if (IsAlpha(C))
            {
                Token.Type = Token_Identifier;

                while (IsAlpha(Tokenizer->At[0]) ||
                        IsNumber(Tokenizer->At[0]) ||
                        (Tokenizer->At[0] == '_'))
                {
                    AdvanceChars(Tokenizer, 1);
                }
            }
            else if (IsNumber(C))
            {
                r32 Number = (r32)(C - '0');

                while (IsNumber(Tokenizer->At[0]))
                {
                    r32 Digit = (r32)(Tokenizer->At[0] - '0');
                    Number = 10.0f*Number + Digit;
                    AdvanceChars(Tokenizer, 1);
                }

                if (Tokenizer->At[0] == '.')
                {
                    AdvanceChars(Tokenizer, 1);
                    r32 Coefficient = 0.1f;
                    while (IsNumber(Tokenizer->At[0] - '0'))
                    {
                        r32 Digit = (r32)(Tokenizer->At[0] - '0');
                        Number += Coefficient*Digit;
                        Coefficient *= 0.1f;
                        AdvanceChars(Tokenizer, 1);
                    }
                }

                Token.Type = Token_Number;
                Token.F32 = Number;
                Token.S32 = RoundReal32ToInt32(Number);
            }
            else
            {
                Token.Type = Token_Unknown;
            }
        } break;
    }

    return (Token);
}

OM_INTERNAL token
GetToken(tokenizer *Tokenizer)
{
    token Token;
    for (;;)
    {
        Token = GetTokenRaw(Tokenizer);
        if ((Token.Type == Token_Space) ||
            (Token.Type == Token_EndOfLine) ||
            (Token.Type == Token_Comment))
        {
            // NOTE(Oskar): Ignore..
        }
        else
        {
            if (Token.Type == Token_String)
            {
                if (Token.Text.Count && (Token.Text.Data[0] == '"'))
                {
                    ++Token.Text.Data;
                    --Token.Text.Count;
                }

                if (Token.Text.Count && (Token.Text.Data[Token.Text.Count - 1] == '"'))
                {
                    --Token.Text.Count;
                }
            }

            break;
        }
    }

    return (Token);
}

OM_INTERNAL tokenizer
Tokenize(string Input, char *FileName)
{
    tokenizer Result = {};

    Result.FileName = FileName;
    Result.ColumnNumber = 1;
    Result.LineNumber = 1;
    Result.Input = Input;
    Refill(&Result);

    return (Result);
}