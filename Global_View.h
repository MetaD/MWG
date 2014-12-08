#ifndef Global_View_H
#define Global_View_H

#include "Grid_View.h"

class Global_View : public Grid_View {
public:
    Global_View();

    void draw() override;

    
    // Setters should never be called for Global_Views
    void set_size(int size_) override {}	//?? TODO use assert
    void set_scale(double scale_) override {}
    void set_origin(Point origin_) override {}
    void set_defaults() override {}
    
protected:
    // print the information of the Global_View
    void print_info() override;
    
    void print_outsiders(std::vector<std::string> outsiders)  override;
    
};

#endif 
