
#include "../Headers/grid.h"
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
	Utilities::Grid g(first_problem->get_width(), first_problem->get_height());

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
	



//**************************Map Blockers******************************
	vector<Blocker> blocker;
	int x,y;//blocker location
	blocker = first_problem->get_blockers();//get blockdrs number
	for ( int blocker_num = 0; blocker_num < blocker.size(); blocker_num++){
		x = blocker.at(blocker_num).location.x;
		y = blocker.at(blocker_num).location.y;
		if(x < 0 && x>g.get_width()){//check x boundary
			cout << "x coord is not valid" << endl; }
		if( y < 0 && y > g.get_height()){//check y boundary
			cout << "x coord is not valid" << endl; 
		}
		for( int i = 0; i < blocker.at(blocker_num).height;i++ ){//blocker height point
			x = blocker.at(blocker_num).location.x;
			for( int j = 0; j < blocker.at(blocker_num).width;j++ ){//blocker width point
				g.get_node(x,y)->set_cost(-1);//set source 's cost is -10
/*				Node* new_node = new Node(x,y,-1);//if the node is blocker, the cost is -1
				g.replace_node(new_node);//replace the node
//Now we need to add connetions to the new Node
				if (x > 0 && x < g.get_width()){
					Utilities::Edge* left = new Utilities::Edge(new_node,g.get_node(x-1,y));
					new_node->add_connection(left);
				}
//debug				cout <<"after add :" << g.get_node(x-1,y)->connections_size()<< endl;
				if (y > 0 && y < g.get_height()){
					Utilities::Edge* up = new Utilities::Edge(new_node,g.get_node(x,y-1));
					new_node->add_connection(up);
				}	

				if(i+1 == blocker.at(blocker_num).height && i+1 < g.get_height()){//woking on the last row of blockers
					Utilities::Edge* boundary_up = new Utilities::Edge(g.get_node(x,y+1),g.get_node(x,y));
					g.get_node(x,y+1)->add_connection(boundary_up);
				}
*/				x++;
			}
/*				if(x < g.get_width()){//woking on last colunm of blockers
					Utilities::Edge* boundary_left = new Utilities::Edge(g.get_node(x,y),g.get_node(x-1,y));
					g.get_node(x,y)->add_connection(boundary_left);
				}
*/			y++;
		}
	}

			cout << "(0,0) is cost is " <<g.get_node(0,0)->get_cost() << " the connection size is " << g.get_node(0,0)->connections_size() << endl;

			cout << "(0,1) is cost is " <<g.get_node(0,1)->get_cost() << " the connection size is " << g.get_node(0,1)->connections_size() << endl;
			cout << "(1,0) is cost is " <<g.get_node(1,0)->get_cost() << " the connection size is " << g.get_node(1,0)->connections_size() << endl;
			cout << "(1,1) is cost is " <<g.get_node(1,1)->get_cost() << " the connection size is " << g.get_node(1,1)->connections_size() << endl;
//**************************Map Connections******************************
	vector<Connection> connection = first_problem->get_connections();
	for(int i = 0; i < connection.size();i++){
		if(connection.at(i).source == connection.at(i).sink){
			cout << connection.at(i).name << " has a source and sink in same position. Please change the position" << endl;
		}
		if(g.get_node(connection.at(i).source)->get_cost() != 0){
			cout << connection.at(i).name << " has an invalid source position" << endl;
		}
		if(g.get_node(connection.at(i).sink)->get_cost() != 0){
			cout << connection.at(i).name << " has an invalid sink position" << endl;
		}
		
		else{
		g.get_node(connection.at(i).source)->set_cost(-10);//set source 's cost is -10
		g.get_node(connection.at(i).sink)->set_cost(-20);//set sink's cost is -20
		}
	}


			cout << "(0,0) is cost is " <<g.get_node(0,0)->get_cost() << " the connection size is " << g.get_node(0,0)->connections_size() << endl;


			cout << "(250,0) is cost is " <<g.get_node(250,0)->get_cost() << " the connection size is " << g.get_node(0,0)->connections_size() << endl;
			cout << "(250,499) is cost is " <<g.get_node(250,499)->get_cost() << " the connection size is " << g.get_node(0,0)->connections_size() << endl;

			cout << "(250,500) is cost is " <<g.get_node(250,500)->get_cost() << " the connection size is " << g.get_node(0,0)->connections_size() << endl;
	vector<Path*> paths;
	srand(time(NULL));
	int number_paths = first_problem->get_connections().size();
	cout << "Creating " << number_paths << " paths...";
	for (int i = 0;i < number_paths;i++) {
		Path* new_path = new Path();
		int x = rand() % first_problem->get_width();
		int y = rand() % first_problem->get_height();
		int path_length = 1+rand()%10;
		for (unsigned j = 0;j < path_length;j++) {
			bool direction = rand()%2;
			Point head(x,y);
			direction?x+=1:y+=1;
			Point tail(x,y);
			PathSegment* new_segment = new PathSegment(head,tail);
			new_path->add_segment(new_segment);
		}
		paths.push_back(new_path);
	}
	cout << "Completed." << endl;
	cout << "add path:" << endl;


	g.set_paths(paths);
//	g.get_path(0);
	//Print the paths/netlists that you have return from your algorithm
	for (unsigned i = 0;i < paths.size();i++) {
		cout << "\tPath " << i+1 << " of " << paths.size() << ": (" 
			 << paths.at(i)->at(0)->get_source().x << "," << paths.at(i)->at(0)->get_source().y << ") ";
		for (unsigned j = 0;j < paths.at(i)->size();j++) {
			cout << "(" << paths.at(i)->at(j)->get_sink().x << "," << paths.at(i)->at(j)->get_sink().y << ") ";
		}
		cout << endl;
		Path* temp = paths.at(i);
		delete temp;
	}
	paths.clear();

	delete first_problem;

	return 0;
}
