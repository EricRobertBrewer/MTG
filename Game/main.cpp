/*
main.cpp
Eric Brewer
11/27/11
DeckTest - Play with a Deck of Cards - 
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <curses.h>
#include <cmath>
using namespace std;
/*
#define MAIN_DEBUG 0
#define main_debug if( MAIN_DEBUG ) cout
*/
#define ROWS                 46
#define COLUMNS             162
#define HAND_HEIGHT          28
#define HAND_COLUMN_WIDTH    38
#define HAND_WIDTH           74
#define MENU_HEIGHT          10
#define MENU_WIDTH           76
#define DISPLAY_HEIGHT       39
#define DISPLAY_COLUMN_WIDTH 38
#define DISPLAY_WIDTH       114
#define INPUT_LENGTH         80
#define EXPAND_LEFT          -1
#define EXPAND_RIGHT          1

const char updated[16] = "12/20/11";

#include "Deck.hpp"
#include "Scanner.hpp"
#include "getMenuInput.hpp"

void startup();
void cruuush();
void wipeAway( int r, int c, int south, int east );
char choicePrompt( int& counter );

int main( int argc, char* argv[] ){

  Scanner* scanner;
  Deck* deck;
  char option;
  int option_counter;
  string dname;
  char input_line[INPUT_LENGTH];
  int maindeck_out;

  if( argc != 2 ){
    cout << "Error: Two arguments needed.\n";
    cout << "Example: " << argv[0] << " ../Decklists/Standard/MonoBlack.txt\n";
    exit( 1 );
  }

  scanner = new Scanner();
  //if( argc >= 2 )
    if( scanner->loadDecklist( argv[1] ) )
      deck = scanner->createDeck();
    else{
      cout << "Cannot find decklist file: " << argv[1] << ".\n";
      exit( 2 );
    }
    /*
  else{
    cout << "Start by loading a decklist file: ";
    cin >> dname;
    while( cin.fail() ){
      cout << "Error: Bad input. Try again\n";
      cin.clear();
      cin >> dname;
    }
    if( scanner->loadDecklist( dname.c_str() ) )
      deck = scanner->createDeck();
    else{
      cout << "Cannot find decklist file: " << dname << ".\n";
      exit( 3 );
    }
  }
    */
  startup();

  for( int i = 0; i < ROWS; i++ ){
    mvaddch( i, 0, '#' );
    mvaddch( i, COLUMNS - 1, '#' );
  }
  for( int i = 1; i < COLUMNS - 1; i++ ){
    mvaddch( 0, i, '=' );
    mvaddch( 2, i, '.' );
    mvaddch( ROWS - 1, i, '=' );
  }
  mvaddstr( 1, 2, "DeckTest -- Last updated " );
  mvaddstr( 1, 27, updated );
  refresh();

  option = ' ';
  option_counter = 1;

  while( option != 'q' ){

    wipeAway( 3, COLUMNS - 2 * HAND_COLUMN_WIDTH, HAND_HEIGHT + 4, HAND_WIDTH );
    mvaddstr( 3, COLUMNS - HAND_COLUMN_WIDTH, "***********************************" );
    mvprintw( 4, COLUMNS - HAND_COLUMN_WIDTH, "Cards in library: %i", deck->cardsInLibrary() );
    mvaddstr( 5, COLUMNS - HAND_COLUMN_WIDTH, "..................................." );
    mvaddstr( 6, COLUMNS - HAND_COLUMN_WIDTH, "Hand: " );
    if( !deck->cardsInHand() )
      mvaddstr( 6, COLUMNS - HAND_COLUMN_WIDTH + 6, "(empty)" );
    deck->displayHand( 7, COLUMNS - HAND_COLUMN_WIDTH, HAND_HEIGHT, HAND_COLUMN_WIDTH, EXPAND_LEFT );
    mvaddstr( 7 + deck->cardsInHand() % HAND_HEIGHT, 
	      COLUMNS - HAND_COLUMN_WIDTH - HAND_COLUMN_WIDTH * ( deck->cardsInHand() / HAND_HEIGHT ), 
	      "***********************************" );
    refresh();

    option = tolower( choicePrompt( option_counter ) );
    //wipeAway( 3, 3, DISPLAY_HEIGHT + 2, DISPLAY_WIDTH );

    switch( option ){

    case 'b':
      wipeAway( 3, 3, DISPLAY_HEIGHT + 2, DISPLAY_WIDTH );
      do{
	deck->displayDecklist( 5, 3, DISPLAY_HEIGHT, DISPLAY_COLUMN_WIDTH, EXPAND_RIGHT );
	mvaddstr( 3, 3, "Which maindeck slot will you take out? " );
	echo();
	getstr( input_line );
	maindeck_out = atoi( input_line );
	wipeAway( 3, 3, 1, DISPLAY_WIDTH );
	mvprintw( 3, 3, "%i: to be swapped with which sideboard slot? ", maindeck_out );
	getstr( input_line );
	noecho();
      } while( !deck->sideIn( maindeck_out, atoi( input_line ) ) );
      wipeAway( 3, 3, DISPLAY_HEIGHT + 2, DISPLAY_WIDTH );
      mvaddstr( 3, 3, "Your change:" );
      deck->displayDecklist( 5, 3, DISPLAY_HEIGHT, DISPLAY_COLUMN_WIDTH, EXPAND_RIGHT );
      break;

    case 'd':
      if( !deck->draw() ){
	mvaddstr( 3, 3, "No more cards in library!" );
	refresh();
      }
      else{
	wipeAway( 3, 3, DISPLAY_HEIGHT + 2, DISPLAY_WIDTH );
	mvaddstr( 3, 3, "Draw..." );
      }
      break;
      
    case 'e':
      wipeAway( 3, 3, DISPLAY_HEIGHT + 2, DISPLAY_WIDTH );
      mvaddstr( 3, 3, "Entire Decklist:" );
      deck->displayDecklist( 5, 3, DISPLAY_HEIGHT, DISPLAY_COLUMN_WIDTH, EXPAND_RIGHT );
      break;

    case 'h':
      wipeAway( 3, 3, 1, DISPLAY_WIDTH );
      mvaddstr( 3, 3, "Hand sorted." );
      deck->sortHand();
      break;
      
    case 'l':
      wipeAway( 3, 3, DISPLAY_HEIGHT + 2, DISPLAY_WIDTH );
      mvaddstr( 3, 3, "Entire Library:" );
      if( !deck->cardsInLibrary() )
	mvaddstr( 3, 19, "(empty)" );
      else
	deck->displayLibrary( 5, 3, DISPLAY_HEIGHT, DISPLAY_COLUMN_WIDTH, EXPAND_RIGHT );
      break;

    case 'm':
      wipeAway( 3, 3, DISPLAY_HEIGHT + 2, DISPLAY_WIDTH );
      mvaddstr( 3, 3, "Mulligan..." );
      deck->mulligan();
      break;

    case 'o':
      wipeAway( 3, 3, DISPLAY_HEIGHT + 2, DISPLAY_WIDTH );
      mvaddstr( 3, 3, "Opening hand:" );
      deck->openingHand();
      break;
      
    case 'p':
      wipeAway( 3, 3, DISPLAY_HEIGHT + 2, DISPLAY_WIDTH );
      do{
	deck->displayLibrary( 5, 3, DISPLAY_HEIGHT, DISPLAY_COLUMN_WIDTH, EXPAND_RIGHT );
	mvaddstr( 3, 3, "Which card are you searching for?: " );
	echo();
	getstr( input_line );
	noecho();
      } while( !deck->searchLibraryToHand( atoi( input_line ) ) );
      wipeAway( 3, 3, DISPLAY_HEIGHT + 2, DISPLAY_WIDTH );
      break;

    case 's':
      wipeAway( 3, 3, DISPLAY_HEIGHT + 2, DISPLAY_WIDTH );
      mvaddstr( 3, 3, "Sorted library:" );
      if( !deck->cardsInLibrary() )
	mvaddstr( 3, 19, "(empty)" );
      else
	deck->displaySortedLibrary( 5, 3, DISPLAY_HEIGHT, DISPLAY_COLUMN_WIDTH, EXPAND_RIGHT );
      break;

    case 't':
      wipeAway( 3, 3, DISPLAY_HEIGHT + 2, DISPLAY_WIDTH );
      mvaddstr( 3, 3, "Top card of library:" );
      if( !deck->cardsInLibrary() )
	mvaddstr( 3, 24, "(empty)" );
      else
	deck->revealTopCard( 5, 3 );
      break;

      /*
    default:
      continue;
      */
    }
  }

  cruuush();
  return 0;
}

