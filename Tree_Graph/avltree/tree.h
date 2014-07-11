/*
 * =========================================================
 *       Filename:  tree.h
 *    Description:  二叉树头文件
 *
 * =========================================================
 */
#ifndef TREE_H
#define TREE_H
#define ElemType char *
typedef struct node{
    struct node *left;
    struct node *right;
    ElemType data;
    int fre;
    int height;
}Node ,* Tree;

extern Node *newNode(ElemType item);
extern Node *findNode(Tree root,ElemType item);
extern Node *findMin(Tree root);
extern Node *findMax(Tree root);
extern Node *insertNode(Tree root , ElemType item);
extern Node *deleteNode(Tree root , ElemType item);
extern void inorder(Tree root);
extern void preorder(Tree root);
extern int treeHeight(Tree root);
extern int Height(Tree root);
extern Node *SingleRotateWithLeft(Node *unbalance);
extern Node *SingleRotateWithRight(Node *unbalance);
extern Node *DoubleRotateWithRight(Node *unbalance);
extern Node *DoubleRotateWithLeft(Node *unbalance);
#endif
