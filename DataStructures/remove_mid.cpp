/*
 * =========================================================
 *       Filename:  remove_mid.cpp
 *    Description:  
 *    Implement an algorithm to delete a node in the middle of a single linked list, given only access to that node.
      Input: the node ‘c’ from the linked list a->b->c->d->e Result: nothing is returned, but the new linked list looks like a->b->d->e
 *
 * =========================================================
 */
#include <iostream>
using namespace std;

typedef struct node{
    int data;
    struct node* next;
}Node;

Node* init(int a[], int n);
bool remove(Node* c);
void printList(Node* head);
int main(){
    int n = 10;
    int a[] = { 9, 2, 1, 3, 5, 6, 2, 6, 3, 1 };
    node *head = init(a, n);
    int cc = 3;
    node *c = head;
    for(int i=1; i<cc; ++i) c = c->next;
    printList(head);
    if(remove(c))
        printList(head);
    else
        cout<<"failure"<<endl;
    return 0;
}



Node* init(int a[], int n){
    Node *head, *tail;
    for(int i = 0; i < n; i++){
        Node* node = new Node();
        node->data = a[i];
        if(i == 0){
            head = tail = node;
            continue;
        }
        tail->next = node;
        tail = node;
    }
    return head;
}



bool remove(Node* c){
    if(c == NULL || c->next == NULL)
        return false;
    // if(c->next==NULL){//c为最后一个元素时直接删除，不行，最后还是会打印出一个为0的结点，需要特殊处理
    //     delete c;
    //     return;
    // }
    Node* q = c->next;
    c->data = q->data;
    c->next = q->next;
    delete q;
    return true;
}

void printList(Node* head){
    while(head){
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}
