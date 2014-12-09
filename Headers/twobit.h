#ifndef _TWOBIT_BASE_H_
#define _TWOBIT_BASE_H_

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
    class Twobit {
        private:
            Map* map;
            int number; //number of source = number of sink = number of path
            vector<Path*> paths;
            vector<Connection> connection;
            vector<Node*> source;        
            vector<Node*> sink;        
        public:
            Twobit(Map* m);
          //  ~Twobit();

            void forward();
            void traceback(int same,Path* path);
            Map* get_map();
            vector<Path*> get_paths();
	    vector<Connection> get_connection();
    };
}
#endif
