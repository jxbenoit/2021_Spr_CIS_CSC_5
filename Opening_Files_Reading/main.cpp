/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    
    fstream In( "/Users/jbenoit/Desktop/score.txt" );
    
    //In.open( "/Users/jbenoit/Desktop/score.txt", ios::in );
    
    if( ! In ) {
        cout << "File didn't open for reading!" << endl;
        return 1;
    }

    while( ! In.eof() ) {
      int roll;
      In >> roll;
    
      cout << roll << endl;
    }
    
    In.close();

    return 0;
}

