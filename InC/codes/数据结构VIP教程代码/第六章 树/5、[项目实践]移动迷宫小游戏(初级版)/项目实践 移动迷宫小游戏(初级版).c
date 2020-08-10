#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef enum {false,true} bool;
//迷宫本身是一个8行10列的矩形
int ROWS=8;
int COLS=10;
//初始化迷宫，随机设置迷宫出入口，同时在迷宫中随机设置可行道路。
void mazeGenerator(char [][COLS],int *,int *,int *,int *);
//使用回溯法从入口处不断地尝试找到出口的路径
void mazeTraversal(char maze[ROWS][COLS],int row,int col,int entryRow,int entryCol,int exitrow,int exitcol);
//迷宫的输出函数
void printMaze(const char[][COLS]);
//判断每一次移动是否有效
bool validMove(const char [][COLS],int,int);

int main()
{
    printf("*********移动迷宫小项目（数据结构就该这么学）*********\n");
    char maze[ROWS][COLS];
    int xStart,yStart,x,y;
    srand(time(0));//种下随机种子数，每次运行种下不同的种子，后序通过rand()函数获得的随机数就不同。
    //通过一个嵌套循环，先将迷宫中各个地方设置为死路(‘#’表示为墙，表示此处不可通过)
    for(int loop=0;loop<ROWS;++loop ){
        for(int loop2=0;loop2<COLS;++loop2 ){
            maze[loop][loop2]='#';
        }
    }
    //初始化迷宫，即在迷宫中随机设置出口、入口和中间的道路，用‘0’表示。通过此函数，可同时得到入口的坐标
    mazeGenerator(maze,&xStart,&yStart,&x,&y);

    printf("迷宫入口位置坐标为(%d,%d);出口位置坐标为：(%d，%d);\n",xStart+1,yStart+1,x+1,y+1);
    printf("迷宫设置如下（‘#’表示墙，‘0’表示通路）：\n");
    printMaze(maze);//输出一个初始化好的迷宫
    //使用回溯法，通过不断地进行尝试，试图找到一条通往出口的路。
    mazeTraversal(maze,xStart,yStart,xStart,yStart,x,y);
}
//由于迷宫整体布局为矩形，有四条边，在初始化迷宫的出口和入口时，随机选择不同的两条边作为设置出口和入口的边
void mazeGenerator(char maze[][COLS],int *xPtr,int *yPtr,int *exitx,int *exity){
    int a,x,y,entry,exit;
    do {
        entry=rand()%4;
        exit=rand()%4;
    }while(entry==exit);
    // 确定入口位置，0 代表选择的为左侧的边，1 代表为上边，2代表为右侧的边，3 代表为下边
    if(entry==0){
        *xPtr=1+rand()%(ROWS-2);
        *yPtr=0;
        maze[*xPtr][*yPtr]='0';
    }else if(entry==1){
        *xPtr=0;
        *yPtr=1+rand()%(COLS-2);
        maze[*xPtr][*yPtr]='0';
    }else if(entry==2){
        *xPtr=1+rand()%(ROWS-2);
        *yPtr=COLS-1;
        maze[*xPtr][*yPtr]='0';
    }else{
        *xPtr=ROWS-1;
        *yPtr=1+rand()%(COLS-2);
        maze[*xPtr][*yPtr]='0';
    }
    //确定出口位置
    if(exit==0){
        a=1+rand()%(ROWS-2);
        *exitx=a;
        *exity=0;
        maze[a][0]='0';}
    else if(exit==1){
        a=1+rand()%(COLS-2);
        *exitx=0;
        *exity=a;
        maze[0][a]='0';}
    else if(exit==2){
        a=1+rand()%(ROWS-2);
        *exitx=a;
        *exity=COLS-1;
        maze[a][COLS-1]='0';}
    else{
        a=1+rand()%(COLS-2);
        *exitx=ROWS-1;
        *exity=a;
        maze[ROWS-1][a]='0';
    }
    //在迷宫中央设置多出不同的随机通路
    for(int loop=1;loop<(ROWS-2)*(COLS-2);++loop) {
        x=1+rand()%(ROWS-2);
        y=1+rand()%(COLS-2);
        maze[x][y]='0';}
}

void mazeTraversal(char maze[ROWS][COLS],int row,int col,int entryRow,int entryCol,int exitrow,int exitcol){
    //由于从入口处进入，为了区分走过的通路和没走过的通路，将走过的通路设置为‘x’，
    maze[row][col]='x';
    static bool judge=false;//设置一个判断变量，判断在入口位置是否有通路存在。
    static int succ=0;//用于统计从入口到出口的可行通路的条数
    if (row==exitrow && col==exitcol) {
        printf("成功走出迷宫，道路图如下：\n");
        printMaze(maze);
        succ++;
        return;
    }
    //判断当前位置的下方是否为通路
    if (validMove(maze, row+1, col)) {
        judge=true;//证明起码有路存在，下面证明是否有可通往出口的路
        mazeTraversal(maze, row+1, col,entryRow,entryCol,exitrow,exitcol);//以下方的位置为起点继续尝试
    }
    //判断当前位置的右侧是否为通路
    if (validMove(maze, row, col+1)) {
        judge=true;
        mazeTraversal(maze, row, col+1,entryRow,entryCol,exitrow,exitcol);
    }
    //判断当前位置的上方是否为通路
    if (validMove(maze, row-1, col)) {
        judge=true;
        mazeTraversal(maze, row-1, col,entryRow,entryCol,exitrow,exitcol);
    }
    //判断当前位置的左侧是否为通路
    if (validMove(maze, row, col-1)) {
        judge=true;
        mazeTraversal(maze, row, col-1,entryRow,entryCol,exitrow,exitcol);
    }
    //如果judge仍为假，说明在入口处全部被墙包围，无路可走
    if (judge==false) {
        printf("入口被封死，根本无路可走！\n");
        printMaze(maze);
    }
    //如果judge为真，但是succ值为0，且最终又回到了入口的位置，证明所有的尝试工作都已完成，但是没有发现通往出口的路
    else if(judge==true && row==entryRow && col==entryCol && succ==0){
        printf("尝试了所有道路，出口和入口之间没有通路！\n");
        printMaze(maze);
    }
}
//有效移动，即证明该位置处于整个迷宫的矩形范围内，且该位置是通路，不是墙，也从未走过
bool validMove(const char maze[][COLS],int r,int c){
    return(r>=0&&r<=ROWS-1&&c>=0&&c<=COLS-1&&maze[r][c]!='#'&& maze[r][c]!='x');
}
//输出迷宫
void printMaze(const char maze[][COLS] ){
    for(int x=0;x<ROWS;++x){
        for(int y=0;y<COLS;++y){
            printf("%c ",maze[x][y]);
        }
        printf("\n");
    }
    printf("\n");
}
