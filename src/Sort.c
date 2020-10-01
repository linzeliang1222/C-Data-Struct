#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 10
#define MAX_LRNGTH_INSERT_SORT 7

typedef struct
{
    int r[MAXSIZE+1]; // ���ڴ���Ҫ��������飬r[0]�����ڱ�����ʱ����
    int length;       // ���ڼ�¼˳���ĳ���
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

/* ����L������r���±�Ϊi��j��ֵ */
void swap(SqList * L, int i, int j)
{
    int temp;
    temp = L->r[i];
    L->r[i] = L->r[j];
    L->r[j] = temp;
}

/* ð������ */
void BubbleSort(SqList * L)
{
    int i, j;
    for (i = 1; i < L->length; i++)
        for (j = L->length - 1; j >= i; j--)
            if (L->r[j] > L->r[j+1])
                swap(L, j, j+1);
}

/* ð�������Ż� */
void BubbleSort2(SqList * L)
{
    int i, j;
    bool flag = true; // flag���������
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

/* ��ѡ������ */
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

/* ֱ�Ӳ������� */
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

/* ϣ������ */
void ShellSort(SqList * L)
{
    int i, j;
    int increment;
    increment = L->length;
    for (increment /= 2; increment >= 1; increment /= 2) // ��������
        for (i = increment; i < L->length; i++)
            if (L->r[i] < L->r[i-increment])
            {
                L->r[0] = L->r[i];
                for (j = i-increment; j > 0 && L->r[j] > L->r[0]; j -= increment) // ��¼���ƣ����Ҳ���λ��
                {
                    L->r[j+increment] = L->r[j];
                }
                L->r[j] = L->r[0]; // �ҵ�λ�ò���
            }
}

/* ������ */
void HeapSort(SqList * L)
{
    int i;
    for (i = L->length/2; i > 0; i--) // ��L�е�r������һ���󶥶�, ����HeapAdjust()���ǹ����󶥶Ѻ���
        HeapAdjust(L, i, L->length);

    for (i = L->length; i > 1; i--)
    {
        swap(L, 1, i);         // ���Ѷ���¼�͵�ǰδ�����������е����һ����¼����
        HeapAdjust(L, 1, i-1); // ���µ���Ϊ��Ѷ�
    }
}

/* �ѵ������� */
void HeapAdjust(SqList * L, int s, int m)
{
    int temp, j;
    temp = L->r[s];
    for (j = s * 2; j <= m; j *= 2)
    {
        if (j < m && L->r[j] < L->r[j+1]) // j�����Һ��ӱȽϴ��ֵ�ĺ��ӵ��±�
            j++;
        if (temp >= L->r[j])              // ��˫�״������Һ��ӣ�����Ҫ�Ķ�������ѭ��
            break;
        L->r[s] = L->r[j];                // �Ȱѽϴ�ĺ��ӵ�ֵ��ֵ��˫��
        s = j;
    }
    L->r[j] = temp;
}

/* �鲢����(�ݹ�ʵ��) */
void MergeSort(SqList * L)
{
    MSort(L->r, L->r, 1, L->length);
}

/* ��SR[s..t]�鲢����ΪTR1[s..t] */
void MSort(int SR[], int TR1[], int s, int t)
{
    int m;
    int TR2[MAXSIZE+1];
    if (s == t)
        TR1[s] = SR[s];
    else
    {
        m = (s + t) / 2;          // ��SR[]ƽ��ΪSR[s..m]��SR[m+1..t]
        MSort(SR, TR2, s, m);     // �ݹ齫SR[s..m]�鲢Ϊ�����TR2[s..m]
        MSort(SR, TR2, m+1, t);   // �ݹ齫SR[m+1..t]�鲢Ϊ�����TR2[m+1..t]
        Merge(TR2, TR1, s, m, t); // ��TR2[s..m]��TR2[m+1..t]�鲢��TR1[s..t]
    }
}

/* �������SR[i..m]��TR[m+1..n]�鲢Ϊ�����TR[i..n] */
void Merge(int SR[], int TR[], int i, int m, int n)
{
    int j, k, l;
    for (k = i, j = m+1; i < m && j <= n; k++)
    {
        if (SR[i] < SR[j])  // ��SR�м�¼��С����鲢��TR
            TR[k] = SR[i++];
        else
            TR[k] = SR[j++];
        if (i <= m)
            for (l = 0; l <= m-i; l++)
                TR[k+l] = SR[i+l]; // ��ʣ���SR[i..m]���Ƶ�TR
        if (j <= n)
            for (l = 0; l <= n-j; l++)
                TR[k+l] = SR[j+l]; // ��ʣ���SR[j..n]���Ƶ�TR
    }
}

/* �鲢����(�ǵݹ�ʵ��) */
void MergeSort2(SqList* L)
{
    int k;
    int * TR;
    TR = (int *) malloc(sizeof(int) * L->length); // ������������ڴ�ռ�
    k = 1;
    while (k < L->length)
    {
        MergePass(L->r, TR, k, L->length);
        k *= 2; // �����г��ȼӱ�
        MergePass(TR, L->r, k, L->length);
        k *= 2; // �����г��ȼӱ�
    }
}

void MergePass(int SR[], int TR[], int s, int n)
{
    int i = 1;
    int j;
    while (i <= n - 2*s + 1)
    {
        Merge(SR, TR, i, i+s-1, i+2*s-1); // �����鲢
        i = i+2*s;
    }
    if (i < n-s+1) // �鲢�����������
        Merge(SR, TR, i, i+s-1, n);
    else           // �����ֻʣ�µ���������
        for (j = i; j <= n; j++)
            TR[j] = SR[j];
}

/* ��˳���L���������� */
void QuickSort(SqList * L)
{
    QSort(L, 1, L->length);
}

/* ��˳���L�е�������L->r[low...high]���������� */
void QSort(SqList * L, int low, int high)
{
    int pivot;
    if ((high - low) > MAX_LRNGTH_INSERT_SORT)
    {
        pivot = Partition(L, low, high); // ��L->r[low...high]һ��Ϊ���������׼ֵpivot
        QSort(L, low, pivot-1);          // �Ե��ӱ�ݹ�����
        low = pivot + 1;                 // β�ݹ�
    }
    else
        InsertSort(L);
}

/* ����˳���L���ӱ�ļ�¼��ʹ��׼ֵ��¼��λ��������������λ�ã���ʱ��֮ǰ(��)�ļ�¼������(С)���� */
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
    pivotkey = L->r[low]; // ���ӱ�ĵ�һ����¼����׼ֵ
    while (low < high)    // �ӱ�����˽������м�ɨ��
    {
        while (low < high && L->r[high] >= pivotkey)
            high--;
        swap(L, low, high);
        while (low < high && L->r[low] <= pivotkey)
            low++;
        swap(L, low, high;)
    }
    return low; // ���ػ�׼ֵ������λ��
}

/* ������������Ż� */
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
    pivotkey = L->r[low]; // ���ӱ�ĵ�һ����¼����׼ֵ
    L->r[0] = pivotkey;   //����׼ֵ���ݵ�L->r[0]
    while (low < high)    // �ӱ�����˽������м�ɨ��
    {
        while (low < high && L->r[high] >= pivotkey)
            high--;
        L->r[low] = L->r[high]; // �����滻�����ǽ����ķ�ʽ���в���
        while (low < high && L->r[low] <= pivotkey)
            low++;
        L->r[high] = L->r[low]; // �����滻�����ǽ����ķ�ʽ���в���
    }
    L->r[low] = L->r[0];        // ����׼ֵ�滻��L->r[low];
    return low;                 // ���ػ�׼ֵ������λ��
}