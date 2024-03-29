**实验目的**

掌握Yacc/Bison工具使用初步，完成简单语法分析。

**任务描述**

相信大家通过flex的实验已经掌握了如何构建一个词法分析器，但是为了创建一个完整的编译程序，我们还需要一个语法分析器。类似的，我们可以使用现有的自动生成工具来节省开发的时间，也就是Unix下的YACC和GNU/Linux下的Bison。

Ubuntu: $`sudo apt install bison&&bison -V` 

`Use bison:$bison -d filename.y ` 

`//output file: filename.tab.h, filename.tab.c)`


本关任务是**利用YACC/Bison构建一个逆波兰符号计算器**。

**相关知识**

**逆波兰表达式**

逆波兰表达式，它的语法规定，表达式必须以逆波兰表达式的方式给出。逆波兰表达式又叫做后缀表达式。下面是一些中缀式与对应逆波兰式的例子：

```c
a+b			 a b +
a+(b-c) 	a b c - +
a+(b-c)*d	 a b c - d * +
a+d*(b-c)     a d b c - * +
a=1+3          a 1 3 + = 
```

逆波兰表达式的逻辑实现是通过栈来完成的，如果当前字符为变量或者为数字，则压栈，如果是运算符（二元或一元运算），则将栈顶两个(一个)元素弹出作相应运算，结果再入栈，最后当表达式扫描完后，栈里的就是结果。

**BNF范式**

由于Bison中使用的是BNF范式来描述产生式，这里先简单介绍一下BNF范式。 BNF规定是推导规则(产生式)的集合，写为： `<符号> ::= <使用符号的表达式>`       这里的 `<符号>` 是`非终结符`，而表达式由一个符号序列，或用指示选择的竖杠’|’分隔的多个符号序列构成，每个符号序列整体都是左端的符号的一种可能的替代。从未在左端出现的符号叫做`终结符`。

`BNF`类似一种数学游戏：从一个符号开始（叫做起始标志，实例中常用`S`表示），然后给出替换前面符号的规则。`BNF`语法定义的语言只不过是一个字符串集合，你可以按照下述规则书写，这些规则叫做书写规范（生产式规则），形式如下：

```
symbol := alternative1 | alternative2 ...
```

**Bison语法结构**

Bison的语法结构和lex/flex类似，也是分为三个部分。 

**参考资料** [Bison官网: www.gnu.org/software/bison/manual/bison.html](https://www.gnu.org/software/bison/manual/bison.html#Grammar-Outline)

```c
%{
Prologue定义段
%}
Bison declarationsBison
声明区
%%
Grammar rules
规则段
%%
Epilogue
用户子程序段 
```

------

- 定义段

  ```c
  %{
  /* 定义段 */
  C/C++头文件、全局文件、全局变量、类型定义词法分析器yylex（采用lex进行词法分析）和错误打印函数头
  %} 
  ```

- 声明区

`Bison声明区间:定义之后用到的终结符、非终结符、操作符优先级` 例如，定义语法分析中使用的**终结符、非终结符**： `token`用于定义**终结符**，`type`定义**非终结符**，操作符也属于终结符； `left`表示左关联（**左结合**）运算符，`right`表示右关联（**右结合**）运算符，下面是声明的例子：

```c
%token NUM   
/*定义终结符NUM*/
%nonassoc ‘<’ 
/*表示该终结符无结合性,不能出现a<b<c*/
%left ‘+’ ‘-’ /*左结合,a+b+c=(a+b)+c*/
%left ‘*’ ‘/’ 
/*规则4在3下面，操作符比其上的优先级高*/
%right NEG    /*NEG表示非*/
%right ‘^’    /*幂运算右结合;最下面，优先级最高*/
```

- 语法规则

  ```c
  %%
  /* 规则段 */
  Bison语法规则定义
  %%
  ```

- 用户代码

 **c/c++代码**：需要定义前面在prologue区域中声明的函数具体实现，或其他代码。这部分代码，最终会被完全复制到生成的语法分析器源码中（c/c++）。

**Bison识别包含加法的逆波兰的片段例子：** 需要你对代码进行补全。

```c
%{
    #include <ctype.h>
    /*需要使用的头文件*/
    #include <stdio.h> 
    #include <math.h>  
    int yylex (void);
    /*需要使用的词法分析函数的声明*/ 
    void yyerror (char const *);
%}
%token NUM  /*需要的终结符声明*/
%define api.value.type {double}
%left '+' '-'   /*结合性、优先级*/
%left '*' '/'
%right 'n'
%right '^'
    
%%
    /* Grammar rules and actions follow.  */
input: 
	%empty
    | input line    
    ;
line:  
	'\n' 
    | exp '\n'      { printf ("%.10g\n", $1); }     ;
exp:  
	NUM    {$$=$1;}   /*NUM NUM +*/  
	|exp exp '+' {$$=$1+$2;}    
	;
%%
    /* The lexical analyzer returns a double floating pointnumber on the stack and the token NUM, or the numeric codeof the character read if not a number.  It skips all blanks and tabs, and returns 0 for end-of-input.  */
    
int yylex (void){ 
    int c; 
    /* Skip white space.  */ 
    while ((c = getchar ()) == ' ' || c == '\t')    
        continue;  
    /* Process numbers.  */  
    if (c == '.' || isdigit (c))    {    
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
int main (int argc, char** argv){ 
    yyparse();   
    return 0;
}
/* Called by yyparse on error.  */
void yyerror (char const *s){ 
    fprintf (stderr, "%s\n", s);
}
```

------

编程要求

`实现加法(+)、减法(-)、乘法(*)、除法(/)、乘方(^)以及取负运算(n)` **输入** 表达式的逆波兰式：

```c
1 2 +
3 4 ^
2 7 + 3 /
16 4 / 12 * n
```

第四行为-12*(16/4)

**输出** 逆波兰表达式运算的结果：

```c
3
81
3
-48 
```
