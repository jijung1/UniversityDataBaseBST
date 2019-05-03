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
  .cpp file implementation UniversityDB program. Class Invariant: Every class will have BST<Student>* masterStudent,
    BST<Faculty>* masterFaculty.
*/

#include "UniversityDB.h"

UniversityDB::UniversityDB(const BST<Student>& masterStudent, const BST<Faculty>& masterFaculty) {  //main constructor
  BST<Student>* temp = new BST<Student>();
  *temp = masterStudent;  //call copy constructor
  BST<Faculty>* temp2 = new BST<Faculty>();
  *temp2 = masterFaculty; //call copy constructor
  this->masterStudent = temp;
  this->masterFaculty = temp2;
}
UniversityDB::UniversityDB(const UniversityDB& copy) {
  cout << "copy const called\n";
  BST<Student>* temp = new BST<Student>();
  BST<Faculty>* temp2 = new BST<Faculty>();
  *temp = *copy.masterStudent;
  *temp2 = *copy.masterFaculty;
  this->masterStudent = temp;
  this->masterFaculty = temp2;
  cout << "made it\n";
}
UniversityDB::UniversityDB() {
  BST<Student>* temp = new BST<Student>();
  BST<Faculty>* temp2 = new BST<Faculty>();
  this->masterStudent = temp;
  this->masterFaculty = temp2;
}
UniversityDB::~UniversityDB() { //destructor
  delete masterStudent;
  delete masterFaculty;
}

