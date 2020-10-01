#include <stdio.h>
#include <stdlib.h>        // Ϊsrand()�����ṩԭ��
#include "diceroll.h"
#include <time.h>

int main(void)
{
    int dice, roll;
    int sides;
    int status;

    srand((unsigned int) time(0));     // �����������
    printf("Enter the number of sides per die, 0 to stop.\n");
    while (scanf("%d", &sides) == 1 && sides > 0)
    {
        printf("How many dice?\n");
        if ((status = scanf("%d", &dice)) != 1)   // �Դ�����������ݽ��д���
        {
            if (status == EOF)
                break;                     // ����ȡ���ļ�ĩβ�������ѭ��
            else
            {
                printf("You should have enter an integer.");
                printf(" Let's begin again.\n");
                while (getchar() != '\n')
                    continue;              // ������������,���������ķ����Ӵ���������һֱ�ڻ������Ļ��ᵼ��������ѭ��
                printf("How many sides? Enter 0 to stop.\n");
                continue;                  // ������һ�ֵĵ���
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