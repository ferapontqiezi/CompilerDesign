%{
#include "string.h"
#include "def.h"

extern int yycolumn;

#define YYSTYPE yylval
extern "C"
{	
	int yywrap(void);
	int yylex(void);
}

void flexout(std::string name,std::string value){
  std::cout<<name<<"\t:"<<value<<std::endl;
}
//flex为bison提供行号信息
%}
%option yylineno 

%%

"0x"[0-9a-fA-F]*([G-Zg-z]+)[0-9a-fA-F]*    {printf("Error type A at Line %d: Illegal hexadecimal number '%s'\n",yylineno,yytext);}
"0"([89a-fA-F])+                               {printf("Error type A at Line %d: Illegal octal number '%s'\n",yylineno,yytext);}


"int"               {flexout("TYPE","int");}
"float"             {flexout("TYPE","float");}
"char"              {flexout("TYPE","char");}

-?[1-9][0-9]*       {flexout("INT",yytext);}
0                   {flexout("INT",yytext);}

-?[0-9]*\.[0-9]*(e|E)(-?[0-9]+)    {flexout("FLOAT",yytext);}

-?[0-9]+\.[0-9]*    {flexout("FLOAT",yytext);}

("0x"|"0X")[0-9a-fA-F]+    {flexout("INT",yytext);}
"0"[0-7]+                  {flexout("INT",yytext);}


\;                  {flexout("SEMI",yytext);}
\,                  {flexout("COMMA",yytext);}

\+                  {flexout("PLUS",yytext);}
\-                  {flexout("MINUS",yytext);}
\=                  {flexout("ASSIGNOP",yytext);}
\*                  {flexout("STAR",yytext);}
\/                  {flexout("DIV",yytext);}
\&\&                {flexout("AND",yytext);}
\|\                 {flexout("OR",yytext);}
\.                  {flexout("DOT",yytext);}
\!                  {flexout("NOT",yytext);}

\(                  {flexout("LP",yytext);}
\)                  {flexout("RP",yytext);}
\[                  {flexout("LB",yytext);}
\]                  {flexout("RB",yytext);}
\{                  {flexout("LC",yytext);}
\}                  {flexout("RC",yytext);}
"struct"            {flexout("STRUCT",yytext);}
"return"            {flexout("RETURN",yytext);}
"if"                {flexout("IF",yytext);}
"else"              {flexout("ELSE",yytext);}
"while"             {flexout("WHILE",yytext);}
\~                  {printf("Error type A at Line %d: Mysterious characters '%s'\n",yylineno,yytext);}

[a-zA-Z][a-z0-9]*   {flexout("ID",yytext);}


[\n]		{yycolumn=1;}
[ \r\t]		{/*printf("过滤空格等字符\n");*/}

%%

int yywrap()
{
    return 1;
}