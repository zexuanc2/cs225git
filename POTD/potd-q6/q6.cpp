// Your code here! :)
#include "student.h"
#include "q6.h"
using namespace potd;


void graduate(Student& s) {
    int newGrade = s.get_grade() + 1;
    s.set_grade(newGrade);
}