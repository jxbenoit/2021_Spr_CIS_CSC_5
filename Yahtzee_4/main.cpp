/*
    Author: Michael Cooper
    Date:   June 1, 2021
    Purpose:Project 2 - Yahtzee
    Version: 3 - Created functions, made adjustments to account for multiple players, text edits.
 */

/*
Official Rules for Yahtzee can be found here:
https://www.hasbro.com/common/instruct/Yahtzee.pdf
*/

//System Libraries
#include <iostream>    //Input/Output Library
#include <iomanip>     //I/O manipulation Library
#include <ctime>       //For rand
#include <cmath>       //find max
#include <cstdlib>     
#include <string>      //Can use for tutorial and dialogue options
#include <fstream>     //For input output files
#include <vector>


using namespace std;   //Library Name-space

//User Libraries

//Global/Universal Constants -- No Global Variables
const int MAX_PLAYERS = 4;
const int NUM_ROUNDS = 13;
//Science, Math, Conversions, Higher Dimensioned constants only

//Function Prototypes
int PlayTurn( string name );
void PrintScores( string Names[], int Scores[], int NumPlayers, bool PrintAvg = false );
void SortScores( string Names[], int Scores[], int NumPlayers );
void SaveGame( string FileName, int rndNum, string Names[], int Scores[], int NumPlayers );
bool LoadGame( string FileName, int &rndNum, string Names[], int Scores[], int &NumPlayers );
float CalcAverage( int Scores[], int NumPlayers );
void CalcAverage( int Scores[], int NumPlayers, int &avg );
bool SearchForTwoOfAKind( int rolCts[], int Size, int &index );
void PrintPlayerNames( string p[], int NumPlayers );

//Execution Begins Here
int main(int argc, char** argv) {
    //Set the Random number seed
    srand( time(0) );
    
    //Declare variables
    int rndNum = 0; //round number
    //Roll counts: stores dice roll results, how .
    int score[MAX_PLAYERS];              //Score for just the current round
    //int Scores[6];        //Scores over all 6 rounds
    
    char tut,beg,st;    //tutorial, begin, start, answer(to roll or stop)
    string tutor,p[MAX_PLAYERS];      //tutorial, player 1, stop
    
    bool done;                              //Done playing?

    int NumPlayers;

    //Initialize Strings (putting strings here)
    tutor = "Game Summary:\nOn each turn, roll the dice to get the highest "
    "scoring combination for one of the 13 categories.\nKeep any dice you do not not wish to reroll. You can roll up to 3 times,\n"
    "but once you fill a category with a score it cannot be replaced.\nAfter you finish rolling, "
    "your score (or zero) will be logged.\nThe game ends when all 13 boxes are filled by all players, "
    "scores are then totaled,\nincluding any bonus points and the player with the highest total wins.\n\n"
            
    "The Thirteen Categories:\n"
    "There are two sections in which to place scores:\nan upper area and a lower area.\n\n"
    "The upper section is aces-sixes (63+ scores a 35 bonus)\n"
    "For example: Total of aces(ones) only, total of twos only, and so on...\n\n"
    "The lower section consists of the following:\n"        
    "3 of a kind = total of all 5 dice\n4 of a kind = total of all 5 dice\n"
    "Full house (3 of a kind and a pair) = 25 points\nSmall straight (any sequence of 4 numbers) = 30 points\n"
    "Large straight (any sequence of 5 numbers) = 40 points\nYahtzee (five of a kind) = 50 points\n"
    "Chance: score the total of any 5 dice, this comes in handy when you\ncan't or don't want to score"
    " in another category and dont want to enter a zero.\n\n";
    
    //Intro
    cout << "Welcome to Yahtzee!\nWould you like to read the rules?"<< endl;
    cout << "Enter Y for yes or N for no" << endl;
    cin  >> tut;

    if(tut=='y'||tut=='Y')
        cout<<tutor<<endl;

    cout<<"Press 'e' to exit, or any other key to start the game!"<<endl;
    cin>>st;
    if( toupper(st) == 'E' ) exit( 0 );

    //Check if game file exists. If so, open it.
    bool game_loaded = LoadGame( "yahtzee.txt", rndNum, p, score, NumPlayers );
    rndNum++;

    if( ! game_loaded || rndNum > NUM_ROUNDS ) {
      do {
        cout << "How many players are there? (1-4)" << endl;
        cin >> NumPlayers;
        if( NumPlayers < 1 || NumPlayers > 4 )
            cout << "You must enter a number from 1 to 4" << endl;
      } while( NumPlayers < 1 || NumPlayers > 4 );
      
      for( int i = 0; i < NumPlayers; i++ ) {
          cout << "Enter player " << (i+1) << " name "<<endl;
          cin  >> p[i];
          cout << endl;
          score[i] = 0;
      }

      rndNum = 1;  //Default to Round #1
    }

    do{
          cout << "Ready to begin? (y/n)";
          cin  >> beg;
    } while (!(beg=='y'||beg=='Y')); //validate player names

    PrintPlayerNames( p, NumPlayers );

    //======================================================
    //Main loop.
    //--Initialize variables
    done = false;
    do {  //For multiple rounds, start over here.
        //Loop through each player.
        for( int player_index = 0; player_index < NumPlayers; player_index++ ) {
            score[player_index] += PlayTurn( p[player_index] );
        } //End of loop through players


      //Ask if player wants to continue
      if( rndNum < NUM_ROUNDS ) {
        cout << "Do you want to play another round? (Y or N): " << endl;

        //Remember to validate user choice.
        char choice;
        cin >> choice;
        choice = toupper( choice );
        if( choice == 'N' ) {
           //Save game.
           cout << "Saving game for next time!" << endl;
           SaveGame( "yahtzee.txt", rndNum, p, score, NumPlayers );

           done = true;
        }
        else {
          cout << "Save the game anyways? (Y or N): " << endl;

          char choice;
          cin >> choice;
          choice = toupper( choice );
          if( choice == 'Y' ) {
             //Save game.
             cout << "Saving game for next time!" << endl;
             SaveGame( "yahtzee.txt", rndNum, p, score, NumPlayers );
          }  
        }
      }
      else {  //We've reached Round NUM_ROUNDS
          //End of game. Total scores, etc.
          //cout<<"ending dialogue";
          //Indicate in the file that the last game was completed.
          SaveGame( "yahtzee.txt", rndNum, p, score, NumPlayers );

          done = true;
      }

      rndNum++;
    
    } while( ! done );  //For multiple round game
    //======================================================
    
    //Print out final scores.
    PrintScores( p, score, NumPlayers, true );

    //printf ("fmax (100.0, 1.0) = %f\n", fmax(100.0,1.0));
    
  
    //Exit stage right
    return 0;
}

