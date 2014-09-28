/*
 * =========================================================
 *       Filename:  lca.c
 *    Description:  非BST上的lca 最近公共祖先问题
 *
 * =========================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define SIZE 10

//二叉树结构定义
typedef struct node{
    int elem;
    struct node *left , *right , *pre;
}Node;

//创建一个新节点
Node *newNode(int data);

//上述由n遍历至root过程由stack 保存
typedef struct stack{
    int array[SIZE];
    int top ; // int top =0 ;
}Stack;


//问题关键是获得一条到n的路径
//---1.前序遍历返回指向n的指针
//---2.由指向n的指针，顺着pre遍历，直到根节点
Node *preorderSearch(Node * root , int data);
void preTrace(Node *result , Stack *s);


void Initial(Stack *s){
    s->top = 0;
}
void push(Stack *s ,int data){
    assert(s->top != SIZE);
    s->array[s->top] = data;
    ++s->top;
}

int pop(Stack *s){
    assert(s->top != 0);
    int data = s->array[s->top - 1];
    --(s->top);
    return data;
}

void print(Stack *s){
    int i = 0;
    while(i<s->top){
        printf("%d%s",s->array[i],(i == s->top-1)?"\n":" ");
        i++;
}
}

int LCA(Node *root , int n1, int n2);


#include <stdio.h>
int main(){
    Node * root = newNode(1);
    Node *n1 = newNode(2);
    Node *n2 = newNode(3);
    root->left = n1;
    n1->pre = root;
    root->right = n2;
    n2->pre = root;
    int a = 2 , b = 3;
    int lca = LCA(root , 2 ,3);
    printf("LCA of %d and %d is %d\n",a,b,lca);
}

Node *newNode(int data){
    Node *n = malloc(sizeof(Node));
    n->elem = data;
    n->left = n->right =n->pre = NULL;
    return n;
}
Node *preorderSearch(Node * root , int data){
    if (root == NULL)
        return NULL;
    else if (data == root->elem)
        return root;
    else{
        Node *result;
        result = preorderSearch(root->left , data);
        if (result == NULL)
            result = preorderSearch(root->right ,data);
        return result;
    }
}
void preTrace(Node *result , Stack *s){
    while (result != NULL){
//        printf("%d\n",result->elem);
        push(s , result->elem);
        result = result->pre;
    }

}
int LCA(Node *root , int n1, int n2){
    Node *n1_p = preorderSearch(root , n1);
    Node *n2_p = preorderSearch(root , n2);
//    printf("%p %p\n",n1_p , n2_p);
//    printf("%d %d\n",n1_p->elem,n2_p->elem);
    assert(n1_p && n2_p);
    Stack s1,s2;
    Initial(&s1);
    Initial(&s2);
    preTrace(n1_p , &s1);
    preTrace(n2_p , &s2);
//    print(&s1);
//    print(&s2);
    int data ,lca;
    while((data = pop(&s1)) == pop(&s2)){
        lca = data;
    }
    return lca;
}
