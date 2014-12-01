#ifndef _LEE_BASE_H_
#define _LEE_BASE_H_

#include "edge.h"
#include "node.h"
#include "path.h"
#include "map.h"
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
    class Lee{
        private:
            Map* map;
            int number; //number of source = number of sink = number of path
            vector<Path*> paths;
            vector<Node*> source;
            vector<Node*> sink;
             
        public:
            Lee(Map* m);
          //  ~Lee();
            vector<Path*> forward();
            Map* get_map();
    };
}
#endif
