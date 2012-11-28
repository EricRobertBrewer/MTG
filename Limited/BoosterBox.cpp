/*
BoosterBox.cpp
Eric Brewer
10/4/11
Booster Box implementation - 
*/

#include "BoosterBox.hpp"

BoosterBox :: BoosterBox( string setname ){

  string sn = "/home/student/brewere/Potpourri/MTG/Sets/";
  sn.append( setname );
  ifstream fin( sn.c_str() );
  if( fin.fail() ){
    cout << "Couldn't find file with name " << setname << '.' << endl;
    exit( 1 );
  }
  string cardname;

  _setname = setname;
  
  fin >> _rarity_slots;
  fin >> _rare_dist;
  fin >> _uncommon_dist;
  fin >> _common_dist;
  if( _rarity_slots == 4 )
    fin >> _other_dist;
  else
    _other_dist = 0;
  
  fin >> _rarity_types;
  fin >> _rare;
  fin >> _uncommon;
  fin >> _common;
  if( _rarity_types >= 4 )
    fin >> _mythic;
  else
    _mythic = 0;
  if( _rarity_types == 8 ){
    fin >> _rare_flip;
    fin >> _uncommon_flip;
    fin >> _common_flip;
    fin >> _mythic_flip;
  }
  else
    _rare_flip = _uncommon_flip = _common_flip = _mythic_flip = 0;

  getline( fin, cardname );
  for( int i = 0; i < _rare; i++ ){
    getline( fin, cardname );
    _rnames.push_back( cardname );
  }
  for( int i = 0; i < _uncommon; i++ ){
    getline( fin, cardname );
    _unames.push_back( cardname );
  }
  for( int i = 0; i < _common; i++ ){
    getline( fin, cardname );
    _cnames.push_back( cardname );
  }
  for( int i = 0; i < _mythic; i++ ){
    getline( fin, cardname );
    _mnames.push_back( cardname );
  }
  for( int i = 0; i < _rare_flip; i++ ){
    getline( fin, cardname );
    _rfnames.push_back( cardname );
  }
  for( int i = 0; i < _uncommon_flip; i++ ){
    getline( fin, cardname );
    _ufnames.push_back( cardname );
  }
  for( int i = 0; i < _common_flip; i++ ){
    getline( fin, cardname );
    _cfnames.push_back( cardname );
  }
  for( int i = 0; i < _mythic_flip; i++ ){
    getline( fin, cardname );
    _mfnames.push_back( cardname );
  }
  
  srand( time( NULL ) );
}

Pack BoosterBox :: pullPack(){

  Pack pack;
  int dud;
  int newu = _uncommon_dist;
  int newc = _common_dist;

  if( _mythic && _setname.compare( "TSP" ) ){
    dud = rand() % 8;
    if( !dud ){
      dud = rand() % _mythic;
      pack.insertCard( _mnames[dud] );
    }
    else{
      dud = rand() % _rare;
      pack.insertCard( _rnames[dud] );
    }
  }
  else{
    dud = rand() % _rare;
    pack.insertCard( _rnames[dud] );
  }

  while( newu ){
    dud = rand() % _uncommon;
    if( !pack.contains( _unames[dud] ) ){
      pack.insertCard( _unames[dud] );
      newu--;
    }
  }
  
  while( newc ){
    dud = rand() % _common;
    if( !pack.contains( _cnames[dud] ) ){
      pack.insertCard( _cnames[dud] );
      newc--;
    }
  }

  if( _rarity_slots >= 4 )
    if( _mythic )
      if( !_setname.compare( "TSP" ) ){
	dud = rand() % _mythic;
	pack.insertCard( _mnames[dud] );
      }
      else{
	dud = rand() % ( 1 + 8 + 24 + 80 - 3 );
	if( dud == 1 ){
	  dud = rand() % _mythic_flip;
	  pack.insertCard( _mfnames[dud] );
	}
	else if( dud < 1 + 8 ){
	  dud = rand() % _rare_flip;
	  pack.insertCard( _rfnames[dud] );
	}
	else if( dud < 1 + 8 + 24 ){
	  dud = rand() % _uncommon_flip;
	  pack.insertCard( _ufnames[dud] );
	}
	else{
	  dud = rand() % _common_flip;
	  pack.insertCard( _cfnames[dud] );
	}
      }

  return pack;
}
