#include <stdio.h>
#define MAX_VERtEX_NUM 1000              //顶点的最大个数
#define VRType int                          //表示弧的权值的类型
#define VertexType char                     //图中顶点的数据类型
#define INFINITY 65535
typedef enum{false,true} bool;
typedef struct {
    VertexType vexs[MAX_VERtEX_NUM];        //存储图中顶点数据
    VRType arcs[MAX_VERtEX_NUM][MAX_VERtEX_NUM];                         //二维数组，记录顶点之间的关系
    int vexnum,arcnum;                      //记录图的顶点数和弧（边）数
}MGraph;
typedef int PathMatrix[MAX_VERtEX_NUM];     //用于存储最短路径中经过的顶点的下标
typedef int ShortPathTable[MAX_VERtEX_NUM]; //用于存储各个最短路径的权值和

//迪杰斯特拉算法，v0表示有向网中起始点所在数组中的下标
void ShortestPath_Dijkstra(MGraph G,int v0,PathMatrix *p,ShortPathTable *D){
    int final[MAX_VERtEX_NUM];//用于存储各顶点是否已经确定最短路径的数组
    //对各数组进行初始化
    for (int v=0; v<G.vexnum; v++) {
        final[v]=0;
        (*D)[v]=G.arcs[v0][v];
        (*p)[v]=0;
    }
    //以起点为下标的顶点为起始点，所以不用再判断
    (*D)[v0]=0;
    final[v0]=1;
    int k = 0;
    for (int i=0; i<G.vexnum; i++) {
        int min=INFINITY;
        //选择到各顶点权值最小的顶点，即为本次能确定最短路径的顶点
        for (int w=0; w<G.vexnum; w++) {
            if (!final[w]) {
                if ((*D)[w]<min) {
                    k=w;
                    min=(*D)[w];
                }
            }
        }
        //设置该顶点的标志位为1，避免下次重复判断
        final[k]=1;
        //对从起点到各顶点的权值进行更新
        for (int w=0; w<G.vexnum; w++) {
            if (!final[w]&&(min+G.arcs[k][w]<(*D)[w])) {
                (*D)[w]=min+G.arcs[k][w];
                (*p)[w]=k;//记录各个最短路径上存在的顶点
            }
        }
    }
}
//在将二维数组转化为图的过程中，需要判断当前的点是否越界或者是否为通路
bool canUsed(int i,int j,int n,int m,char a[][110]){
    if (a[i][j]!='#' && i>=0 && i<n && j>=0 && j<m) {
        return true;
    }
    return false;
}
int main(){
    char a[110][110];
    int n,m;
    scanf("%d %d",&n,&m);
    getchar();
    MGraph G;
    G.vexnum=0;
    G.arcnum=0;
    //记录入口在图的顶点数组中的位置下标
    int start =0;
    //记录出口在图的顶点数组中的位置下标
    int exit=0;
    //初始化记录图的边的二维数组，假设各个边的长度为无穷大，即两顶点之间没有边
    for (int i=0; i<n*m; i++) {
        for (int j=0; j<n*m; j++) {
            G.arcs[i][j]=INFINITY;
        }
    }
    //输入二维数组，同时记录入口和出口的位置
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            scanf("%c",&a[i][j]);
            G.vexs[i*m+j]=a[i][j];
            G.vexnum++;
            if (a[i]
                [j]=='S') {
                start=i*m+j;
            }else if(a[i][j]=='E'){
                exit=i*m+j;
            }
        }
        getchar();//作用是为了读取缓存区中的换行符（因为迷宫是一行一行输入到内存中的）
    }
    //将二维数组转换为无向图，在转换时，从二维数组的左上角开始，每次判断当前顶点的右侧和下侧是否为通路，这样所有的通路就可以转换为无向图中的边。
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            //首先判断当前点是否为通路
            if (canUsed(i, j, n, m, a)) {
                if (canUsed(i+1, j, n, m, a)) {
                    //设定两顶点之间的边的权值为 1
                    G.arcs[i*m+j][(i+1)*m+j]=1;
                    G.arcs[(i+1)*m+j][i*m+j]=1;
                    G.arcnum++;
                }
                if (canUsed(i, j+1, n, m, a)) {
                    G.arcs[i*m+j][i*m+j+1]=1;
                    G.arcs[i*m+j+1][i*m+j]=1;
                    G.arcnum++;
                }
            }
        }
    }
    PathMatrix P;
    ShortPathTable D;
    //进行迪杰斯特拉算法
    ShortestPath_Dijkstra(G,start, &P, &D);
    //如果最终记录的权值和还是无穷大，证明，入口和出口之间没有通路
    if (D[exit]==INFINITY) {
        printf("-1");
    }else{
        printf("入口到出口的最短路径长度为:\n");
        printf("%d\n",D[exit]);
        printf("入口到出口的最短路径为(逆序):\n");
        printf("(%d,%d) ",exit/m,exit%m);
        while (P[exit]!=0) {
            printf("(%d,%d) ",P[exit]/m,P[exit]%m);
            exit=P[exit];
        }
        printf("(%d,%d)\n",start/m,start%m);
    }
    return 0;
}
