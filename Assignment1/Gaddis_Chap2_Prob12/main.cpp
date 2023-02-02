/*Gaddis Chapter 2 Problem 12
 Land Calculation
 */


#include <iostream>

using namespace std;

const int ACRE = 43560;  //1 acre = 43,560 feet

int main(int argc, char** argv) {
    //Declare a variable to hold the square feet.
    float sq_feet;
    
    //Ask user for number of square feet.      INPUT
    cout << "Please enter the number of square feet: ";
    cin >> sq_feet;
    
    //Calculate number of acres.                PROCESSING
    float num_acres = sq_feet / ACRE;
    
    //Output results.                          OUTPUT
    cout << "An area of " << sq_feet << " is equal to " << num_acres
         << " acres " << endl;

    return 0;
}

