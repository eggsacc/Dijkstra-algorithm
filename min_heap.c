#include"min_heap.h"

minHeap* CreateHeap(int size)
{
    minHeap* heap = (minHeap*)malloc(sizeof(minHeap));
    heapNode* arr = (heapNode*)malloc(sizeof(heapNode) * size);

    if(heap == NULL || arr == NULL)
    {
        printf("Error creating heap: malloc fail\n");
    }

    heap->arr = arr;
    heap->size = 0;
    return heap;
}

static void swap(minHeap* heap, int idx1, int idx2)
{
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

heapNode PopHeap(minHeap* heap)
{
    heapNode temp = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;

    int idx = 0;
    while(1)
    {
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

// int main()
// {
//     minHeap* heap = CreateHeap(5);
//     InsertHeap(heap, 0, 1);
//     InsertHeap(heap, 1, 5);
//     InsertHeap(heap, 2, 0);

//     for(int i = 0; i < heap->size; i++)
//     {
//         printf("node: %d, weight: %d\n", heap->arr[i].node, heap->arr[i].weight);
//     }

//     free(heap);

//     return 0;
// }