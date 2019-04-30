#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <iostream>
#include <cstdlib> //include for NULL
#include "Student.h"
#include "Faculty.h"

using namespace std;

template <typename E>
class TreeNode {
public:
  TreeNode();
  TreeNode(const E& value);
  virtual ~TreeNode(); //any derived class should have a virtual destrutor
  E value;
  TreeNode* left;
  TreeNode* right;
};
template <typename E>
TreeNode<E>::TreeNode() {
  this->left = NULL;
  this->right = NULL;
}
template <typename E>
TreeNode<E>::TreeNode(const E& value) {
  this->left = NULL;
  this->right = NULL;
  this->value = value;
}
template <typename E>
TreeNode<E>::~TreeNode() {
  this->left = NULL;
  this->right = NULL;
}
template <typename E>
class BST {
public:
    BST();
  //  BST(const BST<E>& copy);
    ~BST();
    void insert(const E& value);
    bool contains(const E &value);
    TreeNode<E>* findNode(const E& value);
    void findIOTNode(int count, int position, TreeNode<E>* node, TreeNode<E>*& modifiedNode); //returns pointer to a node based on its in order traversal position
    TreeNode<E>* getSuccessor(TreeNode<E>* d);
    bool deleter(E value);
    TreeNode<E>* getRoot();
    TreeNode<E>* getMin();
    TreeNode<E>* getMax();
    unsigned int getSize();
    bool isEmpty();
    void printTree(); //in order print
    void recPrint(TreeNode<E> *node);

  private:
    TreeNode<E> *root;
    unsigned int size;
};

template <typename E>
BST<E>::BST() //default constructor
{
  this->root = NULL;
  this->size = 0;
}


/*
template <typename E>
BST<E>::BST(const BST<E>& copy) {
  BST<E*> temp;
  temp = new BST<E>();
  cout << "bst copy contructor called" << endl;
  temp->root = copy.getRoot();
  temp->size = copy.getSize();
  while(!copy.isEmpty()) {
    temp->insert(copy.getRoot()->value);
    copy.deleter(copy.getRoot()->value);
  }
}
*/
template <typename E>
BST<E>::~BST() {
  while(this->root != NULL) {
    deleter(this->root->value);
  }
}
template <typename E>
TreeNode<E>* BST<E>::getRoot() {
  return this->root;
}

template <typename E>
void BST<E>::findIOTNode(int count, int position, TreeNode<E>* node, TreeNode<E>*& modifiedNode) {
  if (modifiedNode->value.getIDNum() > 299999999) {
    return;
  }
  if (node->left != NULL && modifiedNode->value.getIDNum() < 299999999) {
    cerr << "going left" << endl;
    findIOTNode(count, position, node->left, modifiedNode);
  }

  cout << "modified node value: " << modifiedNode->value.getIDNum() << endl;

  cout << "node id: " << node->value.getIDNum() << endl;
  cerr << "position: " << position << endl;
  cerr << "count: " << count << endl;
  if (modifiedNode->value.getIDNum() >= position && node->value.getIDNum() != 0 && modifiedNode->value.getIDNum() <299999999) {
    cout << "modifed node!" << endl;
    modifiedNode = node;
    cout << modifiedNode->value.getIDNum() << endl;
  }
  if(node->value.getIDNum() != 0 && modifiedNode->value.getIDNum() < 299999999) {
    modifiedNode->value.setIDNum(modifiedNode->value.getIDNum() + 1);
  }


  if (node->right != NULL && modifiedNode->value.getIDNum() < 299999999) {
    cerr << "going right" << endl;
    findIOTNode(count, position, node->right, modifiedNode);
  }
}

template <typename E>
void BST<E>::printTree() {
  recPrint(this->root);
}
template <typename E>
void BST<E>::recPrint(TreeNode<E> *node) { //inorder traversal recursive print
  if(node == NULL) {
    return;
  }
  recPrint(node->left);
  cout << "--------------------------------------\n";
  cout << node->value.toString();
  cout << "--------------------------------------\n";
  recPrint(node->right);
}
template <typename E>
bool BST<E>::isEmpty() {
  return (this->root == NULL);
}

