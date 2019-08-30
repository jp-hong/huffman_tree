
#include "linkedlist.h"

LinkedList createLinkedList() {
    LinkedList newLinkedList = {NULL, NULL};
    return newLinkedList;
}

void destroyLinkedList(LinkedList *ll) {
    ListNode *current = ll->head, *temp;

    while (current != NULL) {
        temp = current;
        current = current->next;
        destroyListNode(temp);
    }
}

ListNode * createListNode(char c) {
    ListNode *newNode;

    if ((newNode = (ListNode *)malloc(sizeof(ListNode))) == NULL) {
        fprintf(stderr, "ERROR: malloc error\n");
        exit(1);
    }

    newNode->c = c;
    newNode->freq = 1;
    newNode->next = NULL;

    return newNode;
}

void destroyListNode(ListNode *n) {
    if (n != NULL) {
        free(n);
    }
}

ListNode * findNode(LinkedList *ll, char c) {
    ListNode *current = ll->head;

    while (current != NULL) {
        if (current->c == c) {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

void appendListNode(LinkedList *ll, ListNode *n) {
    if (ll->head == NULL) {
        ll->head = n;
        ll->tail = n;
    } else {
        ll->tail->next = n;
        ll->tail = ll->tail->next;
    }
}

int getListLength(LinkedList *ll) {
    int len = 0;
    ListNode *current = ll->head;

    while (current != NULL) {
        len++;
        current = current->next;
    }

    return len;
}

