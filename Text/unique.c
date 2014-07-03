/*
 * =========================================================
 *       Filename:  unique.c
 *    Description:  Implement an algorithm to determine if a string has all unique characters.
 *    What if you can not use additional data structures?
 *    hit: 这个string 中包含的字符集有多大
 *    
 *
 * =========================================================
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
bool isUnique_v1(char s[]);
bool isUnique_v2(char s[]);
int main()
{
    char s1[] = "i am lambda.";
    char s2[] = "abcdefghijklmnopqrstuvwxyzABCD1234567890";
    printf("s1 is %d %d\n",isUnique_v1(s1),isUnique_v2(s1));
    printf("s2 is %d %d\n",isUnique_v1(s2),isUnique_v2(s2));
    return 0;
}


bool isUnique_v1(char s[]){
    bool unique[256];
    memset(unique, 0 ,sizeof(unique));
    while(*s){
        int key = (int)(*s);
        if(unique[key])
            return false;
        unique[key] = true;
        ++s;
    }
    return true;
}

bool isUnique_v2(char s[]){
    int unique[8];
    memset(unique, 0 , sizeof(unique));
    while(*s){
        int key = (int)(*s)/32;
        int shift = (int)(*s)%32;
        if(unique[key] & 1<<shift)
            return false;
        unique[key] |= 1<<shift;
        ++s;
    }
    return true;
}
