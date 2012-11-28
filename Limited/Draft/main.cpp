/*
main.cpp
Eric Brewer
10/4/11
Booster Draft Simulator - 
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <curses.h>
using namespace std;

#define DEBUG 0
#define debug if( DEBUG ) cout

#define PACKS_PER_PLAYER 3
#define CARDS_PER_PACK 15
#define ROWS 50
#define COLUMNS 140
#define INPUT_LENGTH 80

#include "../BoosterBox.hpp"
#include "../Pack.hpp"

void wipeAway( int r, int c, int h, int w );

int main( int argc, char* argv[] ){

  // Example: ./draft.x TSP PLC FUT 8
  if( argc != 2 + PACKS_PER_PLAYER ){
    cout << "Format: " << argv[0] << " <abbreviation for Set1> <..Set2> <..Set3> <Number of players>" << endl;
    exit( 1 );
  }

  ofstream fout( "LastDraft.txt" );
  BoosterBox* box[PACKS_PER_PLAYER];
  for( int i = 0; i < PACKS_PER_PLAYER; i++ )
    box[i] = new BoosterBox( argv[i+1] );
  const int numplayers = atoi( argv[PACKS_PER_PLAYER+1] );
  vector<Pack> round[PACKS_PER_PLAYER];
  vector<string> pile[numplayers];
  string player[numplayers];
  int choice = 0;
  char input_line[INPUT_LENGTH];
  int playerid = 0;
  srand( time( NULL ) );

  initscr();
  clear();
  noecho();
  cbreak();

  // The screen border:
  for( int i = 1; i < ROWS; i++ ){
    mvaddch( i, 0, '|' );
    mvaddch( i, COLUMNS - 1, '|' );
  }
  for( int i = 0; i < COLUMNS + 1; i++ ){
    mvaddch( 0, i, '*' );
    mvaddch( 25, i, '=' );
    mvaddch( ROWS - 1, i, '#' );
  }
  refresh();

  // Generate a sufficient amount of packs from each booster box.
  for( int i = 0; i < PACKS_PER_PLAYER; i++ )
    for( int j = 0; j < numplayers; j++ )
      round[i].push_back( box[i]->pullPack() );

  // Fill out the file "LastDraft.txt" with the contents of each pack.
  for( int i = 0; i < PACKS_PER_PLAYER; i++ )
    fout << ' ' << argv[i+1];
  fout << endl;
  for( int i = 0; i < PACKS_PER_PLAYER; i++ ){
    fout << "ROUND: " << i + 1 << endl;
    for( int j = 0; j < numplayers; j++ ){
      fout << "PACK: " << j + 1 << endl;
      round[i][j].display( fout );
    }
    fout << endl;
  }

  // The Draft Process:
  //   Display the pack and display a choice prompt to the user.
  //   Add the card of choice to the player's pile and remove that card from the pack.
  //   Temporary (for testing purposes): For each other player, take a random card from each other pack.
  for( int i = 0; i < PACKS_PER_PLAYER; i++ )
    for( int j = 0; j < CARDS_PER_PACK; j++ ){
      //cout << endl << "Pack " << i + 1 << ", " << "Pick " << j + 1 << ":" << endl;
      mvprintw( 4, 7, "Pack %i, Pick %j:", i + 1, j + 1 );
      //round[i][(j+playerid)%numplayers].display( cout );
      round[i][(j+playerid)%numplayers].display( 7, 8, CARDS_PER_PACK, COLUMNS / 3 - 4 );
      do{
	//cout << "Select a card from the pack by number: ";
	mvaddstr( 5, 7, "Select a card from the pack by number:" );
	//cin.clear();
	//cin >> choice;
 	echo();
	getstr( input_line );
	choice = atoi( input_line );
	noecho();
      } while( /*cin.fail() ||*/ choice < 1 || choice > CARDS_PER_PACK - j );
      pile[playerid].push_back( round[i][(j+playerid)%numplayers].cardName( choice ) );
      round[i][(j+playerid)%numplayers].takeCard( choice );
      for( int k = 1; k < numplayers; k++ ){
	choice = 1 + rand() % round[i][(j+playerid+k)%numplayers].size();
	pile[(playerid+k)%numplayers].push_back( round[i][(j+playerid+k)%numplayers].cardName( choice ) );
	round[i][(j+playerid+k)%numplayers].takeCard( choice );	
      }      
    }

  // Fill out the rest of file "LastDraft.txt" with players' picks in order.
  fout << "=======================" << endl;
  for( int i = 0; i < numplayers; i++ ){
    fout << "PLAYER " << i + 1 << "\'s PILE:" << endl;
    for( int j = 0; j < PACKS_PER_PLAYER; j++ ){
      for( int k = 0; k < CARDS_PER_PACK; k++ )
	fout << pile[i][j*CARDS_PER_PACK+k] << endl;
      fout << endl;
    }
  }

  mvcur( 0, COLS - 1, LINES - 1, 0 );
  clear();
  refresh();
  endwin();
  return 0;
}

void wipeAway( int r, int c, int h, int w ){

  for( int i = 0; i < h; i++ )
    for( int j = 0; j < w; j++ )
      mvaddch( r + i, c + j, ' ' );
}
