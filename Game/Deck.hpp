/*
Deck.hpp
Eric Brewer
11/27/11
Deck class - 
*/

#ifndef _DECK_HPP
#define _DECK_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <curses.h>
using namespace std;

#define DECK_DEBUG 0
#define deck_debug if( DECK_DEBUG ) cout

#define OPENING_HAND_SIZE 7

#include "Card.hpp"

class Deck{
public:
  Deck( vector<string>* md, vector<string>* sb );

  int shuffle();
  void openingHand();
  void mulligan();
  bool draw();
  void reset();
  void revealTopCard( int r, int c );
  void displayHand( int r, int c, int h, int w, int dir );
  void sortHand();
  void displayLibrary( int r, int c, int h, int w, int dir );
  void displaySortedLibrary( int r, int c, int h, int w, int dir );
  void displayDecklist( int r, int c, int h, int w, int dir );
  int cardsInLibrary() const;
  int cardsInHand() const;
  bool searchLibraryToHand( int choice );
  bool sideIn( int md, int sb );

private:
  vector<Card*> _maindeck;
  vector<Card*> _sideboard;
  vector<int> _library_tags;
  vector<int> _hand_tags;
};

#endif
