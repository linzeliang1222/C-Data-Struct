#include <stdio.h>
#include "snakeProperty.h"

extern int score;

/* 将控制台光标移至 x y 处 */
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/* 初始游戏画面 */
void draw(void)
{
    /* 改变界面颜色 */
    system("color 3f");
    printBorder();
    menu();
    getInput(&ch);
    switch (ch)
    {
        case 1:
            startGame();
            break;
        case 2:
            selectLevel();
            break;
        case 3:
            regular();
            getch();
            judge = true;
            menu();
            getInput(&ch);
            draw();
            break;
        case 4:
            system("cls");
            printBorder();
            gotoxy(50, 14);
            printf("正在退出，请稍后...");
            Sleep(1000);
            exit(0);
            break;
        default:
            system("cls");
            printBorder();
            gotoxy(55, 14);
            printf("程序异常终止！");
            Sleep(3000);
            exit(1);
            break;
    }
}

/* 按键操作的代码 */
void keyDowd(void)
{
    int pre_key = key;   // 记录前一个按键的方向
    /* 如果用户按下了键盘中的某个键 */
    if (kbhit())
    {
        fflush(stdin);   // 清空缓冲区的字符

		/* getch()读取方向键的时候，会返回两次，第一次调用返回0或者224，第二次调用返回的才是实际值 */
        /* 第一次调用返回的不是实际值 */
        /* 增加暂停功能 */
        key = getch();
        if (key == 80 || key == 112)
        {
            /* 将当前画面隐藏起来 */
            for (int i = 0; i < snake.len; i++)
            {
                gotoxy(snake.x[i], snake.y[i]);
                printf("  ");
            }
            gotoxy(food.x, food.y);
            printf("  ");
            gotoxy(54, 13);
            printf("   游戏已暂停!");
            gotoxy(54, 14);
            printf("您目前的分数为: %d", score);
            gotoxy(MAPWIDTH - 2, 0);
            while (true)
            {
                if (kbhit())
                {
                    key = getch();
                    if (key == 80 || key == 112)
                        break;
                    getch();  // 若接收到方向键下，则会被识别为80，故再用一个getch来吸收方向键下
                }
            }
            
            /* 继续游戏，打印最后一次贪吃蛇画面 */
            gotoxy(54, 13);
            printf("              ");
            gotoxy(54, 14);
            printf("                   ");
            for (int i = 0; i < snake.len; i++)
            {
                gotoxy(snake.x[i], snake.y[i]);
                printf("■");
            }
            gotoxy(food.x, food.y);
            printf("★");
            gotoxy(MAPWIDTH - 2, 0);
            key = pre_key;
        }
        else if (key == 224)
            key = getch();
        else
            key = pre_key;
    }

    /*
    * 蛇移动的时候先擦去蛇尾的一节
    * changeFlag为0表明此时没有吃到食物，因此每走一步就要擦除蛇尾，营造一个移动的效果
    * changeFlag为1表明吃到了食物，就不需要擦除蛇尾，以此营造一个蛇身增长的效果
    */
    if (changeFlag == 0)
    {
        gotoxy(snake.x[snake.len - 1], snake.y[snake.len - 1]);
        printf("  ");  // 在蛇尾输出空格即表示擦除了蛇尾，注意有两个空格
    }

    /* 将蛇的每一节一次向前移动一节（蛇头除外） */
    for (int i = snake.len - 1; i > 0; i--)
    {
        snake.x[i] = snake.x[i - 1];
        snake.y[i] = snake.y[i - 1];
    }

    /* 蛇移动的方向不能和前一次方向相反，如果相反，则把前一次的移动反向作为当前的移动方向 */
    /*  
    * ↑ ：72
    * ↓ ：80
    * ← ：75
    * → ：77
    */
    if (pre_key == 72 && key == 80)
        key = 72;
    if (pre_key == 80 && key == 72)
        key = 80;
    if (pre_key == 75 && key == 77)
        key = 75;
    if (pre_key == 77 && key == 75)
        key = 77;
        
    /* 判断蛇头应该往那个方向移动 */
    switch (key)
    {
        case 75:
            snake.x[0] -= 2;
            break;
        case 77:
            snake.x[0] += 2;
            break;
        case 72:
            snake.y[0]--;
            break;
        case 80:
            snake.y[0]++;
            break;
    }
    /* 打印处蛇头 */
    gotoxy(snake.x[0], snake.y[0]);
    printf("■");
    gotoxy(MAPWIDTH - 2, 0);   // 将光标移动到上方
    changeFlag = 0;            // 由于目前没有迟到食物，changeFlag值为0
}

/* 实现生成食物 */
void createFood(void)
{
    /* 蛇头碰到食物 */
    if (snake.x[0] == food.x && snake.y[0] == food.y)
    {
        /* 蛇头碰到这个食物代表吃掉这个食物，因此需要再生成一个食物 */
        while (true)
        {
            int flag = 1;
            // srand((unsigned) time(NULL));
            food.x = rand() % (MAPWIDTH - 4) + 2;
            food.y = rand() % (MAPHEIGHT - 2) + 1;

            /* 随机生成的食物不能再蛇身上 */
            for (int i = 0; i < snake.len; i++)
            {
                if (snake.x[i] == food.x && snake.y[i] == food.y)
                {
                    flag = 0;
                    break;
                }
            }
            /* 随机生成的食物不能横坐标为基数，也不能再蛇身上，否则重新生成 */
            if (flag && food.x % 2 == 0)
                break;
        }

        /* 绘制食物 */
        gotoxy(food.x, food.y);
        printf("★");

        snake.len++;       // 吃到食物，蛇身长度加一
        score += 10;       // 每个食物加10分
        if (level == 1)    // 随着吃的食物越来越多，速度会越来越快
            snake.speed -= 5;
        else if (level == 2)
            snake.speed -= 10;
        else if (level == 3)
            snake.speed -= 15;
        changeFlag = 1;    // 很重要，因为迟到了食物，就不用再擦除蛇尾的那一节，以此来造成蛇身体增长的效果
    }
}

