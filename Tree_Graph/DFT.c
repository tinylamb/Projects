/*
 * =========================================================
 *       Filename:  DFT.c
 *    Description:  
 *    hint :全局的visited[] 
 *
 * =========================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct AdjListNode{
    int dest;
//    bool visited; 错误的开始
    struct AdjListNode* next;
};

struct AdjList{
    struct AdjListNode* head;
};

// A structure to represent a graph. A graph is an array of adjacency lists.
// Size of array will be V (number of vertices in graph)
struct Graph{
    int V;
    struct AdjList* array; /* struct AdjList array[]; */
};

struct AdjListNode* newAdjListNode(int dest);//类似c++中的 new 操作
struct Graph* createGraph(int V);
void addEdge(struct Graph* graph, int src, int dest);
void printGraph(struct Graph* graph);
int tarversal(struct Graph* graph);
void DFT(struct AdjListNode* node, bool* visited);
struct Graph* createGraph(int V);

int main(){
 // create the graph given in above fugure
    int V = 5;
    struct Graph* graph = createGraph(V);
    addEdge(graph, 0, 1);
    addEdge(graph, 2, 3);
 
    // print the adjacency list representation of the above graph
//    printGraph(graph);
    int component = tarversal(graph);
    printf("components of the graph is %d\n",component);
 
    return 0;
}


struct AdjListNode* newAdjListNode(int dest){
    struct AdjListNode* newNode = malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
//    newNode->visited = false;
    return newNode;
}

struct Graph* createGraph(int V){
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->V = V;
    graph->array = malloc(V * sizeof(struct AdjList));
    int i;
    for(i = 0; i < V; i++){ // c 用{}来定义block 而不是 缩进.这里忘记了{} 
        struct AdjListNode* node = newAdjListNode(i);
        graph->array[i].head = node;
    }
    return graph;

}

void addEdge(struct Graph* graph, int src, int dest){
    struct AdjListNode* newNode = newAdjListNode(dest);
    // pointer_a = pointer_b  让 a 指向 (b 指向 的) object
    newNode->next = graph->array[src].head->next; 
    graph->array[src].head->next = newNode;

    //undirected graph
    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head->next;
    graph->array[dest].head->next = newNode;
}

void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->V; ++v)
    {
        struct AdjListNode* pCrawl = graph->array[v].head;
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (pCrawl)
        {
            printf("-> %d", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}


int tarversal(struct Graph* graph){
    int component = 0;// 连通分支数
    int ver = graph->V;
    //全局的visited 而不是在 struct AdjListNode 中添加 visited 属性
    bool *visited = malloc(sizeof(bool) * ver);
    for(int v = 0;v < graph->V; ++v)
        visited[v] = false;
//    bool visited[ver] = {false};  这个错误重要
    for(int v = 0; v < ver; ++v)
        if(visited[v] == false){
            DFT(graph->array[v].head, visited);
            ++component;
            printf("\n");
        }
    return component;

/*  错误的思路 利用visited 属性
 *         if(graph->array[v].head->visited == false){
 *             printf("start is %d\n",v);
 *             DFT(graph->array[v].head);
 *             printf("\n");
 *         }
 */

}

void DFT(struct AdjListNode* node, bool* visited){
    if(visited[node->dest] == true)
        return;
    else{
        printf("%d ",node->dest);
        visited[node->dest] = true;
        struct AdjListNode* neighbour = node->next;
        while(neighbour){
            DFT(neighbour, visited);
            neighbour = neighbour->next;
        }

    }
    //错误的思路,利用visited 属性
/*     if(node->visited == true)
 *         return;
 *     else{
 *         printf("%d ",node->dest);
 *         node->visited = true;
 *         struct AdjListNode* neighbour = node->next;
 *         while(neighbour){
 *             if(neighbour->visited == false)
 *                 DFT(neighbour);
 *             neighbour = neighbour->next;
 *         }
 */

}
