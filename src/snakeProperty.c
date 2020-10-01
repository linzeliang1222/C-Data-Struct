#include <stdio.h>
#include "snakeProperty.h"

extern int score;

/* ������̨������� x y �� */
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/* ��ʼ��Ϸ���� */
void draw(void)
{
    /* �ı������ɫ */
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
            printf("�����˳������Ժ�...");
            Sleep(1000);
            exit(0);
            break;
        default:
            system("cls");
            printBorder();
            gotoxy(55, 14);
            printf("�����쳣��ֹ��");
            Sleep(3000);
            exit(1);
            break;
    }
}

/* ���������Ĵ��� */
void keyDowd(void)
{
    int pre_key = key;   // ��¼ǰһ�������ķ���
    /* ����û������˼����е�ĳ���� */
    if (kbhit())
    {
        fflush(stdin);   // ��ջ��������ַ�

		/* getch()��ȡ�������ʱ�򣬻᷵�����Σ���һ�ε��÷���0����224���ڶ��ε��÷��صĲ���ʵ��ֵ */
        /* ��һ�ε��÷��صĲ���ʵ��ֵ */
        /* ������ͣ���� */
        key = getch();
        if (key == 80 || key == 112)
        {
            /* ����ǰ������������ */
            for (int i = 0; i < snake.len; i++)
            {
                gotoxy(snake.x[i], snake.y[i]);
                printf("  ");
            }
            gotoxy(food.x, food.y);
            printf("  ");
            gotoxy(54, 13);
            printf("   ��Ϸ����ͣ!");
            gotoxy(54, 14);
            printf("��Ŀǰ�ķ���Ϊ: %d", score);
            gotoxy(MAPWIDTH - 2, 0);
            while (true)
            {
                if (kbhit())
                {
                    key = getch();
                    if (key == 80 || key == 112)
                        break;
                    getch();  // �����յ�������£���ᱻʶ��Ϊ80��������һ��getch�����շ������
                }
            }
            
            /* ������Ϸ����ӡ���һ��̰���߻��� */
            gotoxy(54, 13);
            printf("              ");
            gotoxy(54, 14);
            printf("                   ");
            for (int i = 0; i < snake.len; i++)
            {
                gotoxy(snake.x[i], snake.y[i]);
                printf("��");
            }
            gotoxy(food.x, food.y);
            printf("��");
            gotoxy(MAPWIDTH - 2, 0);
            key = pre_key;
        }
        else if (key == 224)
            key = getch();
        else
            key = pre_key;
    }

    /*
    * ���ƶ���ʱ���Ȳ�ȥ��β��һ��
    * changeFlagΪ0������ʱû�гԵ�ʳ����ÿ��һ����Ҫ������β��Ӫ��һ���ƶ���Ч��
    * changeFlagΪ1�����Ե���ʳ��Ͳ���Ҫ������β���Դ�Ӫ��һ������������Ч��
    */
    if (changeFlag == 0)
    {
        gotoxy(snake.x[snake.len - 1], snake.y[snake.len - 1]);
        printf("  ");  // ����β����ո񼴱�ʾ��������β��ע���������ո�
    }

    /* ���ߵ�ÿһ��һ����ǰ�ƶ�һ�ڣ���ͷ���⣩ */
    for (int i = snake.len - 1; i > 0; i--)
    {
        snake.x[i] = snake.x[i - 1];
        snake.y[i] = snake.y[i - 1];
    }

    /* ���ƶ��ķ����ܺ�ǰһ�η����෴������෴�����ǰһ�ε��ƶ�������Ϊ��ǰ���ƶ����� */
    /*  
    * �� ��72
    * �� ��80
    * �� ��75
    * �� ��77
    */
    if (pre_key == 72 && key == 80)
        key = 72;
    if (pre_key == 80 && key == 72)
        key = 80;
    if (pre_key == 75 && key == 77)
        key = 75;
    if (pre_key == 77 && key == 75)
        key = 77;
        
    /* �ж���ͷӦ�����Ǹ������ƶ� */
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
    /* ��ӡ����ͷ */
    gotoxy(snake.x[0], snake.y[0]);
    printf("��");
    gotoxy(MAPWIDTH - 2, 0);   // ������ƶ����Ϸ�
    changeFlag = 0;            // ����Ŀǰû�гٵ�ʳ�changeFlagֵΪ0
}

