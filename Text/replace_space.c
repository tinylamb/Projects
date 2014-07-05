/*
 * =========================================================
 *       Filename:  replace_space.c
 *    Description:  Write a method to replace all spaces in a string with ‘%20’.
 * =========================================================
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUF 100
char* replace(char s[]);
void replace_v1(char s[]);
int main(){
    char s[BUF] = "my name is lambda.";//without BUF "abort info"
    replace_v1(s);
//    printf("original str :%s\nreplace str :%s\n",s," ");
    printf("repalce str:%s\n",s);
    return 0;
}


//将替换后的串存到新的空间
char* replace(char s[]){
    char *p = s;
    int space = 0;
    while(*p){
        if(*p == ' ')
            space++;
        p++;
    }
    char* t = malloc(sizeof(char)*(strlen(s) + 2*space + 1));
    char* p_t = t;
    while(*s){
        if(*s == ' '){
            *p_t = '%';
            *(p_t+1) = '2';
            *(p_t+2) = '0';
            p_t += 3;
        }
        else{
            *p_t = *s;
            p_t += 1;
        }
        ++s;
    }
    *p_t = '\0';
    return t;
}

// s 空间足够大,替换结果保存在原来空间
void replace_v1(char s[]){
    char *p = s;
    int space = 0;
    while(*p){
        if(*p == ' ')
            space++;
        p++;
    }
    int tail = strlen(s) + 2*space ;
    s[tail--] = '\0';
    for(int i = strlen(s) - 1;i >= 0;i--){//倒着来替换
        if(s[i] == ' '){
            s[tail] = '0';
            s[tail-1] = '2';
            s[tail-2] = '%';
            tail -= 3;
        }
        else{
            s[tail] = s[i];
            tail--;
        }
    }

}
