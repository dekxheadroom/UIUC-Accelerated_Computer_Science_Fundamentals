/**
 * @file HSLAPixel.h
 *
 * @author University of Illinois CS 225 Course Staff
 * @version 2018r1-lab1 - Updated for CS 400
 */

#pragma once

#include <iostream>
#include <sstream>

namespace uiuc {

  // Put your HSLAPixel class definition here.
  // (Remember to end it with a semicolon!)
  class HSLAPixel {
    public:
      double h; //(h)ue of the pixel in degrees between 0 and 360 
      double s; //(s)aturation of the pixel as a decimal value between 0.0 and 1.0
      double l; //(l)uminance of the pixel as a decimal value between 0.0 and 1.0 
      double a; //(a)lpha channel (blending opacity) as a decimal value between 0.0 and 1.0
      HSLAPixel();
      HSLAPixel(double h, double s, 
      double l, double a); //custom default constructor
  };
}
