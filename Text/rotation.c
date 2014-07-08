/*
 * =========================================================
 *       Filename:  rotation.c
 *    Description:  Assume you have a method isSubstring 
 *    which checks if one word is a substring of another.
 *    Given two strings, s1 and s2, write code to check
 *    if s2 is a rotation of s1 using only one call to isSubstring
 *    ( i.e., “waterbottle” is a rotation of “erbottlewat”).
 *
 *    hint: 熟悉一下string.h内的函数
 *
 * =========================================================
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool isSubstring(char s[],char t[]);
bool isRotation(char s[],char t[]);
int main(){
    char s[] = "gaoyang";
    char t[] = "anggao";
    if(isRotation(s,t))
        printf("%s is rotation of %s\n",t,s);
    else
        printf("%s is Not rotation of %s\n",t,s);
    return 0;
}


bool isSubstring(char s[],char t[]){
    if(strstr(s,t) != NULL)
        return true;
    else
        return false;
}

bool isRotation(char s[],char t[]){
    //构造 s + s
    int len_s = strlen(s);
    int len_t = strlen(t);
    if(len_s != len_t)//needed!
        return false;
//    char double_s[2*len + 1]; segmentfault
    char *double_s = malloc((2*len_s + 1)*sizeof(char));
    int i;
    for(int i = 0;i < (2*len_s);i++)
        double_s[i] = s[i%len_s];
    double_s[i] = '\0';
    if(isSubstring(double_s,t))
        return true;
    else
        return false;
}
