#ifndef HEALTH_VIEW_H
#define HEALTH_VIEW_H

// The Health_View is a list of objects and their health

#include "Info_View.h"

class Health_View: public Info_View {
public:

    // Save the supplied name and health for future use in a draw() call
    void update_health(const std::string& name, int health) override;
    
protected:
    // print "Health"
    void print_info() override;
};

#endif 