int PlayTurn( string player_name ) {
    int roll[5];
    //The roll of dices for turn 1 of up to 3
    int  rolCts[6];
    bool keep[5];
    //Dice to keep for 1st,2nd, and 3rd rolls.
    bool r2ndT, r3rdT;                      //Rolled 2nd Time? Rolled 3rd time?
    //Will player roll a 2nd or 3rd time?
    char ans;
    string s;
    int scr3k;              //Score with 3 of a Kind

    cout << "\n===================================================\n"
         << "It's " << player_name << "'s turn:" << endl;

    //Turn begins //First roll
    cout << "roll 1:\n(Dice are labeled a-e)\n";
    for( int i = 0; i < 5; i++ )
      roll[i] = rand() % 6 + 1;

    //Show dice
    for( int i = 0; i < 5; i++ ) 
       cout << (char)('a' + i) << ") Roll: " << roll[i] << endl;
       cout << endl;    
        r2ndT = r3rdT = false; 
        //setting to false so user can decide if they want to set to true.
        //after first roll dialogue

        cout << "Do you want to (S)top, or choose dice to hold and (R)oll again? [S or R]:";
        cin >> ans;
        ans = toupper( ans ); //will make sure entry is uppercase

        if( ans == 'R' ) {  //User wants to reroll
            r2ndT = true;

            cin.clear();
            cin.ignore();
            cout << "\nType letters of dice (a - e) you would like to keep:"<<endl;
            cout << "(please type a space between letters)"<<endl;
            std::getline( cin, s );  //Get whatever user types ('a' - 'e)

            //Go through string character by character
            for( int i = 0; i < 5; i++ )
                keep[i] = false;

            for( int i = 0; i < s.length(); i++ ) {      
              char choice = s[i];  //String property -- treating as array
              choice = tolower( choice );  //Make sure it's lowercase
              //If a, b, c, d, or e was typed, treat as a choice
              if( choice >= 'a' && choice <= 'e' )
                keep[ choice - 'a' ] = true;

              //Should validate choice is 'a' through 'e'.
            }

            //Second roll
            cout << "roll 2:\n";

            for( int i = 0; i < 5; i++ ) {
              cout << (char)(i + 'a') << ") ";
              string msg = keep[i] ? "KEPT: ":"Roll: ";
              if( keep[i] )  cout << msg << roll[i] << endl;
              else {
                roll[i] = rand() % 6 + 1;
                 cout << msg << roll[i] << endl;
              }
            }

            cout << "Do you want to (S)top, or choose dice to hold and (R)oll again? [S or R]:\n";
            cin >> ans;
            ans = toupper( ans ); //will make sure entry is uppercase

            if( ans == 'R' ) {  //User wants to reroll
                r3rdT = true;   //this was rolled 2nd time. was it a mistake to change this to 3rd?
                //GetKeepersFromUser( Keepers1 );

                cin.clear();
                cin.ignore();
                cout << "Type letters of dice (a - e) you would like to keep:"<<endl;
                cout << "(You must reselect any dice you wish to keep)"<<endl;
                std::getline( cin, s );  //Get whatever user types ('a' - 'e' hopefully)

                //Go through string character by character
                for( int i = 0; i < 5; i++ )
                  keep[i] = false;
                for( int i = 0; i < s.length(); i++ ) {      
                  char choice = s[i];  //This is a property strings have -- treat as array
                  choice = tolower( choice );  //Make sure it's lowercase

                  //If a, b, c, d, or e was typed, treat as a choice
                  if( choice >= 'a' && choice <= 'e' )
                    keep[ choice - 'a' ] = true;

                  //Should validate choice is 'a' through 'e'.
                }

                //Third roll
                cout << "roll 3:\n";
                for( int i = 0; i < 5; i++ ) {
                  cout << (char)(i + 'a') << ") ";
                  string msg = keep[i] ? "KEPT: ":"Roll: ";
                  if( keep[i] )  cout << msg << roll[i] << endl;
                  else {
                    roll[i] = rand() % 6 + 1;
                    cout << msg << roll[i] << endl;
                  }
                }

            } //End of if for 3rd roll
        } //end of if for 2nd roll

        //Scoring sequence beings
        //Score UPPER section.
        //Clear out count 
        cout << "Scoring..." << endl;
        for( int i = 0; i < 6; i++ )
          rolCts[i] = 0;

        //Look at each die in a roll.
        //Add the number to the appropriate entry in Counts
        for( int r = 0; r < 5; r++ ) {  //Loop through rolls
            int index = roll[r] - 1;
            rolCts[ index ]++;
        }

        //Debugging: printing out roll counts.
        cout << "Roll counts:" << endl;
        for( int i = 0; i < 6; i++ ) //Loop through rolls
            cout << "# of " << (i+1) << "'s: " << rolCts[i] << endl;
        cout << endl;
        
        int score = 0;

        bool got_yahtzee = false;
        for( int i = 0; i < 6; i++ ) {
            if( rolCts[i] == 5 ) {
              cout << "Yahtzee!" << endl;
              score += 50;
              got_yahtzee = true;
            }
        }

        if( ! got_yahtzee ) {
          for( int i = 0; i < 6; i++ ) {  //Go through roll counts
            if( rolCts[i] == 3 ) {
              int scr3k = 0;
              for( int j = 0; j < 6; j++ )
                  scr3k += rolCts[j] * (j+1);
              //cout << "HAVE A 3-OF-A-KIND (at least): " << (i+1) << " scr3k=" << scr3k << endl; //debugging
              if( scr3k > 25 ) {
                  //Situation where 3-of-a-kind is worth more pts than full house
                  //(sum of dice just get added together here)
                  cout << "Three of a kind with " << (i+1)
                       << "'s, which scores more than a full house!" << endl;
                  score += scr3k;
              }
              else {
                  int index;
                  bool full_house = SearchForTwoOfAKind( rolCts, 6, index );

                  if( full_house ) {
                      cout << "Full House with three " << (i+1)
                           << "'s and two " << (index+1) << "'s." << endl;
                      score += 25;
                  }
                  else {
                    cout << "Three of a kind with " << (i+1) << "'s." << endl;
                    //Total of all 5 dice
                    score += scr3k;
                  }
              }
            }
          }

          for( int i = 0; i < 6; i++ ) {
            //cout << "i=" << i << " rolCts[" << i << "]=" << rolCts[i] << endl; //Debugging
            if( rolCts[i] == 4 ) {
              cout << "Four of a kind with " << (i+1) << "'s." << endl;
              //Total of all 5 dice
              for( int j = 0; j < 6; j++ )
                score += rolCts[j] * (j+1);
            }
          }

          //Check for straights
          if( (rolCts[0] == 0 && rolCts[1] == 1 && rolCts[2] == 1 &&
               rolCts[3] == 1 && rolCts[4] == 1 && rolCts[5] == 1) ||
              (rolCts[0] == 1 && rolCts[1] == 1 && rolCts[2] == 1 &&
               rolCts[3] == 1 && rolCts[4] == 1 && rolCts[5] == 0) ) {
            cout << "Large straight." << endl;
            score += 40;
          }
          else {
            if( (rolCts[0] == 1 && rolCts[1] == 1 && rolCts[2] == 1 &&
                 rolCts[3] == 1) ||                                                 //1,2,3,4
                (rolCts[1] == 1 && rolCts[2] == 1 && rolCts[3] == 1 &&
                 rolCts[4] == 1) ||                                                 //2,3,4,5
                (rolCts[2] == 1 && rolCts[3] == 1 && rolCts[4] == 1 &&
                 rolCts[5] == 1) ) {                                                //3,4,5,6
              cout << "Small straight." << endl;
              score += 30;
            }
          }      
        }  //end of else
 
        if( score == 0 ) {  //Chance
            for( int j = 0; j < 6; j++ )
              score += rolCts[j] * (j+1);
        }

        //Scores[RoundNum-1] = score;
        cout << "Congratulations " << player_name << "!\nYour Score: " << score << endl;
        return score;
}

