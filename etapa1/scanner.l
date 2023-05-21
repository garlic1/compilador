%{
    #include "tokens.h"

    int running = 1;
    int line_count = 1;
%}
 
%%

"int"       {return TK_PR_INT;}
"float"     {return TK_PR_FLOAT;}
"bool"      {return TK_PR_BOOL;}
"if"        {return TK_PR_IF;}
"else"      {return TK_PR_ELSE;}
"while"     {return TK_PR_WHILE;}
"return"    {return TK_PR_RETURN;}

[-!*/%+-<>\{\}()=,;] {return (int)yytext[0];}

"<="    {return TK_OC_LE;}
">="    {return TK_OC_GE;}
"=="    {return TK_OC_EQ;}
"!="    {return TK_OC_NE;}
"&"     {return TK_OC_AND;}
"|"     {return TK_OC_OR;}
"->"    {return TK_OC_MAP;}

%%

int main() {
    yylex();
}

int yywrap() {
    return 1;
}