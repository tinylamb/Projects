/*
 * =========================================================
 *       Filename:  main.c
 *    Description:  
 *
 * =========================================================
 */
#include <stdio.h>
#include "tree.h"
int main(){
    ElemType item;
    Tree t = NULL;
    while(scanf("%s" , item) == 1)
        t = insertNode(t , item);
    inorder(t);
    printf("\n");
    preorder(t);
    printf("\n");
    int h = t->height;
    printf("height of tree is %d\n",h);
}

