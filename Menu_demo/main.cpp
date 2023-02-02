/*Menu demo
 */

#include <iostream>
#include <string.h>
#include <string>

using namespace std;

int main(int argc, char** argv) {
    char choice;
    char name[80];
    string s;
    
    cout << "What is your name?";
    cin >> name;
    
    char name2[80];
    strcpy( name2, name );
    
   
    
    if( strcmp(name, "John") == 0 ) {  //Matches
      cout << "Your name is " << name << endl;  
    }
    else if( strcmp(name, "John") > 0 ) {
        cout << name << " comes after John in the dictionary " << endl; 
    }
    else {
        cout << name << " comes before John in the dictionary " << endl;         
    }

    //Print menu.
    /*
    cout << "Please enter choice:\n"
         << " A. Print balance\n"
         << " B. Deposit\n"
         << " C. Withdraw\n"
         << " D. Exit" << endl;
    cout << " : ";
    cin >> choice;
    
    //Validate input.
    bool good_input = (choice < 'A' || choice > 'D') ? false : true;

    if( ! good_input ) {
        cout << "You need to enter a letter from A to D."  << endl;
        return 1;
    }
    
    //User entered 1, 2, 3, or 4.
    switch( choice ) {
        case 'A':  //Print balance
        case 'a':
            PrintBalance();
            break;

        case 'B':  //Deposit
        case 'b': 
            float amount;
            cout << "How much?";
            cin >> amount;
            Deposit( amount );
            break;
            
        case 'C':  //Withdrawal
        case 'c': 
            Withdraw();
            break;

        default:
            cout << "Goodbye!" << endl;
    }
    */
    
    return 0;
}

