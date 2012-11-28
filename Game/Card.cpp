/*
Card.cpp
Eric Brewer
11/30/11
Card class implementation - 
*/

#include "Card.hpp"

Card :: Card( string name ){

  _name = name;
  _expansion = "";
}
/*
void Card :: print( ostream& outs ){

  outs << _name << endl;
}
*/
void Card :: print( int r, int c ){
  
  mvaddstr( r, c, _name.c_str() );
  refresh();
}
