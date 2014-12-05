#include "../Headers/map.h"
#include "../Headers/edge.h"
#include "../Headers/problem_object.h"
#include "../Headers/node.h"
#include "../Headers/lee.h"
#include "../Headers/threebit.h"
#include "../Headers/korn.h"
#include "../Headers/twobit.h"
#include "../Headers/ruben.h"
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

	// initailizae the map
	Utilities::Map m(first_problem->get_width(), first_problem->get_height());

        cout << "Mapping the input file..."<<endl;
        cout << "Mapping Blockers, source and sinks file..."<<endl<<endl;
//------------------Set the blockers and connection----------------
        m.set_blocker(first_problem->get_blockers());//set blockers
	m.set_connection(first_problem->get_connections());//set connetions
	Map* mm = &m;
        cout << "Finished Mapping, Starting Algorithm."<<endl<<endl;
//------------------Run different algorithm-----------------------
//        Algorithm::Lee l(mm);
//        Algorithm::Threebit l(mm);
//        Algorithm::Twobit l(mm);
//        Algorithm::Ruben l(mm);
        Algorithm::Korn l(mm);
        l.forward();
        cout<<"the node          dis " <<       mm->get_node(4,3)->get_distance()<<endl;
//------------------------display path--------------------------
 
        mm->display_md();
        mm->display_flag();       vector<Path*> p = l.get_paths();
        for (unsigned i = 0;i < p.size();i++) {
                cout << "\tPath " << i+1 << " of " << p.size() << ":" << endl;
                p.at(i)->display_path();
        }

        cout << " Finished" <<endl<<endl<<endl; 
	delete first_problem;

	return 0;
}
