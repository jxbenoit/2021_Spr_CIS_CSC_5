/*
    Author: Michael Cooper
    Date:   May 12th, 2021  2:00pm
    Purpose:Project 1 - Yahtzee
    Version:6 Adding scoring for regular rolls and special instances (small straight etc.)
 *  Changes: Scoring,Realized I had not done loop correctly on previous version
 *           cleaned up dialogue, edited variables etc.
 */

/*
Official Rules for Yahtzee can be found here:
https://www.hasbro.com/common/instruct/Yahtzee.pdf
*/

//System Libraries
#include <iostream>    //Input/Output Library
#include <iomanip>     //I/O manipulation Library
#include <cstdlib>     //For rand
#include <string>      //Can use for tutorial and dialogue options
#include <fstream>


using namespace std;   //Library Name-space

//User Libraries

//Global/Universal Constants -- No Global Variables
//Science, Math, Conversions, Higher Dimensioned constants only

//Function Prototypes
//Execution Begins Here
int main(int argc, char** argv) {
    //Set the Random number seed
    srand( time(0) );
    
    //Declare variables
    int RoundNum = 1;  //Default to Round #1
    int roll_0, roll_1, roll_2, roll_3, roll_4;
    //int roll2_0, roll2_1, roll2_2, roll2_3, roll2_4;
    //int roll3_0, roll3_1, roll3_2, roll3_3, roll3_4;
    //The roll of five dices for turn 1 of up to 3
    bool keep_0, keep_1, keep_2, keep_3, keep_4;
    
    //Dice to keep for 1st,2nd, and 3rd rolls.
    bool r2ndT, r3rdT;  //Rolled 2nd Time? Rolled 3rd time?
    //Will player roll a 2nd or 3rd time?
    char tut,beg,st,ans; //tutorial, begin, start, answer(to roll or stop)
    string tutor,p1,s; //tutorial, player 1, stop
    int  rolCts1, rolCts2, rolCts3, rolCts4, rolCts5, rolCts6;
    int score;      //Score for just the current round
    //int Scores[6];  //Scores over all 6 rounds
    bool done = false;

    //Roll counts: stores dice roll results.
    
    //Initialize variables
    
    //Initialize Strings (putting strings here)
    //Idea of Keepers not included in tutorial yet
    /*Flow of game:
        roll to see who goes first
        on each turn roll 3 times, keep any dice you like and reroll.
        will need  'roll again' and 'keep dice' rules say you can reroll the "keepers"
        this will be difficult to execute without functions.
    */
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
    " in another category and dont want to enter a zero.\n\n"
    "BONUS:\nYou get a bonus of 35 points if the total number of points you scored in the upper section is 63 or higher.\n"
    "If you roll a Yahtzee and you already filled in the Yahtzee box with a 50, you get a 100-point bonus!\n";
    
   
        //NOTE: A big do while loop may be needed to repeat the game
        //Intro
        cout << "Welcome to Yahtzee!\nWould you like to read the rules?"<< endl;
        cout << "Enter Y for yes or N for no" << endl;
        cin  >> tut;
    
        if(tut=='y'||tut=='Y')
            cout<<tutor<<endl;
 
        cout<<"Press any key to start the game!"<<endl;
        cin>>st;
    
    //Check if game file exists. If so, open it.
    ifstream In( "yahtzee.txt" );
    if( In ) {  //If there is a file & it can be opened, read it.
        In >> RoundNum >> p1;
        In >> score;
        //For saving multiple round scores
        // for( int i = 0; i < RoundNum; i++ )
        //   In >> Scores[i];
        // RoundNum++;
    }

    if( ! In || RoundNum > 6 ) {
      //How many players? menu or switch statement to select
      //Project 1 should most likely be solitare version. 
      //(would need options for multiple getlines to store each player name)
      do{
        cout << "Enter player 1 name"<<endl;
        cin  >> p1;
        cout << endl;
        cout << "Player 1 is "<<p1<<", ready to begin? (y/n)";
        cin  >> beg;
      } while (!(beg=='y'||beg=='Y')); //validate player names
    }

    if( In ) In.close();
    
    //do {  //For multiple rounds, start over here.

    //Turn begins //First roll
    cout << "roll 1:\n(Dice are labeled a-e)\n";
    roll_0 = rand() % 6 + 1;
    roll_1 = rand() % 6 + 1;
    roll_2 = rand() % 6 + 1;
    roll_3 = rand() % 6 + 1;
    roll_4 = rand() % 6 + 1;
    
    //Show dice
    cout << 'a' << ") Roll: " << roll_0 << endl;
    cout << 'b' << ") Roll: " << roll_1 << endl;
    cout << 'c' << ") Roll: " << roll_2 << endl;
    cout << 'd' << ") Roll: " << roll_3 << endl;
    cout << 'e' << ") Roll: " << roll_4 << endl;
    cout << endl;    
    r2ndT = r3rdT = false; 
    //setting to false so user can decide if they want to set to true.
    //after first roll dialogue
    
    cout << "Do you want to (S)top, or choose dice to hold and (R)oll again? [S or R]:";
    cin >> ans;
    ans = toupper( ans ); //will make sure entry is uppercase
    
    if( ans == 'R' ) {  //User wants to reroll
        r2ndT = true;
        //GetKeepersFromUser( Keepers1 );
       
        cin.clear();
        cin.ignore();
        cout << "\nType letters of dice (a - e) you would like to keep:"<<endl;
        cout << "(please type a space between letters)"<<endl;
        std::getline( cin, s );  //Get whatever user types ('a' - 'e' hopefully)
    
        //Go through string character by character
        keep_0 = keep_1 = keep_2 = keep_3 = keep_4 = false;
        for( int i = 0; i < s.length(); i++ ) {      
          char choice = s[i];  //String property -- treating as array
          choice = tolower( choice );  //Make sure it's lowercase
          //If a, b, c, d, or e was typed, treat as a choice
          if( choice >= 'a' && choice <= 'e' ) {            
            switch( choice ) {
              case 'a': keep_0 = true;  break;
              case 'b': keep_1 = true;  break;
              case 'c': keep_2 = true;  break;
              case 'd': keep_3 = true;  break;
              case 'e': keep_4 = true;  break;
            }
          }
          //Should validate choice is 'a' through 'e'.
        }

        //Second roll
        cout << "roll 2:\n";

        cout << "a) ";
        if( keep_0 )  cout << "KEPT: " << roll_0 << endl;
        else {
           roll_0 = rand() % 6 + 1;
           cout << "Roll: " << roll_0 << endl;
        }
        cout << "b) ";
        if( keep_1 )  cout << "KEPT: " << roll_1 << endl;
        else {
           roll_1 = rand() % 6 + 1;
           cout << "Roll: " << roll_1 << endl;
        }
        cout << "c) ";
        if( keep_2 )  cout << "KEPT: " << roll_2 << endl;
        else {
           roll_2 = rand() % 6 + 1;
           cout << "Roll: " << roll_2 << endl;
        }
        cout << "d) ";
        if( keep_3 )  cout << "KEPT: " << roll_3 << endl;
        else {
           roll_3 = rand() % 6 + 1;
           cout << "Roll: " << roll_3 << endl;
        }
        cout << "e) ";
        if( keep_4 )  cout << "KEPT: " << roll_4 << endl;
        else {
           roll_4 = rand() % 6 + 1;
           cout << "Roll: " << roll_4 << endl;
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
            keep_0 = keep_1 = keep_2 = keep_3 = keep_4 = false;
            for( int i = 0; i < s.length(); i++ ) {      
              char choice = s[i];  //This is a property strings have -- treat as array
              choice = tolower( choice );  //Make sure it's lowercase

              //If a, b, c, d, or e was typed, treat as a choice
              if( choice >= 'a' && choice <= 'e' ) {            
                switch( choice ) {
                  case 'a': keep_0 = true;  break;
                  case 'b': keep_1 = true;  break;
                  case 'c': keep_2 = true;  break;
                  case 'd': keep_3 = true;  break;
                  case 'e': keep_4 = true;  break;
                }
              }
              //Should validate choice is 'a' through 'e'.
            }

            //Third roll
            cout << "roll 3:\n";
            cout << "a) ";
            if( keep_0 )  cout << "KEPT: " << roll_0 << endl;
            else {
               roll_0 = rand() % 6 + 1;
               cout << "Roll: " << roll_0 << endl;
            }
            cout << "b) ";
            if( keep_1 )  cout << "KEPT: " << roll_1 << endl;
            else {
               roll_1 = rand() % 6 + 1;
               cout << "Roll: " << roll_1 << endl;
            }
            cout << "c) ";
            if( keep_2 )  cout << "KEPT: " << roll_2 << endl;
            else {
               roll_2 = rand() % 6 + 1;
               cout << "Roll: " << roll_2 << endl;
            }
            cout << "d) ";
            if( keep_3 )  cout << "KEPT: " << roll_3 << endl;
            else {
               roll_3 = rand() % 6 + 1;
               cout << "Roll: " << roll_3 << endl;
            }
            cout << "e) ";
            if( keep_4 )  cout << "KEPT: " << roll_4 << endl;
            else {
               roll_4 = rand() % 6 + 1;
               cout << "Roll: " << roll_4 << endl;
            }
        } //End of if for 3rd roll
    } //end of if for 2nd roll
    
    //Scoring sequence beings
    //Score UPPER section.
    //Clear out count 
    rolCts1 = rolCts2 = rolCts3 = rolCts4 = rolCts5 = rolCts6 = 0;

    //Look at each die in a roll.
    //Add the number to the appropriate entry in Counts
    switch( roll_0 ) {
      case 1: rolCts1++;  break;
      case 2: rolCts2++;  break;
      case 3: rolCts3++;  break;
      case 4: rolCts4++;  break;
      case 5: rolCts5++;  break;
      case 6: rolCts6++;  break;
    }
    switch( roll_1 ) {
      case 1: rolCts1++;  break;
      case 2: rolCts2++;  break;
      case 3: rolCts3++;  break;
      case 4: rolCts4++;  break;
      case 5: rolCts5++;  break;
      case 6: rolCts6++;  break;
    }
    switch( roll_2 ) {
      case 1: rolCts1++;  break;
      case 2: rolCts2++;  break;
      case 3: rolCts3++;  break;
      case 4: rolCts4++;  break;
      case 5: rolCts5++;  break;
      case 6: rolCts6++;  break;
    }
    switch( roll_3 ) {
      case 1: rolCts1++;  break;
      case 2: rolCts2++;  break;
      case 3: rolCts3++;  break;
      case 4: rolCts4++;  break;
      case 5: rolCts5++;  break;
      case 6: rolCts6++;  break;
    }
    switch( roll_4 ) {
      case 1: rolCts1++;  break;
      case 2: rolCts2++;  break;
      case 3: rolCts3++;  break;
      case 4: rolCts4++;  break;
      case 5: rolCts5++;  break;
      case 6: rolCts6++;  break;
    }

    score = 0;

    if( rolCts1 == 5 ) {
      cout << "Yahtzee!" << endl;
      score += 50;
    }
    else if( rolCts2 == 5 ) {
      cout << "Yahtzee!" << endl;
      score += 50;
    }
    else if( rolCts3 == 5 ) {
      cout << "Yahtzee!" << endl;
      score += 50;
    }
    else if( rolCts4 == 5 ) {
      cout << "Yahtzee!" << endl;
      score += 50;
    }
    else if( rolCts5 == 5 ) {
      cout << "Yahtzee!" << endl;
      score += 50;
    }
    else {
      if( rolCts1 == 3 ) {
          int score_w_3ok = rolCts1 * 1 +
                     rolCts2 * 2 +
                     rolCts3 * 3 +
                     rolCts4 * 4 +
                     rolCts5 * 5 +
                     rolCts6 * 6;
          if( score_w_3ok > 25 )
              score += score_w_3ok;
          else {
              if( rolCts2 == 2 ) {
                cout << "Full House with three 1's and two 2's" << endl;
                score += 25;
              }
              else if( rolCts3 == 2 ) {
                cout << "Full House with three 1's and two 3's" << endl;
                score += 25;
              }
              else if( rolCts4 == 2 ) {
                cout << "Full House with three 1's and two 4's" << endl;
                score += 25;
              }
              else if( rolCts5 == 2 ) {
                cout << "Full House with three 1's and two 5's" << endl;
                score += 25;
              }
              else if( rolCts6 == 2 ) {
                cout << "Full House with three 1's and two 6's" << endl;
                score += 25;
              }
              else {
                cout << "Three of a kind with " << 1 << endl;
                //Total of all 5 dice
                score += score_w_3ok;
              }
          }
      }
      if( rolCts2 == 3 ) {
          if( rolCts1 == 2 ) {
            cout << "Full House with three 2's and two 1's" << endl;
            score += 25;
          }
          else if( rolCts3 == 2 ) {
            cout << "Full House with three 2's and two 3's" << endl;
            score += 25;
          }
          else if( rolCts4 == 2 ) {
            cout << "Full House with three 2's and two 4's" << endl;
            score += 25;
          }
          else if( rolCts5 == 2 ) {
            cout << "Full House with three 2's and two 5's" << endl;
            score += 25;
          }
          else if( rolCts6 == 2 ) {
            cout << "Full House with three 2's and two 6's" << endl;
            score += 25;
          }
          else {
            cout << "Three of a kind with " << 2 << endl;
            //Total of all 5 dice
            score += rolCts1 * 1 +
                     rolCts2 * 2 +
                     rolCts3 * 3 +
                     rolCts4 * 4 +
                     rolCts5 * 5 +
                     rolCts6 * 6;
          }
      }
      if( rolCts3 == 3 ) {
          if( rolCts1 == 2 ) {
            cout << "Full House with three 3's and two 1's" << endl;
            score += 25;
          }
          else if( rolCts2 == 2 ) {
            cout << "Full House with three 3's and two 2's" << endl;
            score += 25;
          }
          else if( rolCts4 == 2 ) {
            cout << "Full House with three 3's and two 4's" << endl;
            score += 25;
          }
          else if( rolCts5 == 2 ) {
            cout << "Full House with three 3's and two 5's" << endl;
            score += 25;
          }
          else if( rolCts6 == 2 ) {
            cout << "Full House with three 3's and two 6's" << endl;
            score += 25;
          }
          else {
            cout << "Three of a kind with " << 3 << endl;
            //Total of all 5 dice
            score += rolCts1 * 1 +
                     rolCts2 * 2 +
                     rolCts3 * 3 +
                     rolCts4 * 4 +
                     rolCts5 * 5 +
                     rolCts6 * 6;
          }
      }
      if( rolCts4 == 3 ) {
          if( rolCts1 == 2 ) {
            cout << "Full House with three 4's and two 1's" << endl;
            score += 25;
          }
          else if( rolCts2 == 2 ) {
            cout << "Full House with three 4's and two 2's" << endl;
            score += 25;
          }
          else if( rolCts3 == 2 ) {
            cout << "Full House with three 4's and two 3's" << endl;
            score += 25;
          }
          else if( rolCts5 == 2 ) {
            cout << "Full House with three 4's and two 5's" << endl;
            score += 25;
          }
          else if( rolCts6 == 2 ) {
            cout << "Full House with three 3's and two 6's" << endl;
            score += 25;
          }
          else {
            cout << "Three of a kind with " << 4 << endl;
            //Total of all 5 dice
            score += rolCts1 * 1 +
                     rolCts2 * 2 +
                     rolCts3 * 3 +
                     rolCts4 * 4 +
                     rolCts5 * 5 +
                     rolCts6 * 6;
          }
      }
      if( rolCts5 == 3 ) {
          if( rolCts1 == 2 ) {
            cout << "Full House with three 5's and two 1's" << endl;
            score += 25;
          }
          else if( rolCts2 == 2 ) {
            cout << "Full House with three 5's and two 2's" << endl;
            score += 25;
          }
          else if( rolCts3 == 2 ) {
            cout << "Full House with three 5's and two 3's" << endl;
            score += 25;
          }
          else if( rolCts4 == 2 ) {
            cout << "Full House with three 5's and two 4's" << endl;
            score += 25;
          }
          else if( rolCts6 == 2 ) {
            cout << "Full House with three 5's and two 6's" << endl;
            score += 25;
          }
          else {
            cout << "Three of a kind with " << 5 << endl;
            //Total of all 5 dice
            score += rolCts1 * 1 +
                     rolCts2 * 2 +
                     rolCts3 * 3 +
                     rolCts4 * 4 +
                     rolCts5 * 5 +
                     rolCts6 * 6;
          }
      }
      if( rolCts6 == 3 ) {
          if( rolCts1 == 2 ) {
            cout << "Full House with three 6's and two 1's" << endl;
            score += 25;
          }
          else if( rolCts2 == 2 ) {
            cout << "Full House with three 6's and two 2's" << endl;
            score += 25;
          }
          else if( rolCts3 == 2 ) {
            cout << "Full House with three 6's and two 3's" << endl;
            score += 25;
          }
          else if( rolCts4 == 2 ) {
            cout << "Full House with three 6's and two 4's" << endl;
            score += 25;
          }
          else if( rolCts5 == 2 ) {
            cout << "Full House with three 6's and two 5's" << endl;
            score += 25;
          }
          else {
            cout << "Three of a kind with " << 6 << endl;
            //Total of all 5 dice
            score += rolCts1 * 1 +
                     rolCts2 * 2 +
                     rolCts3 * 3 +
                     rolCts4 * 4 +
                     rolCts5 * 5 +
                     rolCts6 * 6;
          }
      }

      if( rolCts1 == 4 ) {
          cout << "Four of a kind with " << 1 << endl;
            //Total of all 5 dice
          score += rolCts1 * 1 +
                   rolCts2 * 2 +
                   rolCts3 * 3 +
                   rolCts4 * 4 +
                   rolCts5 * 5 +
                   rolCts6 * 6;
      }
      if( rolCts2 == 4 ) {
          cout << "Four of a kind with " << 2 << endl;
          score += rolCts1 * 1 +
                   rolCts2 * 2 +
                   rolCts3 * 3 +
                   rolCts4 * 4 +
                   rolCts5 * 5 +
                   rolCts6 * 6;
      }
      if( rolCts3 == 4 ) {
          cout << "Four of a kind with " << 3 << endl;
          score += rolCts1 * 1 +
                   rolCts2 * 2 +
                   rolCts3 * 3 +
                   rolCts4 * 4 +
                   rolCts5 * 5 +
                   rolCts6 * 6;
      }
      if( rolCts4 == 4 ) {
          cout << "Four of a kind with " << 4 << endl;
          score += rolCts1 * 1 +
                   rolCts2 * 2 +
                   rolCts3 * 3 +
                   rolCts4 * 4 +
                   rolCts5 * 5 +
                   rolCts6 * 6;
      }
      if( rolCts5 == 4 ) {
          cout << "Four of a kind with " << 5 << endl;
          score += rolCts1 * 1 +
                   rolCts2 * 2 +
                   rolCts3 * 3 +
                   rolCts4 * 4 +
                   rolCts5 * 5 +
                   rolCts6 * 6;
      }
      if( rolCts6 == 4 ) {
          cout << "Four of a kind with " << 6 << endl;
          score += rolCts1 * 1 +
                   rolCts2 * 2 +
                   rolCts3 * 3 +
                   rolCts4 * 4 +
                   rolCts5 * 5 +
                   rolCts6 * 6;
      }
      
      //Check for straights
      if( (rolCts1 == 0 && rolCts2 == 1 && rolCts3 == 1 &&
           rolCts4 == 1 && rolCts5 == 1 && rolCts6 == 1) ||
          (rolCts1 == 1 && rolCts2 == 1 && rolCts3 == 1 &&
           rolCts4 == 1 && rolCts5 == 1 && rolCts6 == 0) ) {
        cout << "Large straight" << endl;
        score += 40;
      }
      else {
        if( (rolCts1 == 1 && rolCts2 == 1 && rolCts3 == 1 &&
             rolCts4 == 1) ||                                                 //1,2,3,4
            (rolCts2 == 1 && rolCts3 == 1 && rolCts4 == 1 &&
             rolCts5 == 1) ||                                                 //2,3,4,5
            (rolCts3 == 1 && rolCts4 == 1 && rolCts5 == 1 &&
             rolCts6 == 1) ) {                                                //3,4,5,6
          cout << "Small straight" << endl;
          score += 30;
        }
      }      
    }  //end of else

    if( score == 0 ) {  //Chance
        score = rolCts1 * 1 +
                rolCts2 * 2 +
                rolCts3 * 3 +
                rolCts4 * 4 +
                rolCts5 * 5 +
                rolCts6 * 6;   
    }

    //Scores[RoundNum-1] = score;
    cout << "Congratulations " << p1 << "!\nYour Score: " << score << endl;

    
    //Ask if player wants to continue
    if( RoundNum < 6 ) {
      cout << "Do you want to play another round? (Y or N): " << endl;
      
      //Remember to validate user choice.
      char choice;
      cin >> choice;
      choice = toupper( choice );
      if( choice == 'N' ) {
          //Save game.
          cout << "Saving game for next time!" << endl;
          ofstream Out( "yahtzee.txt" );
          Out << RoundNum << " " << p1 << " ";
          Out << score;
          //For multiple round scores:
          //for( int i = 0; i < RoundNum; i++ )
          //  Out << Scores[i] << " ";
          Out.close();
          
          done = true;
      }
    }
    else {
      //STUB: End of game. Total scores, etc.

      //Indicate in the file that the last game was completed.
      ofstream Out( "yahtzee.txt" );
      Out << 7 << " " << p1 << " " << score;
      Out.close(); 
      
      done = true;
    }
    
    RoundNum++;
    
    // } while( ! done );  //For multiple round game

    //ENDING NOTES:
    //why is char choice not working??
    //was not added into the loop properly
    //need to add some final dialogue
    //I feel like this will be a good enough place to end project 1
    //I did not expect this game to be so long!
    
    //Problems:
    //hitting s for first time does not result in score
    //Rolled 2nd time or rolled 3rd time = true on third role.
    //3rd time keepers are not correct
    //some cases of 3 of a kind and 2 of a kind not working.
    //There is not an option for ans == s
  
    //Exit stage right
    return 0;
}