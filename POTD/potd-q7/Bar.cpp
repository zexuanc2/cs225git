// your code here
#include "Foo.h"
#include "Bar.h"
using namespace std;
using namespace potd;

string Bar::get_name() {
    return  (*f_).get_name();
}
Bar::Bar(string input) {
    *f_ = Foo(input);
}
Bar::Bar(const Bar& that) {
    f_ = new Foo(*(that.f_));
}
Bar& Bar::operator=(const Bar& that) {
    delete f_;
    f_ = new Foo(*(that.f_));
    return *this;
}
Bar::~Bar() {
    delete f_;
}