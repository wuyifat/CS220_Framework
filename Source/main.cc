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
//////////////////////////////////debuging////////////////////////////////////
//	cout << "this is after remove_m_connection"<<endl;
//        m.get_node(1,2)->remove_m_connection(m.get_node(2,2));
//	m.get_node(1,2)->display_edges();
//	m.display_size();
	m.set_blocker(first_problem->get_blockers());//set blockers
	m.set_connection(first_problem->get_connections());//set connetions
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
       
*/
	Map* mm = &m;
        Algorithm::Lee l(mm);
        cout << "there are "<<l.get_connection().size()<< " pair of sources and sinks "<<endl;
        l.forward();
	mm->display_map();
        cout << " Finished" <<endl<<endl<<endl; 

//------------------------display path--------------------------

        vector<Path*> p = l.get_paths();
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

	delete first_problem;

	return 0;
}
