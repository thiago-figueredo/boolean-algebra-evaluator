#include <stdlib.h>
#include <assert.h>
#include "./linked_list.h"

LinkedListNode* new_linked_list_node(void* data, LinkedListNode* next)
{
    LinkedListNode* node = malloc(sizeof(LinkedListNode));
    assert(node && "Could not allocate node");

    node->data = data;
    node->next = next;

    return node;
}

LinkedList* new_linked_list()
{
    LinkedList* linked_list = malloc(sizeof(LinkedList));
    assert(linked_list && "Could not allocate linked list");

    linked_list->head = NULL;
    linked_list->tail = NULL;

    return linked_list;
}

void linked_list_insert(LinkedList* linked_list, void* data)
{
    assert(linked_list && "Could not insert into null linked list");
    LinkedListNode* new_node = new_linked_list_node(data, NULL);

    if (!linked_list->head) {
        linked_list->head = new_node;
        linked_list->tail = new_node;
    } else {
        linked_list->tail->next = new_node;
        linked_list->tail = linked_list->tail->next;
    } 
}