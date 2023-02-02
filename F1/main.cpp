/* 
 * File:   main.cpp
 * Author: YOUR NAME HERE
 * Created on DATE AND TIME HERE
 * Purpose:  Input something, output it reversed with some modifications
 * Note:Range should be 5 digits, 321 = 00321 reverse = 12300 before subtraction
 *      12300 - 999 = 11301 after subtraction
 *      12300 = 00321 = 321 after reversal and no subtraction
 */

//System Libraries Here
#include <iostream>//cin,cout,endl
#include <cstring> //strlen()
using namespace std;
//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here
bool  inRange(const char [],unsigned short &);//Output true,unsigned or false
bool  reverse(unsigned short,signed short &);//Output true,short or false
short subtrct(signed short,int);

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    const int SIZE=80;     //More than enough
    char  digits[SIZE];    //Character digits or not
    unsigned short unShort;//Unsigned short
    short snShort;         //Signed short
    
    //Input or initialize values Here
    cout<<"Reverse a number and subtract if possible."<<endl;
    cout<<"Input a number in the range of an unsigned short"<<endl;
    cin>>digits;
    
    //Test if it is in the Range of an unsigned short
    if(!inRange(digits,unShort)){
        cout<<"No Conversion Possible"<<endl;
        return 0;
    }
    
    //Reverse and see if it falls in the range of an signed short
    if(!reverse(unShort,snShort)){
        cout<<"No Conversion Possible"<<endl;
        return 0;
    }
    
    //Now subtract if the result is not negative else don't subtract
    snShort=subtrct(snShort,999);
    
    //Output the result
    cout<<snShort<<endl;
    
    //Exit
    return 0;
}

bool  inRange(const char digits[], unsigned short &unShort ) {
     //Range of unsigned short: 0 to 65,535

      unShort = 0;
      for( int i = 0; i < strlen(digits); i++ ) {
          if( digits[i] < '0' || digits[i] > '9' )
              return false;

          int d = digits[i] - '0';

          unsigned short diff = 65535 - unShort;   //Amount of space left before overflowing an unsigned short
          if( unShort * 10 + d > diff )
            return false;

          unShort = unShort * 10 + d;
      }
      
      return true;
}

bool  reverse(unsigned short unShort,signed short &snShort) {//Output true,short or false
    //Range of signed short: -32,768 to 32,767
    snShort = 0;
    for( int i = 0; i < 5; i++ ) {
          int d = unShort % 10;
          unShort /= 10;

          unsigned short diff = 32767 - snShort;   //Amount of space left before overflowing an unsigned short
          if( snShort * 10 + d > diff )
            return false;

          snShort = snShort * 10 + d;
    }
    
    return true;
}
short subtrct(signed short snShort ,int sub) {
    return ( snShort - sub >= 0 ) ? snShort - sub : snShort;
}
