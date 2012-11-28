/*
Scanner.cpp
Eric Brewer
11/27/11
Scanner class implementation - 
*/

#include "Scanner.hpp"

Scanner :: Scanner(){
  
}

Scanner :: ~Scanner(){

  _fin.close();
}

bool Scanner :: loadDecklist( const char* filename ){

  _fin.close();
  _fin.open( filename );
  if( _fin.fail() )
    return false;

  return true;
}

Deck* Scanner :: createDeck(){

  int cnum = -1;
  string cname;
  vector<string> md_names;
  vector<string> sb_names;
  Deck* d;

  while( _fin >> cnum && cnum ){
    if( cnum ){
      getline( _fin, cname );
      cname.erase( 0, 1 );
      for( int i = 0; i < cnum; i++ )
	md_names.push_back( cname );
    }
  }
  while( _fin >> cnum ){
    getline( _fin, cname );
    cname.erase( 0, 1 );
    for( int i = 0; i < cnum; i++ )
      sb_names.push_back( cname );
  }

  d = new Deck( &md_names, &sb_names );

  return d;
}
