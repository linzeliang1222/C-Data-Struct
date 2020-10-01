#include <stdio.h>
#include <ctype.h>

float calc_add(float x, float y);
float calc_sub(float x, float y);
float calc_multiply(float x, float y);
float calc_divise(float x, float y);
float get_input(void);
char get_choice(void);

int main(void)
{
    char ch;
    float x, y;
    float last;
    
    while ((ch = get_choice()) != 'q')
    {
        /* �õ��û����������ֵ */
        printf("Please input your first number:");
        x = get_input();
        printf("Please input your second number:");
        y = get_input();

        switch (ch)
        {
            case 'a':
                    last = calc_add(x, y);
                    printf("Result is %.2f", last);
                    break;
            case 's':
                    last = calc_sub(x, y);
                    printf("Result is %.2f", last);
                    break;
            case 'm':
                    last = calc_multiply(x, y);
                    printf("Result is %.2f", last);
                    break;
            case 'd':
                    last = calc_divise(x, y);
                    printf("Result is %.2f", last);
                    break;
            default:
                    printf("Your input is error!\nPlease enter again!\n");
                    break;
        }
    }

    return 0;
}

/* �ж��û��������Ƿ�Υ�� */
char get_choice(void)
{
    int ch;

    printf("\nEnter the operation of your choice:\n");
    printf("a. add\t\ts. subtract\n");
    printf("m. multiply\td. divise\n");
    printf("q.quit\t\t\n");

    while ((ch = getchar()) != 'a' && ch != 's' && ch != 'm' && ch != 'd' && ch != 'q')
    {
        printf("Please input a or s or m or d or q:");
        while (getchar() != '\n')
            continue;
    }
    while (getchar() != '\n')
        continue;

    return ch;
}

/* ���û�������Ч������ */
float get_input(void)
{
    float num;

    while ((scanf("%f", &num) != 1))
    {
        printf(" is invalid number!\nPlease input again!\n");
        while (getchar() != '\n') // ������Ч���ַ�
            continue;
    }
    getchar();
    
    return num;
}

/* ����ӷ� */
float calc_add(float x, float y)
{
    return (x + y);
}

/* ������� */
float calc_sub(float x, float y)
{
    return (x - y);
}

/* ����˷� */
float calc_multiply(float x, float y)
{
    return (x * y);
}

/* ������� */
float calc_divise(float x, float y)
{
    return (x / y);
}