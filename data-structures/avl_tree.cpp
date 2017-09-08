/* AVL Tree (Self-Balancing Binary Search Tree) with Nodes */

#include <algorithm>

using namespace std;

class Node
{
public:
    Node *left;
    Node *right;
    int data;
    int height;

    Node(int _data)
    {
        data = _data;
        height = 0;
    }

    ~Node()
    {
        delete left;
        delete right;
    }
};

class AvlTree
{
private:
    Node *root;

    int getHeight(Node *node)
    {
        if (!node)
            return -1;
        return node->height;
    }

    Node *rightRotate(Node *node)
    {
        Node *leftChild = node->left;

        node->left = leftChild->right;
        leftChild->right = node;

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        leftChild->height =
            1 + max(getHeight(leftChild->left), getHeight(leftChild->right));

        return leftChild;
    }

    Node *leftRotate(Node *node)
    {
        Node *rightChild = node->right;

        node->right = rightChild->left;
        rightChild->left = node;

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        rightChild->height =
            1 + max(getHeight(rightChild->left), getHeight(rightChild->right));

        return rightChild;
    }

    Node *balance(Node *node, int data)
    {
        int balance = getHeight(node->left) - getHeight(node->right);

        if (balance > 1 && data < node->left->data) {
            node = rightRotate(node);
        } else if (balance > 1 && data > node->left->data) {
            node->left = leftRotate(node->left);
            node = rightRotate(node);
        } else if (balance < -1 && data > node->right->data) {
            node = leftRotate(node);
        } else if (balance < -1 && data < node->right->data) {
            node->right = rightRotate(node->right);
            node = leftRotate(node);
        }

        return node;
    }

    Node *insert(Node *node, int data)
    {
        if (!node)
            return new Node(data);

        if (data < node->data) {
            node->left = insert(node->left, data);
        } else {
            node->right = insert(node->right, data);
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        node = balance(node, data);

        return node;
    }

public:
    AvlTree(int data) { root = new Node(data); }

    ~AvlTree() { delete root; }

    void insert(int data) { insert(root, data); }
};
