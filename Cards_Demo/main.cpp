/*CardsDemo - J.Benoit - Apr 22, 2021
 */

#include <iostream>

using namespace std;

int NextCardIndex = 0;

enum SUITS { CLUBS, DIAMONDS, HEARTS, SPADES };
enum RANKS { TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
             JACK, QUEEN, KING, ACE };

int DrawCard( int Deck[] );
void ShowHand( int Hand[], int NumCards );
void ShowCard( int Card );
int GetRank( int Card );
int GetSuit( int Card );

int main(int argc, char** argv) {
    //Set random seed here.
    srand( time(0) );

    //Create a deck of cards.
    int Deck[52];
    int Discards[52], NumDiscards = 0;

    for( int i; i < 52; i++ )
        Deck[i] = i;

    //Shuffle them.
    for( int i = 0; i < 100; i++ ) {
      //Pick two random cards.
      int index1 = rand() % 52;
      int index2 = rand() % 52;

      //Swap them.
      int temp = Deck[index1];
      Deck[index1] = Deck[index2];
      Deck[index2] = temp;
    }
    
    //Draw player cards.

    
    //Draw a 5-card hand.
    cout << "Hand #1\n"
         << "----------------" << endl;
    int Hand1[5], NumCardsInHand1 = 5;
    for( int i = 0; i < 5; i++ )
        Hand1[i] = DrawCard( Deck );

    ShowHand( Hand1, 5 );

    
    //Draw ANOTHER 5-card hand.
    cout << "\n\n" << endl;
    cout << "Hand #2\n"
         << "----------------" << endl;
    int Hand2[5];
    for( int i = 0; i < 5; i++ )
        Hand2[i] = DrawCard( Deck );

    ShowHand( Hand2, 5 );
    
    
    //Discard
    int CardSelected = 3; //Third card
    Discards[NumDiscards] = Hand1[ CardSelected ];
    NumDiscards++;

    for( int i = CardSelected; i < NumCardsInHand1; i++ )
        Hand1[i] = Hand1[i+1];
    NumCardsInHand1--;
    
    return 0;
}

int DrawCard( int Deck[] ) {
  if( NextCardIndex >= 45 )
      cout << "Need to Reshuffle!" << endl;

  return Deck[NextCardIndex++];
}

void ShowHand( int Hand[], int NumCards=5 ) {
    for( int i = 0; i < NumCards; i++ ) {
        ShowCard( Hand[i] );
        cout << endl;
    }
}

void ShowCard( int Card ) {
    int rank = GetRank( Card );
    int suit = GetSuit( Card );
    
    switch( rank ) {
        case TWO: cout << "TWO";  break;
        case THREE: cout << "THREE";  break;
        case FOUR: cout << "FOUR";  break;
        case FIVE: cout << "FIVE";  break;
        case SIX: cout << "SIX";  break;
        case SEVEN: cout << "SEVEN";  break;
        case EIGHT: cout << "EIGHT";  break;
        case NINE: cout << "NINE";  break;
        case TEN: cout << "TEN";  break;
        case JACK: cout << "JACK";  break;
        case QUEEN: cout << "QUEEN";  break;
        case KING: cout << "KING";  break;
        case ACE: cout << "ACE";  break;

        default: cout << "???";
    }

    cout << " of ";

    switch( suit ) {
        case CLUBS: cout << "CLUBS";  break;
        case DIAMONDS: cout << "DIAMONDS";  break;
        case HEARTS: cout << "HEARTS";  break;
        case SPADES: cout << "SPADES";  break;

        default: cout << "???";
    }    
}

int GetRank( int Card ) {
    return Card % 13;
}

int GetSuit( int Card ) {
    return Card % 4;
}