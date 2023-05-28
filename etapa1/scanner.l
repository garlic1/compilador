%option yylineno

%x COMMENT

%{
    #include "tokens.h"
%}
 
%%

{/* 3.1 - reserved words */}
"int"       {return TK_PR_INT;}
"float"     {return TK_PR_FLOAT;}
"bool"      {return TK_PR_BOOL;}
"if"        {return TK_PR_IF;}
"else"      {return TK_PR_ELSE;}
"while"     {return TK_PR_WHILE;}
"return"    {return TK_PR_RETURN;}

{/* 3.2 - special characters */}
[-!*/%+-<>\{\}()=,;] {return (int)yytext[0];}

{/* 3.3 - compound operators */}
"<="    {return TK_OC_LE;}
">="    {return TK_OC_GE;}
"=="    {return TK_OC_EQ;}
"!="    {return TK_OC_NE;}
"&"     {return TK_OC_AND;}
"|"     {return TK_OC_OR;}
"->"    {return TK_OC_MAP;}

{/* 3.4 - identifiers */}
("_"|[a-z])+    {return TK_IDENTIFICADOR;}

{/* 3.5 - literals */}
[0-9]+              {return TK_LIT_INT;}
[0-9]*"."[0-9]+     {return TK_LIT_FLOAT;}
"false"             {return TK_LIT_FALSE;}
"true"              {return TK_LIT_TRUE;}

{/* ignore single line comments */}
"//".*

{/* ignore blank spaces */}
\n
" "
\t

{/* 2.4 - throw error for invalid characters */}
.       {return TK_ERRO;}

%%

int get_line_number() {
    return yylineno;
}

int main() {
    yylex();
}

int yywrap() {
    return 1;
}