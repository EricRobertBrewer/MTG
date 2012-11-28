/*
Scanner.hpp
Eric Brewer
11/27/11
Scanner class - 
*/

#ifndef _SCANNER_HPP
#define _SCANNER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#define SCANNER_DEBUG 0
#define scanner_debug if( SCANNER_DEBUG ) cout

#include "Deck.hpp"

class Scanner{
public:
  Scanner();
  ~Scanner();

  bool loadDecklist( const char* filename );
  // Parses the loaded file and creates a Deck object
  Deck* createDeck();

private:
  ifstream _fin;
};

#endif
