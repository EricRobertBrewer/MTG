/*
main.cpp
Eric Brewer
11/6/11
Rochester Draft Simulator - 
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

#define DEBUG 0
#define debug if( DEBUG ) cout

#define PACKS_PER_PLAYER 3
#define CARDS_PER_PACK 15

#include "../BoosterBox.hpp"
#include "../Pack.hpp"

int main( int argc, char* argv[] ){

  // Example: ./rochester.x SOM MBS NPH 8
  if( argc != 2 + PACKS_PER_PLAYER ){
    cout << "Format: " << argv[0] << " <Abbreviation for Set1> <..Set2> <..Set3> <Number of players>" << endl;
    exit( 1 );
  }

  ofstream fout( "DraftViewer.txt" );
  BoosterBox *box[PACKS_PER_PLAYER];
  for( int i = 0; i < PACKS_PER_PLAYER; i++ )
    box[i] = new BoosterBox( argv[i+1] );
  const int numplayers = atoi( argv[PACKS_PER_PLAYER+1] );
  vector<Pack> round;
  vector<string> pile[numplayers];
  string player[numplayers];
  int choice = 0;
  int playerid = 0;
  int ticker = 0;

  // Generate the packs with which to rochester draft.
  for( int i = 0; i < numplayers * PACKS_PER_PLAYER; i++ )
    round.push_back( box[i%PACKS_PER_PLAYER]->pullPack() );

  // Fill out the file "DraftViewer.txt" with the contents of each pack.
  fout << "Rochester Draft -";
  for( int i = 0; i < PACKS_PER_PLAYER; i++ )
    fout << ' ' << argv[i+1];
  fout << endl;
  for( int i = 0; i < numplayers * PACKS_PER_PLAYER; i++ ){
    fout << "PACK: " << i + 1 << endl;
    round[i].display( fout );
  }
  fout << endl;

  // Rochester Drafting:
  //   Drafting ensues in a "horseshoe" ordering - 
  //   The contents of one pack are revealeded to all players.
  //   The first seat chooses one card and picks continue clockwise.
  //   Once the final seat chooses his first card, the process begins again starting at
  //     the final seat going counterclockwise.
  //   One a pack is depleted, the next pack is revealed and picks begin with player 2.
  //   Example ordering for an 8-man draft:
  //     1 2 3 4 5 6 7 8 8 7 6 5 4 3 2
  //     2 3 4 5 6 7 8 1 1 8 7 6 5 4 3 ...
  //   Or for 6 players:
  //     1 2 3 4 5 6 6 5 4 3 2 1 1 2 3
  //     2 3 4 5 6 1 1 6 5 4 3 2 2 3 4 ...
  for( int i = 0; i < numplayers * PACKS_PER_PLAYER; i++ ){
    ticker = CARDS_PER_PACK;
    while( ticker ){
      for( int j = 0; j < numplayers && ticker; j++, ticker-- ){
	cout << endl << "Pack " << i + 1 << " (" << argv[i%PACKS_PER_PLAYER+1] << "): " << endl;
	round[i].display( cout );
	cout << "+=====================+\n";
	for( int k = 0; k < numplayers; k++ ){
	  cout << "Player " << k + 1 << "\'s last pick: ";
	  if( pile[k].size() )
	    cout << pile[k].back() << endl;
	  else
	    cout << "(empty)\n";
	}
	do{ 
	  cout << "Player " << ( j + i ) % numplayers + 1 << ", Select a card from the pack by number: ";
	   cin.clear();	   
	   cin >> choice;
	} while( cin.fail() || choice < 1 || choice > ticker );
	pile[(j+i)%numplayers].push_back( round[i].cardName( choice - 1 ) );
	round[i].takeCard( choice - 1 );
      }
      for( int j = 1; j <= numplayers && ticker; j++, ticker-- ){
	cout << endl << "Pack " << i + 1 << " (" << argv[i%PACKS_PER_PLAYER+1] << "): " << endl;
	round[i].display( cout );
	cout << "+=====================+\n";
	for( int k = 0; k < numplayers; k++ ){
	  cout << "Player " << k + 1 << "\'s last pick: ";
	  if( pile[k].size() )
	    cout << pile[k].back() << endl;
	  else
	    cout << "(empty)\n";
	}
	do{ 
	   cout  << "Player " << (numplayers - j + i ) % numplayers + 1 << ", Select a card from the pack by number: ";
	   cin.clear();	   
	   cin >> choice;
	} while( cin.fail() || choice < 1 || choice > ticker );
	pile[(numplayers-j+i)%numplayers].push_back( round[i].cardName( choice - 1 ) );
	round[i].takeCard( choice - 1 );
      }
    }
  }

  // Fill out the rest of "DraftViewer.txt" with players' ordered picks.
  fout << "=======================" << endl;
  for( int i = 0; i < numplayers; i++ ){
    fout << "PLAYER " << i + 1 << "\'s PILE:" << endl;
    for( int j = 0; j < CARDS_PER_PACK * PACKS_PER_PLAYER; j++ )
      fout << pile[i][j] << endl;
    fout << endl;
  }

  return 0;
}
