/*
    Gabriel Lima Chimifosk - Compiladores - 2023/2
*/

%option yylineno

%{
    #include "hash.c"
    #include "parser.tab.h"
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

"///"               {BEGIN(COMMENT);}
<COMMENT>"\\\\\\"   {BEGIN(INITIAL);}
<COMMENT>"\n"       {/* nop */}
<COMMENT>.          {/* nop */}

[0-9]+"."[0-9]+ {insert_node(yytext, LIT_REAL); return LIT_REAL;}
[0-9]+          {insert_node(yytext, LIT_INT); return LIT_INT;}
"'"."'"         {insert_node(yytext, LIT_CHAR); return LIT_CHAR;}
"\""([^"\n]|"\\\"")*"\""      {insert_node(yytext, LIT_STRING); return LIT_STRING;}

[a-zA-Z_0-9]* {insert_node(yytext, TK_IDENTIFIER); return TK_IDENTIFIER;}

\n           {/* nop */}
" "          {/* nop */}
\t           {/* nop */}
"//".*       {/* nop */}

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

void initMe(void) {
  init_table();
}

#include "main.c"