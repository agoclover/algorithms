#include <stdio.h>
#include <stdlib.h>
struct queue
{
    int data[1000];
    int head;
    int tail;
};
struct stack
{
    int data[10];
    int top;
};
void showCard(struct queue *q,int *book,struct stack *s){
    int t=(*q).data[(*q).head]; //打出一张牌，即从队列 q 的队头取元素（此时还不往桌子的栈里放）
    //判断取出的这张牌是否会赢牌
    if(book[t]==0){ //若不赢牌，只需放到桌子上入栈即可
        (*q).head++;//由于此时牌已经打出，所以队列的队头需要前进
        (*s).top++;
        (*s).data[(*s).top]=t; //再把打出的牌放到桌上，即入栈
        book[t]=1; //标记桌上现在已经有牌面为t的牌
    }
    else{
        (*q).head++;//由于此时已经打出去一张牌，所以队头需要 +1
        (*q).data[(*q).tail]=t;//将打出的牌放到手中牌的最后（再入队）
        (*q).tail++;
        //把桌子上赢得的牌依次放到手中牌的最后（依次出栈在入队列的过程）
        while((*s).data[(*s).top]!=t){
            book[(*s).data[(*s).top]]=0;//取消对该牌号的标记
            (*q).data[(*q).tail]=(*s).data[(*s).top];//依次放入队尾
            (*q).tail++;
            (*s).top--;
        }
        //最后别忘了将最后一张相等的牌取出放入队列
        book[(*s).data[(*s).top]]=0;
        (*q).data[(*q).tail]=(*s).data[(*s).top];
        (*q).tail++;
        (*s).top--;
    }
}

int main()
{
    struct queue q1,q2;//两个队列，分别模拟两个人，假设分别为小王和小李
    struct stack s;//栈，模拟桌子
    int book[14];//为了便于判断桌子上的牌是否有相同的，增加一个数组用于判断
    int i;
    //初始化队列
    q1.head=0; q1.tail=0;
    q2.head=0; q2.tail=0;
    //初始化栈
    s.top=-1;
    //初始化用来标记的数组
    for(i=0;i<=13;i++)
        book[i]=0;
    //假设初期每个人手中仅有 6 张牌，每个人拥有的牌都是随机的，但都在 1-13 之间
    for(i=1;i<=6;i++){
        q1.data[q1.tail]=rand()%13+1;
        q1.tail++;
    }
    for(i=1;i<=6;i++){
        q2.data[q2.tail]=rand()%13+1;
        q2.tail++;
    }
    //仅当其中一个人没有牌时，游戏结束
    while(q1.head<q1.tail && q2.head<q2.tail ){         showCard(&q2, book, &s);//小李出牌
        showCard(&q1, book, &s);//小王出牌
    }
    //游戏结束时，输出最后的赢家以及手中剩余的牌数
    if(q2.head==q2.tail){
        printf("小李赢\n");
        printf("手中还有：%d 张牌",q1.tail-q1.head);
    }
    else{
        printf("小王赢\n");
        printf("手中还有：%d 张牌",q2.tail-q2.head);
    }
    return 0;
}
