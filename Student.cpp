#include "Student.h"

Student::Student(){
  this->idNum = 0;
  this->name = "";
  this->level = "";
  this->major = "";
  this->gpa = 0.0f;
  this->advisor = 0;
}
Student::Student(const Student& copy) {
  this->idNum = copy.getIDNum();
  this->name = copy.getName();
  this->level = copy.getLevel();
  this->major = copy.getMajor();
  this->gpa = copy.getGPA();
  this->advisor = copy.getAdvisor();
}
Student::Student(string name, string level, string major, double gpa) {  //idNum randomized for even distribution in BST?

  this->idNum = assignIdNum();
  this->name = name;
  this->level = level;
  this->major = major;
  this->gpa = gpa;
  this->advisor = 0;

}
//destructor

Student::~Student() {}

//accessor & mutator functions

string Student::toExtern() const {
  ostringstream strs;
  strs << this->getGPA();
  string gpa = strs.str();
  ostringstream strs2;
  strs2 << this->getIDNum();
  string num = strs2.str();
  ostringstream strs3;
  strs3 << this->getAdvisor();
  string adv = strs3.str();
  string ret = "";
  ret += num;
  ret += ",";
  ret += this->getName();
  ret += ",";
  ret += this->getLevel();
  ret += ",";
  ret += this->getMajor();
  ret += ",";
  ret += gpa;
  ret += ",";
  ret += adv;
  ret += "\n";
  return ret;
}

string Student::toString() const {
  string ret = "\n";
  ret += "Name: " + this->getName() + " ";
  ret += "ID: " + to_string(this->getIDNum()) + " ";
  ret += "Level: " + this->getLevel() + " ";
  ret += "Major: " + this->getMajor() + " ";
  ret += "GPA: " + std::to_string(this->getGPA()).substr(0,4) + " ";
  ret += "Advisor: " + std::to_string(this->getAdvisor()) + "\n";
  return ret;
}

unsigned int Student::getIDNum() const{
    return this->idNum;
}

void Student::setIDNum(unsigned int idNum) {
  this->idNum = idNum;
}

string Student::getName() const {
  return this->name;
}
void Student::setName(string name) {
  this->name = name;
}

string Student::getLevel() const {
  return this->level;
}
void Student::setLevel(string level) {
  this->level = level;
}

string Student::getMajor() const {
  return this->major;
}
void Student::setMajor(string major) {
  this->major = major;
}

double Student::getGPA() const {
  return this->gpa;
}
void Student::setGPA(double gpa) {
  this->gpa = gpa;
}

unsigned int Student::getAdvisor() const {
  return this->advisor;
}
void Student::setAdvisor(unsigned int advisor) {
  this->advisor = advisor;
}

unsigned int Student::assignIdNum() { //    **** TO DO ****
  double a = ((RAND_MAX - rand()) / static_cast<double>(RAND_MAX)); // 0 - .99
  unsigned int b = static_cast<unsigned int>(a * 100000000);
  return b + 200000000;

}
bool operator < (const Student& a, const Student& b) {
  return a.getIDNum() < b.getIDNum();
}
bool operator > (const Student& a, const Student& b) {
  return a.getIDNum() > b.getIDNum();
}
bool operator ==(const Student& a, const Student& b) {
  return a.getIDNum() == b.getIDNum();
}

bool operator !=(const Student& a, const Student& b) {
  return a.getIDNum() != b.getIDNum();
}
