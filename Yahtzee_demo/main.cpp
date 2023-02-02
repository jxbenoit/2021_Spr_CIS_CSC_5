#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

int RollDie() { return rand() % 6 + 1; }
void RollDice( int Roll[] );
void PrintRolls( int Rolls[] );
void GetKeepersFromUser( bool Keepers[] );
char AskUserIfRollingAgain();

int main(int argc, char** argv) {
    srand( time(0) );
    
    int  Roll1[5], Roll2[5], Roll3[5];
    bool Keepers1[5], Keepers2[5];
    bool Rolled2ndTime, Rolled3rdTime;
    int  TotalScore, RoundScore;
    int  UpperSection[6], LowerSection[7], RollCounts[6];
    
    RollDice( Roll1 );   //First roll

    PrintRolls( Roll1 );

    Rolled2ndTime = Rolled3rdTime = false;
    
    char answer = AskUserIfRollingAgain();

    if( answer == 'R' ) {  //User wants to reroll
        Rolled2ndTime = true;
        GetKeepersFromUser( Keepers1 );

        RollDice( Roll2 );   //Roll SECOND time

        char answer = AskUserIfRollingAgain();

        if( answer == 'R' ) {  //User wants to reroll a THIRD TIME
          Rolled3rdTime = true;
          GetKeepersFromUser( Keepers2 );

          RollDice( Roll3 );   //Roll THIRD time
        }        
    }

    //Do scoring.
    //Score UPPER section.
    
    
    CountDice( Rolls1, RollCounts );
    for( int i = 0; i < 6; i++ ) {
        if( RollCounts[i] == 3 ) 
            cout << "Three of a kind with " << (i+1) << endl;
        else if( RollCounts[i] == 4 ) 
            cout << "four of a kind with " << (i+1) << endl;
    }
    

    return 0;
}

void PrintRolls( int Rolls[] ) {
    for( int i = 0; i < 5; i++ ) {
        cout << (char)('a'+i) << ") Roll: " << Rolls[i] << endl;
    }
    cout << endl;    
}

void GetKeepersFromUser( bool Keepers[] ) {
    cout << "Which values do you want to keep? (a - e): ";        

    //Set Keepers to default to all false.
    for( int i = 0; i < 5; i++ )
       Keepers[i] = false;

    string s;
    cin.clear();
    cin.ignore();

    std::getline( cin, s );  //Get whatever user types ('a' - 'e' hopefully)
    
    //Go through string character by character
    for( int i = 0; i < s.length(); i++ ) {      
      char choice = s[i];
      choice = tolower( choice );  //Make sure it's lowercase

      //If a, b, c, d, or e was typed, treat as a choice
      if( choice >= 'a' && choice <= 'e' ) {
        int index = (int)( choice - 'a' );
        Keepers[index] = true;
      }

      //Should validate choice is 'a' through 'e'.
    }
}

void RollDice( int Roll[] ) {
  for( int i = 0; i < 5; i++ )
    Roll[i] = RollDie();
}

char AskUserIfRollingAgain() {
  char answer;
  cout << "Do you want to stop, or select keepers and roll again? [S or R]:";
  cin >> answer;
    
  answer = toupper( answer ); 

  return answer;
}

void CountDice( int Roll[], int Counts[] ) {
    //Clear out count array
    for( int i = 0; i < 6; i++ )
        Counts[i] = 0;

    //Look at each die in a roll.
    //Add the number to the appropriate entry in Counts
    for( int i = 0; i < 5; i++ )
        Counts[ Roll[i] - 1 ]++;
}