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

#ifndef FACULTY_H
#define FACULTY_H

#include "GenericLinkedList.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib> //for rand()
#include <ctime>

using namespace std;

class Faculty {
public:
unsigned int idNum;
string name;
string level;
string department;
GenLinkedList<unsigned int>* advisees;
public:
  //constructor
Faculty();
Faculty(const Faculty& copy);
Faculty(string name, string level, string department, const GenLinkedList<unsigned int>& advisees);  //idNum randomized for even distribution in BST
//destructor
~Faculty();

//accessor & mutator functions

unsigned int getIDNum() const;
void setIDNum(unsigned int idNum);

string getName() const;
void setName(string name);

string getLevel() const ;
void setLevel(string level);

string getDepartment() const;
void setDepartment(string department);

bool addAdvisee(unsigned int idNum);

bool removeAdvisee(unsigned int idNum);

unsigned int assignIdNum();

string toExtern();

string toString();
};

bool operator < (const Faculty& a,const Faculty& b);
bool operator > (const Faculty& a,const Faculty& b);
bool operator ==(const Faculty& a,const Faculty& b);
bool operator !=(const Faculty& a,const Faculty& b);




#endif /*FACULTY_H*/
