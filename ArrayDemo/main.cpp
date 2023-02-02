/* 
 * File:   main.cpp
 * Author: 
 * Created:
 * Purpose:  
 * 
 */

//System Libraries
#include <iostream>  //Input/Output Library
#include <iomanip>   //Format Library
#include <fstream>   
using namespace std;

//User Libraries

//Global Constants, no Global Variables are allowed
//Math/Physics/Conversions/Higher Dimensions - i.e. PI, e, etc...
const int COLS=6;

//Function Prototypes
void fillTbl(int [][COLS],int);
void prntTbl(const int [][COLS],int);
void SaveTable(const int T[][COLS],int Size);
void LoadTable( string FileName, int T[][COLS], int &R, int &C );

//Execution Begins Here!
int main(int argc, char** argv) {
    //Declare Variables
    const int ROWS=6;
    int tablSum[ROWS][COLS];
    
    //Initialize or input i.e. set variable values
    fillTbl(tablSum,ROWS);
    
    //Display the outputs
    //prntTbl(tablSum,ROWS);
    SaveTable( tablSum, ROWS );
    
    int Table1[ROWS][COLS];
    int Rows1, Cols1;
    LoadTable( "Out.txt", Table1, Rows1, Cols1 );

    prntTbl(tablSum,ROWS);

    //Exit stage right or left!
    return 0;
}

void fillTbl( int Table[][COLS], int Rows ) {
    for( int die1 = 1; die1 <= 6; die1++ ) {
      for( int die2 = 1; die2 <= 6; die2++ ) {
          //Table[die1-1][die2-1] = die1 + die2;
          Table[die1-1][die2-1] = rand() % 100 + 1;
      }
    }
}

void prntTbl( const int Table[][COLS], int Rows ) {
    cout << "Think of this as the Sum of Dice Table" << endl;
    
    //Print column headings.
    cout << "           C o l u m n s\n" 
         << "     |   1   2   3   4   5   6\n"
         << "----------------------------------" << endl;
    
    char row_hdg[] = " ROWS ";

    for( int i = 0; i < 6; i++ ) {
      cout << row_hdg[i] << "  " << i+1 << " |"; 
      
      for( int j = 0; j < 6; j++ ) {
          cout << setw(4) << Table[i][j];
      }
      cout << endl;
    }
}


void SaveTable(const int T[][COLS],int Rows) {
    ofstream Out( "out.txt" );
    Out << Rows << " " << COLS << endl;
    for( int i = 0; i < COLS; i++ ) {
        for( int j = 0; j < Rows; j++ )
            Out << T[i][j] << " ";
        Out << endl;
    }
    
    Out.close();
}

void LoadTable( string FileName, int T[][COLS], int &R, int &C ) {
    ifstream In( FileName.c_str() );
    In >> R >> C;
    for( int i = 0; i < C; i++ ) {
        for( int j = 0; j < R; j++ )
            In >> T[i][j];
    }
    
    In.close();    
}
