#ifndef GENSTACK_CPP
#define GENSTACK_CPP

#include <iostream>
using namespace std;
template <typename E>
class GenStack
{
  public:
    GenStack();
    GenStack(int mySize);
    ~GenStack();
    void push(E e);
    E pop();
    E peek();
    int size();
    bool isFull();
    bool isEmpty();
    void delLast();
    int maxSize;
    int top;
    E* myArray;
};
template <typename E>
GenStack<E>::GenStack()
{
  cout << "corgi\n";
  myArray = new E[5];
  maxSize = 5;
  top = -1;
}
template <typename E>
GenStack<E>::GenStack(int mySize)
{
  cout << "german" << endl;
  myArray = new E[mySize];
  cout << "shep" << endl;
  maxSize = mySize;
  top = -1;
}
template <typename E>
GenStack<E>::~GenStack()
{
  delete[] myArray;
}
template <typename E>
void GenStack<E>::push(E e)
{
  if(!isFull())
    myArray[++top] = e;
}
template <typename E>
E GenStack<E>::pop()
{
  if(!isEmpty())
    return myArray[top--];
}
template <typename E>
E GenStack<E>::peek()
{
  if(!isEmpty())
    return myArray[top];
}
template <typename E>
int GenStack<E>::size()
{
  return top;
}
template <typename E>
bool GenStack<E>::isFull()
{
  return top == maxSize-1;
}
template <typename E>
bool GenStack<E>::isEmpty()
{
  return top == -1;
}
template <typename E>
void GenStack<E>::delLast() //if stack is full then delete the last value to allow more appending
{
  //delete the 0th item and shift left
  for(int i = 0; i < size(); i++)
    myArray[i] = myArray[i+1];
  top--;
}

#endif /*GENSTACK_CPP*/
