#include <stdio.h>
#include <stdlib.h>

char upper(char c){
    return (c-'a'+'A');
}

void function(char *s){
    int len = strlen(s), i=0;

    for(i=0; i < len; i++){
    printf("%c",upper(s[i]));
    }
}

int main()
{
    char c[500];
    printf("Please enter a string: \n");
    gets(c);
    printf("Upper case: \n");
    function(c);

    getche();
}
