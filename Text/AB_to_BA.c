/*
 * =========================================================
 *       Filename:  AB_to_BA.c
 *    Description:  rotate AB to BA
 *
 * =========================================================
 */
#include <stdio.h>
#include <string.h>
void reverse(char s[], int start, int end);
void swap(char* a, char* b);
int main(){
    char s[] = "abcdefgh";
    int i = 3;
    int len = strlen(s);
    printf("before : %s\n",s);
    reverse(s, 0, i - 1);
    reverse(s, i, len - 1);
    reverse(s, 0, len - 1);
    printf("after : %s\n",s);
    return 0;


}


void reverse(char s[], int start, int end){
    while(start < end){
        swap(s + start, s + end);
        ++start;
        --end;
    }
    
}

void swap(char* a, char* b){
    char temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
