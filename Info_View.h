#ifndef INFO_VIEW_H
#define INFO_VIEW_H

// Info_View is a list of object names associated with their data (a double)

#include "View.h"
#include <map>

class Info_View: public View {
public:
	// prints out the current information
    void draw() override;

    // Discard the saved information
    void clear() override { info.clear(); }

    // Remove the object name and its data
    void update_remove(const std::string& name) override;

protected:
    Info_View() {};

    // print a title for the type of information
    virtual void print_title() = 0;

    // used by derived class to set the datum for an object
    void update_info(const std::string& name, double information);

private:
    std::map<std::string, double> info;		// the name and numerical data of objects
};

#endif 
