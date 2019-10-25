#ifndef TOKENIZER_H
#define TOKENIZER_H
#pragma once

enum token_type
{
    Token_Unknown,

    Token_OpenParen,
    Token_CloseParen,
    Token_Colon,
    Token_Semicolon,
    Token_Asterisk,
    Token_OpenBracket,
    Token_CloseBracket,
    Token_OpenBrace,
    Token_CloseBrace,
    Token_Equals,
    Token_Comma,
    Token_Or,
    Token_Pound,
    
    Token_String,
    Token_Identifier,
    Token_Number,

    Token_Space,
    Token_EndOfLine,
    Token_Comment,

    Token_EndOfStream,
};

struct token
{
    char *FileName;
    s32 ColumnNumber;
    s32 LineNumber;

    token_type Type;
    string Text;
    r32 F32;
    s32 S32;
};

struct tokenizer
{
    char *FileName;
    s32 ColumnNumber;
    s32 LineNumber;
    //stream *ErrorStream;

    string Input;
    char At[2];

    b32 Error;
};

#endif // TOKENIZER_H