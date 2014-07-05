/*
 * =========================================================
 *       Filename:  anagram.c
 *    Description:  Write a method to decide if two strings are anagrams or not
 *
 *    hint: 变位词的关键就是{cha : counts} 相同
 *
 * =========================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
int compare_char(const void* a,const void*b);
bool Isanagram_v1(char s[],char t[]);
bool Isanagram_v2(char s[],char t[]);
int main(){
    char s[] = "lambdada";
    char t[] = "dalambda";
    if(Isanagram_v1(s,t))
        printf("is anagram.\n");
    return 0;
}


int compare_char(const void* a,const void*b){
    return (*(char*)a - *(char*)b);
}

bool Isanagram_v1(char s[],char t[]){
    qsort(s,strlen(s),sizeof(char),compare_char);
    qsort(t,strlen(t),sizeof(char),compare_char);
    return (strcmp(s , t) == 0)?true:false;

}
//
//由于组成变位词的字符是一模一样的， 因此我们可以先
//统计每个字符串中各个字符出现的次数， 然后看这两个字符串中各字符出现次数是否一样。
//如果是，则它们是一对变位词。 这需要开一个辅助数组来保存各字符的出现次数。
//我们可以开一个大小是256的整数数组， 遍历第一个字符串时，将相应字符出现的次数加1；
//遍历第二个字符串时， 将相应字符出现的次数减1。
//最后如果数组中256个数都为0，说明两个字符串是一对变位词。
//(第1个字符串中出现的字符都被第2个字符串出现的字符抵消了)，
//如果数组中有一个不为0，说明它们不是一对变位词。
bool Isanagram_v2(char s[],char t[]){
    if(strlen(s) != strlen(t))
        return false;
    int len = strlen(s);
    int cha[256];
    memset(cha,0,sizeof(cha));
    for(int i = 0;i < len;i++){
        c[(int)s[i]] += 1;
        c[(int)t[i]] -= 1;
    }
    for(int i = 0;i < 256;i++)
        if(cha[i] != 0)
            return false;
    return true;

}
