/*Review for test
 
 * Loops -- while, do-while, for
 * if, if-else, if-else if-else if-else, ...
 * switch
 * ternary
 * Files - opening, closing, reading, writing
 * Rand, srand
 * cout
 * cin
 * formatting cout, iomanip - fixed, setprecision, setw, showpoint, left, right
 * strings - string library
 * data types - char, int, short, long, float, double, bool, unsigned
 * Math operators: +, -, /, *, +=, ++, *=, --
 * Logic operators: ||, &&, !   x||y, x&&y, !x, x^y
 * const
 * Math functions: pow(), sin(), exp(), log()
 * integer division
 * type casting 
 *  '=' versus '=='
 * ==, !=, >, <, >=, <=
 * c-style strings?  strcmp()
 * Variable scope - global versus local
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

int RollDie( int sides );

int main(int argc, char** argv) {
    
    ofstream Out;
    
    Out.open( "/Users/jbenoit/Desktop/score.txt" );        //, ios::app );
    
    if( ! Out ) {
        cout << "File didn't open for writing!" << endl;
        return 1;
    }
    
    //...
    //...
    for( int i = 0; i < 10; i++ ) {
        int roll = rand() % 6 + 1;   //6-sided die roll
    
        Out << setw(10) << roll << endl;
    }
    
    Out.close();

    return 0;
}

int RollDie( int sides ) {
    return rand() % sides + 1;
}
