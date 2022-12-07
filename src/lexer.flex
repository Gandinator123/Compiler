%option noyywrap

%{
/* Avoid error "error: `fileno' was not declared in this scope" */
extern "C" int fileno(FILE *stream);

#include "parser.tab.hpp"
%}

%%

"int"           { yylval.string=new std::string(yytext); return INT;  }
"float"         {  yylval.string=new std::string(yytext); return FLOAT;}
"double"         {  yylval.string=new std::string(yytext); return DOUBLE;}

"switch"        { return SWITCH; }
"case"          { return CASE; }
"default"       { return DEFAULT; }

"break"         { return BREAK; }
"continue"      { return CONTINUE; }

"enum"          { return ENUM; }

":"             { return COLON; }
"if"            { return IF;  }
"else"          { return ELSE;   }

"while"         { return WHILE; }
"*"             { return TIMES;  }
"-"             { return MINUS;  }
"/"             { return DIVIDE; }
"+"             { return PLUS;   }
"!"             { return NOT;   }
"do"            { return DO; }

"++"            { return INCREMENT; }
"--"            { return DECREMENT; }

"<<"            { return LEFT_SHIFT_OP; }
">>"            { return RIGHT_SHIFT_OP; }

"<"             { return LESS_THAN_OP; }
">"             { return GREATER_THAN_OP; }

"<="            { return LESS_THAN_EQUAL_OP; }
">="            { return GREATER_THAN_EQUAL_OP; }

"for"           { return FOR; }

"%"             { return MODULUS; }

"=="            { return EQUAL_OP; }
"!="            { return NOT_EQUAL_OP; }

"&"             { return BITWISE_AND; }
"&&"            { return LOGICAL_AND; }

"|"             { return BITWISE_OR; }
"||"            { return LOGICAL_OR; }

"^"             { return EXCLUSIVE_OR; }

"{"             { return LCURLYBRACKET; }
"}"             { return RCURLYBRACKET; } 
"("             { return LBRACKET; }
")"             { return RBRACKET; }
"["             { return LSqrBracket; }
"]"             { return RSqrBracket; }
"return"        { return RETURN; }
";"             { return SEMICOLON;}
","             { return COMMA;}

"="             { return STANDARD_ASSIGN;}
"+="            { return ADD_ASSIGN; }
"-="            { return SUB_ASSIGN; }
"*="            { return MUL_ASSIGN; }
"/="            { return DIV_ASSIGN; }
"%="            { return MOD_ASSIGN; }
"<<="           { return LEFT_ASSIGN; }
">>="           { return RIGHT_ASSIGN; }
"&="			      { return AND_ASSIGN; }
"^="			      { return XOR_ASSIGN; }
"|="			      { return OR_ASSIGN; }

[0-9]+ { yylval.number=strtod(yytext, 0); return INT_NUMBER;  }
[0-9]*"."[0-9]*   { yylval.number=strtod(yytext, 0); return FLOAT_NUMBER;  }
[0-9]*"."[0-9]*"f"  { yylval.string=new std::string(yytext); return FLOAT_NUMBER_STRING;  }
[a-zA-Z_][a-zA-Z0-9]*          { yylval.string=new std::string(yytext); return IDENTIFIER; }

[ \t\r\n]+		{;}

.               { fprintf(stderr, "Invalid token\n"); exit(1); }
%%

void yyerror (char const *s)
{
  fprintf (stderr, "Parse error : %s\n", s);
  exit(1);
}
