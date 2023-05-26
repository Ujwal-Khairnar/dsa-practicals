//============================================================================
// Name        : practical7.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
const int MAX_VERTICES = 100;
const int MAX_EDGES = 100;
class Edge
{
	private:
			int src,dest,weight;
	public:
			friend class Graph;
			friend class MinimumSpanningTree;
};
class Graph
{
	private:
		int numVertices, numEdges;
		Edge edges[MAX_EDGES];

		friend class MinimumSpanningTree;
};

class MinimumSpanningTree
{
	public:
			Graph graph;

			MinimumSpanningTree()
			{
				graph.numVertices=0;
				graph.numEdges =0;
			}

			void getInput()
			{
				cout<<"Enter the number of vertices: ";
				cin>>graph.numVertices;

				cout<<"Enter the number of edges: ";
				cin>>graph.numEdges;

				cout<<"Enter the details of the edges:\n";
				for(int i=0;i<graph.numEdges;i++)
				{
					cout<<"Edge "<<i+1<<":\n";
					cout<<"Source: ";
					cin>>graph.edges[i].src;
					cout<<"Destination: ";
					cin>>graph.edges[i].dest;
					cout<<"Weight: ";
					cin>>graph.edges[i].weight;
				}
			}

			void printGraph()
			{
				cout<<"Number of vertices: "<<graph.numVertices<<endl;
				cout<<"Number of edges: "<<graph.numEdges<<endl;
				cout<<"Edges:"<<endl;
				for(int i=0;i<graph.numEdges;i++)
				{
					cout<<graph.edges[i].src<<" -> "<<graph.edges[i].dest<<" : "<<graph.edges[i].weight<<endl;
				}
			}
			int find(int parent[],int vertex)
			{
				if(parent[vertex]==-1)
					return vertex;
				return find(parent,parent[vertex]);
			}

			void unionSet(int parent[],int x, int y)
			{
				int xSet = find(parent,x);
				int ySet = find(parent,y);
				parent[xSet]=ySet;
			}
			void findMinimumSpanningTree()
			{
				Edge sortedEdges[MAX_EDGES];
				for(int i=0;i<graph.numEdges;i++)
				{
					sortedEdges[i]=graph.edges[i];
				}

				//Sort the edges in ascending order by considering the weights
				for(int i=0;i<graph.numEdges-1;i++)
				{
					for(int j=0;j<graph.numEdges-i-1;j++)
					{
						if(sortedEdges[j].weight>sortedEdges[j+1].weight)
						{
							Edge temp = sortedEdges[j];
							sortedEdges[j] = sortedEdges[j+1];
							sortedEdges[j+1]=temp;
						}
					}
				}

				//Printing sorted edges
				cout<<"\nSorted Edges:\n";
				for(int i=0;i<graph.numEdges;i++)
				{
					cout<<sortedEdges[i].src<<" -> "<<sortedEdges[i].dest<<" : "<<sortedEdges[i].weight<<"\n";
				}

				Edge minimumSpanningTree[MAX_EDGES];
				int parent[MAX_VERTICES];
				for(int i=0;i<graph.numVertices;i++)
				{
					parent[i]=-1;
				}

				int numEdges =0;
				int edgeIndex =0;

				while(numEdges<graph.numVertices-1 && edgeIndex<graph.numEdges)
				{
					Edge currentEdge = sortedEdges[edgeIndex];
					int srcParent = find(parent,currentEdge.src);
					int destParent = find(parent,currentEdge.dest);

					if(srcParent!=destParent)
					{
						minimumSpanningTree[numEdges]=currentEdge;
						unionSet(parent,srcParent,destParent);
						numEdges++;
					}

					edgeIndex++;
				}

				cout<<"Minimum Spanning Tree:\n";
				for(int i=0;i<numEdges;i++)
				{
					cout<<minimumSpanningTree[i].src<<" - "<<minimumSpanningTree[i].dest<<" : "
							<<minimumSpanningTree[i].weight<<"\n";
				}
			}
};
int main() {
	MinimumSpanningTree mst;
	mst.getInput();
	mst.printGraph();
	mst.findMinimumSpanningTree();

	return 0;
}
