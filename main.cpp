#include "BST.h"
#include <ctime>
#include <cstdlib>
#include "Student.h"  //can remove after test
#include "Faculty.h"  //can remove after test
#include "UniversityDB.h"
#include <iostream>
using namespace std;

int main(int argc, char** argv) {

  srand(time(NULL));

  BST<Faculty>* ftest;
  ftest = new BST<Faculty>();
  BST<Student>* test;
  test = new BST<Student>();
  UniversityDB database(*test, *ftest);
  database.run();

  getchar();
  return 0;

}
