#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 10
#define MAX_LRNGTH_INSERT_SORT 7

typedef struct
{
    int r[MAXSIZE+1]; // 用于储存要排序的数组，r[0]用作哨兵或临时变量
    int length;       // 用于记录顺序表的长度
} SqList;

void swap(SqList * L, int i, int j);
void BubbleSort(SqList * L);
void BubbleSort2(SqList * L);
void SelectSort(SqList * L);
void InsertSort(SqList * L);
void ShellSort(SqList * L);
void HeapSort(SqList * L);
void HeapAdjust(SqList * L, int s, int m);
void MergeSort(SqList * L);
void MSort(int SR[], int TR1[], int s, int t);
void Merge(int SR[], int TR[], int i, int m, int n);
void MergeSort2(SqList * L);
void MergePass(int SR[], int TR[], int s, int n);
void QuickSort(SqList * L);
void QSort(SqList * L, int low, int high);
int Partition(SqList * L, int low, int high);
int Partition1(SqList * L, int low, int high);

int main(void)
{
    return 0;
}

/* 交换L中数组r的下标为i和j的值 */
void swap(SqList * L, int i, int j)
{
    int temp;
    temp = L->r[i];
    L->r[i] = L->r[j];
    L->r[j] = temp;
}

/* 冒泡排序 */
void BubbleSort(SqList * L)
{
    int i, j;
    for (i = 1; i < L->length; i++)
        for (j = L->length - 1; j >= i; j--)
            if (L->r[j] > L->r[j+1])
                swap(L, j, j+1);
}

/* 冒泡排序优化 */
void BubbleSort2(SqList * L)
{
    int i, j;
    bool flag = true; // flag用来做标记
    for (i = 1; i < L->length; i++)
        for (j = L->length - 1; j >= i && flag; j--)
        {
            flag = false;
            if (L->r[j] > L->r[j+1])
            {
                swap(L, j, j+1);
                flag = true;
            }
        }
    
}

/* 简单选择排序 */
void SelectSort(SqList * L)
{
    int i, j;
    int min;
    for (i = 1; i < L->length; i++)
    {
        min = i;
        for (j = i+1; j <= L->length; j++)
        {
            if (L->r[min] > L->r[j])
                min = j;
        }
        if (min != i)
            swap(L, i, min);
    }
}

/* 直接插入排序 */
void InsertSort(SqList * L)
{
    int i, j;
    for (i = 2; i <= L->length; i++)
        if (L->r[i] < L->r[i-1])
        {
            L->r[0] = L->r[i];
            for (j = i-1; L->r[j] > L->r[0]; j--)
                L->r[j+1] = L->r[j];
            L->r[j+1] = L->r[0];
        }
}

/* 希尔排序 */
void ShellSort(SqList * L)
{
    int i, j;
    int increment;
    increment = L->length;
    for (increment /= 2; increment >= 1; increment /= 2) // 增量序列
        for (i = increment; i < L->length; i++)
            if (L->r[i] < L->r[i-increment])
            {
                L->r[0] = L->r[i];
                for (j = i-increment; j > 0 && L->r[j] > L->r[0]; j -= increment) // 记录后移，查找插入位置
                {
                    L->r[j+increment] = L->r[j];
                }
                L->r[j] = L->r[0]; // 找到位置插入
            }
}

/* 堆排序 */
void HeapSort(SqList * L)
{
    int i;
    for (i = L->length/2; i > 0; i--) // 将L中的r构建成一个大顶堆, 函数HeapAdjust()就是构建大顶堆函数
        HeapAdjust(L, i, L->length);

    for (i = L->length; i > 1; i--)
    {
        swap(L, 1, i);         // 将堆顶记录和当前未经排序子序列的最后一个记录交换
        HeapAdjust(L, 1, i-1); // 重新调整为大堆顶
    }
}

/* 堆调整函数 */
void HeapAdjust(SqList * L, int s, int m)
{
    int temp, j;
    temp = L->r[s];
    for (j = s * 2; j <= m; j *= 2)
    {
        if (j < m && L->r[j] < L->r[j+1]) // j是左右孩子比较大的值的孩子的下标
            j++;
        if (temp >= L->r[j])              // 若双亲大于左右孩子，则不需要改动，跳出循环
            break;
        L->r[s] = L->r[j];                // 先把较大的孩子的值赋值给双亲
        s = j;
    }
    L->r[j] = temp;
}

/* 归并排序(递归实现) */
void MergeSort(SqList * L)
{
    MSort(L->r, L->r, 1, L->length);
}

