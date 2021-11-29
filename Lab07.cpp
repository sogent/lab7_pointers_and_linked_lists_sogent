#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class StudentInfo {
public:
    StudentInfo();

	StudentInfo(string value, StudentInfo* nextItem);
	string getName() { return name; };
	StudentInfo* getNextStudent() { return nextStudentPtr; };
	void setNextStudent(StudentInfo* item);
	void deleteNext();
	void insertAfter(StudentInfo* item);
	friend bool operator== (const StudentInfo &s1, const StudentInfo &s2);
	friend bool operator< (const StudentInfo &s1, const StudentInfo &s2);


    string name;
    StudentInfo* nextStudentPtr;
};
StudentInfo::StudentInfo(){

}


StudentInfo::StudentInfo(string value, StudentInfo* nextItem = nullptr) {
	this->name = value;
	this->nextStudentPtr = nextItem;
}

bool operator== (const StudentInfo &s1, const StudentInfo &s2) {
	return (s1.name == s2.name);
}

bool operator< (const StudentInfo &s1, const StudentInfo &s2) {
	return (s1.name < s2.name);
}

void StudentInfo::setNextStudent(StudentInfo* item) {
	this->nextStudentPtr = item;
}

void StudentInfo::deleteNext() {
	StudentInfo* temp = this->getNextStudent()->getNextStudent();
	delete this->getNextStudent();
	this->nextStudentPtr = temp;
}

void StudentInfo::insertAfter(StudentInfo* item) {
    StudentInfo *temp = this->getNextStudent();

}




//class to manage the nodes of the linked list
class LinkedList{
    StudentInfo* headPtr;
public:
    LinkedList();
    ~LinkedList();
    void addOrdered(string newName);
    bool removeOrdered(string newName);
    void printList();
};

LinkedList::LinkedList() {
    headPtr= nullptr;
}
LinkedList::~LinkedList() {
    while(headPtr!= nullptr){
        StudentInfo* temp=headPtr;
        headPtr=headPtr->nextStudentPtr;
        delete(temp);
    }
}

void LinkedList::addOrdered(string newName) {
    if(headPtr== nullptr){
        headPtr= new StudentInfo(newName);

    }else if(headPtr->name.compare(newName)>0){
        StudentInfo* temp=new StudentInfo;
        temp->name=newName;
        temp->nextStudentPtr=headPtr;
        headPtr=temp;
    }else{
        StudentInfo* currPtr= headPtr;
        StudentInfo* prevPtr= nullptr;
        StudentInfo* temp= new StudentInfo(newName);
        while(currPtr!= nullptr){
            if(currPtr->name.compare(newName)>0){
                prevPtr->nextStudentPtr=temp;
                temp->nextStudentPtr=currPtr;
                return;
            }
            prevPtr=currPtr;
            currPtr=currPtr->nextStudentPtr;
        }
        prevPtr->nextStudentPtr=temp;
    }
}

void LinkedList::printList() {
    if(headPtr == nullptr)
        cout<<"List is empty"<<endl;
    else
    {
        StudentInfo* currPtr = headPtr;
        while(currPtr != nullptr)
        {
            cout<<"->"<<currPtr->name;
            currPtr = currPtr->nextStudentPtr;
        }
    }
}

bool LinkedList::removeOrdered(string newName) {
    if(headPtr== nullptr){
        return false;
    }else if(headPtr->name==newName){
        StudentInfo* temp= headPtr;
        headPtr= headPtr->nextStudentPtr;
        delete(temp);
        return true;
    }else{
        StudentInfo* currPtr= headPtr;
        StudentInfo* prevPtr= nullptr;
        while(currPtr!= nullptr){
            if(currPtr->name==newName){
                prevPtr->nextStudentPtr= currPtr->nextStudentPtr;
                delete(currPtr);
                return true;
            }
            prevPtr= currPtr;
            currPtr= currPtr->nextStudentPtr;
        }
        return false;
    }
}


int main() {

    ifstream fin("/Users/sogent/CLionProjects/lab7-pointers-and-linked-lists-sogent/input7.txt");
    string line;
    LinkedList studentList;

    stringstream  inSS;
    while(getline(fin, line)){

        inSS.str(line);
        string linkedListAction;
        string name;

        inSS>>name;
        inSS>>linkedListAction;

        if(linkedListAction=="add") {
            studentList.addOrdered(name);

        }else if(linkedListAction=="del"){
            studentList.removeOrdered(name);
        }

    }
    fin.close();

    studentList.printList();

        return 0;

}