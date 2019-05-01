#include "UniversityDB.h"

UniversityDB::UniversityDB(const BST<Student>& masterStudent, const BST<Faculty>& masterFaculty) {
  BST<Student>* temp = new BST<Student>();
  *temp = masterStudent;
  BST<Faculty>* temp2 = new BST<Faculty>();
  *temp2 = masterFaculty;
  this->masterStudent = temp;
  this->masterFaculty = temp2;
  this->lastFive = new GenStack<Database>(5);
  this->lastFive->push(this);
  this->externStudent = new FileIO<Student>("studentBSTdata.out"); //open file read stream and initialize database
  this->externFaculty = new FileIO<Faculty>("facultyBSTdata.out");

}
UniversityDB::~UniversityDB() {
  delete masterStudent;
  delete masterFaculty;
  delete lastFive;
}

/*
void UniversityDB::setMasterStudent(const BST<Student>& masterStudent) {

}
void UniversityDB::setMasterFaculty(const BST<Faculty>& masterFaculty) {

}

const BST<Student>& UniversityDB::getMasterStudent() {
  return *this->masterStudent;
}
const BST<Faculty>& UniversityDB::getMasterFaculty() {
  return *this->masterFaculty;
}
*/


void UniversityDB::run() {
  bool boole = true;
  //initialize everything
  while(boole) {
    cout << "\n-------------------------------------------\n";
    cout << "Please choose from the following options: " << endl;
    cout << "[1]: Print all students and their information\n";
    cout << "[2]: Print all faculty information\n";
    cout << "[3]: Find and display a student's information\n";
    cout << "[4]: Find and display a faculty member's information\n";
    cout << "[5]: Print name and information of faculty advisor\n";
    cout << "[6]: List advisees of a faculty member\n";
    cout << "[7]: Add new Student\n";
    cout << "[8]: Add new Faculty\n";
    cout << "[9] Delete a student\n";
    cout << "[10] Delete faculty\n";
    cout << "[11] Change a student's advisor\n";
    cout << "[12] remove an advisee from a faculty member\n";
    cout << "[13] RollBack last Database change\n";
    cout << "[14]: Save and Exit Database\n";
    cout << "[15]: Clear Database\n";
    int choice = 0;
    cin >> choice;
    if(cin.fail()) {
      cout << "invalid input!";
      exit(1);
    }

    //variables used within switch statement declared here to avoid cross initialization
    string newStudentName = "";
    string newStudentLevel = "";
    string newStudentMajor = "";
    double newStudentGPA = 0.0f;
    Student* newStudent;
    string newFacultyName = "";
    string newLevel = "";
    string newDepartment = "";
    unsigned int delStudentID = 0;
    unsigned int delAdvisorID = 0;
    unsigned int remAdviseeID = 0;
    unsigned int remAdviseeFID = 0;

    Faculty* newFaculty;
    GenLinkedList<unsigned int>* adviseeList;

    switch (choice)
    {
      case 1: //print all students and their information sorted by ascending id
        if (this->masterStudent->isEmpty()) {
          cout << "empty student database!\n";
        }
        this->masterStudent->printTree();
        break;

      case 2: //print all faculty
      if (this->masterFaculty->isEmpty()) {
        cout << "empty faculty database!\n";
      }
        this->masterFaculty->printTree();
        break;
      case 3: //Find and display student information
        cout << "Please input the Student's ID: ";
        unsigned int lookupID;
        cin >> lookupID;
        Student* temp;
        temp = new Student;
        temp->setIDNum(lookupID);
        if (masterStudent->findNode(*temp) != NULL) {
          cout << masterStudent->findNode(*temp)->value.toString();
        }
        else {
          cout << "ID number not found!\n";
        }
        delete temp;
        break;
      case 4: //Find and display faculty information
        cout << "Please input the Faculty's ID: ";
        unsigned int lookupID2;
        cin >> lookupID2;
        Faculty* temp2;
        temp2 = new Faculty;
        temp2->setIDNum(lookupID2);
        if (masterFaculty->findNode(*temp2) != NULL) {
          cout << masterFaculty->findNode(*temp2)->value.toString();
        }
        else {
          cout << "ID number not found!\n";
        }
        delete temp2;
        break;
      case 5: //print name and info of faculty advisor

        cout << "Please input student's ID number: ";
        unsigned int lookupID3;
        cin >> lookupID3;
        if (cin.fail()) {
          "invalid input!";
          break;
        }
        Student* temp3;
        temp3 = new Student;
        temp3->setIDNum(lookupID3);
        Faculty* temp4;
        unsigned int facultyID;
        facultyID = this->masterStudent->findNode(*temp3)->value.getAdvisor();
        if (facultyID > 299999999) {
          temp4 = new Faculty;
          temp4->setIDNum(facultyID);
          cout << "facultyID: " << facultyID << endl;
          cout << masterFaculty->findNode(*temp4)->value.toString();
        }
        else {
          cout << "information not found!\n";
        }

        break;
      case 6: //list faculty advisees
      cout << "Please input Faculty member's ID number: ";
      unsigned int lookupID4;
      cin >> lookupID4;
      if (cin.fail()) {
        "invalid input!";
      }
      else {
        Faculty* temp5;
        temp5 = new Faculty;
        temp5->setIDNum(lookupID4);
        if (masterFaculty->findNode(*temp5) != NULL) {
          cout << "Advisees: ";
          cout << masterFaculty->findNode(*temp5)->value.advisees->printList();
        }
        else {
          cout << "No faculty found with input ID: " << lookupID4 << endl;
        }
      }
        break;
      case 7: //add new student

        cout << "Please enter the student's name: ";
        cin.ignore();
        getline(cin, newStudentName);
        if (cin.fail()) {
          cout << "invalid input! \n";
          break;
        }
        cout << "Please enter the student's level: ";
        getline(cin, newStudentLevel);
        if (cin.fail()) {
          cout << "invalid input! \n";
          break;
        }
        cout << "Please enter the student's major: ";
        getline(cin, newStudentMajor);
        if (cin.fail()) {
          cout << "invalid input!\n";
          break;
        }
        cout << "Please enter the student's GPA: "; //must input 0.00 format cannot input integer for some reason
        cin >> newStudentGPA;
        if (cin.fail()) {
          cout << "invalid input! \n";
          break;
        }
        newStudent = new Student(newStudentName, newStudentLevel, newStudentMajor, newStudentGPA);
        newStudent->assignIdNum();
        masterStudent->insert(*newStudent);
        assignAdvisor(*newStudent);
        if(lastFive->isFull())
          lastFive->delLast();
        lastFive->push(this);
        break;
      case 8: //add new faculty
        adviseeList = new GenLinkedList<unsigned int>();
        cout << "Please enter the new Faculty Member's name: ";
        cin.ignore();
        getline(cin, newFacultyName);
        if (cin.fail()) {
          cout << "invalid input! \n";
          break;
        }
        cout << "Please enter the new Faculty member's level: ";
        getline(cin, newLevel);
        if (cin.fail()) {
          cout << "invalid input! \n";
          break;
        }
        cout << "Please enter the new Faculty member's department: ";
        getline(cin, newDepartment);
        if (cin.fail()) {
          cout << "invalid input! \n";
          break;
        }
        newFaculty = new Faculty(newFacultyName, newLevel, newDepartment, *adviseeList);
        newFaculty->assignIdNum();
        masterFaculty->insert(*newFaculty);
        if(lastFive->isFull())
          lastFive->delLast();
        lastFive->push(this);
        break;
      case 9: //delete a student -> remove student from faculty advisee list and delete the student 1
        cout << "Please enter ID of student to delete: ";
        cin >> delStudentID;
        if (cin.fail()) {
          cout << "invalid input! \n";
          break;
        }
        Student* delStudent;
        delStudent = new Student;
        delStudent->setIDNum(delStudentID);
        delAdvisorID = this->masterStudent->findNode(*delStudent)->value.getAdvisor(); //retrieve old advisor id
        Faculty* delFaculty;
        delFaculty = new Faculty;
        delFaculty->setIDNum(delAdvisorID);
        this->masterStudent->deleter(*delStudent);
        this->masterFaculty->findNode(*delFaculty)->value.removeAdvisee(delStudentID);
        if(lastFive->isFull())
          lastFive->delLast();
        lastFive->push(this);
        break;
      case 10:  //delete a faculty member

        break;
      case 11:  //change a student's advisor given student id and new faculty id
        break;
      case 12:  //remove an advisee from a faculty member and reassign advisee to a different fa
      /*
        cout << "Please enter the advisee ID: ";
        cin >> remAdviseeID;
        if (cin.fail()) {
          cout << "invalid input! \n";
          break;
        }
        cout << "Please enter the faculty ID: ";
        cin >> remAdviseeFID;
        if (cin.fail()) {
          cout << "invalid input! \n";
          break;
        }
        Faculty* editFaculty;
        editFaculty = new Faculty;
        editFaculty->setIDNum(remAdviseeFID);
        this->masterFaculty->findNode(editFaculty)
        */
        break;
      case 13:  //roll back LOL
      if(!lastFive.isEmpty())
      {
        this->masterFaculty = lastFive.peek().masterFaculty;
        this->masterStudent = lastFive.pop().masterStudent;
      }
        break;
      case 14:  //Save and exit database to exter output stream to text filepath
        cout << "Saving and exiting..." << endl;
        boole = false;
        break;
      case 15:  //clear Databases
        cout << "WARNING: Are you sure you want to clear the database? (y/n)";
        masterStudent = new BST<Student>();
        masterFaculty = new BST<Faculty>();
        if(lastFive->isFull())
          lastFive->delLast();
        lastFive->push(this);
        break;

      default:
        cout << "unrecognized input!" << endl;
    }
    //update stack for undo operation
  }
}


void UniversityDB::assignAdvisor(const Student& student) {  //randomly assign advisor to advisee and add advisee to advisor
  unsigned int facultyID = 0;
  int size = masterFaculty->getSize(); //randomly choose advisor from existing advisors
  int a = (rand() % size);
  TreeNode<Faculty>* modifiedNode = new TreeNode<Faculty>();
  masterFaculty->printTree();
  masterFaculty->findIOTNode(0,a,this->masterFaculty->getRoot(),modifiedNode); //found faculty to assign
  if (modifiedNode->value.getIDNum() != 0) {
    facultyID = modifiedNode->value.getIDNum();
    Student* tempStudent = new Student;
    *tempStudent = student; //call copy constructor
    modifiedNode->value.addAdvisee(tempStudent->getIDNum()); //add student to target faculty advisee list
    masterStudent->findNode(*tempStudent)->value.setAdvisor(facultyID);
  }
  else {
    cout << "failed to assign advisor!\n";
  }

}
