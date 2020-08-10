#include <stdio.h>
#include <stdlib.h>
#define SIZE 15
typedef struct {
    int key;   //关键字的值
}SLNode;
typedef struct {
    SLNode r[SIZE];//存储记录的数组
    int length;//记录数组中记录的数量
}SqList;
//希尔排序的实现函数，其中 dk 表示增值量
void ShellInsert(SqList * L,int dk){
    //从 dk+1 个记录起，每间隔 dk 个记录就调取一个进行直接插入排序算法
    for (int i=dk+1; i<=L->length; i++) {
        //如果新调取的关键字的值，比子表中最后一个记录的关键字小，说明需要将该值调换位置
        if (L->r[i].key<L->r[i-dk].key) {
            int j;
            //记录表中，使用位置下标为 0 的空间存储需要调换位置的记录的值
            L->r[0]=L->r[i];
            //做直接插入排序，如果下标为 0 的关键字比下标为 j 的关键字小，则向后一行下标为 j 的值，为新插入的记录腾出空间。
            for (j=i-dk; j>0 && (L->r[0].key<L->r[j].key); j-=dk){
                L->r[j+dk]=L->r[j];
            }
            //跳出循环后，将新的记录值插入到腾出的空间中，即完成了一次直接插入排序
            L->r[j+dk]=L->r[0];
        }
    }
}
//希尔排序，通过调用不同的增量值（记录），实现对多个子表分别进行直接插入排序
void ShellSort(SqList * L,int dlta[],int t){
    for (int k=0; k<t; k++) {
        ShellInsert(L, dlta[k]);
    }
}
int main(int argc, const char * argv[]) {
    int dlta[3]={5,3,1};//用数组来存储增量值，例如 5 代表每间隔5个记录组成一个子表，1表示每间隔一个，也就是最后一次对整张表的直接插入排序
    SqList *L=(SqList*)malloc(sizeof(SqList));
    L->r[1].key=49;
    L->r[2].key=38;
    L->r[3].key=64;
    L->r[4].key=97;
    L->r[5].key=76;
    L->r[6].key=13;
    L->r[7].key=27;
    L->r[8].key=49;
    L->r[9].key=55;
    L->r[10].key=4;
    L->length=10;
    //调用希尔排序算法
    ShellSort(L, dlta, 3);
    //输出语句
    for (int i=1; i<=10; i++) {
        printf("%d ",L->r[i].key);
    }
    return 0;
}
