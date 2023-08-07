%option yylineno

%{
    #include "parser.tab.h"
    #include "ast.h"
%}

%x COMMENT
%%

"int"               { yylval.valor_lexico = new_data(yytext, yylineno, PALAVRA_RESERVADA); return TK_PR_INT;}
"float"             { yylval.valor_lexico = new_data(yytext, yylineno, PALAVRA_RESERVADA); return TK_PR_FLOAT;}
"bool"              { yylval.valor_lexico = new_data(yytext, yylineno, PALAVRA_RESERVADA); return TK_PR_BOOL;}
"if"                { yylval.valor_lexico = new_data(yytext, yylineno, PALAVRA_RESERVADA); return TK_PR_IF;}
"else"              { yylval.valor_lexico = new_data(yytext, yylineno, PALAVRA_RESERVADA); return TK_PR_ELSE;}
"while"             { yylval.valor_lexico = new_data(yytext, yylineno, PALAVRA_RESERVADA); return TK_PR_WHILE;}
"return"            { yylval.valor_lexico = new_data(yytext, yylineno, PALAVRA_RESERVADA); return TK_PR_RETURN;}

[0-9]+              { yylval.valor_lexico = new_data_typed(yytext, yylineno, LITERAL, INTEIRO); return TK_LIT_INT;}
[0-9]*"."[0-9]+     { yylval.valor_lexico = new_data_typed(yytext, yylineno, LITERAL, PONTOFLUTUANTE); return TK_LIT_FLOAT;}

[\{\}(),;]          { return (int)yytext[0]; }

"<="                { yylval.valor_lexico = new_data(yytext, yylineno, OPERADOR_COMPOSTO); return TK_OC_LE;}
">="                { yylval.valor_lexico = new_data(yytext, yylineno, OPERADOR_COMPOSTO); return TK_OC_GE;}
"=="                { yylval.valor_lexico = new_data(yytext, yylineno, OPERADOR_COMPOSTO); return TK_OC_EQ;}
"!="                {  yylval.valor_lexico = new_data(yytext, yylineno, OPERADOR_COMPOSTO); return TK_OC_NE;}
"&"                 {  yylval.valor_lexico = new_data(yytext, yylineno, OPERADOR_COMPOSTO); return TK_OC_AND;}
"|"                 {  yylval.valor_lexico = new_data(yytext, yylineno, OPERADOR_COMPOSTO); return TK_OC_OR;}
"->"                {  yylval.valor_lexico = new_data(yytext, yylineno, OPERADOR_COMPOSTO); return TK_OC_MAP;}

[<>!*/%+\-=]        { yylval.valor_lexico = new_data(yytext, yylineno, CARACTERE_ESPECIAL); return (int)yytext[0];}

"false"             { yylval.valor_lexico = new_data_typed(yytext, yylineno, LITERAL, BOOLEANO); return TK_LIT_FALSE;}
"true"              { yylval.valor_lexico = new_data_typed(yytext, yylineno, LITERAL, BOOLEANO); return TK_LIT_TRUE;}

[_a-z][_a-zA-Z0-9]* { yylval.valor_lexico = new_data(yytext, yylineno, IDENTIFICADOR); return TK_IDENTIFICADOR; }

"/*"                {BEGIN(COMMENT);}
<COMMENT>\n         {yylineno++;}
<COMMENT>.          {/* ignore */}
<COMMENT>"*/"       {BEGIN(INITIAL);}

"//".*              {/* ignore */}

\n                  {/* ignore */}
" "                 {/* ignore */}
\t                  {/* ignore */}

.                   {return TK_ERRO;}

%%


int get_line_number() {
    return yylineno;
}

int yywrap() {
    return 1;
}