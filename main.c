#include <stdio.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <stdbool.h>

#include <string.h>

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
    FILE *file = fopen("words1.txt","r");
    if(file == NULL)
    {
        perror("failed to open file");
        return 1;

    }

    char words[200][64];
    int wcount = 0;

    while(fgets(words[wcount],sizeof(words[wcount]),file) != NULL)
    {
        words[wcount][strcspn(words[wcount], "\n")] = '\0';
        wcount++;

    }

    char text[256] = {0};
    char testExpression[256] = {0}; // no more fixed expression
    for(int i = 0; i < 20; i++)
    {
        if(i != 0)
        {
            strcat(testExpression," ");
        }
        strcat(testExpression,words[i]);

    }
    //printf("test of 20 words: %s\n",testExpression);

    printf("please type the expression below to your best accuracy\n");
    printf("%s\n",testExpression);

    tcgetattr(STDIN_FILENO, &tty);
    tty2 = tty;
    tty2.c_lflag &= ~(ICANON | ECHO);
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
            if(currChar == testExpression[count])
            {
                printf("\033[1;32m%c\033[0m", currChar);
            }
            else
            {
                printf("\033[1;31m%c\033[0m", currChar);
            }
            count++;
           // red base  printf("\033[1;32m%c\033[0m", currChar);

           // green base printf("\033[1;31m%c\033[0m", currChar);


        fflush(stdout);
    }
    printf("\n");
    // reset terminal to canonical mode.
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed = (end.tv_sec - start.tv_sec)
                   + (end.tv_nsec - start.tv_nsec) / 1e9;

    int difference = compareStrings(numChars(testExpression),testExpression,text);
    switch(difference){
        case 0:
            printf("Perfect Accuracy\n");
            break;
        case 1:
            printf("You made 1 mistake\n");
            break;
        default:
            printf("You made: %d mistakes\n",difference);
    }
    double wpm = (numChars(testExpression) / elapsed) * 60 / 5;
    printf("Speed: %.2f WPM\n", wpm);

}
