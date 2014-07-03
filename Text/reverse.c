/*
 * =========================================================
 *       Filename:  reverse.c
 *    Description:  Enter a string and the program will reverse it and print it out
 *
 * =========================================================
 */
#include <stdio.h>
#define SIZE 100
#define SWAP(a,b) do{char temp;temp = a;a = b;b = temp;}while(0)
void reverse(char *s);
void swap(char* s,char* t);
int main(){
    char s[SIZE];//store string in heap segment
    printf("input string:");
    scanf("%[^\n]",s);
    printf("before reverse : %s\n",s);
    reverse(s);
    return 0;
}

//reverse string by swap head and tail
void reverse(char *s){
    char* head = s;
    char* tail = s;//tail point to end of string
    while(*(tail + 1) != '\0')
        ++tail;

    while(head < tail){
        SWAP(*head,*tail);
        ++head;
        --tail;
    }
    printf("after reverse : %s\n",s);

}

