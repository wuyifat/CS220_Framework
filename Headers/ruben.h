/*Filename:<ruben.h>
*Author:Shuehng Li
*Date:12/12/2014
*Description:Achieved Ruben Algorithm in grid routing
*/
#ifndef _RUBEN_BASE_H_
#define _RUBEN_BASE_H_

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
    class Ruben {
        private:
            Map* map;
            int number; //number of source = number of sink = number of path
            int cross; //number of source = number of sink = number of path
            vector<Path*> paths;
            vector<Connection> connection;
            vector<Node*> source;        
            vector<Node*> sink;
            
            void reset_map();        
        public:
            Ruben(Map* m);
          //  ~Ruben();

            void run();
            void traceback(Path* path);
            bool set_cross();
            int direction(Point source,Point sink);
            Map* get_map();
            vector<Path*> get_paths();
	    vector<Connection> get_connection();
            Node* min_node(vector<Node*> others);
    };
}
#endif
