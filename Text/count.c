/*
 * =========================================================
 *       Filename:  count.c
 *    Description:  count words in a string
 *
 * =========================================================
 */
#include <stdio.h>
#include <stdbool.h>
int wordcount();
int main(){
    int words = wordcount();
    printf("string contain words : %d\n",words);
    return 0;
}


int wordcount(){
    int count = 0;
    int c;
    bool Inword = false;
    while((c = getchar()) != EOF){
        if(c == ' ' || c == '\t' || c == '\n')
            Inword = false;
        else if(!Inword){
            count++;
            Inword = true;
        }
    }
    return count;
}
