// your code here
#pragma once
#include <iostream>
#include "Foo.h"
using namespace std;

namespace potd {
    class Bar {
        private:
        Foo* f_;

        public:
        Bar(string input);
        Bar(const Bar&);
        Bar& operator=(const Bar&);
        ~Bar();
        string get_name();
    };

}