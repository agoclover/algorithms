#include <stdio.h>
#include <stdlib.h>
#define TElemType char//宏定义，结点中数据域的类型
//枚举，Link为0，Thread为1
typedef enum {
    Link,
    Thread
}PointerTag;
//结点结构构造
typedef struct BiThrNode{
    TElemType data;//数据域
    struct BiThrNode* lchild,*rchild;//左孩子，右孩子指针域
    PointerTag Ltag,Rtag;//标志域，枚举类型
}BiThrNode,*BiThrTree;

BiThrTree pre=NULL;

//采用前序初始化二叉树
//中序和后序只需改变赋值语句的位置即可
void CreateTree(BiThrTree * tree){
    char data;
    scanf("%c",&data);
    if (data!='#'){
        if (!((*tree)=(BiThrNode*)malloc(sizeof(BiThrNode)))){
            printf("申请结点空间失败");
            return;
        }else{
            (*tree)->data=data;//采用前序遍历方式初始化二叉树
            CreateTree(&((*tree)->lchild));//初始化左子树
            CreateTree(&((*tree)->rchild));//初始化右子树
        }
    }else{
        *tree=NULL;
    }
}
//中序对二叉树进行线索化
void InThreading(BiThrTree p){
    //如果当前结点存在
    if (p) {
        InThreading(p->lchild);//递归当前结点的左子树，进行线索化
        //如果当前结点没有左孩子，左标志位设为1，左指针域指向上一结点 pre
        if (!p->lchild) {
            p->Ltag=Thread;
            p->lchild=pre;
        }
        //如果 pre 没有右孩子，右标志位设为 1，右指针域指向当前结点。
        if (pre&&!pre->rchild) {
            pre->Rtag=Thread;
            pre->rchild=p;
        }
        pre=p;//pre指向当前结点
        InThreading(p->rchild);//递归右子树进行线索化
    }
}
//建立双向线索链表
void InOrderThread_Head(BiThrTree *h, BiThrTree t)
{
    //初始化头结点
    (*h) = (BiThrTree)malloc(sizeof(BiThrNode));
    if((*h) == NULL){
        printf("申请内存失败");
        return ;
    }
    (*h)->rchild = *h;
    (*h)->Rtag = Link;
    //如果树本身是空树
    if(!t){
        (*h)->lchild = *h;
        (*h)->Ltag = Link;
    }
    else{
        pre = *h;//pre指向头结点
        (*h)->lchild = t;//头结点左孩子设为树根结点
        (*h)->Ltag = Link;
        InThreading(t);//线索化二叉树，pre结点作为全局变量，线索化结束后，pre结点指向中序序列中最后一个结点
        pre->rchild = *h;
        pre->Rtag = Thread;
        (*h)->rchild = pre;
    }
}
//中序正向遍历双向线索二叉树
void InOrderThraverse_Thr(BiThrTree h)
{
    BiThrTree p;
    p = h->lchild;           //p指向根结点
    while(p != h)
    {
        while(p->Ltag == Link)   //当ltag = 0时循环到中序序列的第一个结点
        {
            p = p->lchild;
        }
        printf("%c ", p->data);  //显示结点数据，可以更改为其他对结点的操作
        while(p->Rtag == Thread && p->rchild != h)
        {
            p = p->rchild;
            printf("%c ", p->data);
        }

        p = p->rchild;           //p进入其右子树
    }
}
int main() {
    BiThrTree t;
    BiThrTree h;
    printf("输入前序二叉树:\n");
    CreateTree(&t);
    InOrderThread_Head(&h, t);
    printf("输出中序序列:\n");
    InOrderThraverse_Thr(h);
    return 0;
}
