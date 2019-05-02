#ifndef UNIVERSITYDB_H
#define UNIVERSITYDB_H

#include <iostream>
#include <cstdlib>
#include "BST.h"
#include "Faculty.h"
#include "Student.h"
#include <string>
#include "FileIO.h"
#include "GenStack.cpp"

using namespace std;

class UniversityDB {
public:
  BST<Student>* masterStudent;
  BST<Faculty>* masterFaculty;
  FileIO<Student>* externStudent;
  FileIO<Faculty>* externFaculty;
  //GenStack<UniversityDB>* lastFive; //every time a tree changing thing occurs, save off DB before and add to stack

public:
  UniversityDB(const UniversityDB& copy);
  UniversityDB(const BST<Student>& masterStudent, const BST<Faculty>& masterFaculty);

  UniversityDB();
  ~UniversityDB();
  /*
  void setMasterStudent(const BST<Student>& masterStudent);
  void setMasterFaculty(const BST<Student>& masterFaculty);
  const BST<Student>& getMasterStudent();
  const BST<Faculty>& getMasterFaculty();
  */
  void run();
  void assignAdvisor(const Student& student);



};


#endif /*UNIVERSITYDB_H*/
