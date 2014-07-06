/*
 * =========================================================
 *       Filename:  rotateMatrix.c
 *    Description:  Given an image represented by an NxN matrix, 
 *    where each pixel in the image is 4 bytes, write a method
 *    to rotate the image by 90 degrees. Can you do this in place?
 *
 *    hint: 这个问题有趣,how about rotate 180,270(same with 90)
 *
 * =========================================================
 */
#include <stdio.h>
#define N 3
void swap(int* a,int* b);
void rotate_180(int m[][N],int n);
void rotete_90(int m[][N],int n);
void printMatrix(int m[][N],int n);
int main(){
    int m[][N] = {{1,2,3},{4,5,6},{7,8,9}};
    printMatrix(m , N);
    rotate_180(m , N);
    printMatrix(m , N);
    rotete_90(m , N);
    printMatrix(m , N);
    return 0;
}


void swap(int* a,int* b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
void rotate_180(int m[][N],int n){
    //上下倒置
    int i,j;
    for(i = 0;i < n/2;i++)
        for(j = 0;j < n;j++)
            swap(m[i]+j , m[n-i-1]+j);
    //每行逆序
    for(i = 0;i < n;i++)
        for(j = 0;j < n/2;j++)
            swap(m[i]+j , m[i]+n-j-1);
}

void printMatrix(int m[][N],int n){
    for(int i = 0;i < n;i++)
        for(int j = 0; j < n;j++)
            printf("%d%s",m[i][j],(j == n-1)?"\n":" ");
    printf("\n\n");
}

void rotete_90(int m[][N],int n){
    int i,j;
    //顺时针90
    //上下倒置
    for(i = 0;i < n/2;i++)
        for(j = 0;j < n;j++)
            swap(m[i]+j , m[n-i-1]+j);
    //转置
    for(i = 0;i < n;i++)
        for(j = i;j < n;j++)//j = i not j = 0
            swap(m[i]+j , m[j]+i);
    //改变上面的顺序,就是逆时针90
}
