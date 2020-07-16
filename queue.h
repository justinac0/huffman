#ifndef _QUEUE_H_
#define _QUEUE_H_

#define QUEUE_DEFAULT_SIZE UINT8_MAX

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

struct Node {
    uint32_t occurence;
    uint8_t  symbol;
    struct Node* left;
    struct Node* right;
};

struct Node node_create(uint32_t occurence, uint8_t symbol, struct Node* left, struct Node* right) {
    struct Node node;
    node.occurence = occurence,
    node.symbol = symbol,
    node.left = (struct Node*) malloc(sizeof(struct Node));
    node.right = (struct Node*) malloc(sizeof(struct Node));

    if (node.left == NULL || node.right == NULL) {
        printf("failed to allocate memory for leaf nodes!\n");
    } else {
        node.left = left;
        node.right = right;
    }

    return node;
}

typedef struct {
    size_t capacity;
    size_t length;
    struct Node* nodes;
} Queue;

Queue queue_create(size_t capacity) {
    Queue queue;
    queue.capacity = capacity;
    queue.length   = 0;
    queue.nodes    = (struct Node*) calloc(sizeof(struct Node), capacity);
    if (!queue.nodes) {
        fprintf(stderr, "failed to allocate memory for queue!\n");
    }

    return queue;
}

void queue_destroy(Queue* queue) {
    free(queue->nodes);
    queue->nodes  = NULL;
    queue->capacity = 0;
    queue->length = 0;
}

// todo: re-allocate space if queue is full
bool queue_enqueue(Queue* queue, struct Node node) {
    // check to see if there is any space left in queue
    if (queue->capacity == queue->length) return false;

    #ifdef QUEUE_DEBUG
    printf("[ EQUEUE ] occurence: %d, symbol: \'%c\'\n", node.occurence, node.symbol);
    #endif

    queue->nodes[queue->length++] = node;
    
    return true;
}

struct Node queue_dequeue(Queue* queue) {
    struct Node node = queue->nodes[queue->length - 1];

    #ifdef QUEUE_DEBUG
    printf("[ DEQUEUE ] occurence: %d, symbol: \'%c\'\n", node.occurence, node.symbol);
    #endif

    queue->nodes[queue->length - 1 ] = (struct Node){0};
    queue->length--;

    return node;
}

void queue_display(Queue queue) {
    printf("Displaying Queue (Length: %zu : Capacity: %zu)\n", queue.length, queue.capacity);
    uint32_t occurence = 0;
    for (int i = 0; i < queue.length; i++) {
        printf("%d = { occurence: %d, symbol: \'%c\' }\n",
               i,
               queue.nodes[i].occurence,
               queue.nodes[i].symbol);
        occurence += queue.nodes[i].occurence;
    }

    printf("Message Length: %d\n\n", occurence);
}

void queue_sort_bubble(Queue* queue) {
    for (int i = 0; i < queue->length; i++) {
        if (i < (queue->length - 1)) {
            if (queue->nodes[i].occurence < queue->nodes[i+1].occurence) {
                struct Node tmp;
                tmp.occurence = queue->nodes[i].occurence;
                tmp.symbol    = queue->nodes[i].symbol;
                tmp.left      = queue->nodes[i].left;
                tmp.right     = queue->nodes[i].right;

                queue->nodes[i].occurence = queue->nodes[i+1].occurence;
                queue->nodes[i].symbol    = queue->nodes[i+1].symbol;
                queue->nodes[i].left      = queue->nodes[i+1].left;
                queue->nodes[i].right     = queue->nodes[i+1].right;

                queue->nodes[i+1].occurence = tmp.occurence;
                queue->nodes[i+1].symbol    = tmp.symbol;
                queue->nodes[i+1].left      = tmp.left;
                queue->nodes[i+1].right     = tmp.right;
            }
        }
    }

    uint32_t fails = 0;
    for (int i = 0; i < queue->length; i++) { // check to see if sorting is done
        if (i < (queue->length - 1)) {
            if (queue->nodes[i].occurence < queue->nodes[i+1].occurence) {
                fails++;
            }
        }
    }


    if (fails > 0) queue_sort_bubble(queue);

    queue_display(*queue);
}

#endif // _QUEUE_H_
