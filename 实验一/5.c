 %{
  #include <ctype.h>
  #include <stdio.h>
  #include <math.h>
  int yylex (void);
  void yyerror (char const *);
%}

%define api.value.type {double}
%token NUM   
/*定义终结符NUM*/
%nonassoc '<' 
/*表示该终结符无结合性,不能出现a<b<c*/
%left '+' '-' /*左结合,a+b+c=(a+b)+c*/
%left '*' '/' 
/*规则4在3下面，操作符比其上的优先级高*/
%right NEG    /*NEG表示非*/
%right '^'    /*幂运算右结合;最下面，优先级最高*/

%% 
/* Grammar rules and actions follow.  */
input:
  %empty
| input line
;


line:
  '\n'
| exp '\n'      { printf ("%.10g\n", $1); }
;

exp:
  NUM           { $$ = $1;           }
 /* begin */
    | exp exp '+'   { $$ = $1 + $2;      }
    | exp exp '-'   { $$ = $1 - $2;      }
    | exp exp '*'   { $$ = $1 * $2;      }
    | exp exp '/'   { $$ = $1 / $2;      }
     /* Exponentiation */
    | exp exp '^'   { $$ = pow($1, $2); }
    /* Unary minus    */
    | exp 'n'       { $$ = -$1;          }
  
  
 /* end */
;

%%

/* The lexical analyzer returns a double floating point
   number on the stack and the token NUM, or the numeric code
   of the character read if not a number.  It skips all blanks
   and tabs, and returns 0 for end-of-input.  */

int yylex (void)
{
  int c;
  /* Skip white space.  */
  while ((c = getchar ()) == ' ' || c == '\t')
    continue;

  /* Process numbers.  */
  if (c == '.' || isdigit (c))
    {
      ungetc (c, stdin);
      scanf ("%lf", &yylval);
      return NUM;
    }

  /* Return end-of-input.  */
  if (c == EOF)
    return 0;
  if (c == '!')
  	return 0;
  /* Return a single char.  */
  return c;
}

int main (int argc, char** argv)
{
   yyparse();
   return 0;
}


/* Called by yyparse on error.  */
void yyerror (char const *s)
{
  fprintf (stderr, "%s\n", s);
}
