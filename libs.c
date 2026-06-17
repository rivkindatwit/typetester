#include <stdio.h>
#include <string.h>

int main(void)
{
    FILE *f1 = fopen("words.txt","r");
    if(f1 == NULL)
    {
        perror("file not opened");
    }

    char word[20];
    int count = 0;

    while(fgets(word,sizeof(word),f1) != NULL)
    {
        word[strcspn(word, "\n")] = '\0';
        printf("%s\n",word);
        count++;

    }


    printf("total words is %d\n",count);



    fclose(f1);



}
