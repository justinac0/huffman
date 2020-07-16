// we need to allocate space to store the nodes otherwise our tree cannot be created

#define QUEUE_DEBUG
#include "queue.h"
#include "symbols.h"


const char* sentence =
"hello";
// "Lorem ipsum dolor sit amet "
// "consectetur adipisicing elit. Nam, nisi.";

struct Node huffman_tree_create(Queue* queue) {
    while (queue->length > 1) {
        // the last item in the queue will be the root node.
        if (queue->length >= 2) {
            struct Node a = queue_dequeue(queue);
            struct Node b = queue_dequeue(queue);
            struct Node new_node = node_create((a.occurence + b.occurence), '\0', &a, &b);

            if (queue_enqueue(queue, new_node) == false) {
                printf("huffman tree has failed to enqueue a node!\n");
            }

            queue_sort_bubble(queue);
        }
    }

    return queue_dequeue(queue);
}

int main(void) {
    Symbols symbols = symbols_create(sentence, strlen(sentence));

    Queue queue = queue_create(QUEUE_DEFAULT_SIZE);

    for (int i = 0; i < UINT8_MAX; i++) {
        if (symbols.occurence[i] != 0) {
            bool enqueue_result = queue_enqueue(&queue, node_create(symbols.occurence[i], i, NULL, NULL));
            if (enqueue_result == false) printf("failed to enqueue new node...\n");
        }
    }

    queue_sort_bubble(&queue);
    queue_display(queue);

    struct Node root = huffman_tree_create(&queue);

    queue_destroy(&queue);

    symbols_destroy(&symbols);

    return 0;
}
