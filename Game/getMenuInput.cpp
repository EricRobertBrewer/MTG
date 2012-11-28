/*
getMenuInput.cpp
Eric Brewer
12/5/11
get_menu_input function implementation - 
*/

#include <iostream>
#include <sys/time.h>
#include <sgtty.h>
#include <curses.h>
#include <signal.h>
#include <stdlib.h>

const int SEC_DELAY = 2000;
const int USEC_DELAY = 0;
static char lastc = ' ';

void die();
char get_menu_input();

static int checkinput( int fd, long secdelay, long usecdelay ){

  int rdmask;
  struct timeval tvec;
  int val;

  if( fd < 0 || secdelay < 0 || usecdelay < 0 )
    return -1;

  rdmask = ( 1 << fd );

  tvec.tv_sec = secdelay;
  tvec.tv_usec = usecdelay;

  val = select( 1, ( fd_set* )& rdmask, NULL, NULL, &tvec );

  return val;
}

char get_menu_input(){

  int x;
  char c;

  if( ( x = checkinput( 0, SEC_DELAY, USEC_DELAY ) ) < 0 )
    die();

  if( x ){
    if( read( 0, &c, 1 ) < 0 )
      die();
    
    if( c == 'o' || 
	c == 'm' || 
	c == 'd' || 
	c == 'h' || 
	c == 'p' || 
	c == 't' || 
    	c == 'b' ||
	c == 'l' || 
	c == 's' || 
	c == 'e' || 
	c == 'q' )
      lastc = c;
  }

  return lastc;
}

void die(){

  signal( SIGINT, SIG_IGN );
  mvcur( 0, COLS - 1, LINES - 1, 0 );
  endwin();
  exit( 1 );
}
