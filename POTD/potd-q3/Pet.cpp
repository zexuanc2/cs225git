#include <string>
#include "Pet.h"

using namespace std;

// Put your constructor code here!
Pet::Pet() {
  Pet::name = "Rover";
  Pet::birth_year = 2018;
  Pet::type = "dog";
  Pet::owner_name = "Wade";
}

Pet::Pet(string n, int b, string t, string o) {
  Pet::name = n;
  Pet::birth_year = b;
  Pet::type = t;
  Pet::owner_name = o;
}

void Pet::setName(string newName) {
  name = newName;
}

void Pet::setBY(int newBY) {
  birth_year = newBY;
}

void Pet::setType(string newType) {
  type = newType;
}

void Pet::setOwnerName(string newName) {
  owner_name = newName;
}

string Pet::getName() {
  return name;
}

int Pet::getBY() {
  return birth_year;
}

string Pet::getType() {
  return type;
}

string Pet::getOwnerName() {
  return owner_name;
}
