//
//  main.cpp
//  BST
//
//  Created by Mikaela Schaefer on 3/12/18.
//  Copyright © 2018 Mikaela Schaefer. All rights reserved.
//

#include <iostream>

using namespace std;

class Node{
private:
    int data;
    Node * parent;
    Node * leftChild;
    Node * rightChild;
    
public:
    Node(int ddata, Node * newP = nullptr, Node * newL = nullptr, Node * newR = nullptr);
    ~Node();
    void setLeftChild(Node * newL);
    void setRightChild(Node * newR);
    void setParent(Node * newP);
    Node * getLeft();
    Node * getRight();
    Node * getParent();
    int getData(void);
    void setData(int newData);
};

Node::Node(int ddata, Node * newP, Node * newL, Node * newR){
    data = ddata;
    parent = newP;
    leftChild = newL;
    rightChild = newR;
}

Node::~Node(){
    if (leftChild != nullptr) {
        free(leftChild);
    }
    if (rightChild!= nullptr) {
        free(rightChild);
    }
}

void Node::setLeftChild(Node *newL){
    this->leftChild = newL;
}

void Node::setRightChild(Node *newR){
    this->rightChild = newR;
}

void Node::setParent(Node *newP){
    this->parent = newP;
}

Node * Node::getLeft(){
    return this->leftChild;
}

Node * Node::getRight(){
    return this->rightChild;
}

Node * Node::getParent(){
    return this->parent;
}

int Node::getData(void){
    return this->data;
}

class BST {
private:
    Node * root;
    int size;
public:
    BST();
    ~BST();
    Node * getRoot() {return this->root;};
    void insert(int num);
    Node * find(int num);
    int remove(int num);
};

BST::BST(){
    root = nullptr;
    size = 0;
}

BST::~BST(){
    if (root != nullptr){
        free(root);
    }
}

void BST::insert(int num){
    Node * newNode = new Node(num);
    if (size == 0) {
        root = newNode;
    }
    else {
        Node * current = getRoot();
        Node * previous;
        bool notDone = true;
        bool isLeftChild = false;
        while (notDone){
            if (current->getData() < num){
                previous = current;
                current = current->getRight();
                isLeftChild = false;
            }
            else {
                previous = current;
                current = current->getLeft();
                isLeftChild = true;
            }
            //Check if nullptr found
            if (current == nullptr) {
                current = newNode;
                if (isLeftChild){
                    previous->setLeftChild(newNode);
                }
                else{
                    previous->setRightChild(newNode);
                }
                newNode->setParent(previous);
                notDone = false;
            }
        }
    }
    this->size++;
}

Node * BST::find(int num){
    Node * returnVal = nullptr;
    bool done = false;
    Node * current = this->getRoot();
    while(!done) {
        if (current != nullptr){
        //if num > current->getData
            if (num == current->getData()){
                returnVal = current;
                done = true;
            }
            else if (num > current->getData()){
                current = current->getRight();
            }
            else {
                current = current->getLeft();
            }
        }
    }
    return returnVal;
}

int BST::remove(int num){
    Node * removeNode = find(num);
    return 1;
}


int main(int argc, const char * argv[]) {
    //
    BST * theBST = new BST();
    cout << "Insert nums into the tree. Enter -1 when done ";
    int usrInput;
    cin >> usrInput;
    while (usrInput != 0){
        theBST->insert(usrInput);
        cin >> usrInput;
    }
    int num;
    Node * found;
    cout << "Find ";
    cin >> num;
    found = theBST->find(num);
    cout << found->getData();
    cout << "Find ";
    cin >> num;
    found = theBST->find(num);
    cout << found->getData();
    cout << "Find ";
    cin >> num;
    found = theBST->find(num);
    cout << found->getData();
    
    return 0;
}
