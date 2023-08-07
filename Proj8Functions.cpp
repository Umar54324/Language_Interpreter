//
// Created by umarc on 11/25/2021.
//

#include "Proj8Functions.h"
#include "Parse.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "ExpressionClass.h"

using namespace std;
map <string, int> variables;
void printText(){
    string txt = peek_next_token();
    if(txt == "\n"){
        cout << endl;
    }
    cout << txt;

}
void printOutput(){
    read_next_token();
    int num;
    if(next_token_type==SYMBOL){
        num = math();
    }
    else if(next_token_type == NAME){
        string variable = next_token();
        map<string, int>::iterator pos;
        pos = variables.find(variable);
        num = pos->second;
    }
    else {
        num = (int) token_number_value;
    }
    cout << num;
}
int math(){
    vector<Node*> expr;
    if (next_token_type == SYMBOL) {

        string type = next_token();
        //char typer = type[0];
        Node *init = new Node(0, 0, type);
        expr.push_back(init);

    }
    string peeked = peek_next_token();
    while(peeked!="text" && peeked != "set" && peeked !="output" && peeked !="var") {
        if (next_token_type == SYMBOL) {
            read_next_token();
            string type = next_token();
            //char typer = type[0];
            Node *init = new Node(0, 0, type);
            expr.push_back(init);

        }
        else if(next_token_type == NAME){
            read_next_token();
            string variable = next_token();
            map<string, int>::iterator pos;
            pos = variables.find(variable);
            Node *next = new Node(1, pos->second, "\0");
            expr.push_back(next);
        }
        else{
            read_next_token();
            int num = token_number_value;
            Node* next = new Node(1, num, "\0");
            expr.push_back(next);
        }
        peeked = peek_next_token();
    }
    int result = execute(expr);


    return result;
}
int execute(vector<Node*>& expr){
//    if(expr.size()==2){
//        Node* next = new Node(1, 0, "\0");
//        expr.push_back(next);
//    }
    ExpressionClass* tree = new ExpressionClass(expr);
    int result = tree->parse();
    return result;

}
void initVar(){
    read_next_token();
    string varName = next_token();

    if(variables.find(varName)!=variables.end()){
        cout << "variable " << varName << " incorrectly re-initialized" << endl;
        setVar(varName);
    }
    else {
        variables.insert({varName, 0});

        read_next_token();
        if (next_token_type == NUMBER) {
            variables[varName] = token_number_value;
        } else if (next_token_type == SYMBOL) {
            variables[varName] = math();
        }
    }

}
void setVar(string name){
    read_next_token();
    map<string, int>::iterator pos;
    if(variables.find(name)!=variables.end()){
        pos = variables.find(name);
    }
    else{
        cout << "variable " << name << " not declared" << endl;
        variables.insert({name, 0});
        pos = variables.find(name);
    }
    if(next_token_type == NUMBER){
        pos->second = token_number_value;
    }
    else if(next_token_type == SYMBOL){
        int res = math();
        pos->second = res;
    }
}