template <typename E>
unsigned int BST<E>::getSize() {
  return this->size;
}
template <typename E>
void BST<E>::insert(const E& value) {
  if (contains(value)) {  //no need to insert duplicate value
    return;
  }
  TreeNode<E>* node = new TreeNode<E>(value);


  if (this->isEmpty()) {  //empty tree
    this->root = node;
  }
  else {  //not an empty tree, let's continue to add
    TreeNode<E>* current = root;
    TreeNode<E>* parent; //empty node

    while(true) { //search for insertion point
      parent = current;
      if(value < current->value) {  //go left
        current = current -> left;
        if(current == NULL) { //we found our location
          parent -> left = node;
          break;
        }
      }
      else {
        current = current -> right;
        if(current == NULL) {
          parent -> right = node;
          break;
        }
      }
    }
  }
  this->size++;
}
template <typename E>
TreeNode<E>* BST<E>::findNode(const E& value) {
  if (isEmpty()) {
    cout << "isempty" <<endl;
    return NULL;
  }
  TreeNode<E>* current = this->root;

  while (current->value != value) {
    if (value < current -> value)
      current = current -> left;
    else
      current = current -> right;
    if (current == NULL) { //item not in tree
      break;
    }
  }
  return current;
}
template <typename E>
bool BST<E>::contains(const E& value) {
  if(this->isEmpty()) {
    return false;
  }
  else {  //not an empty tree
    TreeNode<E>* current = root;
    bool thisishard = current->value == value;
    while(current->value != value) {
      if(value < current->value) {
        current = current->left;
      }
      else {
        current = current->right;
      }
      if(current == NULL) { //item not in tree
        return false;
      }
    }
  }
  return true;
}
template <typename E>
bool BST<E>::deleter(E value) {
  if (isEmpty()) {
    return false;
  }

  //check if value/value exists in tree
  TreeNode<E> *current = this->root;
  TreeNode<E> *parent = this->root;
  bool isLeft = true;

  //now let's iterate and update our pointers
  while(current->value != value) {
    parent = current;

    if(value < current->value) {
      isLeft = true;
      current = current->left;
    }
    else {
      isLeft = false;
      current = current->right;
    }

    if (current == NULL)  //value not in tree
      return false;
  }
  //at this point we found our node to be deleted

  if (current->left == NULL && current->right == NULL) {  //no children
    if(current == this->root) {
      this->root = NULL;
    }
    else if(isLeft) {
      parent->left = NULL;
    }
    else {
      parent->right = NULL;
    }
  }

  //we need to check if node to be deleted has one child
  else if (current->right == NULL) { //no right child
    if(current == this->root) {
      this->root = current -> left;
    }
    else if (isLeft) {
      parent->left = current->left;
    }
    else {
      parent->right = current->left;
    }
  }
  else if (current->left == NULL) { //no left child
    if(current == this->root) {
      this->root = current -> right;
    }
    else if (isLeft) {
      parent->left = current->right;
    }
    else {
      parent->right = current->right;
    }
  }
  else {  //the node to be deleted has 2 children
    //find the successor of the node to be deleted (current)
    TreeNode<E> *successor = getSuccessor(current);

    if(current == this->root) {
      successor->left = current->left;
      this->root = successor;

    }
    else if(isLeft) {
      //parent ->left ->left = NULL;
      //parent ->left->right = NULL;
      //delete parent->left;
      parent->left = successor;
      successor->left = current->left;
    }
    else {
      //null out and delete target node
      parent->right = successor;
      successor->left = current->left;
    }
  }
  delete current;
  this->size--;
  return true;
}
template <typename E>
TreeNode<E>* BST<E>::getSuccessor(TreeNode<E> *d) { //d is the node to be deleted
  TreeNode<E>* sp = d; //successor's parent
  TreeNode<E>* successor = d;
  TreeNode<E> *current = d->right;

  while(current != NULL) {
    sp = successor;
    successor = current;
    current = current->left;
  }

  //we need to check if success is a descendent of right child
  if(successor != d->right) {
    sp->left = successor->right;
    successor->right = d->right;
  }
  return successor;
}
template <typename E>
TreeNode<E>* BST<E>::getMin() {
  TreeNode<E>* curr = this->root;
  while (curr->left != NULL) {
    curr = curr -> left;
  }
  return curr;
}
template <typename E>
TreeNode<E>* BST<E>::getMax() {
  TreeNode<E>* curr = this->root;
  while (curr->right != NULL) {
    curr = curr -> right;
  }
  return curr;
}


#endif /*BINARYSEARCHTREE_H*/
