/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv) {
    int CardsDrawn[52];
    
    for( int i = 0; i < 52; i++ )
        CardsDrawn[i] = i;
    
    //Shuffle
    
    

    int card = rand() % 52;
    CardsDrawn[card] = true;
    
    int suit = card % 4; //Diamonds, Clubs, Spades, Hearts
    int rank = card % 13;  //Ace, two, three, four,

    cout << "Card = " << card << endl;    
    cout << "Suit = " << suit << endl;
    cout << "rank = " << rank << endl;

    int card2;
    
    bool DealerWon = false, PlayerWon = false, Push = false;
    do {
      //card2 = rand() % 52;
    } while( ! DealerWon && ! PlayerWon && ! Push );

    return 0;
}

