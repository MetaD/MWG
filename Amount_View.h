#ifndef AMOUNT_VIEW_H
#define AMOUNT_VIEW_H

// Amount_View is a list of objects and the food amount they have

#include "Info_View.h"

class Amount_View: public Info_View {
public:
	// print "Amounts"
    void print_info() override;
    
    // Save the supplied name and amount for future use in a draw() call
    void update_amount(const std::string& name, double amount) override;
};

#endif 
