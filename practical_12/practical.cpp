#include<bits/stdc++.h>
using namespace std;

class Student{
public:
    int id;
    string name;
public:
    Student(){
        this->id = -1;
        this->name = "";
    }
    
    Student(int id, string name){
        this->id = id;
        this->name = name;
    }
};

class MyClass {
public:
    int id;
    std::string name;
    double value;

    string filename = "abc.txt";

    // Member function to read object data from file
    void readFromFile(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (file) {
            file.read(reinterpret_cast<char*>(this), sizeof(*this));
            file.close();
            std::cout << "Data successfully read from file.\n";
        } else {
            std::cout << "Error opening the file.\n";
        }
    }

    // Member function to display object data
    void displayData() {
        std::cout << "ID: " << id << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Value: " << value << std::endl;
    }

    void writeData(int position){
        Student s1(5, "parth");
        fstream file(filename, ios::app);
        file.seekg(5);
        file.write(reinterpret_cast<const char*>(&s1), sizeof(s1));
        file.close();

    }

    void readeData(int position){
        Student s1;
        fstream file(filename, ios::app);
        file.seekg(5);
        
        file.read(reinterpret_cast<char*>(&s1), sizeof(s1));

        cout <<"name is " <<  s1.name << endl;
        file.close();

    }
};

int main() {
    

    MyClass myclass;

    myclass.writeData(5);
    myclass.readeData(5);

    return 0;
}
