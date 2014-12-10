#ifndef _THREEBIT_BASE_H_
#define _THREEBIT_BASE_H_

#include "edge.h"
#include "node.h"
#include "path.h"
#include "map.h"
#include "problem_object.h"
#include <queue>
#include <vector>
#include <iostream>

using std::vector;
using std::cerr;
using std::endl;


using std::queue;
using Utilities::Node;
using Utilities::Path;
using Utilities::Map;

namespace Algorithm{
    class Threebit{
    private:
        Map* map;
        int number; //number of source = number of sink = number of path
	    int ruben_trace;//if this value = 1,use ruben trace back
	    int cross;//if cross = 1, source and sink can unlimit cross if 0 they can't
        vector<Path*> paths;
        vector<Connection> connection;
        vector<Node*> source;
        vector<Node*> sink;
    public:
        Threebit(Map* m);
        //  ~Threebit();
        
        
	    void set_ruben_trace(int i);
	    void set_cross(int i);
        void run();
        void traceback(Path* path);
        void traceback(Path* path,int i) ;
        Map* get_map();
        vector<Path*> get_paths();
	    vector<Connection> get_connection();
	    Node* min_node(vector<Node*> others);
	    int direction(Point source,Point sink);
    };
}
#endif
