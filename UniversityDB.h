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

#ifndef UNIVERSITYDB_H
#define UNIVERSITYDB_H

//preprocessor directives

#include <iostream>
#include <cstdlib>
#include "BST.h"
#include "Faculty.h"
#include "Student.h"
#include <string>
#include "FileIO.h"
#include "GenericDoublyLinkedList.h"

using namespace std;

class UniversityDB {
public:
  BST<Student>* masterStudent;
  BST<Faculty>* masterFaculty;

public:
  UniversityDB(const BST<Student>& masterStudent, const BST<Faculty>& masterFaculty);
  UniversityDB(const UniversityDB& copy);
  UniversityDB();
  ~UniversityDB();
  bool run(DoublyLinkedList<UniversityDB>& rollback);
  void assignAdvisor(const Student& student);

};


#endif /*UNIVERSITYDB_H*/
