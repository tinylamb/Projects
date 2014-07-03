/*
 * =========================================================
 *       Filename:  vowels.c
 *    Description:  Enter a string and the program counts the 
 *    number of vowels in the text. For added complexity have 
 *    it report a sum of each vowel found
 *
 * =========================================================
 */
#include <stdio.h>
#define BUF_SIZE 100
enum Vowels {a,e,i,o,u} ;
char vowel[]={'a','e','i','o','u'};
int counts[5] = {0};
void vowels_count(char* s);
int main(){
    char s[BUF_SIZE];
    scanf("%[^\n]",s);
    vowels_count(s);
    int i;
    for(i = 0;i < 5;i++)
        printf("%c : %d\n",vowel[i],counts[i]);
    return 0;
}


void vowels_count(char* s){
    while(*s){
        switch(*s){
            case 'a':counts[a]++;break;
            case 'e':counts[e]++;break;
            case 'i':counts[i]++;break;
            case 'o':counts[o]++;break;
            case 'u':counts[u]++;break;
        }
        ++s;
    }
}
