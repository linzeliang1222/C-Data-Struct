#include <stdio.h>
#include <windows.h>
#include <string.h>

struct Stuff
{
    char number[10];
    char name[10];
    char sex[8];
    char birth[10];
    char degree[20];
    char business[20];
    char phone[15];
    char place[50];
    char con[50];
    struct Stuff * next;
};

char Menu(void);                                       // �˵�
struct Stuff * App(struct Stuff * head);               // ���
struct Stuff * Ser(struct Stuff * head);               // ����
struct Stuff * Del(struct Stuff * head, char n[10]);   // ɾ��
void Chn(struct Stuff * head, char n[10]);             // ����
void Scpy(char * p, char * q);                         // ���������ڽ���Ա������Ϣ
void Sort(struct Stuff * head);                        // ����
void Prf(struct Stuff * head);                         // �����Ϣ
void Fre(struct Stuff * head);                         // �ͷ��ڴ�ռ�
int Sel(char ch, struct Stuff * p, struct Stuff * q);  // �ж����򼰹ؼ���ר�ú���

int i = 1; //����ȫ�ֱ���, ʵ��ʵʱԱ������ͳ��

int main(void)
{
    char n[10];
    struct Stuff * head = NULL;   // ����ͷָ�붨��
    while (1)
    {
        switch(Menu())
        {
            case '1':
                printf("������Ա����Ϣ, ֱ������'#'����:\n");
                head = App(head);
                break;
            case '2':
                Sort(head);
                break;
            case '3':
                head = Ser(head);
                break;
            case '4':
                printf("Ա������Ϣ����:\n");
                Prf(head);
                break;
            case '5':
                printf("������Ա�����: ");
                scanf("%s", n);
                Chn(head, n);
                break;
            case '6':
                printf("������Ա�����: ");
                scanf("%s", n);
                head = Del(head, n);
                break;
            case '0':
                printf("��ӭ�´ι��٣�\n");
                exit(0);
                break;
            default:
                printf("�������, ���������룡\n");
                break;
        }
        fflush(stdin); // ��ջ�����
        printf("�����������...");
        getchar();
        system("cls"); // ����
    }
    Fre(head); //�ͷ��ڴ�ռ�

    return 0;
}

/* ��ʾ�˵� */
char Menu(void)
{
    char ch;
    printf("--------------------��ѡ��--------------------\n");
    printf("--              1.���Ա����Ϣ              --\n");
    printf("--              2.Ա����Ϣ����              --\n");
    printf("--              3.����Ա����Ϣ              --\n");
    printf("--              4.���Ա����Ϣ              --\n");
    printf("--              5.����Ա����Ϣ              --\n");
    printf("--              6.ɾ��Ա����Ϣ              --\n");
    printf("--              0.   �˳�                   --\n");
    printf("----------------------------------------------\n");
    scanf("%c", &ch);
    return ch;
}

/* ��ӳ�Ա  ���뺯��: ����ͷָ��   ���غ���: ����ͷָ�� */
struct Stuff * App(struct Stuff * head)
{
    struct Stuff * p = NULL, * q = head;
    while (i)
    {
        p = (struct Stuff *) malloc(sizeof(struct Stuff));   // ����ռ�
        if (p == NULL)
        {
            printf("�ڴ����ʧ�ܣ�\n");
            exit(1);
        }
        p->next = NULL; // ָ����Ϊ��
        printf("�������%d��Ա��:\n", i);
        printf("| ��� |  ����  | �Ա� |  ��������  |  ѧ��  |  ְ��  |      �绰      |     סַ     |\n");
        fflush(stdin);
        scanf("%s", p->number);
        if (!(strcmp(p->number, "#")))
        {
            free(p);
            break;
        }
        else
        {
            i++;
            scanf("%s%s%s%s%s%s%s", p->name, p->sex, p->birth, p->degree, p->business, p->phone, p->place);
            p->con[0] = '\0'; // ��ֹ�����жϳ������ֵ
            if (head == NULL)
                head = p;
            else
            {
                while (q->next != NULL)
                    q = q->next;
                q->next = p;
            }
            q = p; // β����������
        }
    }
    return head;
}

/* ���� �������: ͷָ�� */
void Sort(struct Stuff * head)
{
    char ch;
    struct Stuff * p, * q, * r;
    while (1)
    {
        printf("��ѡ����������: 1.��� 2.���� 3.�Ա� 4.�������� 5.ѧ�� 6.ְ�� 7.�绰 8.��ַ 0.�˳�\n");
        scanf("%c", &ch);
        if (ch == '0')
            break;
        if (ch < '1' || ch > '8')
        {
            printf("�������, ���������룡\n");
            continue;
        }
        p = head;
        while (p->next != NULL) // ѡ������
        {
            q = p->next;
            r = p;
            while (q != NULL)
            {
                if (Sel(ch, r, q)) // �����жϺ���
                    r = q;
                q = q->next;
            }
            if (r != p) // ��������
            {
                Scpy(r->number, p->number);
                Scpy(r->name, p->name);
                Scpy(r->sex, p->sex);
                Scpy(r->birth, p->birth);
                Scpy(r->degree, p->degree);
                Scpy(r->business, p->business);
                Scpy(r->phone, p->phone);
                Scpy(r->place, p->place);
            }
            p = p->next;
        }
        Prf(head); // ���
    }
}

