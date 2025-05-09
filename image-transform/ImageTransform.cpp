#include <iostream>
#include <cmath>
#include <cstdlib>

#include "uiuc/PNG.h"
#include "uiuc/HSLAPixel.h"
#include "ImageTransform.h"

/* ******************
(Begin multi-line comment...)

Write your name and email address in the comment space here:

Name:
Email:

(...end multi-line comment.)
******************** */

using uiuc::PNG;
using uiuc::HSLAPixel;

/**
 * Returns an image that has been transformed to grayscale.
 *
 * The saturation of every pixel is set to 0, removing any color.
 *
 * @return The grayscale image.
 */
PNG grayscale(PNG image) {
  /// This function is already written for you so you can see how to
  /// interact with our PNG class.
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel & pixel = image.getPixel(x, y);

      // `pixel` is a reference to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly. No need to `set`
      // the pixel since you're directly changing the memory of the image.
      pixel.s = 0;
    }
  }

  return image;
}



/**
 * Returns an image with a spotlight centered at (`centerX`, `centerY`).
 *
 * A spotlight adjusts the luminance of a pixel based on the distance the pixel
 * is away from the center by decreasing the luminance by 0.5% per 1 pixel euclidean
 * distance away from the center.
 *
 * For example, a pixel 3 pixels above and 4 pixels to the right of the center
 * is a total of `sqrt((3 * 3) + (4 * 4)) = sqrt(25) = 5` pixels away and
 * its luminance is decreased by 2.5% (0.975x its original value).  At a
 * distance over 160 pixels away, the luminance will always decreased by 80%.
 * 
 * The modified PNG is then returned.
 *
 * @param image A PNG object which holds the image data to be modified.
 * @param centerX The center x coordinate of the crosshair which is to be drawn.
 * @param centerY The center y coordinate of the crosshair which is to be drawn.
 *
 * @return The image with a spotlight.
 */
PNG createSpotlight(PNG image, int centerX, int centerY) {
  //start from centre of image, each pixel decrease lum by factor of 0.05
  //up till the edge of image
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      int deltaX = x - centerX;
      int deltaY = y - centerY;
      double distSq = deltaX*deltaX + deltaY*deltaY;
      double dist = sqrt(distSq);
      double lum_factor = 1.0;

      if (dist > 160.0) {
        lum_factor = 0.2; //decrease by 80%
      } else {
        lum_factor = 1.0 - (dist*0.005); //decrease by 0.5% per pix
        if (lum_factor < 0.2) {lum_factor = 0.2;}; //cap de-illum at 80%
      }
      
      HSLAPixel & pixel = image.getPixel(x, y);
      pixel.l *= lum_factor;
    }
  }
  return image;
}

/**
 * Returns a image transformed to Illini colors.
 *
 * The hue of every pixel is set to the a hue value of either orange or
 * blue, based on if the pixel's hue value is closer to orange than blue.
 *
 * @param image A PNG object which holds the image data to be modified.
 *
 * @return The illinify'd image.
**/
PNG illinify(PNG image) {
  //find the mid-point value between Illini Orange (11) and Illini Blue (216)
  //if pixel hue value less than mid-point, set hue to Orange
  //if pixel hue value greater than mid-point set hue to Blue
  int Ill_Orange = 11;
  int Ill_Blue = 216;

  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel & pixel = image.getPixel(x, y);
    
      double distToOrange = std::fmod(std::abs(pixel.h - Ill_Orange), 360.0);
      double distToBlue = std::fmod(std::abs(pixel.h - Ill_Blue), 360.0);

      if (distToOrange > 180.0) distToOrange = 360.0 - distToOrange;
      if (distToBlue > 180.0) distToBlue = 360.0 - distToBlue;

      if (distToBlue < distToOrange) {
        pixel.h = Ill_Blue;
      } else {
        pixel.h = Ill_Orange;
      }
    }
  }
return image;
}
 

/**
* Returns an immge that has been watermarked by another image.
*
* The luminance of every pixel of the second image is checked, if that
* pixel's luminance is 1 (100%), then the pixel at the same location on
* the first image has its luminance increased by 0.2.
*
* @param firstImage  The first of the two PNGs, which is the base image.
* @param secondImage The second of the two PNGs, which acts as the stencil.
*
* @return The watermarked image.
*/
PNG watermark(PNG firstImage, PNG secondImage) {
  //define the boundaries which both image overlaps;
  //iterate over pixels of secondImage (stencil) within boundaries
  //if secondImage's luminance value is 1,
  //increase luminiscence value of corresponding pixel of firstImage(base)
  //by 0.2 but not exceeding 1.0 
  unsigned minWidth = std::min(firstImage.width(), secondImage.width());
  unsigned minHeight = std::min(firstImage.height(), secondImage.height());

  for (unsigned x = 0; x < minWidth; x++) {
    for (unsigned y = 0; y < minHeight; y++) {
      HSLAPixel & stencil_pixel = secondImage.getPixel(x, y);
      if (stencil_pixel.l==1) { //checking luminescence of stencil pixel
        HSLAPixel & base_pixel = firstImage.getPixel(x,y);
        base_pixel.l += 0.2;
        if (base_pixel.l > 1.0){base_pixel.l = 1.0;}   
        //clamp luminence to 1.0
      }
    }
  } 
  return firstImage;
}
