/*Gaddis - Chapter 2, Problem 17
 Stock Commission
*/

#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    int   stock_shares = 750;
    float price = 35.00;
    float percent = 2.0;
    
    float amount_paid_for_stock = stock_shares * price;
    float commission = (percent / 100) *  amount_paid_for_stock;
    float total_amount_paid = amount_paid_for_stock + commission;
    
    cout << "Amount paid for stock: $" << amount_paid_for_stock << endl;
    cout << "           Commission: $" << commission << endl;
    cout << "    Total amount paid: $" << total_amount_paid << endl;

    return 0;
}

