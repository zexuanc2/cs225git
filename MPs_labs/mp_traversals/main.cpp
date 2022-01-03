
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  PNG input;
  input.readFromFile("tests/pacman.png");
  FloodFilledImage image(input);
  BFS bfs_(input, Point(100,100),0.2);
  MyColorPicker my(HSLAPixel(11,0.5,0.5));
  SolidColorPicker solid(HSLAPixel(116,0.8,0.8));
  image.addFloodFill(bfs_,my);
  image.addFloodFill(bfs_,solid);
  Animation animation = image.animate(1200);

  
  
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  


  return 0;
}
