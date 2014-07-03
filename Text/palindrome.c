/*
 * =========================================================
 *       Filename:  palindrome.c
 *    Description:  Checks if the string entered by the user
 *    is a palindrome. That is that it reads the same forwards as backwards like “racecar
 *
 * =========================================================
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define BUF_SIZE 100
bool isPalindrome(char *s);
int main(){
    char s[BUF_SIZE];
    scanf("%[^\n]",s);
    bool palin = isPalindrome(s);
    if(palin == true)
        printf("%s is palindrome.\n",s);
    else
        printf("%s is not a palindrome.\n",s);
}


bool isPalindrome(char *s){
    bool palindrome = true;
    char* head = s;
    char* tail = s + strlen(s)-1;
    while(head < tail){
        if(*head == *tail){
            ++head;
            --tail;
        }
        else{
            palindrome = false;
            break;
        }
    }
    return palindrome;
}

//source code strlen
/* size_t strlen(const char* str){
 *     register const char* s;
 *     for(s = str; *s; ++s);
 *     return (s - str);
 * }
 */
