//  rand.h <> SlidePuzzleC
//  Created by Rodolfo Gomez
//
//  Description: Generates a random integer seeded by time converted to unsigned for compatiblity
//  Referenced: http://eternallyconfuzzled.com/arts/jsw_art_rand.aspx

#ifndef __SlidePuzzleC__rand__
#define __SlidePuzzleC__rand__

#include <stdlib.h>
#include <time.h>
#include <limits.h>

int getRand(int max);
unsigned timeSeed();

#endif
