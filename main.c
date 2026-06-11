#include <bits/time.h>
#include <stdio.h>
#include <time.h>


struct timespec start,end;

int numChars(char* here)
{
    int counter = 0;
    for(int i = 0; here[i] != '\0'; i++)
    {
        counter++;
    }
    return counter;
}

int compareStrings(int len, char* testArr, char* userArr)
{
    int ret = 0;
    for(int i = 0; i < len; i++)
    {
       if(testArr[i] != userArr[i])
       {
           ret++;
       }
    }

    return ret;
}

int main(void)
{
    char text[30];
    char testExpression[] = {"67 is the best"};
    printf("please type the expression below to your best accuracy\n");
    printf("%s\n",testExpression);
    clock_gettime(CLOCK_MONOTONIC, &start);
    scanf("%29[^\n]", text);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed = (end.tv_sec - start.tv_sec)
                   + (end.tv_nsec - start.tv_nsec) / 1e9;

    int difference = compareStrings(numChars(testExpression),testExpression,text);
    switch(difference){
        case 0:
            printf("perfect score.\n");
            break;
        case 1:
            printf("you made 1 mistake.\n");
            break;
        default:
            printf("you made %d mistakes\n",difference);
    }
    double wpm = (numChars(testExpression) / elapsed) * 60 / 5;
    printf("you typed %d characters in %.2f seconds, which equates to %.2f WPM.",numChars(testExpression),elapsed,wpm);

}
