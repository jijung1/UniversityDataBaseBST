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
  Generic Singly Linked List implementation 
*/

#ifndef GENERICLINKEDLIST_H
#define GENERICLINKEDLIST_H

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;
template<typename E>
class ListNode {
public:
  ListNode();
  ListNode (E d);
  ListNode (ListNode* next, E data);
  ~ListNode();
  ListNode* next;
  E data;
};

//implementation//
template <typename E>
ListNode<E>::ListNode() {
  //default constructor
  this->next = NULL;
}
template <typename E>
ListNode<E>::ListNode(ListNode* next, E data) {
  this->next = next;
  this->data = data;
}
template <typename E>
ListNode<E>::ListNode(E d) {
  this->data = d;
  this->next = NULL; //nullptr
}

template <typename E>
ListNode<E>::~ListNode() {
  this->next = NULL;
}

template <typename E>
class GenLinkedList {
private:
  ListNode<E>* front;
  unsigned int size;
public:
  GenLinkedList();
  GenLinkedList(const GenLinkedList& otherList); //copy constructor
  ~GenLinkedList();
  void insertFront(E d); //inc size, fill new ListNode with e,
  E removeFront(); //dec size, store data to temp, save ListNode to be delete to manually call garbage collection, set head = head->next, point old to null, then delete old, return temp;
  E deletePos(int pos);
  string printList() const;
  int find(E val) const; //aka search();
  bool isEmpty() const;
  unsigned int getSize() const;
};

template <typename E>
GenLinkedList<E>::GenLinkedList() {
  size = 0;
  this->front = NULL;
}

template <typename E>
GenLinkedList<E>::GenLinkedList(const GenLinkedList& otherList) { //copy constructor
  if (otherList.front == NULL) {
    size = 0;
    front = NULL;
  }
  else {

    this->front = new ListNode<E>(otherList.front->data);
    ListNode<E>* tempOther = otherList.front->next;
    ListNode<E>* temp = this->front;
    this->size = 1;
    while (tempOther != NULL) {
      temp->next = new ListNode<E> (tempOther, tempOther->data);
      temp = temp->next;
      tempOther = tempOther->next;
      this->size++;
    }
    temp->next = NULL;
    tempOther = NULL;
    delete temp;
    delete tempOther;
  }
}


template <typename E>
GenLinkedList<E>::~GenLinkedList() {

  while (!isEmpty()) {
     this->removeFront();
  }
  this->front = NULL;
}
template <typename E>
bool GenLinkedList<E>::isEmpty() const {
  return this->front == NULL;
}

template <typename E>
unsigned int GenLinkedList<E>::getSize() const{
  return this->size;
}
template <typename E>
string GenLinkedList<E>::printList() const{
  ListNode<E> *curr = this->front;
  string ret = "";
  while (curr != NULL) {
    ret += to_string(curr->data);
    ret += ",";
    curr = curr -> next;
  }
  ret = ret.substr(0,ret.length()-1);
  delete curr;
  return ret;
}
template <typename E>
void GenLinkedList<E>::insertFront(E d) {
  ListNode<E> *node = new ListNode<E>(d);
  node -> next = this->front;
  this->front = node;
  size++;

}
template <typename E>
E GenLinkedList<E>::removeFront() {
  E temp = this->front->data;
  ListNode<E> *ft = this->front;
  this->front = this->front->next;
  ft->next = NULL; //
  this->size--;
  delete ft;

  return temp;
}
//return the position if value exists
template <typename E>
int GenLinkedList<E>::find(E val) const {
  int idx = -1;
  ListNode<E> *curr = front;
  while (curr != NULL) {
    ++idx;
    if (curr->data == val) {  //found value
      break;
    }
    else {
      curr = curr->next;
    }
  }
  if (curr == NULL) { //we did not find the value
    idx = -1;
  }
  return idx;
}
template <typename E>
E GenLinkedList<E>::deletePos(int pos) {
  if (pos < 0 || pos > this->getSize()-1) {
    cout << "invalid position to delete!\n";
    exit(1);
  }
  int idx = 0;
  //add check to make sure position is valid
  if (pos == 0) { //if position is 0, then call removeFront?
    return removeFront();
  }
  else {
    ListNode<E> *curr = front;
    ListNode<E> *prev = front;
    while (idx != pos) {
      prev = curr;  //stay back
      curr = curr->next;
      ++idx;
    }

    //when we find the correct pos, update pointers
    prev->next = curr->next;
    curr->next = NULL;
    E temp = curr->data;
    delete curr; //ixnayhim
    size--;

    return temp;
  }

}

#endif /*GENERICLINKEDLIST_H*/
