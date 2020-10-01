#include <stdio.h>
#include <stdlib.h>        // 为srand()函数提供原型
#include "diceroll.h"
#include <time.h>

int main(void)
{
    int dice, roll;
    int sides;
    int status;

    srand((unsigned int) time(0));     // 生成随机种子
    printf("Enter the number of sides per die, 0 to stop.\n");
    while (scanf("%d", &sides) == 1 && sides > 0)
    {
        printf("How many dice?\n");
        if ((status = scanf("%d", &dice)) != 1)   // 对错误的输入数据进行处理
        {
            if (status == EOF)
                break;                     // 若读取到文件末尾，则瑞出循环
            else
            {
                printf("You should have enter an integer.");
                printf(" Let's begin again.\n");
                while (getchar() != '\n')
                    continue;              // 处理错误的输入,将缓冲区的非数子处理到，否则一直在缓冲区的话会导致陷入死循环
                printf("How many sides? Enter 0 to stop.\n");
                continue;                  // 进入下一轮的迭代
            }
        }
        roll = roll_n_dice(dice, sides);
        printf("You have rolled a %d using %d %d-sides dice.\n", roll, dice, sides);
        printf("How many sides? Enter 0 to stop.\n");
    }
    printf("The rollem() function was called %d times.\n", roll_count);
    printf("GOOD FORTUNE TO YOU!\n");

    return 0;
}