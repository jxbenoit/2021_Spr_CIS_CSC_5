/* 
 * File:   main.cpp
 * Author:
 * Created on:
 * Purpose: Compare the answer sheet to the key
 *          and grade
 */

//System Libraries
#include <iostream>  //Input/Output Library
#include <fstream>   //File I/O
#include <string.h>    //String Library
using namespace std;

//User Libraries

//Global Constants, no Global Variables are allowed
//Math/Physics/Conversions/Higher Dimensions - i.e. PI, e, etc...

//Function Prototypes
void print(const string );
void read(const char [],string &);
int  compare(const string ,const string ,string &);

//Execution Begins Here!
int main(int argc, char** argv) {
    //Set the random number seed
    
    //Declare Variables
    string key,answers,score;
    char fileKey[]="key.dat",fileAns[]="answer.dat";
    float pRight;
    
    //Initialize or input i.e. set variable values
    read(fileKey,key);
    read(fileAns,answers);
        
    //Score the exam
    pRight=compare(key,answers,score);
    
    //Display the outputs
    cout<<"Key     ";print(key);
    cout<<"Answers ";print(answers);
    cout<<"C/W     ";print(score);
    cout<<"Percentage Correct = "<<pRight/score.size()*100<<"%"<<endl;
    

    //Exit stage right or left!
    return 0;
}

void read( const char filename[], string &content ) {
    ifstream In;
    In.open( filename );
    
    if( ! In.good() ) cout << "File " << filename << " didn't open " << endl;
    
    char c;
    while( In ) {
        In >> c;
        content += c + ' ';
    }
}

void print(const string content ) {

}
int  compare(const string key, const string ans ,string &test_out ) {
    //cout << "key size: " << key.size() << endl;
    //cout << "key length: " << key.length() << endl;
    cout << " KEY:" << key << endl;
    cout << " ANS:" << ans << endl;
    for( int i = 0; i < key.length(); i++ ) {
        if( key[i] == ans[i] ) cout << "C ";
        else cout << "W ";
    }
    cout << endl;
    
    return 0;
}
