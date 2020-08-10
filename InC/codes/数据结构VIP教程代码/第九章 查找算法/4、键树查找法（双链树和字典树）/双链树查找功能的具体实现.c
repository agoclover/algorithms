#include <stdio.h>
typedef enum{LEFT,BRANCH}NodeKind;//定义结点的类型，是叶子结点还是其他类型的结点
typedef  struct {
    char a[20];//存储关键字的数组
    int num;//关键字长度
}KeysType;
//定时结点结构
typedef struct DLTNode{
    char symbol;//结点中存储的数据
    struct DLTNode *next;//指向兄弟结点的指针
    NodeKind *kind;//结点类型
    union{//其中两种指针类型每个结点二选一
        struct DLTNode* first;//孩子结点
        struct DLTNode* infoptr;//叶子结点特有的指针
    };
}*DLTree;
//查找函数，如果查找成功，返回该关键字的首地址，反则返回NULL。T 为用孩子兄弟表示法表示的键树，K为被查找的关键字。
DLTree SearchChar(DLTree T, KeysType k){
    int i = 0;
    DLTree p = T->first;//首先令指针 P 指向根结点下的含有数据的孩子结点
    //如果 p 指针存在，且关键字中比对的位数小于总位数时，就继续比对
    while (p && i < k.num){
        //如果比对成功，开始下一位的比对
        if (k.a[i] == p->symbol){
            i++;
            p = p->first;
        }
        //如果该位比对失败，则找该结点的兄弟结点继续比对
        else{
            p = p->next;
        }
    }
    //比对完成后，如果比对成功，最终 p 指针会指向该关键字的叶子结点 $，通过其自有的 infoptr 指针找到该关键字。
    if ( i == k.num){
        return p->infoptr;
    }
    else{
        return NULL;
    }
}
