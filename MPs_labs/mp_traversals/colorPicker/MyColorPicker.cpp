#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
MyColorPicker::MyColorPicker(HSLAPixel c) : color(c) { }
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */


  return HSLAPixel((x+y) % 180, 1, 0.5);
}
