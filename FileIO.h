/*
Name:                   Jin Jung
Student ID:             2329401
Email:                  jijung@chapman.edu
Course no. & Section:   CS350-02
Assignment:             4
*/

/*
  File class for handling file read/write
*/

#ifndef FILEIO_H
#define FILEIO_H
#include "BST.h"
#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib> //for NULL

using namespace std;

template <typename E>
class FileIO {
public:
  string filePath;
  ifstream istream;
  ofstream ostream;
  FileIO(string filePath);
  ~FileIO();
  string readLine();
  string readFile();
  bool endOfFile();
  int readInt();
  string toUpperCase(string someString);
};

template <typename E>
FileIO<E>::FileIO(string filePath){ //main contructor
  this->filePath = filePath;
  this->istream = ifstream(filePath);
  this->ostream = ofstream(filePath, std::ios_base::app);
}
template <typename E>
FileIO<E>::~FileIO() { //destructor
  this->istream.close();
  this->ostream.close();
  //de
}
template <typename E>
string FileIO<E>::readLine() {
  string temp = "";
  getline(istream,temp);
  if (temp.back() == '\r') {  //remove return carriage character from string temp
  temp.pop_back();
  }
  return temp;
}

//char readChar();
template <typename E>
int FileIO<E>::readInt()
{
  string line = "";
  getline(istream, line);
  return stoi(line);
}
template <typename E>
string FileIO<E>::readFile() {
  string data = "";
  string temp = "";
  while(!istream.eof()) {
    data = readLine();
    if(temp.length() <= 0) {
      cout << "skipping empty line..\n";
      continue;
    }
    data += temp + " ";
  }
  return data;
}
template <typename E>
bool FileIO<E>::endOfFile() {
  return (istream.eof());
}

template <typename E>
string FileIO<E>::toUpperCase(string someString) {
  for(int i = 0; i < someString.length(); ++i)
  {
    if (static_cast<int>(someString[i]) > 96 && static_cast<int>(someString[i]) < 123)
    {
      someString[i] = static_cast<char>(static_cast<int>(someString[i])-32);
    }
  }
  return someString;
}

#endif /*FILEIO_H*/
