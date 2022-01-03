// Your code here! :)
#include "student.h"
#include "q6.h"
#include <iostream>
using namespace std;
using namespace potd;

int main() {
    Student a;
    Student& czx = a;
    cout<<czx.get_name()<<czx.get_grade()<<endl;
    graduate(czx);
    cout<<czx.get_name()<<czx.get_grade()<<endl;
}