/* 将SR[s..t]归并排序为TR1[s..t] */
void MSort(int SR[], int TR1[], int s, int t)
{
    int m;
    int TR2[MAXSIZE+1];
    if (s == t)
        TR1[s] = SR[s];
    else
    {
        m = (s + t) / 2;          // 将SR[]平分为SR[s..m]和SR[m+1..t]
        MSort(SR, TR2, s, m);     // 递归将SR[s..m]归并为有序的TR2[s..m]
        MSort(SR, TR2, m+1, t);   // 递归将SR[m+1..t]归并为有序的TR2[m+1..t]
        Merge(TR2, TR1, s, m, t); // 将TR2[s..m]和TR2[m+1..t]归并到TR1[s..t]
    }
}

/* 将有序的SR[i..m]和TR[m+1..n]归并为有序的TR[i..n] */
void Merge(int SR[], int TR[], int i, int m, int n)
{
    int j, k, l;
    for (k = i, j = m+1; i < m && j <= n; k++)
    {
        if (SR[i] < SR[j])  // 将SR中记录由小到大归并入TR
            TR[k] = SR[i++];
        else
            TR[k] = SR[j++];
        if (i <= m)
            for (l = 0; l <= m-i; l++)
                TR[k+l] = SR[i+l]; // 将剩余的SR[i..m]复制到TR
        if (j <= n)
            for (l = 0; l <= n-j; l++)
                TR[k+l] = SR[j+l]; // 将剩余的SR[j..n]复制到TR
    }
}

/* 归并排序(非递归实现) */
void MergeSort2(SqList* L)
{
    int k;
    int * TR;
    TR = (int *) malloc(sizeof(int) * L->length); // 申请额外数组内存空间
    k = 1;
    while (k < L->length)
    {
        MergePass(L->r, TR, k, L->length);
        k *= 2; // 子序列长度加倍
        MergePass(TR, L->r, k, L->length);
        k *= 2; // 子序列长度加倍
    }
}

void MergePass(int SR[], int TR[], int s, int n)
{
    int i = 1;
    int j;
    while (i <= n - 2*s + 1)
    {
        Merge(SR, TR, i, i+s-1, i+2*s-1); // 两两归并
        i = i+2*s;
    }
    if (i < n-s+1) // 归并最后两个序列
        Merge(SR, TR, i, i+s-1, n);
    else           // 若最后只剩下当个子序列
        for (j = i; j <= n; j++)
            TR[j] = SR[j];
}

/* 对顺序表L做快速排序 */
void QuickSort(SqList * L)
{
    QSort(L, 1, L->length);
}

/* 对顺序表L中的子序列L->r[low...high]做快速排序 */
void QSort(SqList * L, int low, int high)
{
    int pivot;
    if ((high - low) > MAX_LRNGTH_INSERT_SORT)
    {
        pivot = Partition(L, low, high); // 将L->r[low...high]一分为二，算出基准值pivot
        QSort(L, low, pivot-1);          // 对低子表递归排序
        low = pivot + 1;                 // 尾递归
    }
    else
        InsertSort(L);
}

/* 交换顺序表L中子表的记录，使基准值记录到位，并返回其所在位置，此时它之前(后)的记录均不大(小)于它 */
int Partition(SqList * L, int low, int high)
{
    int pivotkey, m;
    m = (low + high) / 2;
    if (L->r[low] > L->r[high])
        swap(L, low, high);
    if (L->r[m] > L->r[high])
        swap(L, high, m);
    if (L->r[low] > L->r[m])
        swap(L, m, low);
    pivotkey = L->r[low]; // 用子表的第一个记录做基准值
    while (low < high)    // 从表的两端交替向中间扫描
    {
        while (low < high && L->r[high] >= pivotkey)
            high--;
        swap(L, low, high);
        while (low < high && L->r[low] <= pivotkey)
            low++;
        swap(L, low, high;)
    }
    return low; // 返回基准值的所在位置
}

/* 快速排序代码优化 */
int Partition1(SqList * L, int low, int high)
{
    int pivotkey, m;
    m = (low + high) / 2;
    if (L->r[low] > L->r[high])
        swap(L, low, high);
    if (L->r[m] > L->r[high])
        swap(L, high, m);
    if (L->r[low] > L->r[m])
        swap(L, m, low);
    pivotkey = L->r[low]; // 用子表的第一个记录做基准值
    L->r[0] = pivotkey;   //将基准值备份到L->r[0]
    while (low < high)    // 从表的两端交替向中间扫描
    {
        while (low < high && L->r[high] >= pivotkey)
            high--;
        L->r[low] = L->r[high]; // 采用替换而不是交换的方式进行操作
        while (low < high && L->r[low] <= pivotkey)
            low++;
        L->r[high] = L->r[low]; // 采用替换而不是交换的方式进行操作
    }
    L->r[low] = L->r[0];        // 将基准值替换回L->r[low];
    return low;                 // 返回基准值的所在位置
}