#include "Utility.h"



#include <iostream>

void handle_error(const Error & err)
{
    std::cout << err.what() << std::endl;
    std::cin.clear();
    while ( std::cin.get() != '\n');	// skip the line
}