void startup(){

  initscr();
  clear();
  noecho();
  cbreak();
}

void cruuush(){

  mvcur( 0, COLS - 1, LINES - 1, 0 );
  clear();
  refresh();
  endwin();
}

void wipeAway( int r, int c, int south, int east ){

  for( int i = 0; i < south; i++ )
    for( int j = 0; j < east; j++ )
      mvaddch( r + i, c + j, ' ' );
}
  
char choicePrompt( int& counter ){

  char c = ' ';
  mvaddstr( ROWS - MENU_HEIGHT,      COLUMNS - MENU_WIDTH, "+-------------------------------[OPTIONS]---------------------------------+" );
  mvaddstr( ROWS - MENU_HEIGHT + 1,  COLUMNS - MENU_WIDTH, "| o: Opening hand                | b: sideBoard in cards                  |" );
  mvaddstr( ROWS - MENU_HEIGHT + 2,  COLUMNS - MENU_WIDTH, "| m: Mulligan this hand          | l: display contents of Library         |" );
  mvaddstr( ROWS - MENU_HEIGHT + 3,  COLUMNS - MENU_WIDTH, "| d: Draw a card                 | s: display Sorted contents of library  |" );
  mvaddstr( ROWS - MENU_HEIGHT + 4,  COLUMNS - MENU_WIDTH, "| h: sort Hand                   | e: display Entire decklist             |" );
  mvaddstr( ROWS - MENU_HEIGHT + 5,  COLUMNS - MENU_WIDTH, "| p: search and Put in hand      | q: Quit                                |" );
  mvaddstr( ROWS - MENU_HEIGHT + 6,  COLUMNS - MENU_WIDTH, "| t: reveal Top card of library  |                                        |" );
  mvaddstr( ROWS - MENU_HEIGHT + 7,  COLUMNS - MENU_WIDTH, "+-------------------------------------------------------------------------+" );
  wipeAway( ROWS - MENU_HEIGHT + 8,  COLUMNS - MENU_WIDTH, 1, MENU_WIDTH - 1 );
  mvprintw( ROWS - MENU_HEIGHT + 8,  COLUMNS - MENU_WIDTH, "(%i) Your choice: ", counter );
  refresh();

  c = get_menu_input();

  counter++;
  
  return c;
}
