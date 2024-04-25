/*
    Gabriel Lima Chimifosk - Compiladores - 2024/1
*/

%option yylineno

%{
    #include "hash.h"
    #include "parser.tab.h"
    int running = 1;
    void init_table();
%}

%x COMMENT

%%

"bool" { return KW_BOOL; }
"char"  { return KW_CHAR; }
"int"   { return KW_INT; }
"float" { return KW_FLOAT; }
"if"    { return KW_IF; }
"else"  { return KW_ELSE; }
"while" { return KW_WHILE; }
"read"  { return KW_READ; }
"print" { return KW_PRINT; }
"return" { return KW_RETURN; }

[-,;:()\[\]{}=+*/%<>&|~]   { return (int)yytext[0]; }

"<="        { return OPERATOR_LE; }
">="        { return OPERATOR_GE; }
"=="        { return OPERATOR_EQ; }
"!="        { return OPERATOR_DIF; }

[0-9]+"."[0-9]+ { insert_node(yytext, LIT_REAL); return LIT_REAL;} 
[0-9]+          { insert_node(yytext, LIT_INT); return LIT_INT; }
"'"."'"         { insert_node(yytext, LIT_CHAR); return LIT_CHAR; }
"\""([^"\n]|"\\\"")*"\""      {insert_node(yytext, LIT_STRING); return LIT_STRING;}
"true" {insert_node(yytext, LIT_TRUE); return LIT_TRUE;}
"false" {insert_node(yytext, LIT_FALSE); return LIT_FALSE;}

[a-zA-Z_]{1}[a-zA-Z_0-9]* {insert_node(yytext, TK_IDENTIFIER); return TK_IDENTIFIER;}

"/*"                { BEGIN(COMMENT); }
<COMMENT>"*/"      { BEGIN(INITIAL); }
<COMMENT>"\n"       {/* nop */}
<COMMENT>.          {/* nop */}

\n              {/* nop */}
" "             {/* nop */}
\t              {/* nop */}
"//".*      {/* nop */}

.           { return TOKEN_ERROR; }

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