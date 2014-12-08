#include "Info_View.h"
#include <iostream>

using std::cout; using std::endl;

void Info_View::draw() {
    cout << "Current ";
    print_info();
    cout << ":" << endl;
    
    cout << "--------------" << endl;
    for (auto &it: info)
    	cout << it.first << ": " << it.second << endl;
    cout << "--------------" << endl;
}

void Info_View::update_info(const std::string& name, double information) {
    info[name] = information;
}

void Info_View::update_remove(const std::string& name) {
    info.erase(name);
}
