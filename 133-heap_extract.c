#include <stdlib.h>
#include "binary_trees.h"

/**
 * swap - Swaps the values of two heap nodes
 * @node1: First heap node
 * @node2: Second heap node
 */
void swap(heap_t *node1, heap_t *node2) {
    int temp = node1->n;
    node1->n = node2->n;
    node2->n = temp;
}

/**
 * heapify_down - Restores the heap property by moving a node down the heap
 * @root: Pointer to the root node of the heap
 */
void heapify_down(heap_t *root) {
    heap_t *largest = root;
    heap_t *left = root->left;
    heap_t *right = root->right;

    if (left != NULL && left->n > largest->n) {
        largest = left;
    }

    if (right != NULL && right->n > largest->n) {
        largest = right;
    }

    if (largest != root) {
        swap(root, largest);
        heapify_down(largest);
    }
}

/**
 * get_last_node - Finds the last node in the heap using level-order traversal
 * @root: Pointer to the root node of the heap
 *
 * Return: Pointer to the last node
 */
heap_t *get_last_node(heap_t *root) {
    if (root == NULL) {
        return NULL;
    }

    heap_t **queue = malloc(sizeof(heap_t *) * 1024);
    int front = 0;
    int rear = 0;

    queue[rear++] = root;
    heap_t *last_node = NULL;

    while (front < rear) {
        heap_t *node = queue[front++];

        if (node->left != NULL) {
            queue[rear++] = node->left;
        }

        if (node->right != NULL) {
            queue[rear++] = node->right;
        }

        last_node = node;
    }

    free(queue);
    return last_node;
}

/**
 * heap_extract - Extracts the root node of a Max Binary Heap
 * @root: Double pointer to the root node of the heap
 *
 * Return: Value stored in the root node, or 0 on failure
 */
int heap_extract(heap_t **root) {
    if (root == NULL || *root == NULL) {
        return 0;  // Return 0 if root is NULL
    }

    int extracted_value = (*root)->n;

    heap_t *last_node = get_last_node(*root);

    if (*root == last_node) {
        free(*root);
        *root = NULL;
        return extracted_value;
    }

    (*root)->n = last_node->n;

    heap_t *parent = last_node->parent;

    if (parent->left == last_node) {
        parent->left = NULL;
    } else {
        parent->right = NULL;
    }

    free(last_node);

    heapify_down(*root);

    return extracted_value;
}
