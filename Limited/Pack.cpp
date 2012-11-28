/*
Pack.cpp
Eric Brewer
10/4/11
Pack implementation - 
*/

#include "Pack.hpp"

void Pack :: insertCard( string name ){

  _lineup.push_back( name );
}

bool Pack :: takeCard( int slot ){

  if( slot >= _lineup.size() )
    return false;

  for( int i = slot + 1; i < _lineup.size(); i++ )
    _lineup[i-1] = _lineup[i];
  _lineup.pop_back();
  return true;
}

bool Pack :: contains( string name ){
  
  for( int i = 0; i < _lineup.size(); i++ )
    if( !_lineup[i].compare( name ) )
      return true;

  return false;
}

void Pack :: display( ostream& fout ){
  
  for( int i = 0; i < _lineup.size(); i++ )
    fout << setw( 2 ) << i + 1 << ' ' << _lineup[i] << endl;
}

void Pack :: display( int r, int c, int h, int w ){

  for( int i = 0; i < _lineup.size(); i++ ){
    mvprintw( r + i % h, c - w * ( i / h ), "%i", i + 1 );
    mvaddstr( r + i % h, 3 + c - w * ( i / h ), _lineup[i].c_str() );
  }
}
