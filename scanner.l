%option nounput

%{
#include "parser.h"

#define YY_INPUT(buf,result,max_size)           \
    {                                           \
        int c = getchar();                      \
        result = (c == EOF || c == '\n') ? YY_NULL : (buf[0] = c, 1);      \
    }
%}

%%

[ \t]+ 

"(" {
    return LEFT_PAREN;
}

")" {
    return RIGHT_PAREN;
}

[\+\-\*\/\^] {
    yylval.op = (char*)malloc(yyleng+1); /* +1 for the null terminator */
    sprintf(yylval.op, "%s", (char*)yytext);
    switch(yytext[0])
    {
    case '+': return PLUS;
    case '-': return MINUS;
    case '*': return TIMES;
    case '/': return DIVIDE;
    case '^': return CARET;
    }
}

[0-9]+\.?[0-9]* {
    yylval.val = strtod((char*)yytext, NULL);
    return NUMBER;
}

x {
    yylval.var = 'x';
    return XVAR;
}

[a-zA-Z][a-zA-Z0-9]* {
    yylval.op = (char*)malloc(yyleng+1); /* +1 for the null terminator */
    sprintf(yylval.op, "%s", (char*)yytext);
    return FUNC;
}

%%

int yywrap() { return 1; }
