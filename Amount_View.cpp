#include "Amount_View.h"
#include <iostream>


void Amount_View::print_info() {
    std::cout << "Amounts";
}

void Amount_View::update_amount(const std::string &name, double amount) {
    Info_View::update_info(name, amount);
}

