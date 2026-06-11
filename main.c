#include <stdio.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <stdbool.h>

struct timespec start,end;
struct termios tty;
struct termios tty2;


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

    char text[100]; // not currently needed.
    char testExpression[] = {"here is the where this one is the one"};
    printf("please type the expression below to your best accuracy\n");
    printf("%s\n",testExpression);

    tcgetattr(STDIN_FILENO, &tty);
    tty2 = tty;
    tty2.c_lflag &= ~(ICANON| ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &tty2);

    // get clock
    clock_gettime(CLOCK_MONOTONIC, &start);
    // input from user
    // scanf("%99[^\n]", text);    * Disabling Scanf in favor of a loop.
    int currChar;
    int count = 0;
    while((currChar =getchar()) != '\n')
    {
        text[count] = currChar;
        count++;
        printf("[%d]", count);
        fflush(stdout);
    }
    // reset terminal to canonical mode.
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);

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
