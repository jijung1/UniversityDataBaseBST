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
#include "GenericDoublyLinkedList.h"
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
  bool boole2 = true;
    DoublyLinkedList<UniversityDB>* rollback;
    rollback = new DoublyLinkedList<UniversityDB>();
    while(boole2 == true) {
      cout << "main rollbacksize: " << rollback->getSize() << endl;
      if(rollback->getSize() != 0) {
        cout << "hi\n";
        UniversityDB* newdatabase;
        newdatabase = new UniversityDB();
        *newdatabase = rollback->removeFront();
        cout << "main remfront successful\n";
      }
      boole2 = database.run(*rollback);
    }  getchar();
  return 0;

}
