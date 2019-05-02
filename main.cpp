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
  Main.cpp file for testing UniversityDB program
*/

//preprocessor directives

#include "BST.h"
#include <ctime>  //need for srand
#include <cstdlib>  //need for NULL
#include "Student.h"
#include "Faculty.h"
#include "UniversityDB.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
  srand(time(NULL));
  BST<Faculty>* ftest;
  ftest = new BST<Faculty>();
  BST<Student>* test;
  test = new BST<Student>();
  GenLinkedList<unsigned int>* advisees;
  UniversityDB database(*test, *ftest);
  database.run();
  getchar();
  return 0;

}
