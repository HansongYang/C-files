#include <stdio.h>
#include <stdlib.h>

int days = 0;
char *zodiac[] = {"Pig","Rat","Ox","Tiger","Rabbit","Dragon","Snake","Horse","Goat","Monkey","Rooster","Dog"};
char *month [] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

int isLeapYear(int y){
    if((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)){
		return 1;
	}
	return 0;
}

int firstDay(int y){
    long n = y * 365;
    int i;
    for(i = 1; i < y; i++){
        if(isLeapYear(i)){
            n+=1;
        }
    }
    return (int) n%7;
}

char* cz(int y){
    int a = 0;
    a = (y + 9) % 12;
    return zodiac[a];
}

void calender(int year){
    int weekday = firstDay(year);
    printf("------------------------------------------------------\n");
    printf("               %d", year);
    printf(": The year of %s\n",  cz(year));

    int i, j;
    for(i = 1; i < 13; i++){
        switch(i) {
			case 2: if(isLeapYear(year))days = 29; else days = 28; break;
			case 4:
			case 6:
			case 9:
			case 11: days = 30; break;
			default: days = 31;
        }

        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n");
        int index = i;
        printf("%s\n", month[--index]);
        printf("\n");
        printf("Su\tMo\tTu\tWe\tTh\tFr\tSa\n");

        for(j = 1; j < weekday; j++){
            printf("\t");
        }

        for(j = 1; j <= days; j++){
            printf("%d\t", j);
            weekday = (weekday + 1) % 7;
            if(weekday == 0){
                printf("\n");
            }
        }
        printf("\n");
    }
}

int main()
{
    printf("Please input a year:");
    int year;
    scanf("%d", &year);
    calender(year);
     return 0;
}
