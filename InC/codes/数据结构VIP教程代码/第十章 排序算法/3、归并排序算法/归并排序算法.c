#include <stdio.h>
#include <stdlib.h>
#define  MAX 8
typedef struct{
    int key;
}SqNode;
typedef struct{
    SqNode r[MAX];
    int length;
}SqList;
//SR中的记录分成两部分：下标从 i 至 m 有序，从 m+1 至 n 也有序，此函数的功能是合二为一至TR数组中，使整个记录表有序
void Merge(SqNode SR[],SqNode TR[],int i,int m,int n){
    int j,k;
    //将SR数组中的两部分记录按照从小到大的顺序添加至TR数组中
    for (j=m+1,k=i; i<=m && j<=n; k++) {
        if (SR[i].key<SR[j].key) {
            TR[k]=SR[i++];
        }else{
            TR[k]=SR[j++];
        }
    }
    //将剩余的比目前TR数组中都大的记录复制到TR数组的最后位置
    while(i<=m) {
        TR[k++]=SR[i++];
    }
    while (j<=n) {
        TR[k++]=SR[j++];
    }
}

void MSort(SqNode SR[],SqNode TR1[],int s,int t){
    SqNode TR2[MAX];
    //递归的出口
    if (s==t) {
        TR1[s]=SR[s];
    }else{
        int m=(s+t)/2;//每次递归将记录表中记录平分，直至每个记录各成一张表
        MSort(SR, TR2, s, m);//将分开的前半部分表中的记录进行排序
        MSort(SR,TR2, m+1, t);//将后半部分表中的记录进行归并排序
        Merge(TR2,TR1,s,m, t);//最后将前半部分和后半部分中的记录统一进行排序
    }
}
//归并排序
void MergeSort(SqList *L){
    MSort(L->r,L->r,1,L->length);
}

int main() {
    SqList * L=(SqList*)malloc(sizeof(SqList));
    L->length=7;
    L->r[1].key=49;
    L->r[2].key=38;
    L->r[3].key=65;
    L->r[4].key=97;
    L->r[5].key=76;
    L->r[6].key=13;
    L->r[7].key=27;
    MergeSort(L);
    for (int i=1; i<=L->length; i++) {
        printf("%d ",L->r[i].key);
    }
    return 0;
}
