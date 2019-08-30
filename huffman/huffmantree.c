
#include "huffmantree.h"

static void getTotalBytesHelper(TreeNode *huffman, int *bytes);

static void printHuffmanTreeHelper(TreeNode *huffman);

void destroyTree(TreeNode *root) {
    if (root == NULL) {
        return;
    }

    destroyTree(root->left);
    destroyTree(root->right);

    destroyTreeNode(root);
}

void destroyTreeNode(TreeNode *node) {
    /*
    Strangely, when this part is enabled the program will sometimes crash with certain text files.
    
    if (node->code != NULL) {
        free(node->code);
    }
    */

    free(node);
}

TreeNode * createTreeNode(char c, int freq) {
    TreeNode *newNode;

    if ((newNode = (TreeNode *)malloc(sizeof(TreeNode))) == NULL) {
        fprintf(stderr, "ERROR: malloc error\n");
        exit(1);
    }

    newNode->c = c;
    newNode->freq = freq;
    newNode->code = NULL;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

TreeNode * createTreeNodeCopy(TreeNode *n) {
    TreeNode *newNode;

    if ((newNode = (TreeNode *)malloc(sizeof(TreeNode))) == NULL) {
        fprintf(stderr, "ERROR: malloc error\n");
        exit(1);
    }

    memcpy(newNode, n, sizeof(TreeNode));
    return newNode;
}

/* comparison function for qsort() in descending order */
int nodeCompare(const void *_elem1, const void *_elem2) {
    TreeNode *elem1 = (TreeNode *)_elem1;
    TreeNode *elem2 = (TreeNode *)_elem2;

    if (elem1->freq < elem2->freq) {
        return 1;
    }

    if (elem1->freq > elem2->freq) {
        return -1;
    }

    return 0;
}

void generateHuffmanTree(TreeNode **huffman, LinkedList *freqList) {
    ListNode *current = freqList->head;
    TreeNode *arr;
    TreeNode  *temp;
    int len = 0, i = 0;

    len = getListLength(freqList);

    if ((arr = (TreeNode *)malloc(sizeof(TreeNode) * len)) ==NULL) {
        fprintf(stderr, "ERROR: malloc error\n");
        exit(1);
    }

    /* fill the array of TreeNode which will be the leaves of the huffman tree */
    while (current != NULL) {
        arr[i].c = current->c;
        arr[i].freq = current->freq;
        arr[i].code = NULL;
        arr[i].left = NULL;
        arr[i].right = NULL;

        current = current->next;
        i++;
    }

    /* generating the tree */
    for (i = len; i > 1; i--) {
        qsort((void *)arr, i, sizeof(TreeNode), nodeCompare);

        temp = createTreeNodeCopy(&arr[i - 2]);
        arr[i - 2].c = -128; /* -128 is just a placeholder value */
        arr[i - 2].freq = arr[i - 1].freq + temp->freq;
        arr[i - 2].right = temp;
        arr[i - 2].left = createTreeNodeCopy(&arr[i - 1]);
    }

    if (((*huffman) = (TreeNode *)malloc(sizeof(TreeNode))) == NULL) {
        fprintf(stderr, "ERROR: malloc error\n");
        exit(1);
    }

    memcpy(*huffman, arr, sizeof(TreeNode));
    free(arr);
}

/* move through the tree to generate the huffman bit patterns */
void generateCodes(TreeNode **huffman, char *prevCode, Direction d, int len) {
    char *newCode;

    if (*huffman == NULL) {
        return;
    }

    if ((newCode = (char *)malloc(sizeof(char) * len)) == NULL) {
        fprintf(stderr, "ERROR: malloc error\n");
        exit(1);
    }

    memset(newCode, 0, sizeof(char) * len);

    /* copy the code of the parent and add 0 or 1 depending on direction */
    if ((d == LEFT || d == RIGHT) && prevCode != NULL) {
        sprintf(newCode, "%s%d", prevCode, d);
    }

    (*huffman)->code = newCode;

    generateCodes(&(*huffman)->left, (*huffman)->code, LEFT, len);
    generateCodes(&(*huffman)->right, (*huffman)->code, RIGHT, len);
}

int getTotalBytes(TreeNode *huffman) {
    int bytes = 0;

    getTotalBytesHelper(huffman, &bytes);
    bytes  = bytes % 8 == 0 ? bytes / 8 : bytes / 8 + 1;

    return bytes;
}

static void getTotalBytesHelper(TreeNode *huffman, int *bytes) {
    if (huffman == NULL) {
        return;
    }

    getTotalBytesHelper(huffman->left, bytes);
    getTotalBytesHelper(huffman->right, bytes);

    if (huffman->left == NULL && huffman->right == NULL) {
        *bytes += huffman->freq * strlen(huffman->code);
    }
}

void printHuffmanTree(TreeNode *huffman) {
    int bytes = getTotalBytes(huffman);

    printHuffmanTreeHelper(huffman);
    printf("%d bytes\n", bytes);
}

static void printHuffmanTreeHelper(TreeNode *huffman) {
    if (huffman == NULL) {
        return;
    }

    printHuffmanTreeHelper(huffman->left);
    printHuffmanTreeHelper(huffman->right);

    if (huffman->left == NULL && huffman->right == NULL) {
        if (isprint(huffman->c)) {
            printf("\'%c\' : %12s (%4d * %5d)\n", huffman->c, huffman->code, (int)strlen(huffman->code), huffman->freq);
        } else {
            printf("%03d : %12s (%4d * %5d)\n", huffman->c, huffman->code, (int)strlen(huffman->code),huffman->freq);
        }
    }
}

