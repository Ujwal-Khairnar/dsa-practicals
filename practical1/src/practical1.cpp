//============================================================================
// Name        : practical1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class Node
{
private:
    string keyword;
    string meaning;
    Node *left;
    Node *right;

public:
    Node(string key, string value)
    {
        keyword = key;
        meaning = value;
        left = NULL;
        right = NULL;
    }
    friend class BST;
};

class BST
{
private:
    Node *root;

public:
    BST()
    {
        root = NULL;
    }

    void displayAscendingOrder()
    {
        if (root == NULL)
        {
            cout << "Dictionary is empty" << endl;
            return;
        }

        Node *current = root;
        Node *stack[100];
        int top = -1;

        while (current != NULL || top != -1)
        {
            while (current != NULL)
            {
                stack[++top] = current;
                current = current->left;
            }

            current = stack[top--];
            cout << current->keyword << ": " << current->meaning << endl;

            current = current->right;
        }
    }

    void displayDescendingOrder()
    {
        if (root == NULL)
        {
            cout << "Dictionary is empty" << endl;
            return;
        }

        Node *current = root;
        Node *stack[100];
        int top = -1;

        while (current != NULL || top != -1)
        {
            while (current != NULL)
            {
                stack[++top] = current;
                current = current->left;
            }

            current = stack[top--];
            cout << current->keyword << ": " << current->meaning << endl;

            current = current->right;
        }
    }
    void insertkeyword(string keyword, string meaning)
    {
        Node *newNode = new Node(keyword, meaning);
        // base case
        if (root == NULL)
        {
            root = newNode;
            cout << "Keyword added successfully" << endl;
            return;
        }

        Node *current = root;
        while (true)
        {
            if (keyword < current->keyword)
            {
                if (current->left == NULL)
                {
                    current->left = newNode;
                    cout << "Keyword added successfully" << endl;
                    return;
                }
                else
                {
                    current = current->left;
                }
            }
            else if (keyword > current->keyword)
            {
                if (current->right == NULL)
                {
                    current->right = newNode;
                    cout << "Keyword added successfully" << endl;
                    return;
                }
                else
                {
                    current = current->right;
                }
            }
            else
            {
                cout << "Keyword already exists" << endl;
                return;
            }
        }
    }
    void deleteKeyword(string keyword)
    {
        if (root == NULL)
        {
            cout << "Dictionary is empty..." << endl;
            return;
        }

        Node *current = root;
        Node *parent = NULL;
        bool isLeftChild = false;

        while (current != NULL && current->keyword != keyword)
        {
            parent = current;

            if (keyword < current->keyword)
            {
                current = current->left;
                isLeftChild = true;
            }
            else
            {
                current = current->right;
                isLeftChild = false;
            }
        }

        if (current == NULL)
        {
            cout << "Keyword not found..." << endl;
            return;
        }

        // Case1:Node to be deleted has no children
        if (current->left == NULL && current->right == NULL)
        {
            if (current == root)
            {
                root = NULL;
            }
            else if (isLeftChild)
            {
                parent->left = NULL;
            }
            else
            {
                parent->right = NULL;
            }

            delete current;
        }
        // Case 2: Node to be deleted has only one child
        else if (current->left == NULL)
        {
            if (current == root)
            {
                root = current->right;
            }
            else if (isLeftChild)
            {
                parent->left = current->right;
            }
            else
            {
                parent->right = current->right;
            }
        }
        else if (current->right == NULL)
        {
            if (current == root)
            {
                root = current->left;
            }
            else if (isLeftChild)
            {
                parent->left = current->left;
            }
            else
            {
                parent->right = current->left;
            }

            delete current;
        }
        // Case3:Node to be deleted has two children
        else
        {
            Node *successor = getSuccessor(current);

            if (current == root)
            {
                root = successor;
            }
            else if (isLeftChild)
            {
                parent->left = successor;
            }
            else
            {
                parent->right = successor;
            }

            successor->left = current->left;

            if (successor != current->right)
            {
                successor->right = current->right;
            }

            delete current;
        }
    }

    Node *getSuccessor(Node *node)
    {
        if (node == NULL)
        {
            return NULL;
        }

        // If the right child exists, find the minimum node in the right subtree
        if (node->right != NULL)
        {
            Node *current = node->right;
            while (current->left != NULL)
            {
                current = current->left;
            }
            return current;
        }
    }

    void updateKeyword(string keyword, string inmeaning)
    {
        Node *current = root;
        while (current != NULL && current->keyword != keyword)
        {
            if (keyword < current->keyword)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }

        if (current==NULL)
        {
            cout << "Keyword not found." << endl;
            return;
        }
        else
        {
            current->meaning = inmeaning;
            cout << "Keyword updated successfully." << endl;
        }
    }
};

int main()
{
    BST dictionary;
    dictionary.insertkeyword("apple", "a fruit");
    dictionary.insertkeyword("banana", "a yellow fruit");
    dictionary.insertkeyword("cat", "a small mammal");

    cout << "Ascending order: " << endl;
    dictionary.displayAscendingOrder();

    cout << "Descending order: " << endl;
    dictionary.displayDescendingOrder();

    dictionary.updateKeyword("banana", "a curved yellow fruit");
    cout << endl<< "Update meaning of 'banana':" << endl;
    dictionary.displayAscendingOrder();

    dictionary.deleteKeyword("cat");
    cout << endl<< "After deleting 'cat': " << endl;
    dictionary.displayAscendingOrder();

    return 0;
}
