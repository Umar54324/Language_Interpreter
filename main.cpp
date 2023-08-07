#include <iostream>
#include "Parse.h"
#include "Proj8Functions.h"
#include <string>
using namespace std;

void run(){
    do{
        read_next_token();
        if(next_token_type == SYMBOL){
            string cmd(next_token());
            if(cmd=="//"){
                skip_line();
            }
        }
        if(next_token_type == NAME){
            string cmd(next_token());
            if(cmd==("text")){
                printText();
            }
            else if(cmd=="output"){
                printOutput();
            }
            else if(cmd=="var"){
                initVar();
            }
            else if(cmd=="set"){
                read_next_token();
                setVar(next_token());
            }
            else if(cmd == "//"){
                skip_line();
            }
        }


    } while(next_token_type != END);

}
int main() {
/*
    cout << "Test1" << endl;
    set_input("test1.blip");
    run();
    cout<< endl << endl;
    cout << "Test2" << endl;
    set_input("test2.blip");
    run();
    cout<< endl << endl;
    cout << "Test3" << endl;
    set_input("test3.blip");
    run();
    cout<< endl << endl;

    cout << "Test4" << endl;
    set_input("test4.blip");
    run();
    cout<< endl << endl;

    cout << "Test5" << endl;
    set_input("test5.blip");
    run();
    cout<< endl << endl;
    */
    set_input("test_grader.blip");
    run();

}
