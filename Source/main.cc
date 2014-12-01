#include "../Headers/map.h"
#include "../Headers/edge.h"
#include "../Headers/problem_object.h"
#include "../Headers/node.h"
#include "../Headers/lee.h"
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
	Utilities::Map m(first_problem->get_width(), first_problem->get_height());

	m.display();
        cout << " Before set source sink and blockers" <<endl<<endl<<endl; 
	m.set_blocker(first_problem->get_blockers());
        vector<Connection> connection = first_problem->get_connections();
	for(int i = 0; i < connection.size();i++){
		m.set_source(connection.at(i).source);//set source 's cost is -10
                m.set_sink(connection.at(i).sink);//set sink's cost is -20
                }
        Map* mm =&m;
		////////////////////////////////////////////
        Algorithm::Lee l(mm);
/*        vector<Path*> p = l.forward();
        for (unsigned i = 0;i < p.size();i++) {
                cout << "\tPath " << i+1 << " of " << p.size() << ": ("
                         << p.at(i)->at(0)->get_source().x << "," << p.at(i)->at(0)->get_source().y << ") ";
                for (unsigned j = 0;j < p.at(i)->size();j++) {
                        cout << "(" << p.at(i)->at(j)->get_sink().x << "," << p.at(i)->at(j)->get_sink().y << ") ";
                }
                cout << endl;
                Path* temp = p.at(i);
                delete temp;
        }
       
*/      l.forward();
//	mm = l.get_map();
	mm->display();
	
        cout << " Finished" <<endl<<endl<<endl; 
	delete first_problem;

	return 0;
}
