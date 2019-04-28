#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib> //for rand()
#include <ctime>



using namespace std;

class Student {
private:
unsigned int idNum;
string name;
string level;
string major;
double gpa;
int advisor;

public:

  //constructor

Student();
Student(string name, string level, string major, double gpa);  //idNum randomized for even distribution in BST?

//destructor

~Student();

//accessor & mutator functions

unsigned int getIDNum() const;
void setIDNum(unsigned int idNum);

string getName() const;
void setName(string name);

string getLevel() const;
void setLevel(string level);

string getMajor() const;
void setMajor(string major);

double getGPA() const;
void setGPA(double gpa);

unsigned int getAdvisor() const;
void setAdvisor(unsigned int advisor);

unsigned int assignIdNum();


string toExtern() const;

string toString() const;
};

bool operator < (const Student& a, const Student& b);
bool operator > (const Student& a, const Student& b);
bool operator ==(const Student& a, const Student& b);
bool operator !=(const Student& a, const Student& b);




#endif /*STUDENT_H*/
