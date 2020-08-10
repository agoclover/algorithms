#include <stdio.h>
typedef enum{false,true} bool;

typedef struct {
    int x;
    int y;
    char mess;
    int value;
}check;

bool canUsed(int x,int y,char data,int n,int m){
    if (x>=0 && x<n && y>=0 && y<m && data!='#') {
        return true;
    }
    return false;
}
void createMaze(int n,int m,check a[][110],int *entryx,int *entryy,int *exitx,int *exity){
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            scanf("%c",&a[i][j].mess);
            a[i][j].x=i;
            a[i][j].y=j;
            if (a[i][j].mess=='S') {
                *entryx=i;
                *entryy=j;
            }else if(a[i][j].mess=='E'){
                *exitx=i;
                *exity=j;
            }
        }
        getchar();
    }
}
//使用的广度优先搜索的思想，采用队列的数据结构实现
void findRoad(check a[][110],int top,int rear,check queue[],int *value,int entryx,int entryy,int n,int m){
    //首先将入口顶点入队
    check data;
    data.x=entryx;
    data.y=entryy;
    a[entryx][entryy].mess='#';
    data.mess=a[entryx][entryy].mess;
    data.value=0;
    queue[rear]=data;
    bool success=false;
    rear++;
    //队列不满
    while (top!=rear) {
        //逐个出队
        check temp=queue[top];
        a[temp.x][temp.y].value=temp.value;
        top++;
        //对于出队的顶点判断是否是出口，首个判断为出口的顶点，其value值就是最短路径的长度
        if (temp.mess=='E') {
            *value=temp.value;
            printf("%d\n",temp.value);
            success=true;
            break;
        }
        //每次入队，判断其上、下、左、右的顶点是否符合条件，若符合，则入队，同时对其value值赋值为前一个顶点value+1，为了避免重复判断此顶点，对每个入队的顶点，设定其字符为‘#’
        if(canUsed(temp.x-1,temp.y,a[temp.x-1][temp.y].mess,n,m)){
            data.x=temp.x-1;
            data.y=temp.y;
            data.mess=a[temp.x-1][temp.y].mess;
            data.value=temp.value+1;
            queue[rear]=data;
            a[temp.x-1][temp.y].mess='#';
            rear++;
        }
        //右边
        if(canUsed(temp.x,temp.y+1,a[temp.x][temp.y+1].mess,n,m)){
            data.x=temp.x;
            data.y=temp.y+1;
            data.mess=a[temp.x][temp.y+1].mess;
            data.value=temp.value+1;
            queue[rear]=data;
            a[temp.x][temp.y+1].mess='#';
            rear++;
        }
        //下边
        if(canUsed(temp.x+1,temp.y,a[temp.x+1][temp.y].mess,n,m)){
            data.x=temp.x+1;
            data.y=temp.y;
            data.mess=a[temp.x+1][temp.y].mess;
            data.value=temp.value+1;
            queue[rear]=data;
            a[temp.x+1][temp.y].mess='#';
            rear++;
        }
        //左边
        if(canUsed(temp.x,temp.y-1,a[temp.x][temp.y-1].mess,n,m)){
            data.x=temp.x;
            data.y=temp.y-1;
            data.mess=a[temp.x][temp.y-1].mess;
            data.value=temp.value+1;
            queue[rear]=data;
            a[temp.x][temp.y-1].mess='#';
            rear++;
        }
    }
    //如果不成功，证明出口和入口之间没有通路
    if (success==false) {
        printf("-1\n");
    }
}
//用于输出最短路径时回溯过程中的判断
bool judgeValue(int x,int y,int n,int m){
    if (x>=0 && x<n && y>=0 && y<m ){
        return true;
    }
    return false;
}
//在输出时，由于最短路径中从入口开始，一直到出口，所经过的顶点的 value 值逐渐 +1，所以采用回溯法查找所有可能的最短路径
void displayRoad(check a[][110],int entryx,int entryy,int n,int m,int value){
    //设置静态数组，实现栈的作用
    static check stack[1000];
    static int top=-1;//栈的栈顶
    //对于每个当前的顶点，首先需要判断其是否符合最基本的要求，由于在前期二维数组中的通路都变成了‘#’，这里采用另一个关键字 ，value的值为主关键字进行搜索
    if (judgeValue(entryx, entryy, n, m)) {
        //回溯思想的实现用的是递归，所以需要设置一个出口，出口就是当查找到顶点的value值为最短路径的顶点数时，表明此时已经搜索在出口位置，此时就可以依次输出栈内存储的各个经过的顶点的坐标
        if (a[entryx][entryy].value==value) {
            for (int i=0; i<top; i++) {
                printf("(%d,%d) ",stack[i].x,stack[i].y);
            }
            printf("\n");
            return;
        }
        //从入口出发，判断当前点的上、下、左、右位置上的顶点是否符合要求：1、该顶点的坐标没有超出范围；2该顶点的value值是前一个顶点的value值+1，如果都符合，说明之前判断最短路径时就途径此顶点，将其入栈进行保存
        if (judgeValue(entryx+1, entryy, n, m) && a[entryx+1][entryy].value==a[entryx][entryy].value+1) {
            top++;
            stack[top]=a[entryx+1][entryy];
            displayRoad(a, entryx+1, entryy, n, m,value);
            //当运行至此，又两种情况：途径此顶点最终找到出口，并将最终结果输出，此时应将该顶点弹栈；该顶点的路径不是正确的，应弹栈。两种情况都应弹栈。
            top--;
        }
        if (judgeValue(entryx-1, entryy, n, m) && a[entryx-1][entryy].value==a[entryx][entryy].value+1) {
            top++;
            stack[top]=a[entryx-1][entryy];
            displayRoad(a, entryx-1, entryy, n, m,value);
            top--;
        }
        if (judgeValue(entryx, entryy+1, n, m) && a[entryx][entryy+1].value==a[entryx][entryy].value+1) {
            top++;
            stack[top]=a[entryx][entryy+1];
            displayRoad(a, entryx, entryy+1, n, m,value);
            top--;
        }
        if (judgeValue(entryx, entryy-1, n, m) && a[entryx][entryy-1].value==a[entryx][entryy].value+1) {
            top++;
            stack[top]=a[entryx][entryy-1];
            displayRoad(a, entryx, entryy-1, n, m,value);
            top--;
        }
    }
}
int main(int argc, const char * argv[]) {
    check a[110][110];
    check queue[100000];
    int top=0,rear=0;
    int n,m;
    int entryx = 0,entryy=0,exitx=0,exity=0;
    scanf("%d %d",&n,&m);
    getchar();
    //创建迷宫，并找到入口和出口的位置坐标
    createMaze(n,m,a,&entryx,&entryy,&exitx,&exity);
    //在迷宫中查找从入口到出口的最短路径，若有，输出最短路径的长度；反之，输出-1
    int value;
    findRoad(a,top,rear,queue,&value,entryx,entryy,n,m);
    //输出所有的最短路径
    displayRoad(a, entryx, entryy, n, m, value);
    return 0;
}
