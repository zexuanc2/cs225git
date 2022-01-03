// Your code here! :)
#include <iostream>
#include "student.h"
using namespace std;
 
potd::Student::Student() {
    Student::name_ = "mick";
    Student::grade_ = 3;
}

void potd::Student::set_name(string n) {
    name_ = n;

}
void potd::Student::set_grade(int g) {
    grade_ = g;
}
int potd::Student::get_grade() {
    return grade_;
}
string potd::Student::get_name() {
    return name_;
}
