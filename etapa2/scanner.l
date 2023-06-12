%option yylineno

%{
    #include "tokens.h"
%}

%x COMMENT
%%

"int"               {return TK_PR_INT;}
"float"             {return TK_PR_FLOAT;}
"bool"              {return TK_PR_BOOL;}
"if"                {return TK_PR_IF;}
"else"              {return TK_PR_ELSE;}
"while"             {return TK_PR_WHILE;}
"return"            {return TK_PR_RETURN;}

[0-9]+              {return TK_LIT_INT;}
[0-9]*"."[0-9]+     {return TK_LIT_FLOAT;}

[!*/%+\-<>\{\}()=,;] {return (int)yytext[0];}

"<="                {return TK_OC_LE;}
">="                {return TK_OC_GE;}
"=="                {return TK_OC_EQ;}
"!="                {return TK_OC_NE;}
"&"                 {return TK_OC_AND;}
"|"                 {return TK_OC_OR;}
"->"                {return TK_OC_MAP;}

"false"             {return TK_LIT_FALSE;}
"true"              {return TK_LIT_TRUE;}

("_"|[a-z])+        {return TK_IDENTIFICADOR;}

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