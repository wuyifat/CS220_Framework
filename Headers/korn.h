#ifndef _KORN_BASE_H_
#define _KORN_BASE_H_

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

namespace Algorithm {
    class Korn {
        private:
            Map* map;
            int number;    //number of source = number of sink = number of path
            int cross;    //number of source = number of sink = number of path
            double alpha;    // the overpull number of Korn's cost
            vector<Path*> paths;
            vector<Connection> connection;
            vector<Node*> source;        
            vector<Node*> sink;
            
            void reset_map();        
        public:
            Korn(Map* m);
          //  ~Korn();

            void run();
            void traceback(Path* path);
            bool set_alpha();
            bool set_cross();
            double get_alpha();
            int direction(Point source,Point sink);
            Map* get_map();
            vector<Path*> get_paths();
	    vector<Connection> get_connection();
           
    };
}
#endif
