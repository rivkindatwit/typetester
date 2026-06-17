#include <stdio.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>


int main()
{
    FILE *f1 = fopen("words.txt","r");
    if(f1 == NULL)
    {
        perror("file open failed");
        return 1;
    }

    char buf[200];

    while((fgets(buf,sizeof(buf),f1)) != NULL)
    {

    }



    return 0;
}
