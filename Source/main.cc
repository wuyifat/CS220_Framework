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

       
        m.get_node(2,2)->display_edges();
        cout << " node (1,2) size is "<< m.get_node(1,2)->connections_size();
 	Node* t = m.get_node(2,2);
 	Node* t1 = m.get_node(1,2);
//	m.display();
//        cout << " Before set source sink and blockers" <<endl<<endl<<endl;
 
//	m.set_blocker(first_problem->get_blockers());
        t->display_node();
        t->display_edges();
 	t1->display_node();
        t1->display_edges();


        cout << " the (2,2) wether contain the edge  "<< t->connections_contains(t->connections_at(0))<<endl;
        m.get_node(1,2)->display_node();
	cout << endl;
        m.get_node(1,2)->display_edges();
        t->connections_at(0)->reverse()->display_edge();

	
        m.get_node(1,2)->display_node();
        m.get_node(1,2)->display_edges();
 
        cout << " the (1,2) now check reverse edge or not "<< m.get_node(1,2)->connections_contains(t->connections_at(2)->reverse())<<endl;

        cout << " the (1,2) now check original edge "<< m.get_node(1,2)->connections_contains(t->connections_at(2))<<endl;
//        m.replace_node(t);
//       for(int ii = 0; ii < m.get_node(2,2)->connections_size();ii++){
        Node* tt = m.get_node(2,2)->connections_at(0)->get_end(m.get_node(2,2));
        Utilities::Edge* cc = new Utilities::Edge(m.get_node(2,2),m.get_node(1,2));
        cout<< "cc the edge's head is ";
        cc->get_head()->display_node();
         cout<< "cc the edge's tail is ";
        cc->get_tail()->display_node();
       cout<< "now reverse cc!!!!!!!!!!!!!!"<<endl;
        Utilities::Edge* ccc= cc->reverse(); 
	cout<< "ccc the edge's head is ";
        ccc->get_head()->display_node();
         cout<< "ccc the edge's tail is ";
        ccc->get_tail()->display_node();      
 
        cout << "Node(1,2 )contain edge(22) to (12) size is "<< m.get_node(1,2)->connections_size()<<"     "<<m.get_node(1,2)->connections_contains(cc)<<endl;
        cout << "(1,2 )the size is "<< m.get_node(1,2)->connections_size()<<"     "<<m.get_node(1,2)->connections_contains(ccc)<<endl;
       cout << "the node (2,2) neibor is "<<endl;
m.get_node(2,2)->connections_at(0)->get_end(m.get_node(2,2))->display_node();
        m.get_node(2,2)->remove_connection(m.get_node(2,2)->connections_at(0));
//        delete m.get_node(2,2);
	cout<< "NOw I remove all connection of node (2,2) the connection size is "<<m.get_node(2,2)->connections_size()<<endl;

        cout << "after the size is "<< m.get_node(2,2)->connections_size()<<endl;

        cout << " (2,3) the size is "<< m.get_node(2,3)->connections_size()<<"     "<<m.get_node(2,3)->connections_contains(cc)<<endl;
        cout << " (2,1) size is "<< m.get_node(2,1)->connections_size()<<"     "<<m.get_node(2,1)->connections_contains(cc)<<endl;
        cout << "(3,2) the size is "<< m.get_node(3,2)->connections_size()<<"     "<<m.get_node(3,2)->connections_contains(cc)<<endl;
       
        cout << "(1,2 )the size is "<< m.get_node(1,2)->connections_size()<<"     "<<m.get_node(1,2)->connections_contains(ccc)<<endl;
//        cout << " the m.get_node(2,2) size si "<<m.get_node(2,2)->connections_size() <<"and the II valueis " << ii<< endl; 

        cout << " the m.get_node(2,2) size si "<<t->connections_size() << endl; 
//}

      for(int i = 0; i < m.get_node(1,2)->connections_size();i++){
	m.get_node(1,2)->connections_at(i)->get_end(m.get_node(1,2))->display_node();
        cout<<"           the cost is  " <<m.get_node(1,2)->connections_at(i)->get_end(m.get_node(1,2))->get_cost()<<endl;

        cout<<"           the size is  " <<m.get_node(1,2)->connections_at(i)->get_end(m.get_node(1,2))->connections_size()<<endl;
}

       for(int i = 0; i < m.get_node(1,2)->connections_size();i++){
	m.get_node(2,1)->connections_at(i)->get_end(m.get_node(2,1))->display_node();
}
        vector<Connection> connection = first_problem->get_connections();
	for(int i = 0; i < connection.size();i++){
		m.set_source(connection.at(i).source);//set source 's cost is -10
                m.set_sink(connection.at(i).sink);//set sink's cost is -20
                }

		////////////////////////////////////////////

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
        Map* mm =&m;
        Algorithm::Lee l(mm);
//        l.forward();
	mm->display_map();
        cout << " Finished" <<endl<<endl<<endl; 
	delete first_problem;

	return 0;
}
