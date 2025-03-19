#include"min_heap.h"

/*
 * @brief Mallocs new heap struct
 * @return minHeap* heap
 * @note returns NULL if malloc unsuccessful
 */
minHeap* CreateHeap(int size)
{
    minHeap* heap = (minHeap*)malloc(sizeof(minHeap));
    heapNode* arr = (heapNode*)malloc(sizeof(heapNode) * size);

    /* Check if malloc successful */
    if(heap == NULL || arr == NULL)
    {
        printf("Error creating heap: malloc fail\n");
        return NULL;
    }

    heap->arr = arr;
    heap->size = 0;
    return heap;
}

/*
 * @brief Swaps 2 elements in a heap
 * @return void
 * @note Static function
 */
static void swap(minHeap* heap, int idx1, int idx2)
{
    /* Check if indexes are valid */
    if(idx1 > heap->size || idx1 < 0 || idx2 > heap->size || idx2 < 0)
    {
        printf("Heap swap error: index out of heap size\n");
        return;
    }

    if(idx1 == idx2)
    {
        return;
    }

    heapNode temp = heap->arr[idx1];
    heap->arr[idx1] = heap->arr[idx2];
    heap->arr[idx2] = temp;
}

/*
 * @brief Insert new node in heap based on node weight
 * @return void
 */
void InsertHeap(minHeap* heap, int node, int weight)
{
    heap->arr[heap->size].node = node;
    heap->arr[heap->size].weight = weight;
    int idx = heap->size;
    while(idx > 0 && heap->arr[idx].weight < heap->arr[(idx - 1) / 2].weight)
    {
        swap(heap, idx, (idx - 1) / 2);
        idx = (idx - 1) / 2;
    }
    heap->size++;
}

/*
 * @brief Pop & returns the node with smallest weight
 * @return heapNode node
 */
heapNode PopHeap(minHeap* heap)
{
    if(heap->size == 0)
    {
        printf("Pop heap error: heap empty\n");
    }

    heapNode temp = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;

    int idx = 0;
    while(1)
    {
        /* Check if node is larger than children nodes */
        int left_idx = idx * 2 + 1;
        int right_idx = idx * 2 + 2;
        int smallest = idx;

        if(left_idx < heap->size && heap->arr[left_idx].weight < heap->arr[smallest].weight)
        {
            smallest = left_idx;
        }

        if(right_idx < heap->size && heap->arr[right_idx].weight < heap->arr[smallest].weight)
        {
            smallest = right_idx;
        }

        /* If a smaller child node is present, swap values with it */
        if(smallest != idx)
        {
            swap(heap, idx, smallest);
            idx = smallest;
        }
        
        else{
            break;
        }
    }

    return temp;
}
