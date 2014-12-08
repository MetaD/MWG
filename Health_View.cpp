#include "Health_View.h"
#include <iostream>

using std::cout; using std::endl;

void Health_View::print_info() {
    cout << "Health";
}

void Health_View::update_health(const std::string &name, int health) {
    Info_View::update_info(name, health);
}
