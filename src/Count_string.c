/*
** �������ӱ�׼�����ж�ȡ�����в��ڱ�׼����д�ӡ��Щ������
** ÿ�������еĺ���һ���Ǹ����ݵ�һ����
**
** ����ĵ�һ����һ����ţ����������һ��������β
** ��Щ�б�ųɶԳ��֣�˵����Ҫ����ӡ�������е��з�Χ
** ���磬0 3 10 12 -1��ʾ��0�е���3�У���10�е���12�е����ݱ���ӡ
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COLS 20      /* �ܹ����������к� */
#define MAX_INPUT 1000   /* ÿ�������е���󳤶� */ 

int read_column_numbers(int column[], int max);
void rearrange(char *output, char const *input,
        int n_column, int const column[]);

int main(void)
{
    int n_column;            /* ���д�����б�� */
    int columns[MAX_COLS];   /* ��Ҫ��������� */
    char input[MAX_INPUT];   /* ���������е����� */
    char output[MAX_INPUT];  /* ��������е����� */

    /*
    ** ��ȡ�ô��б��
    */
    n_column = read_column_numbers(columns, MAX_COLS);

    /*
    ** ��ȡ����ʹ�ӡ�����ʣ����
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
** ��ȡ��ţ����������Χ�����
*/
int read_column_numbers(int columns[], int max)
{
    int num = 0;
    int ch;

    /*
    ** ȡ���б�ţ������ȡ����С��0��ֹͣ
    */
    while (num < max && scanf("%d", &columns[num]) == 1 && columns[num] >= 0)
    {
        num++;
    }

    /*
    ** ���б��Ϊ�����������һ���б�Ž�������ָ��Ϊ��β
    */
    if (num % 2 != 0)
    {
        columns[num] = MAX_INPUT;
    }

    /*
    ** ���������а������һ�����ֵ��ǲ�������
    */
    while ((ch = getchar()) != EOF && ch != '\n')
            ;

    return num;
}
/*
** ���������У���ָ���е�������������һ�������NUL��β
*/
void rearrange(char *output, char const *input,
        int n_columns, int const colunms[])
{
    int col;            /* column������±� */
    int output_col;     /* ������������� */
    int len;            /* ����еĳ��� */

    len = strlen(input);
    output_col = 0;

    /*
    ** ����ÿ�ж�Ӧ���
    */
    for (col = 0; col < n_columns; col += 2)
    {
        int nchars = colunms[col + 1] - colunms[col] + 1;

        /*
        ** ��������н�����������������ͽ�������
        */
        if ((colunms[col] >= len) || (output_col == MAX_INPUT - 1))
        {
            break;
        }

        /*
        ** �����������ݿռ䲻����ֻ���ƿ����ɵ�����
        */
        if (output_col + nchars > MAX_INPUT - 1)
        {
            nchars = MAX_INPUT - output_col - 1;
        }
        
        /*
        ** ������ص�����
        */
        strncat(output, input + colunms[col], nchars);
        output_col += nchars;
    }
    output[output_col] = '\0';
}