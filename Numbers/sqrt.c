/*
 * =========================================================
 *       Filename:  sqrt.c
 *    Description:  利用牛顿法求平方根
 *
 * =========================================================
 */
#include <stdio.h>
#include <stdlib.h>
#define Error 1e-6
int main(){
    float k;
    printf("input k(k > 0) :\n");
    scanf("%f",&k);
    float init;
    printf("input init(init > 0) :\n");
    scanf("%f",&init);
    while(abs(init * init - k) > Error)
        init = 0.5 * (init + k / init); //关键理解这里的迭代模型
    printf("sqrt(%f) is %f\n", k, init);

    return 0;
}

