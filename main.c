#include <stdio.h>
#include <stdlib.h>


    char data1[19][10] = {"one","two","three","four","five","six","seven","eight","nine","ten","eleven","twelve",
                            "thirteen","forteen","fifteen","sixteen","seventeen","eighteen","nineteen"};

    char data2[8][7] = {"twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"};

translation(long M){
    long k;
    if(M==0){
        printf("Zero\n");
        return;
    }
    k = M/1000000000;

    if(k != 0){
        translation_A(k);
        printf("billion ");
    }
    k = M % 1000000000;
    if(k!=0){
        translation_A(k);
    }
}

translation_A(long N){
    long a;
    a = N/1000000;

    if(a!=0){
        translation_B(a);
        printf("million ");
    }
    a = N % 1000000;
    if(a!=0){
        translation_B(a);
    }
}

translation_B(long N){
    long a;
    a = N/1000;

    if(a!=0){
        translation_C(a);
        printf("thousand ");
    }
    a = N % 1000;
    if(a!=0){
        translation_C(a);
    }
}

translation_C(long a){
    long b;
    b = a/100;

    if(b!=0){
    translation_D(b);
    printf("hundred ");
    }

    b = a % 100;
    if(b!=0){
        translation_D(b);
    }

}

translation_D(long b){
    long c;
    if(b<=19){
        printf("%s ", data1[b-1]);
    }
    else{
        c = b/10;
        printf("%s ", data2[c-2]);
        c = b%10;
        if(c!=0){
            printf("%s ", data1[c-1]);
        }
    }
}
int main()
{
    long N;
    printf("Please input a number:\n");
    scanf("%ld",&N);
    translation(N);
    printf(".");
    getche();
    return 0;
}
