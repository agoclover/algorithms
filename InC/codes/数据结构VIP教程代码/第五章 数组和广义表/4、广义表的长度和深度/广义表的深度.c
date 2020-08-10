#include <stdio.h>
#include <stdlib.h>

typedef struct GLNode{
    int tag;//标志域
    union{
        char atom;//原子结点的值域
        struct{
            struct GLNode * hp,*tp;
        }ptr;//子表结点的指针域，hp指向表头；tp指向表尾
    };
}*Glist,GNode;

Glist creatGlist(Glist C){
    //广义表C
    C=(Glist)malloc(sizeof(GNode));
    C->tag=1;
    //表头原子‘a’
    C->ptr.hp=(Glist)malloc(sizeof(GNode));
    C->ptr.hp->tag=0;
    C->ptr.hp->atom='a';
    //表尾子表（b,c,d）,是一个整体
    C->ptr.tp=(Glist)malloc(sizeof(GNode));
    C->ptr.tp->tag=1;
    C->ptr.tp->ptr.hp=(Glist)malloc(sizeof(GNode));
    C->ptr.tp->ptr.tp=NULL;
    //开始存放下一个数据元素（b,c,d）,表头为‘b’，表尾为（c,d）
    C->ptr.tp->ptr.hp->tag=1;
    C->ptr.tp->ptr.hp->ptr.hp=(Glist)malloc(sizeof(GNode));
    C->ptr.tp->ptr.hp->ptr.hp->tag=0;
    C->ptr.tp->ptr.hp->ptr.hp->atom='b';
    C->ptr.tp->ptr.hp->ptr.tp=(Glist)malloc(sizeof(GNode));
    //存放子表(c,d)，表头为c，表尾为d
    C->ptr.tp->ptr.hp->ptr.tp->tag=1;
    C->ptr.tp->ptr.hp->ptr.tp->ptr.hp=(Glist)malloc(sizeof(GNode));
    C->ptr.tp->ptr.hp->ptr.tp->ptr.hp->tag=0;
    C->ptr.tp->ptr.hp->ptr.tp->ptr.hp->atom='c';
    C->ptr.tp->ptr.hp->ptr.tp->ptr.tp=(Glist)malloc(sizeof(GNode));
    //存放表尾d
    C->ptr.tp->ptr.hp->ptr.tp->ptr.tp->tag=1;
    C->ptr.tp->ptr.hp->ptr.tp->ptr.tp->ptr.hp=(Glist)malloc(sizeof(GNode));
    C->ptr.tp->ptr.hp->ptr.tp->ptr.tp->ptr.hp->tag=0;
    C->ptr.tp->ptr.hp->ptr.tp->ptr.tp->ptr.hp->atom='d';
    C->ptr.tp->ptr.hp->ptr.tp->ptr.tp->ptr.tp=NULL;
    return C;
}
int GlistDepth(Glist C){
    //如果表C为空表时，直接返回长度1；
    if (!C) {
        return 1;
    }
    //如果表C为原子时，直接返回0；
    if (C->tag==0) {
        return 0;
    }
    int max=0;//设置表C的初始长度为0；
    for (Glist pp=C; pp; pp=pp->ptr.tp) {
        int dep=GlistDepth(pp->ptr.hp);
        if (dep>max) {
            max=dep;//每次找到表中遍历到深度最大的表，并用max记录
        }
    }
    //程序运行至此处，表明广义表不是空表，由于原子返回的是0，而实际长度是1，所以，此处要+1；
    return max+1;
}
int main(int argc, const char * argv[]) {
    Glist C=creatGlist(C);
    printf("广义表的深度为：%d",GlistDepth(C));
    return 0;
}