/* ʵ������ʳ�� */
void createFood(void)
{
    /* ��ͷ����ʳ�� */
    if (snake.x[0] == food.x && snake.y[0] == food.y)
    {
        /* ��ͷ�������ʳ�����Ե����ʳ������Ҫ������һ��ʳ�� */
        while (true)
        {
            int flag = 1;
            // srand((unsigned) time(NULL));
            food.x = rand() % (MAPWIDTH - 4) + 2;
            food.y = rand() % (MAPHEIGHT - 2) + 1;

            /* ������ɵ�ʳ�ﲻ���������� */
            for (int i = 0; i < snake.len; i++)
            {
                if (snake.x[i] == food.x && snake.y[i] == food.y)
                {
                    flag = 0;
                    break;
                }
            }
            /* ������ɵ�ʳ�ﲻ�ܺ�����Ϊ������Ҳ�����������ϣ������������� */
            if (flag && food.x % 2 == 0)
                break;
        }

        /* ����ʳ�� */
        gotoxy(food.x, food.y);
        printf("��");

        snake.len++;       // �Ե�ʳ������ȼ�һ
        score += 10;       // ÿ��ʳ���10��
        if (level == 1)    // ���ųԵ�ʳ��Խ��Խ�࣬�ٶȻ�Խ��Խ��
            snake.speed -= 5;
        else if (level == 2)
            snake.speed -= 10;
        else if (level == 3)
            snake.speed -= 15;
        changeFlag = 1;    // ����Ҫ����Ϊ�ٵ���ʳ��Ͳ����ٲ�����β����һ�ڣ��Դ������������������Ч��
    }
}

/* �ж����˶��Ƿ���Ϲ淶 */
bool snakeStatus(void)
{
    /* ��ͷ�������±߽磬��Ϸ���� */
    if (snake.y[0] == 0 || snake.y[0] == MAPHEIGHT)
        return false;
    /* ��ͷ�絽���ұ߽磬��Ϸ���� */
    if (snake.x[0] == 0 || snake.x[0] == MAPWIDTH)
        return false;
    /* ��ͷ����������Ϸ���� */
    for (int i = 1; i < snake.len; i++)
    {
        if (snake.x[i] == snake.x[0] && snake.y[i] == snake.y[0])
            return false;
    }
    return true;
}

/* ��ʼ���� */
void menu(void)
{
    gotoxy(35, 10);
    printf("**************************************************");
    gotoxy(35, 11);
    printf("**************************************************");
    gotoxy(35, 12);
    printf("**             ��ӭ����̰����С��Ϸ!            **");
    gotoxy(35, 13);
    printf("**                 1.��ʼ��Ϸ                   **");
    gotoxy(35, 14);
    printf("**                 2.�Ѷ�ѡ��                   **");
    gotoxy(35, 15);
    printf("**                 3.��Ϸ����                   **");
    gotoxy(35, 16);
    printf("**                 4.�˳���Ϸ                   **");
    gotoxy(35, 17);
    printf("**                ����: ������                  **");
    gotoxy(35, 18);
    printf("**************************************************");
    gotoxy(35, 19);
    printf("**************************************************");
    gotoxy(35, 21);
    if (judge)
        printf("����������ѡ��: ");
    else
        printf("�Ѷ��������,�������������ѡ��: ");
}

