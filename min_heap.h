#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
 * Heap & node structs
 */
typedef struct 
{
    int node;
    int weight;
}heapNode;

typedef struct
{
    heapNode* arr;
    int size;
}minHeap;

/*
 * Public functions
 */
minHeap* CreateHeap(int size);
void InsertHeap(minHeap* heap, int node, int weight);
heapNode PopHeap(minHeap* heap);