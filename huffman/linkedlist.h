
#include <stdio.h>
#include <stdlib.h>

typedef struct listnode {
    char c;
    int freq;
    char *code;
    struct listnode *next;
} ListNode;

typedef struct linkedlist {
    ListNode *head;
    ListNode *tail;
} LinkedList;

LinkedList createLinkedList();

void destroyLinkedList(LinkedList *ll);

ListNode * createListNode(char c);

void destroyListNode(ListNode *n);

ListNode * findNode(LinkedList *ll, char c);

void appendListNode(LinkedList *ll, ListNode *n);

int getListLength(LinkedList *ll);