/* 判断蛇运动是否符合规范 */
bool snakeStatus(void)
{
    /* 蛇头碰到上下边界，游戏结束 */
    if (snake.y[0] == 0 || snake.y[0] == MAPHEIGHT)
        return false;
    /* 蛇头喷到左右边界，游戏结束 */
    if (snake.x[0] == 0 || snake.x[0] == MAPWIDTH)
        return false;
    /* 蛇头碰到蛇身，游戏结束 */
    for (int i = 1; i < snake.len; i++)
    {
        if (snake.x[i] == snake.x[0] && snake.y[i] == snake.y[0])
            return false;
    }
    return true;
}

/* 开始界面 */
void menu(void)
{
    gotoxy(35, 10);
    printf("**************************************************");
    gotoxy(35, 11);
    printf("**************************************************");
    gotoxy(35, 12);
    printf("**             欢迎来到贪吃蛇小游戏!            **");
    gotoxy(35, 13);
    printf("**                 1.开始游戏                   **");
    gotoxy(35, 14);
    printf("**                 2.难度选择                   **");
    gotoxy(35, 15);
    printf("**                 3.游戏介绍                   **");
    gotoxy(35, 16);
    printf("**                 4.退出游戏                   **");
    gotoxy(35, 17);
    printf("**                作者: 林泽良                  **");
    gotoxy(35, 18);
    printf("**************************************************");
    gotoxy(35, 19);
    printf("**************************************************");
    gotoxy(35, 21);
    if (judge)
        printf("请输入您的选择: ");
    else
        printf("难度设置完成,请输入接下来的选择: ");
}

/* 开始游戏 */
void startGame(void)
{
    printBorder();
    /* 随机生成初始食物 */
    while (true)
    {
        food.x = rand() % (MAPWIDTH - 4) + 2;
        food.y = rand() % (MAPHEIGHT - 2) + 1;
        /* 生成的食物横坐标的奇偶必须和初始时蛇头所在的坐标的奇偶一
        致，因为一个字符占两个字节， 会导致吃食物的时候只迟到一半 */
        if (food.x % 2 == 0)
            break;
    }
    gotoxy(food.x, food.y);
    printf("★");

    /* 初始化蛇的属性 */
    snake.len = 3;
    if (level == 1)
        snake.speed = 250;
    else if (level == 2)
        snake.speed = 200;
    else if (level == 3)
        snake.speed = 150;

    /* 在屏幕中间生成蛇头 */
    snake.x[0] = MAPWIDTH / 2 + 1;  // x坐标为偶数
    snake.y[0] = MAPHEIGHT / 2;

    /* 打印蛇头 */
    gotoxy(snake.x[0], snake.y[0]);
    printf("■");

    /* 生成初始的蛇身 */
    for (int i = 1; i < snake.len; i++)
    {
        /* 蛇身的打印。纵坐标不变，横坐标为上一节蛇身的坐标值+2 */
        snake.x[i] = snake.x[i - 1] + 2;
        snake.y[i] = snake.y[i - 1];
        gotoxy(snake.x[i], snake.y[i]);
        printf("■");
    }
    /* 打印完蛇身后将光标移到屏幕最上方，避免光标在蛇身处一直闪烁 */
    gotoxy(MAPWIDTH - 2, 0);
}

/* 难度选择 */
void selectLevel(void)
{
    printBorder();
    gotoxy(50, 14);
    printf("1.简单");
    gotoxy(50, 15);
    printf("2.中等");
    gotoxy(50, 16);
    printf("3.困难");
    gotoxy(35, 21);
    printf("请输入要选择的难度: ");
    getInput(&level);
    judge = false;
    draw();
}

/* 打印边框 */
void printBorder(void)
{
    system("cls");
    for (int i = 0; i <= MAPWIDTH; i += 2)  //i+=2是因为横向占用的是两个位置
    {
        gotoxy(i, 0);
        printf("■");
        gotoxy(i, MAPHEIGHT);
        printf("■");
    }

    for (int i = 1; i < MAPHEIGHT; i++)
    {
        gotoxy(0, i);
        printf("■");
        gotoxy(MAPWIDTH, i);
        printf("■");
    }
    gotoxy(MAPWIDTH - 2, 0);
}

/*获取用户的输入选项 */
void getInput(int * temp)
{
    while (scanf("%d", temp) != 1 || (*temp != 1 && *temp != 2 && *temp != 3 && *temp != 4))
    {
        while (getchar() != '\n')
            continue;
        gotoxy(35, 21);
        printf("您输入的选项不存在，请重新输入:                                          ");
        gotoxy(67, 21);
    }
}

/* 游戏规则 */
void regular(void)
{
    printBorder();
    gotoxy(35, 10);
    printf("**************************************************");
    gotoxy(35, 11);
    printf("**************************************************");
    gotoxy(35, 12);
    printf("**                  规则如下:                   **");
    gotoxy(35, 13);
    printf("**           使用方向键来控制蛇的方向           **");
    gotoxy(35, 14);
    printf("**                按P/p暂停游戏                 **");
    gotoxy(35, 15);
    printf("**              按任意键返回主菜单              **");
    gotoxy(35, 16);
    printf("**                作者: 林泽良                  **");
    gotoxy(35, 17);
    printf("**************************************************");
    gotoxy(35, 18);
    printf("**************************************************");
    gotoxy(MAPWIDTH - 2, 0);
}