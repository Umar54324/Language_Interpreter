//
// Created by umarc on 11/26/2021.
//

#include "ExpressionClass.h"
#include <iostream>
#include <string>



ExpressionClass::ExpressionClass(vector<Node*>& expr) { // construct from expression vector
    overallRoot = add(overallRoot, expr);
    // add(overallRoot, expr);
}
// void ExpTree::add(Node* root, vector<Node*>& expr) { // passing expr as a reference
// private method
Node* ExpressionClass::add(Node* root, vector<Node*>& expr) { // passing expr as areference
        vector<Node*> dummy;
        Node* next = new Node(1, 0, "\0");
        dummy.push_back(next);
        Node* first = expr[0]; // store the first element
        expr.erase(expr.begin()); // remove the first element
        root = first; // root points to the first token Node
        if (!(first->isOperand)) { // if first is an operator, add 2 operands
            if(first->optr == "~" || first->optr == "!"){
                root->left = add(root->left, expr);
                root->right = add(root->right, dummy);
            }
            else {
                root->left = add(root->left, expr);
                root->right = add(root->right, expr);
            }
        }
        return root; // return the new sub-tree
    }
void ExpressionClass::printTree() {
    printTree(overallRoot, 0); // call helper method
}
void ExpressionClass::printSpaces(int level) { // print 4 spaces per level, for indentation
    for (int i = 0; i < level*4; i++) {
        cout << ' ';
    }
}
// private recursive helper method
void ExpressionClass::printTree(Node* root, int level) {
    if (root == nullptr) return;
    printTree(root->right, level+1); // print the right sub-tree
    printSpaces(level); // print the indentation for the root of sub-tree
    root->print(); // print the root
    printTree(root->left, level+1); // print the left sub-tree
}
int ExpressionClass::parse() {
    return parse(overallRoot);
}



// copy constructor, assignment operator, destructor
Node* ExpressionClass::copy(const Node* that) {
    Node* n = new Node(that->isOperand, that->operand, that->optr );
    if (that->left != nullptr)
        n->left = copy(that->left);
    if (that->right != nullptr)
        n->right = copy(that->right);
    return n;
}
ExpressionClass::ExpressionClass(const ExpressionClass& that) {
    overallRoot = copy(that.overallRoot);
}
ExpressionClass& ExpressionClass::operator=(const ExpressionClass& that) {
    if (this != &that) {
        destroy(overallRoot);
        overallRoot = copy(that.overallRoot);
    }
    return *this;
}
int ExpressionClass::parse(Node* root) {
    if (root->isOperand) return root->operand;
    int arg1 = parse(root->left);
    int arg2 = parse(root->right);
    if(root->optr == "*"){
        return arg1*arg2;
    }
    else if(root->optr == "/"){
        return arg1/arg2;
    }
    else if(root->optr == "+"){
        return arg1+arg2;
    }
    else if(root->optr == "-"){
        return arg1-arg2;
    }
    else if(root->optr == ">"){
        if(arg1>arg2){
            return 1;
        }
        else{
            return 0;
        }
    }
    else if(root->optr == "<"){
        if(arg1<arg2){
            return 1;
        }
        else{
            return 0;
        }
    }
    else if(root->optr == "!"){
        return !arg1;
    }
    else if(root->optr == "%"){
        return arg1%arg2;
    }
    else if(root->optr == "&&"){
        if(arg1!=0 && arg2 !=0){
            return 1;
        }
        else{
            return 0;
        }
    }
    else if(root->optr == "||"){
        if(arg1!=0 || arg2 !=0){
            return 1;
        }
        else{
            return 0;
        }
    }
    else if(root->optr == "=="){
        if(arg1 == arg2){
            return 1;
        }
        else{
            return 0;
        }
    }
    else if(root->optr == "!="){
        if(arg1 != arg2){
            return 1;
        }
        else{
            return 0;
        }
    }
    else if(root->optr == ">="){
        if(arg1>=arg2){
            return 1;
        }
        else{
            return 0;
        }
    }
    else if(root->optr == "<="){
        if(arg1<=arg2){
            return 1;
        }
        else{
            return 0;
        }
    }
    else if(root->optr == "~"){
        return -1*arg1;
    }






}
ExpressionClass::~ExpressionClass() {
    destroy(overallRoot);
}
void ExpressionClass::destroy(Node* n) {
    if (n == nullptr)
        return;
    destroy(n->left);
    destroy(n->right);
    delete n;
    n = nullptr;
}