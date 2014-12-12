/* Filename: main.cc
 * Author: Yi Wu, Shuheng Li, Deen Ma
 * Date: 12/12/2014
 * Description: our group members:
 */

#include "../Headers/map.h"
#include "../Headers/edge.h"
#include "../Headers/problem_object.h"
#include "../Headers/node.h"
#include "../Headers/lee.h"
#include "../Headers/threebit.h"
#include "../Headers/korn.h"
#include "../Headers/twobit.h"
#include "../Headers/ruben.h"
 #include "../Headers/hadlock.h"
#include "../Headers/bidirection.h"
#include <time.h>
#include <cstdlib>
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;
using std::vector;
using std::cin;
int main(int argc,char* argv[]) {
    // DO NOT CHANGE THIS SECTION OF CODE
    if(argc < 2) { cout << "Usage: ./grid_router <test_file>" << endl; }
    Utilities::ProblemObject* first_problem = new Utilities::ProblemObject(std::string(argv[1]));

    // initailizae the map
    Utilities::Map m(first_problem);

    cout << "Mapping the input file..."<<endl;
    cout << "Mapping Blockers, source and sinks file..."<<endl<<endl;
//------------------Set the blockers and connection----------------
    Map* mm = &m;
    mm->display_map();
    cout << "Finished Mapping, Starting ";

//------------------Run different algorithm-----------------------

    cout << "Lee Algorithm." <<endl<<endl; Algorithm::Lee l(mm);
//    cout << "threebit Algorithm." <<endl<<endl; Algorithm::Threebit l(mm);
//    cout << "twobit Algorithm." <<endl<<endl; Algorithm::Twobit l(mm);
//    cout << "Ruben Algorithm." <<endl<<endl; Algorithm::Ruben l(mm);
//    cout << "Hadlock Algorithm." <<endl<<endl; Algorithm::Hadlock l(mm);
//    cout << "Korn Algorithm." <<endl<<endl; Algorithm::Korn l(mm);
//    cout << "bidirection Algorithm." <<endl<<endl; Algorithm::Bidirection l(mm);

      l.run();
//------------------------display path--------------------------
    vector<Path*> p = l.get_paths();
    for (unsigned i = 0;i < p.size();i++) {
        cout << "\tPath " << i+1 << " of " << p.size() << ":" << endl;
        p.at(i)->display_path();
    }

    cout << " Finished" <<endl<<endl<<endl; 
    return 0;
}
