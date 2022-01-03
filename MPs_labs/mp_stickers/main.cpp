#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image base, student, supreme, money;
  base.readFromFile("myImages/base.png");

  student.readFromFile("myImages/student.png");
  student.scale(100,100);

  supreme.readFromFile("myImages/supreme.png");
  supreme.scale(200,100);

  money.readFromFile("myImages/money.png");
  money.scale(100,100);

  StickerSheet output(base, 3);
  output.addSticker(student, 120, 50);
  output.addSticker(supreme, 300, 200);
  output.addSticker(money, 50, 100);

  Image outImage = output.render();
  outImage.writeToFile("myImage.png");



  return 0;
}
