#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct LinkedListNode {
    void* data;
    struct LinkedListNode* next;
} LinkedListNode;

typedef struct LinkedList {
    LinkedListNode* head;
    LinkedListNode* tail;
} LinkedList;

LinkedListNode* new_linked_list_node(void* data, LinkedListNode* next);
LinkedList* new_linked_list();
void linked_list_insert(LinkedList* linked_list, void* data);

#endif