/* �������� */
void Scpy(char * p, char * q)
{
    char c[50];
    strcpy(c, p);
    strcpy(p, q);
    strcpy(q, c);
}

/* �жϺ��� �������: 1Ϊ��, 0Ϊ�� */
int Sel(char ch, struct Stuff * p, struct Stuff * q)
{
    switch (ch)
    {
        case '1':
            return (strcmp(q->number, p->number) < 0 || strcmp(q->con, p->number) == 0); //���򼰲�������
        case '2':
            return (strcmp(q->name, p->name) < 0 || strcmp(q->con, p->name) == 0);
        case '3':
            return (strcmp(q->sex, p->sex) < 0 || strcmp(q->con, p->sex) == 0);
        case '4':
            return (strcmp(q->birth, p->birth) < 0 || strcmp(q->con, p->birth) == 0);
        case '5':
            return (strcmp(q->birth, p->birth) < 0 || strcmp(q->con, p->birth) == 0);
        case '6':
            return (strcmp(q->business, p->business) < 0 || strcmp(q->con, p->business) == 0);
        case '7':
            return (strcmp(q->phone, p->phone) < 0 || strcmp(q->con, p->phone) == 0);
        case '8':
            return (strcmp(q->place, p->place) < 0 || strcmp(q->con, p->place) == 0);
        default:
            exit(0);
    }
}

/* ���Һ��� */
struct Stuff * Ser(struct Stuff * head)
{
    struct Stuff * p = NULL, * q = NULL;
    struct Stuff a = {"\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0"}; // ��ֹ�ж�ʱ����
    int flag; // �����ж�
    char ch, sh;
    q = &a;
    while (1)
    {
        printf("������Ҫ���ҵ�����: 1.��� 2.���� 3.�Ա� 4.�������� 5.ѧ�� 6.ְ�� 7.�绰 8.סַ 0.�˳�\n");
        scanf("%c", &ch);
        if (ch == '0')
            break;
        if (ch < '1' || ch > '8')
        {
            printf("�������, ���������룡\n");
            continue;
        }
        fflush(stdin);
        printf("������: ");
        gets(q->con);
        p = head; //ָ���ͷ
        flag = 0;
        while (p != NULL)
        {
            if (ch, p, q)
            {
                printf("Ա����Ϣ����:\n");
                printf("| ��� |   ����   | �Ա� |  ��������  |   ѧ��   |   ְ��   |     �绰     |         סַ         |\n  %-8s%-11s%-6s%-15s%-11s%-10s%-15s%-s",
                    p->number, p->name, p->sex, p->birth, p->degree, p->business, p->phone, p->place);
                printf("�Ƿ���Ҫ: 1.���� 2.ɾ�� 3.����\n");
                scanf("%c", &sh);
                if (sh == '1')
                    Chn(head, p->number);        //���ø��ĺ���
                else if (sh == '2')
                    head = Del(head, p->number);  // ����ɾ������
                flag = 1;
                break;
            }
            p = p->next;
        }
        if (flag == 0)
            printf("û���ҵ���Ա������Ϣ��\n");
    }
    return head;
}

/* ���ĺ��� �������: n[10]ΪԱ����� */
void Chn(struct Stuff * head, char n[10])
{
    struct Stuff * p = head;
    int flag = 0;
    if (head == NULL)
        printf("δ�ҵ�Ա����Ϣ��\n");
    else
    {
        while (p != NULL)
        {
            if (!strcmp(p->number, n))
            {
                printf("�������µ���Ϣ:\n| ��� |  ����  | �Ա� |  ��������  |  ѧ��  |  ְ��  |     �绰     |      סַ      |\n");
                scanf("%s%s%s%s%s%s%s%s", p->number, p->name, p->sex, p->birth, p->degree, p->business, p->phone, p->place);
                printf("Ա������Ϣ����:\n");
                flag++;
                break;
            }
            p = p->next;
        }
        if (flag == 0)
            printf("δ�ҵ���Ա����Ϣ��\n");
    }
    Prf(head);
}

/* ɾ������ �������: nΪԱ���ı�� �������: ͷָ�� */
struct Stuff * Del(struct Stuff * head, char n[10])
{
    struct Stuff * p = NULL, * pr = NULL;
    int flag;
    p = head, pr = head;
    if (head == NULL)
        printf("δ�ҵ�Ա����Ϣ��\n");
    else
    {
        while (strcmp(p->number, n) && (p->next != NULL))
        {
            pr = p;
            p = p->next;
        }
        if (!strcmp(p->number, n))
        {
            if (p == head)
                head = p->next;
            else
                pr->next = p->next;
            free(p);
            printf("ɾ���ɹ���\n");
            i--;
        }
        else
            printf("δ�ҵ�Ա����Ϣ��\n");
    }
    Prf(head);
    return head;
}

/* ������� */
void Prf(struct Stuff * head)
{
    struct Stuff * p = head;
    int i = 1;
    while (p != NULL)
    {
        printf("%d.  %s  %s  %s  %s  %s  %s  %s  %s\n", i++, p->number, p->name, p->sex, p->birth, p->degree, p->business, p->phone, p->place);
        p = p->next;
    }
}

/* �ͷ��ڴ�ռ� */
void Fre(struct Stuff * head)
{
    struct Stuff * p = NULL;
    while (head != NULL)
    {
        p = head;
        head = head->next;
        free(p);
    }
}