/*
Name:                   Rose Ramirez
Student ID:             2317195
Email:                  roramirez@chapman.edu
Course no. & Section:   CS350-02

Name:                   Jin Jung
Student ID:             2329401
Email:                  jijung@chapman.edu
Course no. & Section:   CS350-02
*/

/*
  .cpp file for implementation of Faculty class. Class Invariant: Every instance will have unsigned int idNum, string name, string level, and string department.
*/

#include "Faculty.h"
  //constructor
Faculty::Faculty() {  //default constructor
  this->idNum = 0;
  this->name = "";
  this-> level = "";
  this-> department = "";
  GenLinkedList<unsigned int>* temp;
  temp = new GenLinkedList<unsigned int>();
  this->advisees = temp;
}

Faculty::Faculty(string name, string level, string department, const GenLinkedList<unsigned int>& advisees) { //main constructor
  this->idNum = assignIdNum();
  this->name = name;
  this-> level = level;
  this-> department = department;
  GenLinkedList<unsigned int>* temp = new GenLinkedList<unsigned int>();
  *temp = advisees;
  this->advisees = temp;
}

Faculty::Faculty(const Faculty& copy) { //copy constructor
  this->idNum = copy.getIDNum();
  this->name = copy.getName();
  this->level = copy.getLevel();
  this->department = copy.getDepartment();
  GenLinkedList<unsigned int>* temp;
  GenLinkedList<unsigned int>* temp2;
  temp = new GenLinkedList<unsigned int>();
  temp2 = new GenLinkedList<unsigned int>();
  while (!copy.advisees->isEmpty()) {
    temp->insertFront(copy.advisees->removeFront());
  }
  while (!temp -> isEmpty()) {
    temp2->insertFront(temp->removeFront());
  }
  this->advisees = temp2;
}

//destructor

Faculty::~Faculty() {
  if(!this->advisees->isEmpty())
  {
    delete this->advisees;
  }
}

//accessor & mutator functions

unsigned int Faculty::getIDNum() const {
  return this->idNum;
}
void Faculty::setIDNum(unsigned int idNum) {
  this->idNum = idNum;
}

string Faculty::getName() const {
  return this->name;
}
void Faculty::setName(string name) {
  this->name = name;
}

string Faculty::getLevel() const {
  return this->level;
}
void Faculty::setLevel(string level) {
  this->level = level;
}

string Faculty::getDepartment() const {
  return this->department;
}
void Faculty::setDepartment(string department) {
  this->department = department;
}

bool Faculty::addAdvisee(unsigned int idNum) {
  if ((this->advisees->find(idNum)) == -1) {
    this->advisees->insertFront(idNum);
  }
  else {
  }
}
bool Faculty::removeAdvisee(unsigned int idNum) {
  int position = this->advisees->find(idNum);
  if (position != -1)
    this->advisees->deletePos(position);

}

unsigned int Faculty::assignIdNum() { //function to randomly assign a faculty id number
  double a = ((RAND_MAX - rand()) / static_cast<double>(RAND_MAX)); // 0 - .99
  unsigned int b = static_cast<unsigned int>(a * 100000000);
  return b + 300000000;
}

string Faculty::toExtern() {  //formatted output for external file read/write
  ostringstream strs;
  strs << this->getIDNum();
  string idnum = strs.str();

  string ret = ""; //int idnum, string name, string level, string department, GenLinkedList<int>* advisees
  ret += idnum;
  ret += ",";
  ret += this->getName();
  ret += ",";
  ret += this->getLevel();
  ret += ",";
  ret += this->getDepartment();
  ret += ",";
  ret += this->advisees->printList();
  ret+="\n";
  return ret;
}
string Faculty::toString() {  //formatted output for terminal output
  string ret = "\n";
  ret += "Faculty Name: " + this->getName();
  ret += " ID: " + to_string(this->getIDNum());
  ret += " Level: " + this->getLevel();
  ret += " Department: " + this->getDepartment();
  ret += " Advisee IDs: ";
  string ret2 = this->advisees->printList();
  ret += ret2;
  ret += "\n\n";
  return ret;
}

//overloaded operators 

bool operator < (const Faculty& a,const Faculty& b) {
  unsigned int c = a.getIDNum();
  unsigned int d = b.getIDNum();
  return (c < d);
}
bool operator > (const Faculty& a,const Faculty& b) {
  unsigned int c = a.getIDNum();
  unsigned int d = b.getIDNum();
  return (c > d);}
bool operator ==(const Faculty& a,const Faculty& b) {
  unsigned int c = a.getIDNum();
  unsigned int d = b.getIDNum();
  return (c == d);}

bool operator !=(const Faculty& a,const Faculty& b) {
  unsigned int c = a.getIDNum();
  unsigned int d = b.getIDNum();
  return (c != d);
}
