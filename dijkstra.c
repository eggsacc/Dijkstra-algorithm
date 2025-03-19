#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "min_heap.h"

/* 
 * Macros definition
 */
#define V 9        // Number of nodes in graph
#define INF 9999


/*
 * @brief Adds an bi-directional edge with weight to a graph
 * @return void
 */
void addEdge(int mat[V][V], int p1, int p2, int weight)
{
    mat[p1][p2] = weight;
    mat[p2][p1] = weight;
}

/*
 * @brief Utility function to print all edges in a graph
 * @return void
 */
void printGraph(int mat[V][V])
{
    printf("**** Graph nodes ****\n");
    for(int i = 0; i < V; i++)
    {
        /* Only for columns [row+1] and above to avoid printing repeated edges */
        for(int j = i+1; j < V; j++)
        {
            if(mat[i][j] != 0)
            {
                printf("%d <-> %d, weight: %d\n", i, j, mat[i][j]);
            }
        }
    }
    printf("*********************\n\r");
}

/*
 * @brief Dijkstra's algorithm
 * @return void
 */
void Dijkstra(int graph[V][V], int start, int end)
{
    /* Arrays to track node weights & previous nodes to back-track later */
    int node_weight[V];
    int prev_node[V];

    /* Create min heap */
    minHeap* heap = CreateHeap(V);
    
    /* Initialize array values */
    for (int i = 0; i < V; i++)
    {
        node_weight[i] = INF;
        prev_node[i] = -1;
    }

    node_weight[start] = 0;

    /* Push starting node onto heap with weight 0 */
    InsertHeap(heap, start, 0);

    while(heap->size > 0)
    {
        /* Get node with lowest weight */
        heapNode node = PopHeap(heap);
        
        if(node.node == end)
        {
            break;
        }

        for(int i = 0; i < V; i++)
        {
            /* If edge exist (weight not 0) */
            if(graph[node.node][i] != 0)
            {
                int new_weight = node.weight + graph[node.node][i];

                /* Update node weight, previous node & push node onto heap if new weight is less than current weight */
                if(new_weight < node_weight[i])
                {
                    node_weight[i] = new_weight;
                    prev_node[i] = node.node;
                    InsertHeap(heap, i, new_weight);
                }
            }
        }
    }

    int path[V] = {0};
    int path_idx = 0;

    /* Back-track starting from end node to obtain path */
    for(int i = end; i != -1; i = prev_node[i])
    {
        path[path_idx] = i;
        path_idx++;
    }

    /* Print path in reverse */
    printf("Path: ");
    for(int i = path_idx - 1; i >= 0; i--)
    {
        if(i != 0)
        {
            printf("%d -> ", path[i]);
        }
        else
        {
            printf("%d\n\r", path[i]);
        }
    }

    /* Free malloced heap */
    free(heap);
}

int main()
{
    /* Create graph & add edges */
    int graph[V][V] = {0};
    addEdge(graph, 0, 1, 4);
    addEdge(graph, 0, 7, 8);
    addEdge(graph, 1, 7, 11);
    addEdge(graph, 7, 6, 1);
    addEdge(graph, 7, 8, 7);
    addEdge(graph, 1, 2, 8);
    addEdge(graph, 6, 5, 2);
    addEdge(graph, 6, 8, 6);
    addEdge(graph, 8, 2, 2);
    addEdge(graph, 2, 5, 4);
    addEdge(graph, 2, 3, 7);
    addEdge(graph, 3, 5, 14);
    addEdge(graph, 3, 4, 9);
    addEdge(graph, 5, 4, 10);

    printGraph(graph);

    Dijkstra(graph, 3, 7);

    return 0;
}
