extern int roll_count;                 // 将调用rollem的计数器扩展到manydice中去，用于最后将总共使用的次数打印出来

int roll_n_dice(int dice, int sides);  // 进行判断和调用rollem函数，声明函数原型以便在manydice.c中使用