#ifndef Global_View_H
#define Global_View_H

#include "Grid_View.h"

class Global_View : public Grid_View {
public:
    Global_View();

    void draw() override;

    // Setters should never be called for Global_Views
    // assert(0) in implementation
    void set_size(int size_) override;
    void set_scale(double scale_) override;
    void set_origin(Point origin_) override;
    void set_defaults() override;
    
protected:
    // print the information of the Global_View
    void print_info() override;
    
    // do nothing for Global View. Moreover, the outsiders should be empty
    void print_outsiders(std::vector<std::string> outsiders) override;
};

#endif 
