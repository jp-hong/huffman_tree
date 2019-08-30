
#include "huffmantree.h"

void openTextFile(FILE **fp, char *fileName);

void updateFrequencyList(LinkedList *freqList, char c);

void scanText(char *fileName, LinkedList *freqList);

int main(int argc, char *argv[]) {
    LinkedList freqList;
    TreeNode *huffman = NULL;
    int len;

    if (argc != 2) {
        fprintf(stderr, "ERROR: Enter one argument\n");
        return 1;
    }

    freqList = createLinkedList();
    len = getListLength(&freqList);

    scanText(argv[1], &freqList);

    generateHuffmanTree(&huffman, &freqList);
    generateCodes(&huffman, NULL, NA, len);
    printHuffmanTree(huffman);

    destroyLinkedList(&freqList);
    destroyTree(huffman);

    return 0;
}

void openTextFile(FILE **fp, char *fileName) {
    if ((*fp = fopen(fileName, "rt")) == NULL) {
        fprintf(stderr, "ERROR: fopen error\n");
        exit(1);
    }
}

void updateFrequencyList(LinkedList *freqList, char c) {
    ListNode *target;

    if ((target = findNode(freqList, c)) != NULL) {
        target->freq++;
    } else {
        appendListNode(freqList, createListNode(c));
    }
}

void scanText(char *fileName, LinkedList *freqList) {
    FILE *fp;
    char c;

    openTextFile(&fp, fileName);
    c = fgetc(fp);

    while (c != EOF) {
        updateFrequencyList(freqList, c);
        c = fgetc(fp);
    }
}

