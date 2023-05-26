//============================================================================
// Name        : practical4.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

const int TABLE_SIZE=10;
class Client
{
	private:
			string name;
			string teleNo;

	public:
			Client()
			{
				name=teleNo=" ";
			}

			Client(string name,string teleNo)
			{
				this->name=name;
				this->teleNo=teleNo;
			}

			friend class HashTable;
};

class HashTable
{
	private:
			Client* table[TABLE_SIZE];

	public:
			HashTable()
			{
				for(int i=0;i<TABLE_SIZE;i++)
				{
					table[i]= new Client();
				}
			}

			HashTable(int size)
			{
				for(int i=0;i<size;i++)
				{
					table[i]=new Client();
				}
			}
			//Hash Function
			int hashFunction(string key)
			{
				int sum=0;
				for(char ch:key)
				{
					sum+=ch;
				}

				return sum % TABLE_SIZE;
			}
			//finding slot in table
			int find_slot(string key)
			{
				int index=hashFunction(key);
				while(table[index]->name!=" " && table[index]->name!=key)
				{
					index=(index+1)%TABLE_SIZE;
				}
				return index;
			}

			//insert with no replacement
			void insert_no_replacement(string key,string value)
			{
				int index=find_slot(key);
				table[index]->name=key;
				table[index]->teleNo=value;
			}

			//insert with replacement
			void insert_with_replacemnt(string key,string value)
			{
				int index=hashFunction(key)%TABLE_SIZE;
				string name,telNum;

				while(table[index]->name!=" " && table[index]->name!=key)
				{
					int tempindx = hashFunction(table[index]->name);

					if(tempindx!=index)
					{
						name=table[index]->name;
						telNum=table[index]->teleNo;

						table[index]->name=key;
						table[index]->teleNo=value;

						key=name;
						value=telNum;
					}
					index=(index+1)%TABLE_SIZE;
				}
				table[index]->name=key;
				table[index]->teleNo=value;
			}

			//to count number of pass
			int countComparisons(string key)
			{
				int pass = 0;
				int index = hashFunction(key);

				for(int i=0;i<TABLE_SIZE;i++)
				{
					pass++;
					if(table[index]->name==key)
					{
						cout<<"Name= "<<key<<endl;
						cout<<"Telephone No.= "<<table[index]->teleNo<<endl;
						return pass;
					}
					else index=(index+1)%TABLE_SIZE;

				}
				cout<<key<<" not present in record!"<<endl;
				return pass;
			}

			//To search index
			int search_index(string key)
			{
				int index=hashFunction(key);
				for(int i=0;i<TABLE_SIZE;i++)
				{
					if(table[index]->name==key)
					{
						cout<<"Name= "<<key<<endl;
						cout<<"Telephone No.= "<<table[index]->teleNo<<endl;
						return index;
					}
					else index=(index+1)%TABLE_SIZE;
				}
				cout<<key<<" not present in record!"<<endl;
				return -1;
			}

			void display()
			{
				cout<<"Index\t"<<"Name\t\t"<<"Telephone Number"<<endl;
				for(int i=0;i<TABLE_SIZE;i++)
				{
					cout<<"("<<i<<")"<<"\t"<<table[i]->name<<"\t\t"<<table[i]->teleNo<<endl;
				}
			}

			void remove(string key)
			{
				int index = this->search_index(key);
				table[index]->name=" ";
				table[index]->teleNo=" ";
				cout<<"Entry deleted..."<<endl;

			}
};

//Main Function
int main()
{
	HashTable ht1;
	HashTable ht2;

	int choice =-1;
	int temp=0;
	string name=" ";
	string teleNo=" ";

	cout<<"#Hash-Table Telephone Record\n";
	while(choice)
	{
		cout<<"\n-------MENU----------\n"
				<<"1.Insert name-number pair\n"
				<<"2.Search number by name\n"
				<<"3.Display List\n"
				<<"4.Delete List\n"
				<<"0.Exit"
				<<"\n---------------------------"<<endl;
		cout<<"Enter choice=";
		cin>>choice;

		switch(choice)
		{
			case 1: //Insert name-number pair
			{
				cout<<"Enter name= ";
				cin>>name;
				cout<<"Enter telephone no.= ";
				cin>>teleNo;
				ht1.insert_no_replacement(name, teleNo);
				ht2.insert_with_replacemnt(name, teleNo);
				break;
			}
			case 2:
			{
				cout<<"Enter name to search= ";
				cin>>name;
				temp=ht1.countComparisons(name);
				cout<<"No. of passes(without replacement)= "<<temp<<endl;

				temp=ht2.countComparisons(name);
				cout<<"No of passes(with replacement)="<<temp<<endl;
				break;
			}
			case 3:
			{
				cout<<"Without replacement:"<<endl;
				ht1.display();
				cout<<endl;
				cout<<"With replacement: "<<endl;
				ht2.display();
				break;
			}
			case 4:
			{
				cout<<"Enter name to delete=";
				cin>>name;
				ht1.remove(name);
				ht2.remove(name);
				break;
			}
			case 0:
			{
				cout<<"Thank you :)"<<endl;
				break;
			}
			default:
			{
				cout<<"#Forced exit due to error"<<endl;
				exit(0);
			}
		}
	}

	return 0;
}
