%option yylineno

%{
    #include "tokens.h"
    int running = 1;
%}

%x COMMENT

%%

"char"          {return KW_CHAR;}
"int"           {return KW_INT;}
"float"         {return KW_FLOAT;}
"code"          {return KW_CODE;}
"if"            {return KW_IF;}
"else"          {return KW_ELSE;}
"while"         {return KW_WHILE;}
"input"         {return KW_INPUT;}
"print"         {return KW_PRINT;}
"return"        {return KW_RETURN;}

[-,;()\[\]{}=+*/%<>&|~]   {return (int)yytext[0];}

"<="        {return OPERATOR_LE;}
">="        {return OPERATOR_GE;}
"=="        {return OPERATOR_EQ;}
"!="        {return OPERATOR_DIF;}

[a-zA-Z_][a-zA-Z_0-9]* {return TK_IDENTIFIER;}

[0-9]+"."[0-9]+ {return LIT_REAL;}
[0-9]+      {return LIT_INT;}
"'"."'"     {return LIT_CHAR;}

\n          {/* nop */}
" "         {/* nop */}
\t          {/* nop */}

.           {return TOKEN_ERROR;}

%%

int yywrap() {
    running = 0;
    return 1;
}

int getLineNumber() {
    return yylineno;
}

int isRunning() {
    return running;
}

#include "main.c"