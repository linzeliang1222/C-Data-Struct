#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>

#define SNAKESIZE 100  // �����������
#define MAPWIDTH  118  // ���
#define MAPHEIGHT 29   // ����

static int key = 72;       // ��ʾ�ߵ��ƶ�����72Ϊ���¡����������������
static int changeFlag = 0; // �����ж����Ƿ�Ե���ʳ���һ������Ҫ���漰���Ƿ����������ƶ�Ч��������������Ч��
static int level = 1;      // ������Ϸˮƽ�Ѷȣ�����Խ���Ѷ�Խ��
static int ch;             // �û�ѡ��ģʽ
static bool judge = true;  // �ж��Ƿ��ӡѡ�������ʾ

/* ʳ������� */
typedef struct Food
{
    int x;
    int y;
} Food;

/* �ߵ�������� */
typedef struct Snake
{
    int speed;        // �ߵ��ƶ��ٶ�
    int len;          // �ߵĳ���
    int x[SNAKESIZE]; // ��������ÿһ��С�����е�x����
    int y[SNAKESIZE]; // ��������ÿһ��С�����е�y����
} Snake;

/* �����ṹ�� */
Food food;
Snake snake;

void draw(void);                // ������Ϸ�߿�
void createFood(void);          // �������ʳ��
void keyDowd(void);             // �����Ĳ���
bool snakeStatus(void);         // �ߵ�״̬
void gotoxy(int x, int y);      // �ӿ���̨�ƶ����
void menu(void);                // ��ʼ����
void startGame(void);           // ��ʼ��Ϸ
void selectLevel(void);         // �Ѷ�ѡ��
void printBorder(void);         // ��ӡ�߿�
void getInput(int *);           // ��ȡ�û�������
void regular(void);             // ��Ϸ����