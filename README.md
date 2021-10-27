# 编译原理实验

头歌平台Educoder测评作业

## 实验一

*.c后缀的都是AC代码，~~其中**第四题**和**第七题**真的毒瘤！！！！！~~

- 第四题：别偷懒，全写就是了，码农是这样的。
- 第七题：多科学上网多看英文，参考链接：
  - https://stackoverflow.com/questions/44037660/calc-with-bison-and-flex-doesnt-work-operation-negative
  - https://www.gnu.org/software/bison/manual/html_node/Infix-Calc.html

联系课上学得NFA和DFA就会好写很多，但大多还是照葫芦画瓢。

### flex

常用字符含义

| 符号  | 含义                                  |
| ----- | ------------------------------------- |
| \|    | 或                                    |
| []    | 括号中的字符取其一                    |
| **-** | a-z表示ascii码中介于a-z包括a、z的字符 |
| \     | 转义（flex不能识别除字母外的字符）    |
| *     | 0或多个字符                           |
| ?     | 0或1个字符                            |
| +     | 1或多个字符                           |
| ^     | 除此之外的其余字符                    |
| **.** | 除\n外的所有字符，等价于^\n           |

特殊字符用转义

| 符号 | 含义                                                         |
| ---- | ------------------------------------------------------------ |
| \b   | 匹配一个单词边界，也就是指单词和空格间的位置。               |
| \B   | 匹配非单词边界。                                             |
| \cx  | 匹配由x指明的控制字符。                                      |
| \d   | 匹配一个数字字符。等价于[0-9]。                              |
| \D   | 匹配一个非数字字符。等价于[ ^0-9]。                          |
| \f   | 匹配一个换页符。等价于\x0c和\cL。                            |
| \n   | 匹配一个换行符。等价于\x0a和\cJ。                            |
| \r   | 匹配一个回车符。等价于\x0d和\cM。                            |
| \s   | 匹配任何空白字符，包括空格、制表符、换页符等等。等价于[\f\n\r\t\v]。 |
| \t   | 匹配一个制表符。等价于\x09和\cI。                            |
| \v   | 匹配一个垂直制表符。等价于\x0b和\cK。                        |
| \w   | 匹配包括下划线的任何单词字符。等价于’[A-Za-z0-9]。           |
| \W   | 匹配任何非单词字符。等价于[ ^A-Za-z0-9_]                     |
| \xn  | 匹配n，其中n为十六进制转义值。十六进制转义值必须为确定的两个数字长。 |
| \num | 匹配num，其中num是一个正整数。对所获取的匹配的引用。         |
| \n   | 标识一个八进制转义值或一个后向引用。如果\n之前至少n个获取的子表达式，则n为后向引用。否则，如果n为八进制数字(0-7)，则n为一个八进制转义值。 |
| \nm  | 标识一个八进制转义值或一个后向引用。如果\nm之前至少有isprecededbyatleastnm个获取得子表达式，则nm为后向引用。如果\nm之前至少有n个获取，则n为一个后跟文字m的后向引用。如果前面的条件都不满足，若n和m均为八进制数字(0-7)，则\nm将匹配八进制转义值nm。 |

更多代码格式和细节参考[flex学习](Ex1/flex学习.md)

### bison

格式范例：

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

更多代码格式和细节参考[bison学习](Ex1/bison学习.md)

## 参考文献

1. [正则表达式菜鸟教程](https://www.runoob.com/regexp/regexp-metachar.html)
2. [bison官方文档](https://www.gnu.org/software/bison/manual/bison.html#Infix-Calc)
3. flex 2.5官方文档
4. flex和bison中文版.东南大学出版社
