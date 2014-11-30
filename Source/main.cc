
#include "../Headers/map.h"
#include "../Headers/edge.h"
#include "../Headers/problem_object.h"
#include "../Headers/node.h"
#include <time.h>
#include <cstdlib>
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;
using std::vector;
int main(int argc,char* argv[]) {

	// DO NOT CHANGE THIS SECTION OF CODE
	if(argc < 2) { cout << "Usage: ./grid_router <test_file>" << endl; }
	Utilities::ProblemObject* first_problem = new Utilities::ProblemObject(std::string(argv[1]));
	// EDIT FROM HERE DOWN

	//Create your problem map object (in our example, we use a simple grid, you should create your own)
	Utilities::Map m(first_problem->get_width(), first_problem->get_height());

	/*
	Note: we do not take into account the connections or blockers that exist in the Project Object
	You should be accouting for these in your problem map objects (you should not be using Grid). You
	should be using both the Node and Edge classes as the background for whatever problem map object
	you create.
	*/

	/*
	Run your algorithm after creating your problem map object. You should be returning from your algorithm 
	either a Path or a Netlist

	Path: a series of straight line segments, with a single source and a single sink
	Netlist: a series of stright line segments, with a single source and more than one sink
	*/

	//Note, we create random paths just as an example of how to create paths, netlists are created similarly
	


	m.set_blocker(first_problem->get_blockers());
        vector<Connection> connection = first_problem->get_connections();
	for(int i = 0; i < connection.size();i++){
		m.set_source(connection.at(i).source);//set source 's cost is -10
                m.set_sink(connection.at(i).sink);//set sink's cost is -20
                }
			cout << "(0,0) is cost is " <<m.get_node(0,0)->get_cost() << " the connection size is " << m.get_node(0,0)->connections_size() << endl;
			cout << "(0,1) is cost is " <<m.get_node(0,1)->get_cost() << " the connection size is " << m.get_node(0,1)->connections_size() << endl;
			cout << "(1,0) is cost is " <<m.get_node(1,0)->get_cost() << " the connection size is " << m.get_node(1,0)->connections_size() << endl;
			cout << "(1,1) is cost is " <<m.get_node(1,1)->get_cost() << " the connection size is " << m.get_node(1,1)->connections_size() << endl;
			cout << "(0,3) is cost is " <<m.get_node(0,3)->get_cost() << " the connection size is " << m.get_node(0,3)->connections_size() << endl;
			cout << "(0,2) is cost is " <<m.get_node(0,2)->get_cost() << " the connection size is " << m.get_node(0,2)->connections_size() << endl;
			cout << "(250,0) is cost is " <<m.get_node(250,0)->get_cost() << " the connection size is " << m.get_node(250,0)->connections_size() << endl;
			cout << "(250,100) is cost is " <<m.get_node(250,100)->get_cost() << " the connection size is " << m.get_node(250,100)->connections_size() << endl;

			cout << "(250,499) is cost is " <<m.get_node(250,499)->get_cost() << " the connection size is " << m.get_node(250,499)->connections_size() << endl;
	delete first_problem;

	return 0;
}
