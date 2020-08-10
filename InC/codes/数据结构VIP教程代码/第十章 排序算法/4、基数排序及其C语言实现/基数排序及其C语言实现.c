#include <stdio.h>
#include <stdlib.h>
#define MAX_NUM_OF_KEY 8//构成关键字的组成部分的最大个数
#define RADIX 10        //基数，例如关键字是数字，无疑由0~9组成，基数就是10；如果关键字是字符串（字母组成），基数就是 26
#define MAX_SPACE 10000
//静态链表的结点结构
typedef struct{
    int data;//存储的关键字
    int keys[MAX_NUM_OF_KEY];//存储关键字的数组（此时是一位一位的存储在数组中）
    int next;//做指针用，用于是静态链表，所以每个结点中存储着下一个结点所在数组中的位置下标
}SLCell;
//静态链表结构
typedef struct{
    SLCell r[MAX_SPACE];//静态链表的可利用空间，其中r[0]为头结点
    int keynum;//当前所有的关键字中最大的关键字所包含的位数，例如最大关键字是百，说明所有keynum=3
    int recnum;//静态链表的当前长度
} SLList;

typedef int  ArrType[RADIX];//指针数组，用于记录各子序列的首尾位置
//排序的分配算法，i表示按照分配的位次（是个位，十位还是百位），f表示各子序列中第一个记录和最后一个记录的位置
void Distribute(SLCell *r,int i,ArrType f,ArrType e){
    //初始化指针数组
    for (int j=0; j<RADIX; j++) {
        f[j]=0;
    }
    //遍历各个关键字
    for (int p=r[0].next; p; p=r[p].next) {
        int j=r[p].keys[i];//取出每个关键字的第 i 位，由于采用的是最低位优先法，所以，例如，第 1 位指的就是每个关键字的个位
        if (!f[j]) {//如果只想该位数字的指针不存在，说明这是第一个关键字，直接记录该关键字的位置即可
            f[j]=p;
        }else{//如果存在，说明之前已经有同该关键字相同位的记录，所以需要将其进行连接，将最后一个相同的关键字的next指针指向该关键字所在的位置，同时最后移动尾指针的位置。
            r[e[j]].next=p;
        }
        e[j]=p;//移动尾指针的位置
    }
}
//基数排序的收集算法，即重新设置链表中各结点的尾指针
void Collect(SLCell *r,int i,ArrType f,ArrType e){
    int j;
    //从 0 开始遍历，查找头指针不为空的情况，为空表明该位没有该类型的关键字
    for (j=0;!f[j]; j++);
    r[0].next=f[j];//重新设置头结点
    int t=e[j];//找到尾指针的位置
    while (j<RADIX) {
        for (j++; j<RADIX; j++) {
            if (f[j]) {
                r[t].next=f[j];//重新连接下一个位次的首个关键字
                t=e[j];//t代表下一个位次的尾指针所在的位置
            }
        }
    }
    r[t].next=0;//0表示链表结束
}
void RadixSort(SLList *L){
    ArrType f,e;
    //根据记录中所包含的关键字的最大位数，一位一位的进行分配与收集
    for (int i=0; i<L->keynum; i++) {
        //秉着先分配后收集的顺序
        Distribute(L->r, i, f, e);
        Collect(L->r, i, f, e);
    }
}
//创建静态链表
void creatList(SLList * L){
    int key,i=1,j;
    scanf("%d",&key);
    while (key!=-1) {
        L->r[i].data=key;
        for (j=0; j<=L->keynum; j++) {
            L->r[i].keys[j]=key%10;
            key/=10;
        }
        L->r[i-1].next=i;
        i++;
        scanf("%d",&key);
    }
    L->recnum=i-1;
    L->r[L->recnum].next=0;
}
//输出静态链表
void print(SLList*L){
    for (int p=L->r[0].next; p; p=L->r[p].next) {
        printf("%d ",L->r[p].data);
    }
    printf("\n");
}
int main(int argc, const char * argv[]) {
    SLList *L=(SLList*)malloc(sizeof(SLList));
    L->keynum=3;
    L->recnum=0;
    creatList(L);//创建静态链表
    printf("排序前：");
    print(L);

    RadixSort(L);//对静态链表中的记录进行基数排序

    printf("排序后：");
    print(L);
    return 0;
}
