//============================================================================
// Name        : 1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <queue>
using namespace std;

class Node
{

	public:
		int data;
		Node *left;
		Node *right;

		Node(int value)
		{
			data=value;
			left=NULL;
			right=NULL;
		}

};

//Function to perform inorder traversal
void inorderTraversal(Node* root)
{
	if(root==NULL)
	{
		return;
	}

	inorderTraversal(root->left);
	cout<<root->data<<" ";
	inorderTraversal(root->right);
}

//Function to perform preorder traversal
void preorderTraversal(Node* root)
{
	if(root==NULL)
	{
			return;
	}
	cout<<root->data<<" ";
	preorderTraversal(root->left);
	preorderTraversal(root->right);
}

//Function to perform postorder traversal
void postorderTraversal(Node* root)
{
	if(root==NULL)
	{
			return;
	}
	postorderTraversal(root->left);
	postorderTraversal(root->right);
	cout<<root->data<<" ";
}

//Function to swap left and right pointers at every node
void swapTree(Node* root)
{	/*
	if(root==NULL)
		return;

	swapTree(root->left);
	swapTree(root->right);
	swap(root->left,root->right);*/

	if(root==NULL)
	{
		return;
	}

	queue<Node*> q;
	q.push(root);

	while(!q.empty())
	{
		Node* curr=q.front();
		q.pop();

		Node* temp=curr->left;
		curr->left = curr->right;
		curr->right=temp;

		if(curr->left!=NULL)
			q.push(curr->left);
		if(curr->right!=NULL)
			q.push(curr->right);
	}
}

//Function to calculate the height of the tree
int getHeight(Node* root)
{
	//Recurrsive
	if(root==NULL)
	{
		return 0;
	}
	int leftHeight = getHeight(root->left);
	int rightHeight = getHeight(root->right);

	return max(leftHeight,rightHeight)+1;

	/*//Iterative
	if(root==NULL)
	{
		return 0;
	}

	const int MAX_SIZE=1000;
	Node* queue[MAX_SIZE];
	int front=0;
	int rear=0;
	int levelSize=1;
	int height=0;

	queue[rear++]=root;

	while(front<rear)
	{
		Node* node = queue[front++];
		levelSize--;

		if(node->left!=NULL)
		{
			queue[rear++]=node->left;
		}

		if(node->left!=NULL)
		{
			queue[rear++]=node->right;
		}

		if(levelSize==0)
		{
			levelSize=rear-front;
			height++;
		}
	}

	return height;*/
}

//Function to copy a binary tree to another using operator=
Node* copyTree(Node* root)
{	//Recursive way
	/*
	if(root==NULL)
	{
		return NULL;
	}

	Node* newNode = new Node(root->data);
	newNode->left=copyTree(root->left);
	newNode->right=copyTree(root->right);

	return newNode;*/

	//Iterative Way
	if (root == NULL)
	        return NULL;

	Node* newRoot=new Node(root->data);

	const int MAX_SIZE=100;
	Node* stack1[MAX_SIZE];
	Node* stack2[MAX_SIZE];
	int top1 =-1;
	int top2 =-1;

	stack1[++top1]=root;
	stack2[++top2]=newRoot;

	while(top1!=-1)
	{
		Node* curr1 = stack1[top1--];
		Node* curr2 = stack2[top2--];

		if(curr1->left)
		{
			curr2->left=new Node(curr1->left->data);
			stack1[++top1]=curr1->left;
			stack2[++top2]=curr2->left;
		}

		if(curr1->right)
		{
			curr2->right=new Node(curr1->right->data);
			stack1[++top1]=curr1->right;
			stack2[++top2]=curr2->right;
		}
	}

	return newRoot;
}

void countNodes(Node* root,int& leaves,int& internalNodes)
{
	//Recursive Code
	/*if(root==NULL)
		return;

	if(root->left==NULL && root->right==NULL)
	{
		leaves++;
	}
	else
	{
		internalNodes++;
	}

	countNodes(root->left,leaves,internalNodes);
	countNodes(root->right,leaves,internalNodes);*/

	//Iterative code
	if(root==NULL)
		return;

	const int MAX_SIZE=100;
	Node* stack[MAX_SIZE];
	int top=-1;

	stack[++top]=root;

	while(top>=0)
	{
		Node* node = stack[top--];

		if(node->left==NULL && node->right==NULL)
		{
			leaves++;
		}
		else
		{
			internalNodes++;

			if(node->right!=NULL)
				stack[++top]=node->right;
			if(node->left!=NULL)
				stack[++top]=node->left;
		}
	}

}

