/*
Pack.hpp
Eric Brewer
10/4/11
Pack class - 
*/

#ifndef _PACK_HPP
#define _PACK_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <curses.h>
using namespace std;

#define PACKSIZE 15

class Pack{
public:
  Pack() {}

  void insertCard( string name );
  bool takeCard( int slot );
  bool contains( string name );
  void display( ostream& fout );
  void display( int r, int c, int h, int w );
  int size() const { return _lineup.size(); }
  string cardName( int slot ) const { return _lineup[slot-1]; }

private:
  vector<string> _lineup;
};

#endif
