#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>

#define SNAKESIZE 100  // 蛇身的最大节数
#define MAPWIDTH  118  // 宽度
#define MAPHEIGHT 29   // 长度

static int key = 72;       // 表示蛇的移动方向，72为按下“↑”所代表的数字
static int changeFlag = 0; // 用来判断蛇是否吃掉了食物，这一步很重要，涉及到是否会有蛇身的移动效果及摄生的增长效果
static int level = 1;      // 设置游戏水平难度，数字越高难度越高
static int ch;             // 用户选择模式
static bool judge = true;  // 判断是否打印选择完成提示

/* 食物的坐标 */
typedef struct Food
{
    int x;
    int y;
} Food;

/* 蛇的相关属性 */
typedef struct Snake
{
    int speed;        // 蛇的移动速度
    int len;          // 蛇的长度
    int x[SNAKESIZE]; // 组成蛇身的每一个小方块中的x坐标
    int y[SNAKESIZE]; // 组成蛇身的每一个小方块中的y坐标
} Snake;

/* 声明结构体 */
Food food;
Snake snake;

void draw(void);                // 绘制游戏边框
void createFood(void);          // 随机生成食物
void keyDowd(void);             // 按键的操作
bool snakeStatus(void);         // 蛇的状态
void gotoxy(int x, int y);      // 从控制台移动光标
void menu(void);                // 开始界面
void startGame(void);           // 开始游戏
void selectLevel(void);         // 难度选择
void printBorder(void);         // 打印边框
void getInput(int *);           // 获取用户的输入
void regular(void);             // 游戏规则