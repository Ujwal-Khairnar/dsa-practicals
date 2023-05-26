//============================================================================
// Name        : practical5.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class Node
{
	string word;
	string meaning;
	Node* next;

	public:

			Node()
			{
				word=meaning=" ";
				next=NULL;
			}

			Node(string w,string m)
			{
				word=w;
				meaning=m;
				next=NULL;
			}
			friend class Dictionary;
};

class Dictionary
{
	Node** table;
	int tableSize;

	public:
			Dictionary()
			{
				tableSize=10;
				table=new Node*[tableSize];
				for(int i=0;i<tableSize;i++)
				{
					table[i]=NULL;
				}

			}
			Dictionary(int size)
			{
				tableSize=size;
				table=new Node*[tableSize];
				for(int i=0;i<tableSize;i++)
				{
					table[i]=NULL;
				}

			}

			int hash_func(string key)
			{
				int hash = 0;
				for(int i=0; i<key.size(); ++i)
				{
						hash += key[i];
				}
				return (hash%tableSize);
			}

			void insert(string key,string value)
			{
				int index=hash_func(key);

				//empty slot
				if(table[index]==NULL)
				{
					table[index]=new Node(key,value);
					return;
				}

				//non-empty list-insert at tail
				Node* temp=table[index];
				while(temp->next!=NULL)
				{
					if(temp->word==key)
					{
						cout<<"duplicate entry for "<<key<<endl;
						return;
					}
					temp=temp->next;
				}
				if(temp->word==key)
				{
					cout<<"Duplicate entry for "<<key<<endl;
					return;
				}
				temp->next=new Node(key,value);
				cout<<"Key "<<key<<" inserted successfully..\n";
			}

			void find(string key)
			{
				int index = hash_func(key);

				Node* temp = table[index];
				while(temp!=NULL)
				{
					if(temp->word==key)
					{
						cout<<temp->word<<" = "<<temp->meaning<<endl;
						return;
					}
					temp=temp->next;
				}

				cout<<key<<"not found..."<<endl;
			}


			void remove(string key)
			{
				int index = hash_func(key);
				Node* temp = table[index];
				Node* prev = NULL;

				//Traverse the linked list to find the key
				while(temp!=NULL)
				{
					if(temp->word==key)
					{
						if(prev==NULL)
						{
							//NOde to be deleted is the head of the linked list
							table[index]=temp->next;
						}
						else
						{
							//Node to be deleted is not the head
							prev->next=temp->next;
						}
						delete temp;
						cout<<"Key "<<key<<" deleted successfully.\n";
						return;
					}
					prev=temp;
					temp=temp->next;
				}

				cout<<"Key not found. Deletion failed.\n";
			}

			void display()
			{
				cout<<"Sr.No. \t Word-Meaning Pairs"<<endl;
				for(int i=0;i<tableSize;i++)
				{
					cout<<i<<"\t";
					Node* temp = table[i];
					while(temp!=NULL)
					{
						cout<<temp->word<<" = "<<temp->meaning<<" | ";
						temp=temp->next;
					}
					cout<<endl;
				}
			}


};

int main()
{
	Dictionary dict;

	int choice=-1;
	//int temp = 0;
	string key=" ";
	string value=" ";

	cout<<"# Hash-Table Dictionary\n";

		while(choice)
		{
			cout<<"\n----------MENU------------\n"
					<<"1.Insert word-meaning pair\n"
					<<"2.search meaning of word\n"
					<<"3.Display dictionary"
					<<"4.Delete entry\n"
					<<"0. Exit"
					<<"\n-----------------------"<<endl;
			cout<<"Enter choice = ";
			cin>>choice;

			switch(choice)
			{
				case 1://Insert word-meaning pair
				{
					cout<<"Enter word= ";
					cin>>key;
					cout<<"Enter meaning= ";
					cin.ignore(1000,'\n');
					getline(cin,value);
					dict.insert(key,value);
					break;
				}

				case 2: //Search meaning of word
				{
					cout<<"Enter word to search=";
					cin>>key;
					dict.find(key);
					break;
				}

				case 3://Display dictionary
				{
					cout<<"Dictionary: "<<endl;
					dict.display();
					cout<<endl;
					break;
				}

				case 4://Delete entry
				{
					cout<<"Enter name to delete = ";
					cin>>key;
					dict.remove(key);
					break;
				}

				case 0: //Exit
				{
					cout<<"Thank you :)"<<endl;
					break;
				}

				default: //forced exit
				{
					cout<<"# Forced exit due to error"<<endl;
					exit(0);
				}
			}
		}

}
