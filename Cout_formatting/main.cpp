/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <iomanip>

using namespace std;


int main(int argc, char** argv) {
    //Get input from user.
    float number1, number2, number3, number4;
    cin >> number1 >> number2 >> number3 >> number4;
    
    //Output
    cout << setw(9) << static_cast<int>(number1)
         << setw(10) << setprecision(1) << showpoint << fixed
            << number1
         << setw(10) << setprecision(2) << showpoint << fixed
            << number1 << "\n"

         << setw(9) << static_cast<int>(number2)
         << setw(10) << setprecision(1) << showpoint << fixed
            << number2
         << setw(10) << setprecision(2) << showpoint << fixed
            << number2 << "\n"

         << setw(9) << static_cast<int>(number3)
         << setw(10) << setprecision(1) << showpoint << fixed
            << number3
         << setw(10) << setprecision(2) << showpoint << fixed
            << number3 << "\n"

         << setw(9) << static_cast<int>(number4)
         << setw(10) << setprecision(1) << showpoint << fixed
            << number4
         << setw(10) << setprecision(2) << showpoint << fixed
            << number4;

    return 0;
}

