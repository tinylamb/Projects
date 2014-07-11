/*
 * =========================================================
 *       Filename:  tree.c
 *    Description:  二叉树方法的实现
 *
 * =========================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "tree.h"
#define MAX(x , y) ((x > y)?x:y)

int Max(int x , int y){
    return (x > y)?x:y;
}
Node *newNode(ElemType item){
    Node *n = malloc(sizeof(Node));
    n->left = n->right = NULL;
    n->fre = 0;
    n->height = 0;
    n->data = malloc(sizeof(char) * (strlen(item) + 1));
    strcpy(n->data , item);
    return n;
}
Node *findNode(Tree root ,ElemType item){
    while (root){
        if (strcmp(root->data , item) == 0){
            root->fre += 1;
            break;
        }
        else if (strcmp(root->data , item) > 0)
            root = root->left;
        else
            root = root->right;
    }
    return root;
/*     if (root == NULL)
 *         return NULL;
 *     if (strcmp(root->data , item) == 0)
 *         return root;
 *     else if (strcmp(root->data ,item) > 0)
 *         return findNode(root->left , item);
 *     else
 *         return findNode(root->right ,item);
 */
}
Node *findMin(Tree root){
    Node *min = root;
    while(root){
        min = root;
        root = root->left;
    }
    return min;
}

Node *findMax(Tree root){
    if(root == NULL)
        return NULL;
    else{
        if(root->right == NULL)
            return root;
        else
            return fidnMax(root->right);
    }
}

Node *insertNode(Tree root , ElemType item){
//    if(root == NULL)
//        root = newNode(item);
//    else{
//        Node *iter = root;
//        Node *parent;
//        bool left = true;
//        while(iter){
//            if(strcmp(iter->data , item) == 0)
//                break;
//            else{
//                parent = iter;
//                if(strcmp(iter->data , item) > 0){
//                    left = true;
//                    iter = iter->left;
//                }
//                else{
//                    left = false;
//                    iter = iter->right;
//                }
//            }
//        }
//        if(iter == NULL){
//            Node *n = newNode(item);
//            if (left)
//                parent->left = n;
//            else
//                parent->right = n;
//        }
//    }
//    return root;

    if (root == NULL){
        root = newNode(item);
    }
    else if (strcmp(root->data , item) > 0){
        root->left = insertNode(root->left , item);
        if ((Height(root->left) - Height(root->right)) > 1){
            if(strcmp(root->left->data , item) > 0)
                root = SingleRotateWithLeft(root);
            else
                root = DoubleRotateWithRight(root);
        }
    }
    else if (strcmp(root->data , item) < 0){
        root->right = insertNode(root->right ,item);
        if ((Height(root->right) - Height(root->left)) > 1){
            if (strcmp(root->right->data , item) < 0)
                root = SingleRotateWithRight(root);
            else
                root = DoubleRotateWithLeft(root);
        }
    }
    root->height = MAX(Height(root->left) , Height(root->right)) + 1;
    return root;

}
Node *deleteNode(Tree root , ElemType item){
    assert(root != NULL);
    Node *temp;
    if(strcmp(root->data , item) > 0)
        root->left = deleteNode(root->left , item);
    else if(strcmp(root->data , item) < 0)
        root->right = deleteNode(root->right ,item);
    else if(root->left && root->right){
        temp = findMax(root->left);
        strcpy(root->data , temp->data);
        root->left = deleteNode(root->left ,temp->data);
    }
    else{
        temp = root;
        if(root->left)
            temp = root->left;
        else if(root->right)
            temp = root->right;
        free(temp);
    }
    return root;
}
void inorder(Tree root){
    if (root){
        inorder(root->left);
        printf("%s ",root->data);
        inorder(root->right);
    }
}
void preorder(Tree root){
    if(root){
        printf("%s ",root->data);
        preorder(root->left);
        preorder(root->right);
    }
}


int treeHeight(Tree root){
    if(root == NULL)
        return -1;
    else{
//        printf("%s\n",root->data);
//        printf("%d\n",treeHeight(root));
//        return Max(treeHeight(root->left) , treeHeight(root->right)) + 1;
//        return (((treeHeight(root->left) > treeHeight(root->right)) )?treeHeight(root->left):treeHeight(root->right)) + 1;
        return (MAX(treeHeight(root->left) , treeHeight(root->right)) + 1);
    }
}
int Height(Tree root){
    if(root == NULL)
        return -1;
    else
        return root->height;
}
Node *SingleRotateWithLeft(Node *unbalance){
    Node *balance = unbalance->left;
    unbalance->left = balance->right;
    balance->right = unbalance;
    unbalance->height = MAX(Height(unbalance->left),Height(unbalance->right)) + 1;
    balance->height = MAX(Height(balance->left) , Height(unbalance)) + 1;
    return balance;
}
Node *SingleRotateWithRight(Node *unbalance){
    Node *balance = unbalance->right;
    unbalance->right = balance->left;
    balance->left = unbalance;
    unbalance->height = MAX(Height(unbalance->left),Height(unbalance->right)) + 1;
    balance->height = MAX(Height(balance->left) , Height(balance->right)) + 1;
    return balance;
}
Node *DoubleRotateWithRight(Node *unbalance){
    unbalance->left = SingleRotateWithRight(unbalance->left);
    return SingleRotateWithLeft(unbalance);
}
Node *DoubleRotateWithLeft(Node *unbalance){
    unbalance->right = SingleRotateWithLeft(unbalance->right);
    return SingleRotateWithRight(unbalance);
}
