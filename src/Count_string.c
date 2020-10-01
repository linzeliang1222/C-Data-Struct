/*
** 这个程序从标准输流中读取输入行并在标准输出中打印这些输入行
** 每个输入行的后面一行是改内容的一部分
**
** 输入的第一行是一串标号，串的最后以一个负数结尾
** 这些列标号成对出现，说明需要被打印的输入列的列范围
** 例如，0 3 10 12 -1表示第0列到第3列，第10列到第12列的内容被打印
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COLS 20      /* 能够处理的最大列号 */
#define MAX_INPUT 1000   /* 每个输入行的最大长度 */ 

int read_column_numbers(int column[], int max);
void rearrange(char *output, char const *input,
        int n_column, int const column[]);

int main(void)
{
    int n_column;            /* 进行处理的列标号 */
    int columns[MAX_COLS];   /* 需要处理的列数 */
    char input[MAX_INPUT];   /* 容纳输入行的数组 */
    char output[MAX_INPUT];  /* 容纳输出行的数组 */

    /*
    ** 读取该串列表号
    */
    n_column = read_column_numbers(columns, MAX_COLS);

    /*
    ** 读取处理和打印输入的剩余行
    */
    while (gets(input) != NULL)
    {
        printf("Original input : %s\n", input);
        rearrange(output, input, n_column, columns);
        printf("Rearrange line : %s\n", output);
    }

    return EXIT_SUCCESS;
}

/*
** 读取标号，如果超出范围则不理会
*/
int read_column_numbers(int columns[], int max)
{
    int num = 0;
    int ch;

    /*
    ** 取得列标号，如果读取的数小于0则停止
    */
    while (num < max && scanf("%d", &columns[num]) == 1 && columns[num] >= 0)
    {
        num++;
    }

    /*
    ** 若列标号为奇数个则将最后一个列标号结束部分指定为行尾
    */
    if (num % 2 != 0)
    {
        columns[num] = MAX_INPUT;
    }

    /*
    ** 丢弃该行中包含最后一个数字的那部分内容
    */
    while ((ch = getchar()) != EOF && ch != '\n')
            ;

    return num;
}
/*
** 处理输入行，将指定列的输入行连接在一起，输出以NUL结尾
*/
void rearrange(char *output, char const *input,
        int n_columns, int const colunms[])
{
    int col;            /* column数组的下标 */
    int output_col;     /* 输出列数计数器 */
    int len;            /* 输出行的长度 */

    len = strlen(input);
    output_col = 0;

    /*
    ** 处理每列对应标号
    */
    for (col = 0; col < n_columns; col += 2)
    {
        int nchars = colunms[col + 1] - colunms[col] + 1;

        /*
        ** 如果输入行结束或输出行已满，就结束任务
        */
        if ((colunms[col] >= len) || (output_col == MAX_INPUT - 1))
        {
            break;
        }

        /*
        ** 如果输出行数据空间不够，只复制可容纳的数据
        */
        if (output_col + nchars > MAX_INPUT - 1)
        {
            nchars = MAX_INPUT - output_col - 1;
        }
        
        /*
        ** 复制相关的数据
        */
        strncat(output, input + colunms[col], nchars);
        output_col += nchars;
    }
    output[output_col] = '\0';
}