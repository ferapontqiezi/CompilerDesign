**任务描述** 参考flex手册0.6实现简单的toy语言的词法分析，调试、修改给出的词法分析代码。

```C
%{ 
	//You need to include a head file here.
%}
DIGIT [0-9]
ID [a-z][a-z0-9]
%%
{DIGIT}                 {printf( "An integer: %s (%d)\n", yytext,atoi( yytext ) );}
{DIGIT}+"."{DIGIT}      {printf( "A float: %s (%g)\n", yytext,atof( yytext ) );}

if|then|begin|end|procedure|function {printf( "A keyword: %s\n", yytext );}
{ID} printf( "An identifier: %s\n", yytext );
"+"|"-"|"*"|"/"         printf( "An operator: %s\n", yytext );
"{"[^}\n]*"}"		 /* eat up one-line comments */
[ \t\n]+        	 /* eat up whitespace */
.       printf( "Unrecognized character: %s\n", yytext );
%%
int main( argc, argv )
int argc;
char **argv;
{
++argv, --argc; /* skip over program name */
if ( argc > 0 )
	yyin = fopen( argv[0], "r" );
else        
	yyin = stdin; 
    yylex();
}  
```

问题：

```
该语言中有哪些关键字？
识别该语言关键字的规则与识别标识符ID的规则，能否调换顺序？
该语言中注释是什么格式？
词法分析中处理注释后，有没有输出？
该语言中有哪些空白符号？ 
```

**编成环境搭建**  Ubuntu下 `$sudo apt update&&sudo apt install flex&&flex -h&&flex -V` 

Compile the lex file and link it: `$flex -o lex.yy.c mylex.l  && gcc -o mylex lex.yy.c -lfl` **测试说明** 平台会对你编写的代码进行测试：

`./task2 1.in >1.out` 本例是从文件读入待分析文件。

**测试输入**

```c
abc
123
12.3
abc123 
123
abc
if 
else 
then
12 
3
```

**预期输出**

```c
An identifier: abc
An integer: 123 (123)
A float: 12.3 (12.3)
An identifier: abc123
An integer: 123 (123)
An identifier: abc
A keyword: if
An identifier: else
A keyword: then
An integer: 12 (12)
An integer: 3 (3) 
```

开始你的任务吧，祝你成功！

**前面需要掌握的相关知识** `flex`是产生词法分析器`scanners`的工具。词法分析程序是识别文本中单词模式的源程序。`flex`读入描述词法分析规则的文件，该描述文件由`正规式`和`C代码`对（规则rules）构成。flex默认产生的输出是一个C文件：`lex.yy.c`，其中定义了关键过程`yylex()`。这个文件被编译、链接（加`-lfl`）后，产生词法分析的可执行程序。当执行时，它能分析出于对应`正规式`对应的单词；并在找到单词后，执行对应的`C代码`动作。

**lex/flex的语法结构** lex/flex是通过处理其源文件来生词法和语法分析器的，源文件的扩展名为.l，其语法被分为三个部分：：

```C
 /* 预定义段 */
 %{
 
 %}
 %%
 /* 规则段 */
 %%
 /* 用户子程序段 */
```

三个段用 %% 进行分离。

1. 预定义段，这一部分一般是一些声明及选项设置等。C 语言的注释、头文件包含等一般就放在`%{ %}` 之间，这一部分的内容会被直接复制到输出文件的开头部分；

2. 规则段为一系列匹配模式和动作，模式一般使用正则表达式书写，动作部分为C代码：`模式1    {动作1(C代码)}`，在输入和模式 1 匹配的时候，执行动作部分的代码；

   | 符号   | 含义                                  |
   | ------ | ------------------------------------- |
   | **\|** | 或                                    |
   | []     | 括号中的字符取其一                    |
   | **-**  | a-z表示ascii码中介于a-z包括a、z的字符 |
   | \      | 转义（flex不能识别除字母外的字符）    |
   | *      | 0或多个字符                           |
   | ?      | 0或1个字符                            |
   | +      | 1或多个字符                           |
   | ^      | 除此之外的其余字符                    |
   | **.**  | 除\n外的所有字符，等价于^\n           |

