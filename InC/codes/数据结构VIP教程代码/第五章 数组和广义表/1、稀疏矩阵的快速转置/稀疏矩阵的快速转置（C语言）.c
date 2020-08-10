#include<stdio.h>
#define number 10
typedef struct {
    int i,j;
    int data;
}triple;
typedef struct {
    triple data[number];
    int rpos[number];
    int n,m,num;
}TSMatrix;

//实现快速转置算法的函数
TSMatrix fastTransposeMatrix(TSMatrix M,TSMatrix T){
    //第1步：行和列置换
    T.m=M.n;
    T.n=M.m;
    T.num=M.num;
    if (T.num) {
        //计算array数组
        int array[number];
        for (int col=1; col<=M.m; col++) {
            array[col]=0;
        }
        for (int t=0; t<M.num; t++) {
            int j=M.data[t].j;
            array[j]++;
        }

        //创建并初始化cpot数组
        int cpot[T.m+1];
        cpot[1]=1;//第一列中第一个非0元素的位置默认为1
        for (int col=2; col<=M.m; col++) {
            cpot[col]=cpot[col-1]+array[col-1];
        }
        //遍历一次即可实现三元组表的转置
        for (int p=0; p<M.num; p++) {
            //提取当前三元组的列数
            int col=M.data[p].j;
            //根据列数和cpot数组，找到当前元素需要存放的位置
            int q=cpot[col];
            //转置矩阵的三元组默认从数组下标0开始，而得到的q值是单纯的位置，所以要减1
            T.data[q-1].i=M.data[p].j;
            T.data[q-1].j=M.data[p].i;
            T.data[q-1].data=M.data[p].data;
            //存放完成后，cpot数组对应的位置要+1，以便下次该列存储下一个三元组
            cpot[col]++;
        }
    }
    return T;
}

int main() {
    TSMatrix M;
    M.m=2;
    M.n=3;
    M.num=3;

    M.data[0].i=1;
    M.data[0].j=2;
    M.data[0].data=1;

    M.data[1].i=2;
    M.data[1].j=2;
    M.data[1].data=3;

    M.data[2].i=3;
    M.data[2].j=1;
    M.data[2].data=6;

    TSMatrix T;
    T=fastTransposeMatrix(M, T);
    printf("转置矩阵三元组表为：\n");
    for (int i=0; i<T.num; i++) {
        printf("(%d,%d,%d)\n",T.data[i].i,T.data[i].j,T.data[i].data);
    }
    return 0;
}
