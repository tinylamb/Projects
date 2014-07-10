/*
 * =========================================================
 *       Filename:  nthtolast.cpp
 *    Description:  Implement an algorithm to find the nth
 *    to last element of a singly linked list.
 *    
 *
 * =========================================================
 */
#include <iostream>
using namespace std;

typedef struct node{
    int data;
    struct node* next;
}Node;

Node* findNth(Node* head,int n);
Node* init(int a[],int n);
void findNth_v1(Node* head);

int N = 4;
Node* nth = NULL;
int main(){
    int n = 4;
    int a[] = {1,3,4,1,3,5,6,1,3,4};
    Node* head = init(a,sizeof(a)/sizeof(a[0]));
//    Node* p = findNth(head,n);
    findNth_v1(head);
    if(nth)
        cout<< nth->data << endl;
    else
        cout<< "None" << endl;
    return 0;
}

Node* init(int a[],int n){
    Node* head, *tail;
    for(int i = 0;i < n;i++){
        Node* nd = new Node(); /* in C Node *nd = malloc(sizeof(Node)) */
        nd->data = a[i];
        if(i == 0){
            head = tail = nd;
            continue;
        }
        tail->next = nd;
        tail = nd;
    }
    return head;
}

Node* findNth(Node* head,int n){
    if(head == NULL || n < 1)
        return NULL;
    Node* p = head, *q = head;
    while(n > 0 && q){
        q = q->next;
        n--;
    }
    if(n > 0)
        return NULL;
    while(q){
        p = p->next;
        q = q->next;
    }
    return p;
}

void findNth_v1(Node* head){
    if(head == NULL)
        return;
    findNth_v1(head->next);
    if(N == 1)
        nth = head;
    N--;
}
