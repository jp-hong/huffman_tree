
#include <string.h>
#include <ctype.h>
#include "linkedlist.h"

typedef struct treenode {
    char c;
    int freq;
    char *code;
    struct treenode *left;
    struct treenode *right;
} TreeNode;

typedef enum direction {
    LEFT,
    RIGHT,
    NA = -1
} Direction;

void destroyTree(TreeNode *root);

void destroyTreeNode(TreeNode *node);

TreeNode * createTreeNode(char c, int freq);

TreeNode * createTreeNodeCopy(TreeNode *n);

int nodeCompare(const void *_elem1, const void *_elem2);

void generateHuffmanTree(TreeNode **huffman, LinkedList *freqList);

void generateCodes(TreeNode **huffman, char *prevCode, Direction d, int len);

int getTotalBytes(TreeNode *huffman);

void printHuffmanTree(TreeNode *huffman);

