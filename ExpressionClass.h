//
// Created by umarc on 11/26/2021.
//
#include <iostream>
#include <string>
#include <vector>
#ifndef PROJECT8_EXPRESSIONCLASS_H
#define PROJECT8_EXPRESSIONCLASS_H
using namespace std;
class Node{
public:
    bool isOperand;
    int operand;
    string optr;
    Node* left;
    Node* right;
    Node(bool isOperand, int operand, string optr){    //contructor that takes in node inputs
        left = nullptr;
        right = nullptr;
        this->isOperand = isOperand;
        this->operand = operand;
        this->optr = optr;
    }
    void print(){                                   //prints value of the node
        if(isOperand){
            cout << operand << endl;

        }
        else{
            cout << optr << endl;
        }
    }
};
class ExpressionClass {
private:
    const int spaces_per_level = 4;
    Node* overallRoot;
    Node* add(Node* root, vector<Node*>&);
    void printTree(Node*, int);
    void printSpaces(int);
    int parse(Node*);
    Node* copy(const Node* that);
    void destroy(Node*);
public:
    int parse();
    ExpressionClass(vector<Node*>& expr); // constructor
    void printTree();
    ExpressionClass(const ExpressionClass& that);
    ExpressionClass& operator=(const ExpressionClass& that);
    ~ExpressionClass();


};


#endif //PROJECT8_EXPRESSIONCLASS_H
