/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main(int argc, char** argv) {
    int a, b;
    
    cout << "Enter the first number: ";
    cin >> a;
    cin.ignore( 100, '\n');
    cin.clear();
    
    cout << "Enter the second number: ";
    cin >> b;
    
    
    /*
    float amount1 = 123.45;
    float amount2 = 1.00;
    float amount3 = 2048.73;
    //float, int, long, double, char, bool
    string s = "This is a string with lots of characters";
    
    cout << '$' << setw(10) << left << setprecision(2) << fixed << showpoint << amount1 << endl;
    cout << '$' << setw(10) << setprecision(2) << fixed << showpoint << amount2 << endl;
    cout << '$' << setw(10) << setprecision(2) << fixed << showpoint << amount3 << endl;
    */
    return 0;
}

