// Red Black Tree 
// b. Try implementing (a) Red Black Tree insertion in C Program and print those datas with InOrder Traversal
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    char color;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->color = 'R';
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void colorRed(struct Node* node) {
    if (node != NULL)
        node->color = 'R';
}

void colorBlack(struct Node* node) {
    if (node != NULL)
        node->color = 'B';
}

int isRoot(struct Node* node) {
    return node->parent == NULL;
}

int isLeaf(struct Node* node) {
    return node == NULL;
}

void leftRotate(struct Node** root, struct Node* node) {
    struct Node* rightChild = node->right;
    node->right = rightChild->left;

    if (!isLeaf(rightChild->left))
        rightChild->left->parent = node;

    rightChild->parent = node->parent;

    if (isRoot(node))
        *root = rightChild;
    else if (node == node->parent->left)
        node->parent->left = rightChild;
    else
        node->parent->right = rightChild;

    rightChild->left = node;
    node->parent = rightChild;
}

void rightRotate(struct Node** root, struct Node* node) {
    struct Node* leftChild = node->left;
    node->left = leftChild->right;

    if (!isLeaf(leftChild->right))
        leftChild->right->parent = node;

    leftChild->parent = node->parent;

    if (isRoot(node))
        *root = leftChild;
    else if (node == node->parent->left)
        node->parent->left = leftChild;
    else
        node->parent->right = leftChild;

    leftChild->right = node;
    node->parent = leftChild;
}

void fixRedBlackTree(struct Node** root, struct Node* node) {
    struct Node* parent = NULL;
    struct Node* grandparent = NULL;

    while ((node != *root) && (node->color != 'B') && (node->parent->color == 'R')) {
        parent = node->parent;
        grandparent = node->parent->parent;

        if (parent == grandparent->left) {
            struct Node* uncle = grandparent->right;

            if (uncle != NULL && uncle->color == 'R') {
                colorBlack(uncle);
                colorBlack(parent);
                colorRed(grandparent);
                node = grandparent;
            } else {
                if (node == parent->right) {
                    leftRotate(root, parent);
                    node = parent;
                    parent = node->parent;
                }

                rightRotate(root, grandparent);
                char tempColor = parent->color;
                parent->color = grandparent->color;
                grandparent->color = tempColor;
                node = parent;
            }
        } else {
            struct Node* uncle = grandparent->left;

            if (uncle != NULL && uncle->color == 'R') {
                colorBlack(uncle);
                colorBlack(parent);
                colorRed(grandparent);
                node = grandparent;
            } else {
                if (node == parent->left) {
                    rightRotate(root, parent);
                    node = parent;
                    parent = node->parent;
                }

                leftRotate(root, grandparent);
                char tempColor = parent->color;
                parent->color = grandparent->color;
                grandparent->color = tempColor;
                node = parent;
            }
        }
    }

    colorBlack(*root);
}

void insertNode(struct Node** root, struct Node* newNode) {
    if (*root == NULL) {
        *root = newNode;
        colorBlack(*root);
        return;
    }

    struct Node* current = *root;
    struct Node* parent = NULL;

    while (!isLeaf(current)) {
        parent = current;

        if (newNode->data < current->data)
            current = current->left;
        else
            current = current->right;
    }

    newNode->parent = parent;

    if (newNode->data < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;

    fixRedBlackTree(root, newNode);
}

void inorderTraversal(struct Node* node) {
    if (node == NULL)
        return;

    inorderTraversal(node->left);
    printf("%d ", node->data);
    inorderTraversal(node->right);
}

int main() {
    
    int data[] = {41, 22, 5, 51, 48, 29, 18, 21, 45, 3};
    int n = sizeof(data) / sizeof(data[0]);

    struct Node* root = NULL;

    for (int i = 0; i < n; i++) {
        struct Node* newNode = createNode(data[i]);
        insertNode(&root, newNode);
    }

    printf("Inorder Traversal of Created Tree\n");
    inorderTraversal(root);

    return 0;
}