/* ��ʼ��Ϸ */
void startGame(void)
{
    printBorder();
    /* ������ɳ�ʼʳ�� */
    while (true)
    {
        food.x = rand() % (MAPWIDTH - 4) + 2;
        food.y = rand() % (MAPHEIGHT - 2) + 1;
        /* ���ɵ�ʳ����������ż����ͳ�ʼʱ��ͷ���ڵ��������żһ
        �£���Ϊһ���ַ�ռ�����ֽڣ� �ᵼ�³�ʳ���ʱ��ֻ�ٵ�һ�� */
        if (food.x % 2 == 0)
            break;
    }
    gotoxy(food.x, food.y);
    printf("��");

    /* ��ʼ���ߵ����� */
    snake.len = 3;
    if (level == 1)
        snake.speed = 250;
    else if (level == 2)
        snake.speed = 200;
    else if (level == 3)
        snake.speed = 150;

    /* ����Ļ�м�������ͷ */
    snake.x[0] = MAPWIDTH / 2 + 1;  // x����Ϊż��
    snake.y[0] = MAPHEIGHT / 2;

    /* ��ӡ��ͷ */
    gotoxy(snake.x[0], snake.y[0]);
    printf("��");

    /* ���ɳ�ʼ������ */
    for (int i = 1; i < snake.len; i++)
    {
        /* ����Ĵ�ӡ�������겻�䣬������Ϊ��һ�����������ֵ+2 */
        snake.x[i] = snake.x[i - 1] + 2;
        snake.y[i] = snake.y[i - 1];
        gotoxy(snake.x[i], snake.y[i]);
        printf("��");
    }
    /* ��ӡ������󽫹���Ƶ���Ļ���Ϸ���������������һֱ��˸ */
    gotoxy(MAPWIDTH - 2, 0);
}

/* �Ѷ�ѡ�� */
void selectLevel(void)
{
    printBorder();
    gotoxy(50, 14);
    printf("1.��");
    gotoxy(50, 15);
    printf("2.�е�");
    gotoxy(50, 16);
    printf("3.����");
    gotoxy(35, 21);
    printf("������Ҫѡ����Ѷ�: ");
    getInput(&level);
    judge = false;
    draw();
}

/* ��ӡ�߿� */
void printBorder(void)
{
    system("cls");
    for (int i = 0; i <= MAPWIDTH; i += 2)  //i+=2����Ϊ����ռ�õ�������λ��
    {
        gotoxy(i, 0);
        printf("��");
        gotoxy(i, MAPHEIGHT);
        printf("��");
    }

    for (int i = 1; i < MAPHEIGHT; i++)
    {
        gotoxy(0, i);
        printf("��");
        gotoxy(MAPWIDTH, i);
        printf("��");
    }
    gotoxy(MAPWIDTH - 2, 0);
}

/*��ȡ�û�������ѡ�� */
void getInput(int * temp)
{
    while (scanf("%d", temp) != 1 || (*temp != 1 && *temp != 2 && *temp != 3 && *temp != 4))
    {
        while (getchar() != '\n')
            continue;
        gotoxy(35, 21);
        printf("�������ѡ����ڣ�����������:                                          ");
        gotoxy(67, 21);
    }
}

/* ��Ϸ���� */
void regular(void)
{
    printBorder();
    gotoxy(35, 10);
    printf("**************************************************");
    gotoxy(35, 11);
    printf("**************************************************");
    gotoxy(35, 12);
    printf("**                  ��������:                   **");
    gotoxy(35, 13);
    printf("**           ʹ�÷�����������ߵķ���           **");
    gotoxy(35, 14);
    printf("**                ��P/p��ͣ��Ϸ                 **");
    gotoxy(35, 15);
    printf("**              ��������������˵�              **");
    gotoxy(35, 16);
    printf("**                ����: ������                  **");
    gotoxy(35, 17);
    printf("**************************************************");
    gotoxy(35, 18);
    printf("**************************************************");
    gotoxy(MAPWIDTH - 2, 0);
}