void PrintScores( string Names[], int Scores[], int NumPlayers, bool PrintAvg ) {
    SortScores( Names, Scores, NumPlayers );
    
    cout << "Congratulations, " << Names[NumPlayers - 1] << "!" << endl;
    cout << "You are the winner!!!" << endl;
    cout << "\n\n";
    cout << setw(20) << "NAME" << setw(10) << "SCORE" << "\n"
         << "--------------------------------------------------" << endl;
    for( int i = NumPlayers - 1; i >= 0; i-- ) {
        cout << "|" << setw( 20 ) << Names[i] << setw(10) << Scores[i]
             << " | " << endl;
    }
    
    //Print average.
    if( PrintAvg ) {
        float avg = CalcAverage( Scores, NumPlayers );
        cout << "\n"
             << "Average score: " << avg << endl;
    }
}

void SortScores( string Names[], int Scores[], int NumPlayers ) {
    for( int i = 0; i < NumPlayers - 1; i++ ) {
        for( int j = i + 1; j < NumPlayers; j++ ) {
            if( Scores[i] > Scores[j] ) {
                //Swap scores & player's names
                int temp_score = Scores[i];
                Scores[i] = Scores[j];
                Scores[j] = temp_score;
                string temp_name = Names[i];
                Names[i] = Names[j];
                Names[j] = temp_name;
            }
        }
    }
}

