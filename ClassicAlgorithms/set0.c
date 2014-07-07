/*
 * =========================================================
 *       Filename:  set0.c
 *    Description:  Write an algorithm such that if an element in an 
 *    MxN matrix is 0, its entire row and column is set to 0.
 *    
 *    hint : 二维数组作为参数
 * =========================================================
 */
#include <stdio.h>
#define M 3
#define N 4
void set(int m[][N],int r,int c);
void printMatrix(int m[][N],int r,int c);
int main(){
    int m[M][N] = {{0,1,2,3},{4,5,0,7},{8,9,10,6}};
    printMatrix(m, M ,N);
    set(m , M , N);
    printMatrix(m , M ,N);
    return 0;
}


void set(int m[][N],int r,int c){
    int row = 0;
    int col = 0;
    int i,j;
    for(i = 0;i < r;i++)
        for(j = 0;j < c;j++)
            if(m[i][j] == 0){
                row |= (1 << i);
                col |= (1 << j);
            }
    for(i = 0;i < r;i++)
        for(j = 0;j < c;j++)
            //检测元素所在行或列是否存在 0
            if(((row & (1 << i)) != 0) || ((col & (1 << j)) != 0))
                m[i][j] = 0;
}

void printMatrix(int m[][N],int r,int c){
    int i,j;
    for(i = 0;i < r;i++)
        for(j = 0;j < c;j++)
            printf("%d%s",m[i][j],(j == c-1)?"\n":" ");
    printf("\n\n");
}
