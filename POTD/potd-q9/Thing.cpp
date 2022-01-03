// Your code here!
#include "Thing.h"
#include <iostream>
using namespace std;
using namespace potd;

Thing::Thing(int size) {
    props_max_ = size;
    props_ct_ = 0;
    properties_ = new string[size];
    values_ = new string[size];
}
Thing::Thing(const Thing& that) {
    props_max_ = that.props_max_;
    props_ct_ = that.props_ct_;
    properties_ = new string[props_max_];
    values_ = new string[props_max_];
    _copy(that);
}
Thing& Thing::operator=(const Thing& That) {
    _destroy();
    props_max_ = That.props_max_;
    props_ct_ = That.props_ct_;
    properties_ = new string[props_max_];
    values_ = new string[props_max_];
    _copy(That);
    

    return *this;
}
void Thing::_copy(const Thing& That) {
    for(int i = 0; i < That.props_max_; i++) {
        properties_[i] = That.properties_[i];
        values_[i] = That.values_[i];
    }

}
void Thing::_destroy() {
    delete[] properties_;
    delete[] values_;
}
int Thing::set_property(string name, string value) {
    for(int i = 0; i < props_ct_; i++) {
        if (properties_[i] == name) {
            values_[i] = value;
            return i;
        }
    }
    if (props_ct_ < props_max_) {
        properties_[props_ct_] = name;
        values_[props_ct_] = value;
        props_ct_++;
        return props_ct_ - 1;
    }
    
    return -1;
}
string Thing::get_property(string name) {
    for (int i = 0; i < props_ct_; i++) {
        if(properties_[i] == name) {
            return values_[i];
        }
    }
    return "";
}
Thing::~Thing() {
    _destroy();
}
 