/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: jbenoit
 *
 * Created on May 27, 2021, 1:52 PM
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//int add( int a, int b );
int add( int a, int b, int c = 0, int d = 0 );
//float add( float a, float b, float c = 0, float d = 0 );
//int add( float a, float b );

int main(int argc, char** argv) {
    string s = "abc";
    vector<int> V( 45 );
    V[0] = 35;
    V[1] = 10;
  
    
    cout << "3 + 5 = " << add( 3, 5) << endl;
    cout << "3 + 5 + 7 = " << add( 3, 5, 7 ) << endl;

    return 0;
}

/*
int add( int a, int b ) {
    return a + b;
}
 */

int add( int a, int b, int c, int d ) {
    return a + b + c + d;
}

/*
int add( float a, float b ) {
    return a + b;
}

 */
