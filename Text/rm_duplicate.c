/*
 * =========================================================
 *       Filename:  rm_duplicate.c
 *
 *    Description:  Design an algorithm and write code to 
 *    remove the duplicate characters in a string without 
 *    using any additional buffer. NOTE: One or two additional
 *    variables are fine. An extra copy of the array is not
 *
 *    hint:为了明确题目,多问一些问题让题目更具体(in place 就地)删除重复字符
 *    字符长度?字符集长度?
 * =========================================================
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define BUF 100
void rm_v1(char s[]);
void rm_v2(char s[]);
void rm_v3(char s[]);
int main(){
    char s[BUF];
    scanf("%[^\n]",s);
    rm_v1(s);
    printf("%s\n",s);
    rm_v2(s);
    printf("%s\n",s);
    rm_v3(s);
    printf("%s\n",s);

}

//using any additional buffer
void rm_v1(char s[]){
    int len = strlen(s);
    if(len < 2)
        return ;
    int i,j,p = 0;
    for(i = 0;i < len;i++){
        if(s[i] != '\0'){
            s[p++] = s[i];//p 指向当前无重复字符的串尾
            for(j = i+1;j < len;j++)
                if(s[j] == s[i])
                    s[j] = '\0';//重复的字符先置'\0'
        }
    }
    s[p] = '\0';

}

//using specfic buffer
void rm_v2(char s[]){
    int len = strlen(s);
    if(len < 2)
        return ;
    bool cha[256];
    memset(cha,0,sizeof(cha));
    int i,p = 0;
    for(i = 0;i < len;i++){
        if(!cha[s[i]]){
            s[p++] = s[i];
            cha[s[i]] = true;
        }
    }
    s[p] = '\0';
}

//using bitmap idea deal 32 character
void rm_v3(char s[]){
    int len = strlen(s);
    if(len < 2)
        return ;
    int test = 0;//bitmap idea
    int i,p = 0;
    for(i = 0;i < len;i++){
        if(!(test & (1 << (s[i]-'a')))){
            s[p++] = s[i];
            test |= 1 << (s[i] - 'a');
        }
    }
    s[p] = '\0';
}
