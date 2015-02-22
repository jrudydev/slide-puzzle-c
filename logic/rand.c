//  rand.c <> SlidePuzzleC
//  Created by Rodolfo Gomez
//
//  Description: Generates a random integer seeded by time converted to unsigned for compatiblity
//  Referenced: http://eternallyconfuzzled.com/arts/jsw_art_rand.aspx

#include "rand.h"

int getRand(int max) {
    return (max <= 1) ? 0 : rand() / ( RAND_MAX / max + 1 );
}


unsigned timeSeed()
{
    time_t now = time(0);
    unsigned char *p = (unsigned char *)&now;
    unsigned seed = 0;
    size_t i;
    
    for(i = 0; i < sizeof now; i++)
        seed = seed * (UCHAR_MAX + 2U) + p[i];
    return seed;
}