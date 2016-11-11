#include <stdio.h>
#include <stdlib.h>

char operation[5] = {'#','+','-','*','/'};

float cal(float x, float y, int op){
    switch(op){
        case 1: return x+y;
        case 2: return x-y;
        case 3: return x*y;
        case 4: return x/y;
    }
}

float model1(float i, float j, float k, float t, int op1, int op2, int op3){
    float r1,r2,r3;
    r1 = cal(i,j,op1);
    r2 = cal(r1,k,op2);
    r3 = cal(r2,t,op3);
    return r3;
}

float model2(float i, float j, float k, float t, int op1, int op2, int op3){
    float r1, r2, r3;
    r1 = cal(j,k,op2);
    r2 = cal(i,r1,op1);
    r3 = cal(r2,t, op3);
    return r3;
}

float model3(float i, float j, float k, float t, int op1, int op2, int op3){
    float r1,r2,r3;
    r1 = cal(k,t,op3);
    r2 = cal(j,r1,op2);
    r3 = cal(i,r2,op1);
    return r3;
}

float model4(float i, float j,float k, float t, int op1, int op2, int op3){
    float r1,r2,r3;
    r1 = cal(j,k,op2);
    r2 = cal(r1,t,op3);
    r3 = cal(i,r2,op1);
    return r3;
}

float model5(float i, float j, float k,float t,int op1, int op2, int op3){
    float r1,r2,r3;
    r1 = cal(i,j,op1);
    r2 = cal(k,t,op3);
    r3 = cal(r1,r2,op2);
    return r3;
}

int get24(int i, int j, int k, int t){
    int op1, op2, op3;
    int flag = 0;
    for(op1 = 1; op1<=4;op1++){
        for(op2 = 1; op2<=4; op2++){
            for(op3 = 1; op3<=4; op3++){
                if(model1(i,j,k,t,op1,op2,op3) == 24){
                    printf("((%d%c%d)%c%d)%c%d=24\n",i,operation[op1],j,operation[op2],k,operation[op3],t);
                    flag = 1;
                }
                if(model2(i,j,k,t,op1,op2,op3) == 24){
                        printf("(%d%c(%d%c%d))%c%d=24\n", i,operation[op1],j,operation[op2],k,operation[op3],t);
                        flag = 1;
                }
                if(model3(i,j,k,t,op1,op2,op3) == 24){
                        printf("%d%c(%d%c(%d%c%d))=24\n",i,operation[op1],j,operation[op2],k,operation[op3],t);
                        flag = 1;
                }
                if(model4(i,j,k,t,op1,op2,op3) == 24){
                    printf("%d%c((%d%c%d)%c%d)=24\n",i,operation[op1],j,operation[op2],k,operation[op3],t);
                    flag=1;
                }
                if(model5(i,j,k,t,op1,op2,op3) == 24){
                    printf("(%d%c%d)%c(%d%c%d)=24\n",i,operation[op1],j,operation[op2],k,operation[op3],t);
                    flag = 1;
                }
            }
        }
    }
    return flag;
}
int main()
{
    int i,j,k,t;
    printf("Please input four integer (1-10): \n");
    scanf("%d %d %d %d", &i,&j,&k,&t);

    if(i<1||i>10 || j<1||j>10 || k<1||k>10 || t<1||t>10){
        printf("Input illegal, please input again.");
    }
        if(get24(i,j,k,t));
        else{
            printf("Sorry, these four numbers cannot be calculated to get 24\n");
        }
        getche();

    return 0;
}
