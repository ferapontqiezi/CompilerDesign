/* PL�ʷ������� */
/* ���ܣ��ܹ�ʶ���PL֧�ֵ����е��ʷ��Ų������ֱ�ֵ */
/* ˵�����������begin��end֮����Ӵ��룬�Ѿ�ʵ���˱�ʶ������������ʶ������Ҫ���ʣ�µĲ��֣����Ͱɣ� */
/* ��ʾ����Ϊ��˳��ƥ�䣬��������������ƥ�����������Ҫ������˳�� */
%{
#include <stdio.h>
%} /*** begin ****/

PROGRAMSYM		program
VARSYM			var
PROCSYM			procedure
BEGINSYM		begin
IFSYM			if
ANDSYM			and
ORSYM			or
NOTSYM			not
THENSYM			then
ELSESYM			else
CALLSYM			call
ENDSYM			end
WHILESYM		while
DOSYM			do
CONSTSYM		const
ARRAYSYM		array

INTCON			[\-]?[1-9][0-9]*|0
IDENT			[A-Za-z][A-Za-z0-9]*

BECOME			\:\=
COLON			\:

LEQ				\<\=
NEQ				\<\>
LSS				\<

GEQ				\>\=
GTR				\>

DPERIOD			\.\.
PERIOD			\.

CHARCON			\'[^\']*\'

PLUS			\+
MINUS			\-
TIMES			\*
DIVSYM			\/

LPAREN 			\(
RPAREN			\)
EQL				\=
LBRACK			\[
RBRACK			\]
SEMICOLON		\;
COMMA			\,
ERROR			[\~\!\@\#\$\%\^\&\_\\]+

%%  

{PROGRAMSYM}	{printf("%s: PROGRAMSYM\n", yytext);}
{VARSYM}		{printf("%s: VARSYM\n", yytext);}
{PROCSYM}		{printf("%s: PROCSYM\n", yytext);}
{BEGINSYM}		{printf("%s: BEGINSYM\n", yytext);}
{IFSYM}			{printf("%s: IFSYM\n", yytext);}
{ANDSYM}		{printf("%s: ANDSYM\n", yytext);}
{ORSYM}			{printf("%s: ORSYM\n", yytext);}
{NOTSYM}		{printf("%s: NOTSYM\n", yytext);}
{THENSYM}		{printf("%s: THENSYM\n", yytext);}
{ELSESYM}		{printf("%s: ELSESYM\n", yytext);}
{CALLSYM}		{printf("%s: CALLSYM\n", yytext);}
{ENDSYM}		{printf("%s: ENDSYM\n", yytext);}
{WHILESYM}		{printf("%s: WHILESYM\n", yytext);}
{DOSYM}			{printf("%s: DOSYM\n", yytext);}
{CONSTSYM}		{printf("%s: CONSTSYM\n", yytext);}
{ARRAYSYM}		{printf("%s: ARRAYSYM\n", yytext);}

{INTCON}		{printf("%s: INTCON\n", yytext);}
{IDENT}			{printf("%s: IDENT\n", yytext);}

{BECOME}		{printf("%s: BECOME\n", yytext);}
{COLON}			{printf("%s: COLON\n", yytext);}

{LEQ}			{printf("%s: LEQ\n", yytext);}
{NEQ}			{printf("%s: NEQ\n", yytext);}
{LSS}			{printf("%s: LSS\n", yytext);}

{GEQ}			{printf("%s: GEQ\n", yytext);}
{GTR}		  	{printf("%s: GTR\n", yytext);}

{DPERIOD}		{printf("%s: DPERIOD\n", yytext);}
{PERIOD}		{printf("%s: PERIOD\n", yytext);}

{CHARCON}  		{printf("%s: CHARCON\n", yytext);}

{PLUS}			{printf("%s: PLUS\n", yytext);}
{MINUS}			{printf("%s: MINUS\n", yytext);}
{TIMES}			{printf("%s: TIMES\n", yytext);}
{DIVSYM}		{printf("%s: DIVSYM\n", yytext);}

{LPAREN}		{printf("%s: LPAREN\n", yytext);}
{RPAREN}		{printf("%s: RPAREN\n", yytext);}
{EQL}			{printf("%s: EQL\n", yytext);}
{LBRACK}		{printf("%s: LBRACK\n", yytext);}
{RBRACK}		{printf("%s: RBRACK\n", yytext);}
{SEMICOLON}		{printf("%s: SEMICOLON\n", yytext);}
{COMMA}			{printf("%s: COMMA\n", yytext);}
{ERROR}			{printf("%s: ERROR\n", yytext);}

\n				{}
.				{}
%% /*** end ***/
int yywrap() { return 1; }
int main(int argc, char **argv)
{
	if (argc > 1) {
		if (!(yyin = fopen(argv[1], "r"))) {
			perror(argv[1]);
			return 1;
		}
	}
	while (yylex());
	return 0;
}
