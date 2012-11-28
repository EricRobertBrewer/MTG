/*
BoosterBox.hpp
Eric Brewer
10/4/11
Booster Box class - 
*/

#ifndef _BOOSTERBOX_HPP
#define _BOOSTERBOX_HPP

#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Pack.hpp"

class BoosterBox{
public:
  BoosterBox( string setname );

  Pack pullPack();

private:
  string _setname;

  int _rarity_slots;
  int _rare_dist;
  int _uncommon_dist;
  int _common_dist;
  int _other_dist;

  int _rarity_types;
  int _rare;
  int _uncommon;
  int _common;
  int _mythic;
  int _rare_flip;
  int _uncommon_flip;
  int _common_flip;
  int _mythic_flip;

  vector<string> _rnames;
  vector<string> _unames;
  vector<string> _cnames;
  vector<string> _mnames;
  vector<string> _rfnames;
  vector<string> _ufnames;
  vector<string> _cfnames;
  vector<string> _mfnames;
};

#endif
