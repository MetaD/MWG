#include "Amount_View.h"
#include <iostream>

using std::cout; using std::endl;

void Amount_View::print_title() {
    cout << "Amounts";
}

void Amount_View::update_amount(const std::string &name, double amount) {
    Info_View::update_info(name, amount);
}

