/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: jbenoit
 *
 * Created on March 2, 2021, 1:14 PM
 */

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv) {
    int A, B;

    unsigned char c1, c2;  //range: 0 - 255
    string first, last, full_name;
    
    cout << "What is your full name: ";
    getline( cin, full_name );

    cout << "Hello " << full_name << "!" << endl;
    
    return 0;
}