void SaveGame( string FileName, int rndNum, string Names[], int Scores[], int NumPlayers ) {
  static int save_count = 0;

  cout << "The game has been saved " << save_count << " times" << endl;

  ofstream Out( FileName.c_str() );

  //NOTE: Probably should check for file-open errors here.

  Out << rndNum << " " << NumPlayers << endl;
  for( int i = 0; i < NumPlayers; i++ ) {
    Out << Names[i] << " " << Scores[i] << endl;
  }
  Out.close();
  
  save_count++;
}

bool LoadGame( string FileName, int &rndNum, string Names[], int Scores[], int &NumPlayers ) {
  ifstream In( FileName.c_str() );

  //NOTE: Probably should check for file-open errors here.
  if( ! In ) return false;  //Can't open file

  In >> rndNum >> NumPlayers;
  
  //Read game data in as vectors.
  vector<string> N;
  vector<int> S;
  for( int i = 0; i < NumPlayers; i++ ) {
    string name;
    int    score;
    In >> name >> score;
    N.push_back( name );
    S.push_back( score );
  }
  In.close();
  
  //Copy vectors to arrays.
  for( int i = 0; i < N.size(); i++ ) {
      Names[i] = N[i];
      Scores[i] = S[i];
  }
  
  return true;
}

void  CalcAverage( int Scores[], int NumPlayers, int &avg ) {
    avg = CalcAverage( Scores, NumPlayers );
}

float  CalcAverage( int Scores[], int NumPlayers ) {
   int sum = 0;
   for( int i = 0; i < NumPlayers; i++ )
      sum += Scores[i];
        
   float avg = (float)(sum) / NumPlayers;    
   
   return avg;
}

bool SearchForTwoOfAKind( int rolCts[], int Size, int &index ) {
  //Use linear search to look for two-of-a-kind.
  bool found = false;
  for( index = 0; index < Size && ! found; index++ ) {
    if( rolCts[index] == 2 ) {
      return true;
    }
  }
  return false;
}

void PrintPlayerNames( string p[], int NumPlayers ) {
  //Copy names to new array
  string names[NumPlayers];
  for( int i = 0; i < NumPlayers; i++ )
      names[i] = p[i];
  
  //Using selection sort to alphabetize names.
  int min_index;
  string min_name;
  for( int start = 0; start < NumPlayers - 1; start++ ) {
      min_index = start;
      min_name = names[start];
      for( int index = start + 1; index < NumPlayers; index++ ) {
          if( names[index] < min_name ) {
              min_name = names[index];
              min_index = index;
          }
      }
      
      //Swap
      string temp = names[min_index];
      names[min_index] = names[start];
      names[start] = temp;
  }

  for( int i = 0; i < NumPlayers; i++ ) {
      if( i == NumPlayers - 1 ) cout << " and ";
      else if( i > 0 ) cout << ", ";

      cout << names[i];
  }
  cout << " are playing.\n" << endl;
}

