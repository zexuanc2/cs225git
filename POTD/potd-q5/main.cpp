// your code here
#include <iostream>
#include "Food.h"
#include "q5.h"

using namespace std;

int main() {
    Food food;
    food.set_name("apples");
    food.set_quantity(5);
    cout<<"You have "<<food.get_quantity()<<" "<<food.get_name()<<endl;
    Food* ptr = &food;
    increase_quantity(ptr);
    cout<<"You have "<<food.get_quantity()<<" "<<food.get_name()<<endl;

    return 0;



}