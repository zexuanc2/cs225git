/* Your code here! */
#include "maze.h"
#include <sys/time.h>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

//a default constructor creating an empty maze
SquareMaze::SquareMaze(){
}

/* Makes a new SquareMaze of the given height and width.
If this object already represents a maze it will clear all the existing data before doing so. 
You will start with a square grid (like graph paper) with the specified height and width.
You will select random walls to delete without creating a cycle, 
until there are no more walls that could be deleted without creating a cycle. 
Do not delete walls on the perimeter of the grid.
*/

void SquareMaze::makeMaze(int width, int height){
  width_ = width;
  height_ = height;
  int mazeSize = width * height;
  mazeSets.addelements(mazeSize);
  for(int i = 0; i < mazeSize; i++){
    rightWalls.push_back(true);
    downWalls.push_back(true);
  }
  //select random walls to delete without creating a cycle
  int x, y;
  struct timeval tv;
  gettimeofday(&tv,NULL);
  srand(tv.tv_usec);
  //clear the sets such that there's only one set
  while(mazeSets.size(0) < mazeSize){  
    x = rand() % width_;
    y = rand() % height_;
    if(rand() % 2 == 1){
      if (x != width_ - 1) {
        if (mazeSets.find(y * width_ + x) != mazeSets.find(y * width_ + x + 1)) {
          rightWalls[y * width_ + x] = false; 
          mazeSets.setunion(y * width_ + x, y * width_ + x + 1);
        }
      }
    }
    else {
      if (y != height_ - 1) {
        if (mazeSets.find(y * width_ + x) != mazeSets.find(y * width_ + x + width_)) {
          setWall(x, y, 1, false);
          mazeSets.setunion(y * width_ + x, y * width_ + x + width_);
        }
      }
    }
  }

}


/*
This uses your representation of the maze to determine whether it is possible 
to travel in the given direction from the square at coordinates (x,y).

For example, after makeMaze(2,2), the possible input coordinates will be (0,0), (0,1), (1,0), and (1,1).

dir = 0 represents a rightward step (+1 to the x coordinate)
dir = 1 represents a downward step (+1 to the y coordinate)
dir = 2 represents a leftward step (-1 to the x coordinate)
dir = 3 represents an upward step (-1 to the y coordinate)
You can not step off of the maze or through a wall.

This function will be very helpful in solving the maze. 
It will also be used by the grading program to verify that your maze is a tree that occupies the whole grid, 
and to verify your maze solution. So make sure that this function works!
*/
bool SquareMaze::canTravel(int x, int y, int dir) const{
    //travel by the correct order
  
  switch(dir){
    case 0: //right
      return rightWalls[y * width_ + x] == false;
    case 1: //down
      return downWalls[y * width_ + x] == false;
    case 2: //left
      return (x != 0) && (rightWalls[y * width_ + x - 1] == false);
    case 3: //up
      return (y != 0) && (downWalls[y * width_ + x - width_] == false);
  }
  return false;
}

/*
Sets whether or not the specified wall exists.

This function should be fast (constant time). You can assume that in grading we 
will not make your maze a non-tree and then call one of the other member functions. 
setWall should not prevent cycles from occurring, but should simply set a wall to be present or not present. 
Our tests will call setWall to copy a specific maze into your implementation.
*/
void SquareMaze::setWall(int x, int y, int dir, bool exists){
  if(dir == 0){
    rightWalls[y * width_ + x] = exists;
  }
  else if(dir == 1){
    downWalls[y * width_ + x] = exists;
  }
}


/*
For each square on the bottom row (maximum y coordinate), there is a distance from the origin (i.e. the top-left cell), 
which is defined as the length (measured as a number of steps) of the only path through the maze from the origin to that square.
Select the square in the bottom row with the largest distance from the origin as the destination of the maze. 
solveMaze() returns the winning path from the origin to the destination as a vector of integers, 
where each integer represents the direction of a step, using the same encoding as in canTravel().
If multiple paths of maximum length exist, use the one with the destination cell that has the smallest x value.
*/
vector<int> SquareMaze::solveMaze(){
    int x, y, curr_idx;
    //stores the bfs path using vector int
    vector<int> path;  
    //stores the distance of every cell from entrance
    vector<int> distance;  
    path.push_back(0); //entrance is visited
    distance.push_back(0);
    for(int i = 1; i < width_ * height_; i++){
      //non-visited
      path.push_back(-1); 
      distance.push_back(0);
    }
    queue<int> bfs;
    bfs.push(0);
    while(!bfs.empty()){
      curr_idx = bfs.front();
      x = curr_idx % width_;
      y = curr_idx / width_;
      bfs.pop();

      if(canTravel(x, y, 0)){
        if(path[curr_idx + 1] == -1){
          bfs.push(curr_idx + 1);
          path[curr_idx + 1] = curr_idx;
          distance[curr_idx + 1] = distance[curr_idx] + 1;
        }
      }
      if(canTravel(x, y, 1)){
        if(path[curr_idx + width_] == -1){
          bfs.push(curr_idx + width_);
          path[curr_idx + width_] = curr_idx;
          distance[curr_idx + width_] = distance[curr_idx] + 1;
        }
      }
      if(canTravel(x, y, 2)){
        if(path[curr_idx - 1] == -1){
          bfs.push(curr_idx - 1);
          path[curr_idx - 1] = curr_idx;
          distance[curr_idx - 1] = distance[curr_idx] + 1;
        }
      }
      if(canTravel(x, y, 3)){
        if(path[curr_idx - width_] == -1){
          bfs.push(curr_idx - width_);
          path[curr_idx - width_] = curr_idx;
          distance[curr_idx - width_] = distance[curr_idx] + 1;
        }
      }
    }
    int longest_path = width_ * (height_ - 1);
    for(int k = 0; k < width_; k++){
      if(distance[width_ * (height_ - 1) + k] > distance[longest_path]){
        longest_path = width_ * (height_ - 1) + k;
      }
    }
    destination = longest_path;
    vector<int> result;
    curr_idx = destination;
    while(curr_idx != 0){
      if(path[curr_idx] == curr_idx - 1){
        result.push_back(0);
      }
      if(path[curr_idx] == curr_idx - width_){
        result.push_back(1);
      }
      if(path[curr_idx] == curr_idx + 1){
        result.push_back(2);
      }
      if(path[curr_idx] == curr_idx + width_){
        result.push_back(3);
      }
      curr_idx = path[curr_idx];
    }
    reverse(result.begin(), result.end());

  return result;
}


