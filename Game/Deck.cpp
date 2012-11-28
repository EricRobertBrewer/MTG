/*
Deck.cpp
Eric Brewer
11/27/11
Deck class implementation - 
*/

#include "Deck.hpp"

Deck :: Deck( vector<string>* md, vector<string>* sb ){

  _maindeck.clear();
  _sideboard.clear();
  _library_tags.clear();
  _hand_tags.clear();

  srand( time( NULL ) );

  for( int i = 0; i < md[0].size(); i++ ){
    Card* c = new Card( md[0][i] );
    _maindeck.push_back( c );
    _library_tags.push_back( i );
  }
  for( int i = 0; i < sb[0].size(); i++ ){
    Card* c = new Card( sb[0][i] );
    _sideboard.push_back( c );
  }
}

int Deck :: shuffle(){

  int a;
  vector<int> v;

  while( _library_tags.size() ){
    a = rand() % _library_tags.size();
    v.push_back( _library_tags[a] );
    _library_tags[a] = _library_tags.back();
    _library_tags.pop_back();
  }

  while( v.size() ){
    a = rand() % v.size();
    _library_tags.push_back( v[a] );
    v[a] = v.back();
    v.pop_back();
  }

  return _library_tags[0];
}

void Deck :: openingHand(){
  
  reset();
  shuffle();
  for( int i = 0; i < OPENING_HAND_SIZE; i++ )
    draw();
}

void Deck :: mulligan(){

  int n = _hand_tags.size();

  reset();
  shuffle();
  for( int i = 0; i < n - 1; i++ )
    draw();
}

bool Deck :: draw(){

  if( !_library_tags.size() )
    return false;

  _hand_tags.push_back( _library_tags.back() );
  _library_tags.pop_back();

  return true;
}

void Deck :: reset(){

  _hand_tags.clear();
  _library_tags.clear();
  for( int i = 0; i < _maindeck.size(); i++ )
    _library_tags.push_back( i );
}

void Deck :: revealTopCard( int r, int c ){

  _maindeck[_library_tags.back()]->print( r, c );
}

void Deck :: displayHand( int r, int c, int h, int w, int dir ){

  for( int i = 0; i < _hand_tags.size(); i++ ){
    mvprintw( r + i % h, c + dir * w * ( i / h ), "%i", i + 1 );
    _maindeck[_hand_tags[i]]->print( r + i % h, 3 + c + dir * w * ( i / h ) );
  }
}

void Deck :: sortHand(){

  if( _hand_tags.size() < 2 )
    return;

  for( int i = 0; i < _hand_tags.size(); i++ )
    for( int j = 1; j < _hand_tags.size(); j++ )
      if( _hand_tags[j-1] > _hand_tags[j] ){
	_hand_tags[j-1] += _hand_tags[j];
	_hand_tags[j] = _hand_tags[j-1] - _hand_tags[j];
	_hand_tags[j-1] = _hand_tags[j-1] - _hand_tags[j];
      }
}

void Deck :: displayLibrary( int r, int c, int h, int w, int dir ){

  for( int i = 0; i < _library_tags.size(); i++ ){
    mvprintw( r + i % h, c + dir * w * ( i / h ), "%i", i + 1 );
    _maindeck[_library_tags[i]]->print( r + i % h, 3 + c + dir * w * ( i / h ) );
  }
}

void Deck :: displaySortedLibrary( int r, int c, int h, int w, int dir ){

  if( !_library_tags.size() )
    return;

  if( _library_tags.size() == 1 ){
    _maindeck.back()->print( r, c );
    return ;
  }

  vector<int> v;

  for( int i = 0; i < _library_tags.size(); i++ )
    v.push_back( _library_tags[i] );

  for( int i = 0; i < _library_tags.size(); i++ )
    for( int j = 1; j < _library_tags.size(); j++ )
      if( v[j-1] > v[j] ){
	v[j-1] += v[j];
	v[j] = v[j-1] - v[j];
	v[j-1] = v[j-1] - v[j];
      }

  for( int i = 0; i < v.size(); i++ ){
    mvprintw( r + i % h, c + dir * w * ( i / h ), "%i", i + 1 );
    _maindeck[v[i]]->print( r + i % h, 3 + c + dir * w * ( i / h ) );
  }
}

void Deck :: displayDecklist( int r, int c, int h, int w, int dir ){

  int i;

  for( i = 0; i < _maindeck.size(); i++ ){
    mvprintw( r + i % h, c + dir * w * ( i / h ), "%i", i + 1 );
    _maindeck[i]->print( r + i % h, 3 + c + dir * w * ( i / h ) );
  }

  for( i; i < _maindeck.size() + _sideboard.size(); i++ ){
    mvprintw( r + ( i + 1 ) % h, c + w * ( i / h ), "%i", i + 1 - _maindeck.size() );
    _sideboard[i-_maindeck.size()]->print( r + ( i + 1 ) % h, 3 + c + dir * w * ( i / h ) );
  }
}

int Deck :: cardsInLibrary() const{

  return _library_tags.size();
}

int Deck :: cardsInHand() const{

  return _hand_tags.size();
}

bool Deck :: searchLibraryToHand( int choice ){

  if( choice < 1 || choice > _library_tags.size() )
    return false;

  _hand_tags.push_back( _library_tags[choice-1] );
  _library_tags[choice-1] = _library_tags.back();
  _library_tags.pop_back();

  shuffle();

  return true;
}

bool Deck :: sideIn( int md, int sb ){

  if( md > _maindeck.size() )
    return false;
  if( sb > _sideboard.size() )
    return false;

  Card* c = _maindeck[md-1];
  _maindeck[md-1] = _sideboard[sb-1];
  _sideboard[sb-1] = c;

  reset();
  shuffle();

  return true;
}
