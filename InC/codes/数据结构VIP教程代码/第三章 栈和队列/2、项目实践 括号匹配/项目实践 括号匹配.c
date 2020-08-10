#include <stdio.h>
#include <string.h>
int top=-1;//top变量时刻表示栈顶元素所在位置
void push(char * a,int elem){
    a[++top]=elem;
}
void pop(char* a){
    if (top==-1) {
        return ;
    }
    top--;
}
char visit(char * a){
    //调取栈顶元素，不等于弹栈，如果栈为空，为使程序不发生错误，返回空字符
    if (top!=-1) {
        return a[top];
    }else{
        return ' ';
    }
}
int main() {
    char a[30];
    char bracket[100];
    printf("请输入括号序列：");
    scanf("%s",bracket);
    getchar();
    int length=(int)strlen(bracket);
    for (int i=0; i<length; i++) {
        //如果是左括号，直接压栈
        if (bracket[i]=='('||bracket[i]=='{') {
            push(a, bracket[i]);
        }else{
            //如果是右边括号，判断与栈顶元素是否匹配，如果匹配，栈顶元素弹栈，程序继续运行；否则，发现括号不匹配，输出结果直接退出
            if (bracket[i]==')') {
                if (visit(a)=='(') {
                    pop(a);
                }else{
                    printf("括号不匹配");
                    return 0;
                }
            }else{
                if (visit(a)=='{') {
                    pop(a);
                }else{
                    printf("括号不匹配");
                    return 0;
                }
            }
        }
    }
    //如果所有括号匹配完成，栈内为空，说明所有括号全部匹配成功
    if (top!=-1) {
         printf("括号不匹配");
    }else{
       printf("括号匹配");
    }
}