//Function to erase all nodes in a binary tree
void eraseTree(Node* root)
{	//Recursive way

	if(root==NULL)
	{
		return;
	}

	eraseTree(root->left);
	eraseTree(root->right);

	delete root;
	/*
	//Iterative way
	if(root==NULL)
		return;

	const int MAX_SIZE=1000;
	Node* stack[MAX_SIZE];
	int top=-1;

	stack[++top]=root;

	while(top>=0)
	{
		Node* currNode=stack[top--];

		if(currNode->left!=NULL)
			stack[++top]=currNode->left;
		if(currNode->right!=NULL)
			stack[++top]=currNode->right;

		delete currNode;
	}

	cout<<"All Nodes deleted successfully"<<endl;*/
}

//Code for constructing Binary Tree;
Node* constructTree(int arr[],int n) // @suppress("No return")
{
	if(n==0)
		return NULL;

	Node* root= new Node(arr[0]);
	queue<Node*> q;
	q.push(root);

	int i=1;

	while(!q.empty() && i<n)
	{
		Node* curr=q.front();
		q.pop();

		Node* leftChild=NULL;
		Node* rightChild=NULL;

		if(i<n)
		{
			leftChild=new Node(arr[i]);
			curr->left=leftChild;
			q.push(leftChild);
			i++;
		}

		if(i<n)
		{
			rightChild = new Node(arr[i]);
			curr->right=rightChild;
			q.push(rightChild);
			i++;
		}
	}

	return root;
}

//Printing tree in level order
void levelOrderTraversal(Node* root)
{
	queue<Node*> q;
	q.push(root);
	q.push(NULL);

	while(!q.empty())
	{
		Node* temp=q.front();
		q.pop();

		if(temp==NULL)
		{
			cout<<endl;
			if(!q.empty())
			{
				q.push(NULL);
			}
		}
		else
		{
			cout<<temp->data<<" ";

			if(temp->left)
			{
				q.push(temp->left);
			}

			if(temp->right)
			{
				q.push(temp->right);
			}
		}

	}

}

int main()
{
	int arr[] ={1,2,3,4,5,6,7};

	//Constructing a binary tree
	int n = sizeof(arr)/sizeof(arr[0]);
	Node* root=constructTree(arr,n);
	levelOrderTraversal(root);

	//Perform inorder,preorder,postorder
	cout<<"Inorder traversal:";
	inorderTraversal(root);
	cout<<endl;

	cout<<"Preorder traversal";
	preorderTraversal(root);
	cout<<endl;

	cout<<"Postorder traversal:";
	postorderTraversal(root);
	cout<<endl;
	cout<<endl;
	//Swap left and right pointers at every node;
	swapTree(root);
	cout<<"After swapping the tree: "<<endl;
	cout<<"Swapped tree "<<endl;;
	levelOrderTraversal(root);
	cout<<endl;

	//Find the height of the tree
	int height=getHeight(root);
	cout<<"Height of the tree: "<<height<<endl;
	cout<<endl;
	cout<<endl;
	//Copy the tree to another using operator=
	Node* copiedTree = copyTree(root);
	cout<<"Copied Tree: "<<endl;
	levelOrderTraversal(copiedTree);
	cout<<endl;

	//count the number of leaves and internal nodes
	int leaves=0,internalNodes=0;
	countNodes(root,leaves,internalNodes);
	cout<<"Number of leaves: "<<leaves<<endl;
	cout<<"Number of internal nodes: "<<internalNodes<<endl;
	cout<<endl;
	cout<<endl;
	//Erase all nodes in a binary tree
	eraseTree(root);
	root=NULL;
	cout<<"Nodes deleted successfully..."<<endl;
	cout<<endl;
}
