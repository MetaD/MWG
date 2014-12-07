#include "Utility.h"
#include <iostream>
using std::cout; using std::cin; using std::endl;

void handle_error(const Error & err) {
    error_msg(err);
    cin.clear();
    while (cin.get() != '\n');	// skip the line
}

// output the error message
void error_msg(const Error& err) {
    cout << err.what() << endl;
}
