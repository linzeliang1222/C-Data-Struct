#include <stdio.h>
#include "snakeProperty.h"

int score;
char chr = 'y';           // 是否继续游戏

int main(void)
{
    srand((unsigned) time(NULL));
    while (chr == 'y' || chr == 'Y')
    {
        draw();
        while (true)
        {
            keyDowd();
            if (!snakeStatus())
                break;
            createFood();
            Sleep(snake.speed);
        }

        gotoxy(54, 13);
        printf("Game Over!\n");
        gotoxy(49, 14);
        printf("本次的游戏得分为: %d\n", score);
        gotoxy(49, 15);
        printf("是否继续游戏(y/n): ");
        fflush(stdin);
        while (scanf("%c", &chr) != 1 && (chr != 'y' && chr != 'Y' && chr != 'n' && chr != 'N'))
        {
            gotoxy(49, 16);
            printf("输入有误，请重新输入:                         ");
            gotoxy(71, 16);
            while (getchar() != '\n');
                continue;
        }
        judge = true;
        score = 0;
    }
    gotoxy(55, 16);
    printf("正在退出...");
    gotoxy(MAPWIDTH - 2, 0);
    Sleep(2000);

    return 0;
}