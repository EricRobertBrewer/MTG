/*
Card.hpp
Eric Brewer
11/17/11
Card Class - 
*/

#ifndef _CARD_HPP
#define _CARD_HPP

#include <iostream>
#include <string>
#include <curses.h>
using namespace std;

#define CARD_DEBUG 0
#define card_debug if( CARD_DEBUG ) cout

class Card{
public:
  Card( string name );

  //void print( ostream& outs );
  void print( int r, int c );
  string name() { return _name; }

private:
  string _name;
  string _expansion;
};

#endif
