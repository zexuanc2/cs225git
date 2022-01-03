#include "Image.h"
#include "StickerSheet.h"

StickerSheet::StickerSheet(const cs225::Image & picture, unsigned size) {
  base_ = picture;
  maxNum = size;
  layernum = 0;
  imageSheet = new cs225::Image * [size];
  for(int i = 0; i < maxNum; i++){
    imageSheet[i] = NULL;
  }
  row = new unsigned[size];
  col= new unsigned[size];
}

StickerSheet::~StickerSheet() {
  clear();
}

StickerSheet::StickerSheet(const StickerSheet & other) {
  copy(other);
}

void StickerSheet::clear() {
  if(imageSheet != NULL){
    for(int i = 0; i < maxNum; i++){
      imageSheet[i] = NULL;
    }
    delete[] imageSheet;
    imageSheet = NULL;
  }
  if(row != NULL){
    delete[] row;
    row = NULL;
  }
  if(col != NULL){
    delete[] col;
    col = NULL;
  }
}

void StickerSheet::copy(const StickerSheet& other) {
  maxNum = other.maxNum;
  base_ = other.base_;
  layernum = other.layernum;
  imageSheet = new cs225::Image * [maxNum];
  row = new unsigned[maxNum];
  col = new unsigned[maxNum];
  for(int i = 0; i < maxNum; i++){
    imageSheet[i] = other.imageSheet[i];
    row[i] = other.row[i];
    col[i] = other.col[i];
  }
}

const StickerSheet & StickerSheet::operator= (const StickerSheet& other) {
  clear();
  if(&other != this){
    copy(other);
  }
  return *this;
}

int StickerSheet::addSticker(cs225::Image & sticker, unsigned x, unsigned y) {
  if(layernum < maxNum) {
    imageSheet[layernum] = &sticker;
    row[layernum] = x;
    col[layernum] = y;
    layernum++;
    return layernum;
  }
  else{
    return -1;
  }
}

void StickerSheet::changeMaxStickers(unsigned size) {
  cs225::Image ** tempSheet = new cs225::Image*[size];
  unsigned * tempRow = new unsigned[size];
  unsigned * tempCol = new unsigned[size];
  for(int i = 0; i < int(size); i++) {
    tempSheet[i] = NULL;
  }
  for(int i = 0; i < std::min(int(size), int(maxNum)); i++) {
    tempSheet[i] = imageSheet[i];
    tempRow[i] = row[i];
    tempCol[i] = col[i];
  }
  clear();
  maxNum = size;
  imageSheet = tempSheet;
  row = tempRow;
  col = tempCol;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
  if (int(index) >= layernum) {
    return false;
  }
  if (imageSheet[index] == NULL) {
    return false;
  }
  row[index] = x;
  col[index] = y;
  return true;
}

cs225::Image * StickerSheet::getSticker(unsigned index) const {
  if(int(index) >= layernum) {
    return NULL;
  }
  return imageSheet[index];
}

void StickerSheet::removeSticker(unsigned index) {
  if(int(index) >= maxNum) {
    return;
  }
  if(imageSheet[index] == NULL) {
    return;
  }
  imageSheet[index] = NULL;
  row[index] = 0;
  col[index] = 0;
  layernum --;
}

cs225::Image StickerSheet::render() const {
  cs225::Image baseSheet = base_;
  for(int i = 0; i < maxNum; i++){
    if(imageSheet[i] != NULL){
      for(unsigned j = 0; j < imageSheet[i]->width(); j++){
        for(unsigned k = 0; k < imageSheet[i]->height(); k++){
          if((row[i]+imageSheet[i]->width()) > baseSheet.width()){
            baseSheet.resize(unsigned(row[i]+imageSheet[i]->width()), baseSheet.height());
          }
          if((col[i]+imageSheet[i]->height()) > baseSheet.height()){
            baseSheet.resize(unsigned(col[i]+imageSheet[i]->height()), baseSheet.width());
          }
          cs225::HSLAPixel & basepixel = baseSheet.getPixel(j+row[i], k+col[i]);
          if(imageSheet[i]->getPixel(j,k).a != 0){
            basepixel = imageSheet[i]->getPixel(j,k);
          }
        }
      }
    }
  }
  return baseSheet;
}

