#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>


void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  cs225::PNG png1;
  cs225::PNG png2;

  png1.readFromFile(inputFile);
  png2.readFromFile(inputFile);
  for (unsigned x = 0; x < png1.width(); x++) {
    for (unsigned y = 0; y < png1.height(); y++) {
      cs225::HSLAPixel & before = png1.getPixel(x, y);
      cs225::HSLAPixel & after = png2.getPixel(png1.width()-1 - x, png1.height()-1 - y);
      
      before = after;
    }
  }
  png1.writeToFile(outputFile);
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3
  for (unsigned x = 0; x < png.width(); x++) {
    for (unsigned y = 0; y < png.height(); y++) {
      cs225::HSLAPixel & pixel = png.getPixel(x, y);
      pixel.s = 0.8;
      pixel.l = 0.5;
      pixel.h = x%360;
    }
  }

  return png;
}
