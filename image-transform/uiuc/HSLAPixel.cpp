/**
 * @file HSLAPixel.cpp
 * Implementation of the HSLAPixel class for use in with the PNG library.
 *
 * @author University of Illinois CS 225 Course Staff
 * @version 2018r1-lab1 - Updated for CS 400
 */

#include <cmath>
#include <iostream>
#include "HSLAPixel.h"
using namespace std;

namespace uiuc {
    uiuc::HSLAPixel::HSLAPixel() : h(0.0), s(0.0), l(1.0), a(1.0) {};
    // Initialization list  for constructors
    uiuc::HSLAPixel::HSLAPixel(double hue, double sat, double lum, double alph) :
    h(hue), s(sat), l(lum), a(alph){};

}
