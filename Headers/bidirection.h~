#ifndef _BIDIRECTION_BASE_H_
#define _BIDIRECTION_BASE_H_

#include "node.h"
#include "path.h"
#include "map.h"
#include <vector>

using Utilities::Node;
using Utilities::Path;
using Utilities::Map;

namespace Algorithm {
    class Bidirection{
        private:
            Map map;
            int number; //number of source = number of sink = number of path
            vector<Path*> paths;
            vector<Node*> source;
            vector<Node*> sink;
        public:
            Bidirection(Map m);
            ~Bidirection();
            vector<Node*> result();
    }
}
#endif
