#include<iostream>
#include<queue>
using namespace std;

class Node
{
	public:
			int data;
			Node* left;
			Node* right;
			bool lthread;
			bool rthread;

			Node(int value)
			{
				data=value;
				left=right=NULL;
				lthread=rthread=0;
			}

			friend class ThreadBST;
};

class ThreadedBST
{
	private:
			Node *root=NULL;
			Node *header=NULL;

	public:
			ThreadedBST()
			{
				header=root=NULL;
			}

			void insert(int value)
			{
				if (root == NULL)
				{
						// create header
						header = new Node(-99);
						header->right = header;

						// create root
						root = new Node(value);

						header->left = root;
						header->lthread = 1;

						root->left = root->right = header;

						return;
				}
				else{
						Node *parent = root;
						Node *temp = new Node(value);

						while(true)
						{
							if (value == parent->data){
								cout << "Node " << value << " already exists" << endl;
								delete temp;
								temp = NULL;
								return;
							}
							else if (value < parent->data){
								// explore left subtree
								if (parent->lthread == 1){
									// left link
									parent = parent->left;
								}
								else{
									// left thread - insert node as left child
									temp->left = parent->left;
									temp->right = parent;
									parent->left = temp;
									parent->lthread = 1;
									return;
								}
							}
							else {	// key > parent->data
								// explore right subtree
								if (parent->rthread == 1){
									// right link
									parent = parent->right;
								}
								else{
									// right thread - insert node as right child
									temp->right = parent->right;
									temp->left = parent;
									parent->right = temp;
									parent->rthread = 1;
									return;
								}

							}
							// end-comparison
						}
						// end-while-loop
					}
			}

			//Function for Inorder traversal
			void inorderTraversal()
			{
				if(root==NULL)
				{
					cout<<"Tree is empty."<<endl;
					return;
				}

				Node* current = root;

				while(current->lthread==1)
				{
					current=current->left;
				}

				while(current!=header)
				{
					cout<<current->data<<" ";

					if(current->rthread==1)
					{
						current=current->right;
						while(current->lthread==1)
						{
							current=current->left;
						}
					}
					else
					{
						current=current->right;
					}
				}
			}

			//Function for Preorder Traversal of the TBST;
			void preorderTraversal()
			{
				if(root==NULL)
				{
					cout<<"Tree is empty"<<endl;
					return;
				}
				Node* current=root;
				do{
					while(current->lthread!=0)
					{
						cout<<current->data<<" ";
						current=current->left;
					}

					cout<<current->data<<" ";

					while(current->rthread==0)
					{
						current=current->right;
						if(current==header)
							return;
					}
					current=current->right;

				}while(current!=header);



			}

			//Function to delete Node of TBST


};
int main()
{
	ThreadedBST tree;
	tree.insert(50);
	tree.insert(30);
	tree.insert(70);
	tree.insert(20);
	tree.insert(40);
	tree.insert(60);
	tree.insert(80);
	//tree.levelOrderTraversal();
	cout<<"Inorder Traversal: ";
	tree.inorderTraversal();
	cout<<endl;
	cout<<endl;
	cout<<"Preorder Traversal: ";
	tree.preorderTraversal();
	//Function to delete Node
	tree.deleteNode(30);
	cout<<"Inorder Traversal after deleting 30: ";
	tree.inorderTraversal();

	return 0;

}