3. 用户子程序段，这里为 C 代码，会被原样复制到输出文件中，一般这里定义一些辅助函数等，如动作代码中使用到的辅助函数。

通过一个简单的例子来学习如何写一条规则：

```c
/* 这里是定义段 */
%{
/* 这里的部分会被直接拷贝到生成的 .c 文件的开始部分，在这里可以包含需要使用的头文件，如 stdio.h*/
#include <stdio.h>
#include <math.h>
%}
/* 下面是规则段 */
%%
/* 这里定义了四条规则，前面的部分是模式，处于一行的开始位置，后面的部分是动作。第一个模式是匹配连续的一个到多个字符，匹配到之后就将其打印出来。注意到 yytext，在输入匹配到该模式的时候，匹配的部分就存储在这个 yytext 里面，这里把它作为字符串直接输出就可以了；第二条规则的模式部分，就是匹配连续的一个或者多个数字，匹配到了之后，也是以字符串的形式输出；第三条规则的模式部分，就是匹配一个换行符了，并且匹配到之后就打印一个新行的信息；第四条规则的模式部分，是一个点。正则表达式里面这个也就是匹配任何除了 \n 之外的字符。因此，下面的规则就是，匹配到字符串，则将该字符串输出，匹配到连续数字，将其输出；匹配到换行符，打印一条信息；匹配到任何其他的字符，则直接忽略*/
[a-zA-Z]+       {printf("get string:%s\n", yytext);}
[0-9]+          {printf("get number:%s\n", yytext);}
\n              {printf("get new line\n"); }
.               { }
/* 下面是用户子程序段 */
%%
int yywrap() { return 1; }
int main(int argc, char** argv) { 
	if (argc > 1) { 
    	if (!(yyin = fopen(argv[1], "r"))) {  
        	perror(argv[1]);   
            return 1;    
        }  
    }  
    while (yylex()); 
    return 0;
}
```



**特殊符号**

\b 匹配一个单词边界，也就是指单词和空格间的位置。
\B 匹配非单词边界。
\cx 匹配由x指明的控制字符。
\d 匹配一个数字字符。等价于[0-9]。
\D 匹配一个非数字字符。等价于[ ^0-9]。
\f 匹配一个换页符。等价于\x0c和\cL。
\n 匹配一个换行符。等价于\x0a和\cJ。
\r 匹配一个回车符。等价于\x0d和\cM。
\s 匹配任何空白字符，包括空格、制表符、换页符等等。等价于[\f\n\r\t\v]。

\S 匹配任何非空白字符。等价于[ ^\f\n\r\t\v]。
\t 匹配一个制表符。等价于\x09和\cI。
\v 匹配一个垂直制表符。等价于\x0b和\cK。
\w 匹配包括下划线的任何单词字符。等价于’[A-Za-z0-9_]’。
\W 匹配任何非单词字符。等价于’[^A-Za-z0-9_]’。
\xn 匹配n，其中n为十六进制转义值。十六进制转义值必须为确定的两个数字长。
\num匹配num，其中num是一个正整数。对所获取的匹配的引用。
\n 标识一个八进制转义值或一个后向引用。如果\n之前至少n个获取的子表达式，则n为后向引用。否则，如果n为八进制数字(0-7)，则n为一个八进制转义值。
\nm 标识一个八进制转义值或一个后向引用。如果\nm之前至少有isprecededbyatleastnm个获取得子表达式，则nm为后向引用。如果\nm之前至少有n个获取，则n为一个后跟文字m的后向引用。如果前面的条件都不满足，若n和m均为八进制数字(0-7)，则\nm将匹配八进制转义值nm。