/*
Draws the maze without the solution.

First, create a new PNG. Set the dimensions of the PNG to (width*10+1,height*10+1). 
where height and width were the arguments to makeMaze. Blacken the entire topmost row and leftmost column of pixels, 
except the entrance (1,0) through (9,0). For each square in the maze, call its maze coordinates (x,y). 
If the right wall exists, then blacken the pixels with coordinates ((x+1)*10,y*10+k) for k from 0 to 10. 
If the bottom wall exists, then blacken the pixels with coordinates (x*10+k, (y+1)*10) for k from 0 to 10.

The resulting PNG will look like the sample image, except there will be no exit from the maze and the red line will be missing.
*/
PNG* SquareMaze::drawMaze() const{
  int canvas_width = width_ * 10 + 1;
  int canvas_height = height_ * 10 + 1;
  PNG* canvas = new PNG(canvas_width, canvas_height);
  //Blacken the entire topmost row and leftmost column of pixels
  for(int y = 0; y < canvas_height; y++){
    HSLAPixel& p = canvas->getPixel(0, y);
    p.l = 0; 
  }
  for(int x = 10; x < canvas_width; x++){
    HSLAPixel& p = canvas->getPixel(x, 0);
    p.l = 0;
  }

  for(int x = 0; x < width_; x++){
    for(int y = 0; y < height_; y++){
      if(rightWalls[y * width_ + x]){
        //blacken the pixels with coordinates ((x+1)*10,y*10+k) for k from 0 to 10
        for(int k = 0; k <= 10; k++){
          HSLAPixel& p = canvas->getPixel((x + 1) * 10, y * 10 + k);
          p.l = 0;  
        }
      }
      if(downWalls[y * width_ + x]){
        //blacken the pixels with coordinates (x*10+k, (y+1)*10) for k from 0 to 10
        for(int k = 0; k <= 10; k++){
          HSLAPixel& p = canvas->getPixel(x * 10 + k, (y + 1) * 10);
          p.l = 0;  
        }
      }
    }
  }
  return canvas;
}

/*
This function calls drawMaze, then solveMaze; it modifies the PNG from drawMaze to show the solution vector and the exit.

Start at pixel (5,5). Each direction in the solution vector corresponds to a trail of 11 red pixels in the given direction.
If the first step is downward, color pixels (5,5) through (5,15) red. (Red is 0,1,0.5,1 in HSLA). Then if the second step 
is right, color pixels (5,15) through (15,15) red. Then if the third step is up, color pixels (15,15) through (15,5) red. 
Continue in this manner until you get to the end of the solution vector, so that your output looks analogous the above picture.

Make the exit by undoing the bottom wall of the destination square: call the destination maze coordinates (x,y), 
and whiten the pixels with coordinates (x*10+k, (y+1)*10) for k from 1 to 9.
*/
PNG* SquareMaze::drawMazeWithSolution(){
  //initializing some important variables
  PNG* canvas = drawMaze();
  vector<int> solution = solveMaze();
  int x = 5;
  int y = 5;

  //whiten the pixels with coordinates (x*10+k, (y+1)*10) for k from 1 to 9.
  int destinationX = destination % width_;
  int destinationY = destination / height_;
  for(int k = 1; k <= 9; k++){
    HSLAPixel& p = canvas->getPixel(destinationX * 10 + k, (destinationY + 1) * 10);
    p.l = 1;
  }
  for(size_t i = 0; i < solution.size(); i++){
    switch (solution[i]) {
      case 0:
        for(int k = 0; k <= 10; k++){
          HSLAPixel& p = canvas->getPixel(x + k, y);
          p.h = 0;
          p.s = 1;
          p.l = 0.5;
          p.a = 1;
        }
        x += 10;
        break;

      case 1:
      for(int k = 0; k <= 10; k++){
        HSLAPixel& p = canvas->getPixel(x, y + k);
        p.h = 0;
        p.s = 1;
        p.l = 0.5;
        p.a = 1;
      }
        y += 10;
        break;

      case 2:
      for(int k = 0; k <= 10; k++){
        HSLAPixel& p = canvas->getPixel(x - k, y);
        p.h = 0;
        p.s = 1;
        p.l = 0.5;
        p.a = 1;
      }
        x -= 10;
        break;

      case 3:
      for(int k = 0; k <= 10; k++){
        HSLAPixel& p = canvas->getPixel(x, y - k);
        p.h = 0;
        p.s = 1;
        p.l = 0.5;
        p.a = 1;
      }
        y -= 10;
        break;
    }
  }
  return canvas;
}
