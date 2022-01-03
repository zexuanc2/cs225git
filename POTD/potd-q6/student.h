// Your code here! :)
#pragma once
#include <iostream>
using namespace std;

namespace potd {
    class Student
    {
    private:
        /* data */
        std::string name_;
        int grade_;
    public:
        Student();
        void set_name(string n);
        void set_grade(int g);
        string get_name();
        int get_grade();
    };
    
}

