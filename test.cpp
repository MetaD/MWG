//
//
//
//
//#include "Composite.h"
//#include "Commander.h"
//#include "Soldier.h"
//#include "Peasant.h"
//#include "Archer.h"
//
//#include "Agent_factory.h"
//
//#include <iostream>
//#include <string>
//#include <map>
//
//using namespace std;
//
//
//
//int main()
//{
//    
//    
//    try{
//
//    map<string, shared_ptr<Component>> container;
//    
//    shared_ptr<Agent> merry;
//    container["Pippin"] = create_agent("Pippin", "Peasant", Point(5., 10.));
//    container["Merry"] = merry = create_agent("Merry", "Peasant", Point(0., 25.));
//    container["Zug"] = create_agent("Zug", "Soldier", Point(20., 30.));
//    container["Bug"] = create_agent("Bug", "Soldier", Point(15., 20.));
//    container["Iriel"] = create_agent("Iriel", "Archer", Point(20., 38.));
//    
//    shared_ptr<Component> group1 = shared_ptr<Composite>(new Composite("group1"));
//
//    group1->add_component(container["Pippin"]);
//    group1->add_component(container["Bug"]);
//    group1->add_component(container["Iriel"]);
//    group1->add_component(container["Bug"]);
//
//    
//    shared_ptr<Component> group2 = shared_ptr<Composite>(new Composite("group2"));
//
//    group1->move_to(Point(0, 25));
//        
//        for(auto &i:container){
//            i.second->update();
//            i.second->update();
//            i.second->update();
//            i.second->update();
//            i.second->describe();
//        }
//        
//        
//    group1->start_attacking(merry);
//    
//    container["group1"] = group1;
//    container["group2"] = group2;
//
//    for(auto &i:container){
//        i.second->describe();
//    }
//    
//
//    }catch(...){
//        
//    }
//    
//    return 0;
//}
//
//
//
