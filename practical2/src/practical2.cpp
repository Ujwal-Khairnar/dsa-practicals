//============================================================================
// Name        : practical2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include<iostream>
#include<queue>
using namespace std;

class Node {
public:
	int data;
	Node *left;
	Node *right;

	Node(int d) {
		this->data = d;
		this->left = NULL;
		this->right = NULL;
	}
};

Node* buildTree(Node *root) {
	int data;
	cout << "Enter the data...";
	cin >> data;
	root = new Node(data);

	if (data == -1) {
		return NULL;
	}

	cout << "Enter data for inserting in left" << data << endl;
	root->left = buildTree(root->left);
	cout << "Enter data for inserting in right" << data << endl;
	root->right = buildTree(root->right);

	return root;

}

void levelOrderTraversal(Node* root) {
    queue<Node*> q;
    q.push(root);
    q.push(NULL);

    while(!q.empty()) {
        Node* temp = q.front();
        q.pop();

        if(temp == NULL) {
            //purana level complete traverse ho chuka hai
            cout << endl;
            if(!q.empty()) {
                //queue still has some child ndoes
                q.push(NULL);
            }
        }
        else{
            cout << temp -> data << " ";
            if(temp ->left) {
                q.push(temp ->left);
            }

            if(temp ->right) {
                q.push(temp ->right);
            }
        }
    }

}
int main() {
	Node *root = NULL;
	//input:1 3 7 -1 -1 11 -1 -1 5 17 -1 -1 -1
	//creating a Tree
	root = buildTree(root);
	cout << "Printing level "<<endl;;
	levelOrderTraversal(root);
	return 0;
}