bool UniversityDB::run(DoublyLinkedList<UniversityDB>& rollback) {  //bread and butter function
  FileIO<Student>* externStudent;
  FileIO<Faculty>* externFaculty;
  externStudent = new FileIO<Student>("studentBSTdata.txt"); //open file read stream and initialize database
  externFaculty = new FileIO<Faculty>("facultyBSTdata.txt");
  UniversityDB* dbstate = new UniversityDB();
  *dbstate = *this;
  rollback.insertFront(*dbstate);

  bool boole = true; //run switch cases until boole dies
  //if externStudent and externFaculty are not empty, load 'er up
  Student* insertStudent;
  insertStudent = new Student;
  unsigned int newStudentID;
  string sname = "";
  string slevel = "";
  string smajor = "";
  double sgpa = 0.0f;
  unsigned int sadvisor = 0;
  string germanShepherd = "";
  while (!externStudent->endOfFile()) { //create instances of Student objects from file read and push into masterStudent
    germanShepherd = externStudent->readLine();
    int i = 0;
    if (germanShepherd.length() > 18) {
      i = 0;
      while (germanShepherd[i] != static_cast<char>(44)) { //while there there are still delimiters and end of string has not been reached
        ++i;
      }
      newStudentID = stoul(germanShepherd.substr(0,i),nullptr,0 );
      germanShepherd = germanShepherd.substr(i+1, germanShepherd.length());
      i = 0;
      while (germanShepherd[i] != static_cast<char>(44)) {
        ++i;
      }
      sname = germanShepherd.substr(0,i);
      germanShepherd = germanShepherd.substr(i+1, germanShepherd.length());
      i = 0;
      while (germanShepherd[i] != static_cast<char>(44)) {
        ++i;
      }
      slevel = germanShepherd.substr(0,i);
      germanShepherd = germanShepherd.substr(i+1, germanShepherd.length());
      i = 0;
      while (germanShepherd[i] != static_cast<char>(44)) {
        ++i;
      }
      smajor = germanShepherd.substr(0,i);
      germanShepherd = germanShepherd.substr(i+1, germanShepherd.length());
      i = 0;
      while (germanShepherd[i] != static_cast<char>(44)) {
        ++i;
      }
      sgpa = stod(germanShepherd.substr(0,i));
      germanShepherd = germanShepherd.substr(i+1, germanShepherd.length());
      i = 0;

      sadvisor = stoul(germanShepherd,nullptr,0 );
      insertStudent->setIDNum(newStudentID);
      insertStudent->setName(sname);
      insertStudent->setLevel(slevel);
      insertStudent->setGPA(sgpa);
      insertStudent->setMajor(smajor);
      insertStudent->setAdvisor(sadvisor);
      this->masterStudent->insert(*insertStudent);
    }
    else {
      break;
    }
  }
  Faculty* insertFaculty;
  insertFaculty = new Faculty; //name level major gpa advisor
  unsigned int newFacultyID = 0;
  string fname = "";
  string flevel = "";
  string fdepartment = "";
  GenLinkedList<unsigned int>* insertadvisees;
  string australianshepherd = "";
  unsigned int insertadviseeID = 0;
  while (!externFaculty->endOfFile()) { //Create instances of Faculty objects from file read and push into masterFaculty
    insertadvisees = new GenLinkedList<unsigned int>();
    australianshepherd = externFaculty->readLine();
    int i = 0;
    if (australianshepherd.length() > 10) {
      while (australianshepherd[i] != static_cast<char>(44)) { //while there there are still delimiters and end of string has not been reached
        ++i;
      }
      newFacultyID = stoul(australianshepherd.substr(0,i),nullptr,0);
      australianshepherd = australianshepherd.substr(i+1, australianshepherd.length());
      i = 0;
      while (australianshepherd[i] != static_cast<char>(44)) { //while there there are still delimiters and end of string has not been reached
        ++i;
      }
      fname = australianshepherd.substr(0,i);
      australianshepherd = australianshepherd.substr(i+1, australianshepherd.length());
      i = 0;
      while (australianshepherd[i] != static_cast<char>(44)) { //while there there are still delimiters and end of string has not been reached
        ++i;
      }
      flevel = australianshepherd.substr(0,i);
      australianshepherd = australianshepherd.substr(i+1, australianshepherd.length());
      i = 0;
      while (australianshepherd[i] != static_cast<char>(44)) { //while there there are still delimiters and end of string has not been reached
        ++i;
      }
      fdepartment = australianshepherd.substr(0,i);
      australianshepherd = australianshepherd.substr(i+1, australianshepherd.length());
      int j = 0;
      while (australianshepherd.length() > 9) {
        j = 0;
        while (australianshepherd[j] != static_cast<char>(44)) {
          ++j;
        }
        insertadviseeID = stoul(australianshepherd.substr(0,j),nullptr,0);
        insertadvisees->insertFront(insertadviseeID);
        australianshepherd = australianshepherd.substr(j+1, australianshepherd.length());
      }
      if (australianshepherd.length() > 8) {
        insertadviseeID = stoul(australianshepherd,nullptr,0);
        insertadvisees->insertFront(insertadviseeID);
      }

      insertFaculty = new Faculty(fname, flevel, fdepartment, *insertadvisees);
      insertFaculty->setIDNum(newFacultyID);
      this->masterFaculty->insert(*insertFaculty);
    }
    else {
      break;
    }
  }

  while(boole) {  //display menu and loop switch options
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
    unsigned int delFacultyID = 0;
    unsigned int reassignSID = 0;
    string cleardb = "";
    Faculty* newFaculty;
    GenLinkedList<unsigned int>* adviseeList;
    GenLinkedList<unsigned int>* adviseesToDelete;

    switch (choice)
    {
      case 1: //print all students and their information sorted by ascending id
        if (this->masterStudent->isEmpty()) {
          cout << "empty student database!\n";
        }
        this->masterStudent->printTree();
        break;

      case 2: //print all faculty and their information sorted by ascending id
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
        if (this->masterStudent->findNode(*temp) != NULL) {
          cout << this->masterStudent->findNode(*temp)->value.toString();
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
        temp2 ->setIDNum(lookupID2);
        if (this->masterFaculty->findNode(*temp2) != NULL) {
          cout << this->masterFaculty->findNode(*temp2)->value.toString();
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
        if (this->masterStudent->getSize() != 0 && this->masterStudent->findNode(*temp3) != NULL)
        {
          facultyID = this->masterStudent->findNode(*temp3)->value.getAdvisor();
          if (facultyID > 299999999) {
            temp4 = new Faculty;
            temp4->setIDNum(facultyID);
            cout << "facultyID: " << facultyID << endl;
            cout << this->masterFaculty->findNode(*temp4)->value.toString();
          }
          else {
            cout << "information not found!\n";
          }
        }
        else {
          cout << "ID number not found!\n" << endl;
          break;
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
        temp5 -> setIDNum(lookupID4);
        if (this->masterFaculty->findNode(*temp5) != NULL) {
          cout << "Advisees: ";
          cout << this->masterFaculty->findNode(*temp5)->value.advisees->printList();
        }
        else {
          cout << "No faculty found with input ID: " << lookupID4 << endl;
        }
      }
        break;
      case 7: //add new student

        cout << "Please enter the student's name: ";
        cin.ignore(10000,'\n');
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
        cout << "Please enter the student's GPA: ";
        cin >> newStudentGPA;
        if (cin.fail()) {
          cout << "invalid input! \n";
          break;
        }
        newStudent = new Student(newStudentName, newStudentLevel, newStudentMajor, newStudentGPA);
        newStudent->assignIdNum();
        this->masterStudent->insert(*newStudent);
        if (this->masterFaculty->getSize() > 0) {
          assignAdvisor(*newStudent);
        }
        else
          cout << "No Faculty Advisor available to assign!\n";


        break;
      case 8: //add new faculty
        adviseeList = new GenLinkedList<unsigned int>();
        cout << "Please enter the new Faculty Member's name: ";
        cin.ignore(10000,'\n');
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
        this->masterFaculty->insert(*newFaculty);
        break;
      case 9: //delete a student -> remove student from faculty advisee list and delete the student
        cout << "Please enter ID of student to delete: ";
        cin >> delStudentID;
        if (cin.fail()) {
          cout << "invalid input! \n";
          break;
        }
        Student* delStudent;
        delStudent = new Student;
        delStudent->setIDNum(delStudentID);
        if (this->masterStudent->findNode(*delStudent) != NULL) {
          delAdvisorID = this->masterStudent->findNode(*delStudent)->value.getAdvisor(); //retrieve old advisor id
          Faculty* delFaculty;
          delFaculty = new Faculty;
          delFaculty->setIDNum(delAdvisorID);
          this->masterStudent->deleter(*delStudent);
          if (this->masterFaculty->findNode(*delFaculty)->value.advisees->find(delStudentID) != -1) {
            this->masterFaculty->findNode(*delFaculty)->value.removeAdvisee(delStudentID);
          }
          else {
            cout << "Student's assigned advisor does not have student in advisee list!\n";
          }
        }
        else {
          cout << "Invalid ID entered! \n";
          break;
        }
        break;
      case 10:  //delete a faculty member
        cout << "please enter faculty ID: ";
        cin >> delFacultyID;
        if (cin.fail()) {
          cout << "invalid input!\n";
          break;
        }
        Faculty* facultyToDelete;
        facultyToDelete = new Faculty;
        facultyToDelete->setIDNum(delFacultyID);
        if (this->masterFaculty->findNode(*facultyToDelete) != NULL) {
          adviseesToDelete = new GenLinkedList<unsigned int>();
          *adviseesToDelete = *this->masterFaculty->findNode(*facultyToDelete)->value.advisees; //we have a list of advisees to reassign
          while (!adviseesToDelete->isEmpty()) {
            reassignSID = adviseesToDelete->removeFront();
            if (reassignSID > 199999999) {
              Student* tempStudent;
              tempStudent = new Student;
              tempStudent->setIDNum(reassignSID);

              while (masterStudent->findNode(*tempStudent)->value.getAdvisor() == delFacultyID) { //make sure advisor is different
                assignAdvisor(*tempStudent);
              }
              delete tempStudent;
            }
          }
          this->masterFaculty->deleter(*facultyToDelete);
        }
        else {
          cout << "ID not found!\n";
        }

        break;
      case 11:  //change a student's advisor given student id and new faculty id
        cout << "Please enter the student id: ";
        cin >> remAdviseeID;
        if (cin.fail()) {
          "invalid input!\n";
          break;
        }
        cout << "Please enter faculty to assign's id: ";
        cin >> remAdviseeFID;
        Student* replaceAdvisor;
        replaceAdvisor = new Student;
        replaceAdvisor->setIDNum(remAdviseeID);
        if (this->masterStudent->findNode(*replaceAdvisor) != NULL) {
          delAdvisorID = this->masterStudent->findNode(*replaceAdvisor)->value.getAdvisor(); //old advisor
          this->masterStudent->findNode(*replaceAdvisor)->value.setAdvisor(remAdviseeFID); //set new advisor
          Faculty* removeAdvisee2;
          removeAdvisee2 = new Faculty;
          removeAdvisee2->setIDNum(delAdvisorID);
          this->masterFaculty->findNode(*removeAdvisee2)->value.removeAdvisee(remAdviseeID); //remove from old advisor
          Faculty* addAdvisee2;
          addAdvisee2 = new Faculty;
          addAdvisee2->setIDNum(remAdviseeFID);
          if (this->masterFaculty->findNode(*addAdvisee2) != NULL) {
            this->masterFaculty->findNode(*addAdvisee2)->value.addAdvisee(remAdviseeID); //add advisee to new advisor
          }
          else {
            cout << "Invalid faculty ID entered!\n";
            break;
          }
        }
        else {
          cout << "Invalid advisee ID entered!\n";
          break;
        }
        break;
      case 12:  //remove an advisee from a faculty member and reassign advisee
      cout << "Please enter the Faculty id: ";
      cin >> remAdviseeFID;
      if (cin.fail()) {
        "invalid input!\n";
        break;
      }
      cout << "Please enter advisee to remove's ID: ";
      cin >> remAdviseeID;
      Faculty* removeAdvisee;
      removeAdvisee = new Faculty;
      removeAdvisee->setIDNum(remAdviseeFID);
      Student* editStudent;
      editStudent = new Student;
      editStudent->setIDNum(remAdviseeID);
      if (this->masterStudent->findNode(*editStudent) != NULL) {
        while (this->masterStudent->findNode(*editStudent)->value.getAdvisor() == remAdviseeFID) {
          assignAdvisor(*editStudent);
        }
      }
      else {
        cout << "Invalid Advisee ID entered!\n";
        break;
      }
      if (this->masterFaculty->findNode(*removeAdvisee) != NULL) {
        this->masterFaculty->findNode(*removeAdvisee)->value.removeAdvisee(remAdviseeID);
      }
      else {
        cout << "Invalid Faculty ID entered!\n";
      }
      break;
      case 13:  //roll back: TO-DO
      if (rollback.getSize() != 0) {
        cout << "db rollbacksize: " << rollback.getSize() << endl;
        return true;
      }
      else {
        cout << "nothing to rollback\n";
      }
        return true;
        break;
      case 14:  //Save and exit database to exter output stream to text filepath
        cout << "Saving and exiting..." << endl;
        externStudent->ostream.close();
        externStudent->ostream = ofstream("studentBSTdata.txt");
        externFaculty->ostream.close();
        externFaculty->ostream = ofstream("facultyBSTdata.txt");
        while (!this->masterStudent->isEmpty()) {
          externStudent->ostream << this->masterStudent->getRoot()->value.toExtern();
          this->masterStudent->deleter(this->masterStudent->getRoot()->value);
        }
        while (!this->masterFaculty->isEmpty()) {
          externFaculty->ostream << this->masterFaculty->getRoot()->value.toExtern();
          this->masterFaculty->deleter(this->masterFaculty->getRoot()->value);
        }
        boole = false;
        break;
      case 15:  //clear Databases
        cout << "WARNING: Are you sure you want to clear the database? (y/n)";
        cin >> cleardb;
        if (cin.fail()) {
          cout << "unrecognized input!\n";
          cin.ignore(10000,'\n');
          break;
        }
        if (externFaculty->toUpperCase(cleardb) == "YES" || externFaculty->toUpperCase(cleardb) == "Y") {
          this->masterStudent = new BST<Student>();
          this->masterFaculty = new BST<Faculty>();
        }
        break;

      default:
        cout << "unrecognized input!" << endl;
    }
  }
  delete externStudent;
  delete externFaculty;
  return false;
}


void UniversityDB::assignAdvisor(const Student& student) {  //randomly assign advisor to advisee and add advisee to advisor
  unsigned int facultyID = 0;
  int size = this->masterFaculty->getSize(); //randomly choose advisor from existing advisors
  int a = (rand() % size);
  TreeNode<Faculty>* modifiedNode = new TreeNode<Faculty>();
  this->masterFaculty->printTree();
  this->masterFaculty->findIOTNode(0,a,this->masterFaculty->getRoot(),modifiedNode); //found faculty to assign
  if (modifiedNode->value.getIDNum() != 0) {
    facultyID = modifiedNode->value.getIDNum();
    Student* tempStudent = new Student;
    *tempStudent = student; //call copy constructor
    Faculty* tempFaculty = new Faculty;
    tempFaculty->setIDNum(facultyID);
    this->masterFaculty->findNode(*tempFaculty)->value.addAdvisee(tempStudent->getIDNum()); //add student to target faculty advisee list
    this->masterStudent->findNode(*tempStudent)->value.setAdvisor(facultyID);
  }
  else {
    cout << "failed to assign advisor!\n";
  }

}
