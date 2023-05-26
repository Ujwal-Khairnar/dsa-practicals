//============================================================================
// Name        : practical6.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stack>
#include <queue>
using namespace std;

class Node
{
	private:
			string place;
			Node* next;
	public:
			Node()
			{
				this->place=" ";
				next=NULL;
			}

			Node(string p)
			{
				this->place=p;
				next=NULL;
			}

			friend class Graph;

			bool has_next()
			{
				return next!=NULL;
			}

			Node* get_next()
			{
				return next;
			}

			void add_next(Node* node)
			{
				next=node;
			}
};

class Graph
{
	private:
			int nv=0;
			Node** vertices;
	public:
			Graph()
			{
				cout<<"Enter the number of vertices: ";
				cin>>nv;
				cout<<endl;

				vertices = new Node*[nv];
			}

			//function for creating the adjacency list
			void create()
			{
				for(int i=0;i<nv;i++)
				{
					cout<<"Enter the name of place: ";
					string curr;
					cin>>curr;

					vertices[i]=new Node(curr);
				}

				cout<<endl;

				for(int i=0;i<nv;i++)
				{
					Node* temp = vertices[i];
					Node* curr = vertices[i];

					cout<<endl;

					for(int j=0;j<nv-1;j++)
					{
						string place;
						cout<<"Enter the name of place to which "<<temp->place<<" is connected: ";
						cin>>place;

						int index = get_index(place);

						if(index==-1)
						{
							break;
						}

						curr->add_next(new Node(place));
						curr=curr->get_next();
					}
				}
			}

			//Function for BFS traversal
			void BFS()
			{
				bool* visited=new bool[nv];
				for(int i=0;i<nv;i++)
				{
					visited[i]=false;
				}

				cout<<"Enter the starting place for BFS traversal: ";
				string start;
				cin>>start;
				cout<<endl;


				queue<Node*> q;

				int startIndex = get_index(start);
				if(startIndex==-1)
				{
					cout<<"Invalid starting place!"<<endl;
					delete[] visited;
					return;
				}

				q.push(vertices[startIndex]);
				visited[startIndex]=true;

				cout<<"BFS traversal starting from "<<start<<": ";

				while(!q.empty())
				{
					Node* node = q.front();
					q.pop();
					cout<<node->place<<" ";

					Node* curr = node->next;
					while(curr!=NULL)
					{
						int index = get_index(curr->place);
						if(!visited[index])
						{
							q.push(vertices[index]);
							visited[index]=true;
						}
						curr=curr->next;
					}
				}
				cout<<endl;
				delete[] visited;
			}

			//DFS
			void DFS()
			{
				stack<Node*> stk;
				bool* visited = new bool[nv];
				for(int i=0;i<nv;i++)
				{
					visited[i]=false;
				}

				cout<<"Enter the starting place for DFS traversal: ";
				string start;
				cin>>start;
				cout<<endl;

				Node* startNode= getNode(start);
				if(startNode==NULL)
				{
					cout<<"Invalid starting place!"<<endl;
					delete[] visited;
					return;
				}

				stk.push(startNode);

				cout<<"DFS traversal starting from "<<start<<": ";
				while(!stk.empty())
				{
					Node* node = stk.top();
					stk.pop();

					int index = get_index(node->place);
					if(!visited[index])
					{
						cout<<node->place<<" ";
						visited[index]=true;

						Node* curr = node->next;
						while(curr!=NULL)
						{
							index=get_index(curr->place);
							if(!visited[index])
							{
								stk.push(getNode(curr->place));
							}
							curr=curr->next;
						}
					}
				}
			}

			//For getting the index of the correct node
			int get_index(string place)
			{
				for(int i=0;i<nv;i++)
				{
					if(vertices[i]->place==place)
					{
						return i;
					}
				}
				return -1;
			}

			//fuction for getting node
			Node* getNode(const string& place)
			{
				for(int i=0;i<nv;i++)
				{
					if(vertices[i]->place==place)
					{
						return vertices[i];
					}
				}
				return NULL;
			}
			//function for displaying adjacency list
			void display()
			{
				cout<<endl<<"Graph adjacency list: "<<endl;
				for(int i=0;i<nv;i++)
				{
					Node* curr = vertices[i];

					cout<<curr->place<<" -> ";

					while(curr->has_next())
					{
						curr=curr->get_next();
						cout<<curr->place<<" -> ";
					}

					cout<<endl;
				}
				cout<<endl;
			}
};
int main() {
	 Graph graph;

	 //for creating adjacency list to represent the graph
	 graph.create();

	 //Code for displaying the adjacency list
	 graph.display();

	 //BFS
	 cout<<"Performing BFS traversal...."<<endl;
	 graph.BFS();

	 //DFS
	 cout<<"Performing DFS traversal..."<<endl;
	 graph.DFS();
}
