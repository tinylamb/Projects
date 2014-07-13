/*
 * =========================================================
 *       Filename:  graph_adjlist.c
 *    Description:  图的adjlist 实现
 *
 * =========================================================
 */
#include <stdio.h>
#include <stdlib.h>

struct AdjListNode{
    int dest;
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
int main(){
 // create the graph given in above fugure
    int V = 5;
    struct Graph* graph = createGraph(V);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
 
    // print the adjacency list representation of the above graph
    printGraph(graph);
 
    return 0;
}


struct AdjListNode* newAdjListNode(int dest){
    struct AdjListNode* newNode = malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int V){
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->V = V;
    graph->array = malloc(V * sizeof(struct AdjList));
    for(int i = 0; i < V; i++)
        graph->array[i].head = NULL;
    return graph;

}

void addEdge(struct Graph* graph, int src, int dest){
    struct AdjListNode* newNode = newAdjListNode(dest);
    // pointer_a = pointer_b  让 a 指向 (b 指向 的) object
    newNode->next = graph->array[src].head; 
    graph->array[src].head = newNode;

    //undirected graph
    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
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
