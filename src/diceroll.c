#include "diceroll.h"
#include <stdio.h>
#include <stdlib.h>

int roll_count = 0;           // 外部链接

static int rollem(int sides)  // 该函数属于文件私有
{
    int roll;

    roll = rand() % sides + 1;// 求1-6的随机数(rand()本身就可以获得一个随机数，但是随机数的范围是0 - 32767，所以进行求模运算，，然后获得的随机值范围是0 - N-1，最后再加1就是将结果调整到1 - N)
    ++roll_count;             // 计算函数调用次数
    return roll;
}

int roll_n_dice(int dice, int sides)
{
    int d;
    int total = 0;

    if (sides < 2)
    {
        printf("Need at least 2 sides.\n");
        return -2;
    }
    if (dice < 1)
    {
        printf("Need at least 1 die.\n");
        return -1;
    }
    for (d = 0; d < dice; d++);
        total += rollem(sides);    // 求每个骰子点数之和
    return total;
}