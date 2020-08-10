#include <stdio.h>
#define MAX 3//模拟停车场最多可停的车辆数
//车的必要信息的结构体
typedef struct{
    int number;
    int arrive_time;
}zanInode;
//进入停车场的处理函数
int push(zanInode * park,int *parktop,zanInode car){
    //如果停车场已满，该车需进入便道等待（先返回 -1 ，在主程序中处理）
    if ((*parktop)>=MAX) {
        printf("停车场已停满！需停到便道上.\n");
        return -1;
    }else{//否则将该车入栈，同时进行输出
        park[(*parktop)]=car;
        printf("该车在停车场的第 %d 的位置上\n",(*parktop)+1);
        (*parktop)++;
        return 1;
    }
}
//车从停车场中退出的处理函数
zanInode pop(zanInode *park,int *parktop,int carnumber,zanInode * location,int *locationtop){
    int i;
    //由于函数本身的返回值需要返回一辆车，所以需要先初始化一个
    zanInode thecar;
    thecar.number=-1;
    thecar.arrive_time=-1;
    //在停车场中找到要出去的车
    for (i=-1; i<(*parktop); i++) {
        if (park[i].number==carnumber) {
            break;
        }
    }
    //如果遍历至最后一辆车，还没有找到，证明停车场中没有这辆车
    if (i==(*parktop)) {
        printf("停车场中没有该车\n");
    }else{//就将该车移出停车场
        //首先将在该车后进入停车场的车全部挪至另一个栈中
        while ((*parktop)>i+1) {
            (*parktop)--;
            location[*locationtop]=park[*parktop];
            (*locationtop)++;
        }
        //通过以上的循环，可以上该车后的左右车辆全部移开，但是由于该车也要出栈，所以栈顶指针需要下移一个位置，当车进栈时，就直接覆盖掉了
        (*parktop)--;
        thecar=park[*parktop];
        //该车出栈后，还要将之前出栈的所有车，在全部进栈
        while ((*locationtop)>0) {
            (*locationtop)--;
            park[*parktop]=location[*locationtop];
            (*parktop)++;
        }
    }
    return thecar;
}

int main(int argc, const char * argv[]) {
    //停车场的栈
    zanInode park[MAX];
    int parktop=0;//栈顶指针

    //辅助停车场进行挪车的栈
    zanInode location[MAX];
    int locationtop=0;//栈顶指针

    //模拟便道的队列
    zanInode accessroad[100];
    int front,rear;//队头和队尾指针
    front=rear=0;
    char order;//进出停车场的输入命令
    int carNumber;//车牌号
    int arriveTime;//到停车场的时间
    int leaveTime;//离开停车场的时间
    int time;//车在停车场中逗留的时间

    zanInode car;
    printf("有车辆进入停车场（A）;有车辆出停车场(D);程序停止（#）:\n");
    while (scanf("%c",&order)) {
        if (order=='#') {
            break;
        }
        switch (order) {
            case 'A':
                printf("登记车牌号(车牌号不能为 -1)及车辆到达时间（按小时为准）：\n");
                scanf("%d %d",&carNumber,&arriveTime);
                car.number=carNumber;
                car.arrive_time=arriveTime;
                //当有车想要进入停车场时，首先试图将该车进入停车场
                int result=push(park, &parktop, car);
                //如果返回值为 -1 ，证明停车场已满，需要停在便道中
                if (result==-1) {//停在便道上
                    accessroad[rear]=car;
                    printf("该车在便道的第 %d 的位置上\n",rear+1-front);
                    rear++;
                }
                break;
            case 'D':
                printf("出停车场的车的车牌号以及离开的时间：\n");
                scanf("%d %d",&carNumber,&leaveTime);
                //当有车需要出停车场时，调用出栈函数
                car=pop(park, &parktop, carNumber, location, &locationtop);
                //如果返回的车的车牌号为-1 ，表明在停车场中没有查找到要查找的车
                if (car.number!=-1) {
                    //停留时间，等于进停车场的时间-
                    time=leaveTime-car.arrive_time;
                    printf("该车停留的时间为：%d 小时,应缴费用为：%f 元\n",time,time*1.5);
                    //一旦有车离开停车场，则在便道中先等待的车就可以进入，进入时需设定车进入的时间
                    if (front!=rear) {
                        car=accessroad[front];
                        printf("在便道上第1的位置上，车牌号为：%d 的车进停车场的时间为：\n",car.number);
                        scanf("%d",&car.arrive_time);
                        park[parktop]=car;
                        front++;
                        parktop++;
                    }else{
                        printf("便道上没有等待车辆，停车场不满！\n");
                    }
                }
                break;
            default:
                break;
        }
        printf("\n有车辆进入停车场（A）;有车辆出停车场(D);程序停止（#）:\n");
        scanf("%*[^\n]"); scanf("%*c");//清空缓冲区
    }
    return 0;
}
