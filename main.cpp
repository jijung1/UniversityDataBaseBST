#include "BST.h"
#include <ctime>
#include <cstdlib>
#include "Student.h"  //can remove after test
#include "Faculty.h"  //can remove after test
#include "UniversityDB.h"
#include "FileIO.h"
#include "GenericLinkedList.h"
#include <iostream>
using namespace std;

int main(int argc, char** argv) {

  srand(time(NULL));
  FileIO<Student> studentData("studentTable.txt");
  Student a("alice", "freshmen", "communications", 3.8);
  Student b("bob", "senior", "computer science", 3.0);
  Student c("charlie", "junior", "biology", 4.0);
  Student d("dexter", "sophomore", "linguistics", 3.5);
  GenLinkedList<unsigned int>* list;
  GenLinkedList<unsigned int>* list2;
  GenLinkedList<unsigned int>* list3;
  GenLinkedList<unsigned int>* list4;

  list = new GenLinkedList<unsigned int>();
  list->insertFront(10);
  list->insertFront(20);
  list2 = new GenLinkedList<unsigned int>();
  list2->insertFront(30);
  list2->insertFront(40);
  list3 = new GenLinkedList<unsigned int>();
  list4 = new GenLinkedList<unsigned int>();


  Faculty f1("poppy", "Professor", "computer science", *list);
  Faculty f2("riven", "Associate Professor", "chemistry", *list2);
  Faculty f3("linstead","Head of Computer Science Department", "Comptuter Science", *list3);
  Faculty f4("german", "Professor", "computer science", *list4);
  cout << f1.toExtern() << endl;
  cout << a.toExtern() << endl;

  BST<Faculty>* ftest;
  ftest = new BST<Faculty>();

  ftest->insert(f1);
  ftest->insert(f2);
  ftest->insert(f3);
  ftest->insert(f4);

  BST<Student>* test;
  test = new BST<Student>();

  test->insert(a);
  test->insert(b);
  test->insert(c);
  test->insert(d);

  //studentData.storeStudentNode(test->getRoot());
  //studentData.retrieveStudentNode();
  UniversityDB database(*test, *ftest);
  database.run();

  getchar();
  return 0;

}
