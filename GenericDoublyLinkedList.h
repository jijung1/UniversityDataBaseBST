/*
Name:                   Jin Jung
Student ID:             2329401
Email:                  jijung@chapman.edu
Course no. & Section:   CS350-02
Assignment:             5
*/

/*
  Generic Double Linked List file
*/

#ifndef GENERICDOUBLYLINKEDLIST_H
#define GENERICDOUBLYLINKEDLIST_H

#include <iostream>
#include <stdexcept>
#include <cstdlib>
using namespace std;

template <typename E>
class DLListNode {
public:
    DLListNode();
    DLListNode(E d);
    ~DLListNode();
    E data;
    DLListNode *next;
    DLListNode *prev;
};

class ListEmpty : public runtime_error {  //throws this error when attempting to access data from empty list
public:
  ListEmpty(const string& err) : runtime_error(err) {};
};
class KeyNotFound : public runtime_error {  //throws this error when search for a key is not found
public:
  KeyNotFound(const string& err) : runtime_error(err) {};
};

template <typename E>
DLListNode<E>::DLListNode() {
  next = NULL;
  prev = NULL;
}
template <typename E>
DLListNode<E>::DLListNode(E d) {
  data = d;
  next = NULL;
  prev = NULL;
}

//no delete in node destructor
template <typename E>
DLListNode<E>::~DLListNode() {
  next = NULL;
  prev = NULL;
}

template <typename E>
class DoublyLinkedList {
public:
  DLListNode<E> *front;  //sentinel node for beginning of list
  DLListNode<E> *back;   //sentinel node for end of list
  unsigned int size;
public:
  DoublyLinkedList();
  virtual ~DoublyLinkedList();
  void insertFront(E Data);
  void insertBack(E data);
  E removeFront();
  E removeBack();
  virtual int getSize();
  virtual bool empty();
  E remove(E key);
  //bool contains(E key);
};

template <typename E>
DoublyLinkedList<E>::DoublyLinkedList() {
  size = 0;
  front = new DLListNode<E>();
  back = new DLListNode<E>();
  front->next = back;
  back->prev = front;
}
template <typename E>
DoublyLinkedList<E>::~DoublyLinkedList() {
  while(!empty()) {removeFront();}
  front = NULL;
  back = NULL;
}
template <typename E>
bool DoublyLinkedList<E>::empty() {
  return size == 0;
}
template <typename E>
int DoublyLinkedList<E>::getSize() {
  return size;
}
template <typename E>
void DoublyLinkedList<E>::insertFront(E data) {
  DLListNode<E>* node = new DLListNode<E>(data);
  front->next->prev = node;
  node->next = front->next;
  node->prev = front;
  front->next = node;
  size++;
}
template <typename E>
void DoublyLinkedList<E>::insertBack(E data) {
  DLListNode<E>* node = new DLListNode<E>(data);
  back->prev->next = node;
  node->prev = back->prev;
  node->next = back;
  back->prev = node;
  size++;
}
template <typename E>
E DoublyLinkedList<E>::removeFront() {
  cout << "in remove front\n";
  DLListNode<E>* node = front->next;
  //check if empty
  if (front->next == back) {
    throw ListEmpty("removeFront from empty list!");
  }
  node->next->prev = node->prev;
  node->prev->next = node->next;
  node->next = NULL;
  node->prev = NULL;
  E temp = node -> data;
  cout << "wow info: " << temp.masterFaculty->getRoot()->value.getName() << endl;
  cout << "wow more info: " << temp.masterStudent->getSize() << endl;

  size--;
  //delete node;
  cout << "removefront success\n";
  return temp;
}
template <typename E>
E DoublyLinkedList<E>::removeBack() {
  DLListNode<E>* node = back->prev;
  //check if empty
  if (back->prev == front) {
    throw ListEmpty("removeBack from empty list!");
  }
  node->prev->next = back;
  back->prev = node->prev;
  E temp = node->data;
  node->prev = NULL;
  node->next = NULL;
  delete node;
  size--;
  return temp;
}
template <typename E>
E DoublyLinkedList<E>::remove(E key) { //search for data and remove it
  DLListNode<E>* curr = front;
  while(curr->data != key) {
    curr = curr->next;
    if(curr == NULL) {  //key not found
      throw KeyNotFound("Key not Found!");
    }
  }
  curr->next->prev = curr->prev;
  curr->prev->next = curr->next;
  E temp = curr->data;
  curr->next = NULL;
  curr->prev = NULL;
  delete curr;
  size--;

  return temp;
}

#endif
