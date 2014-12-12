/*Filename:<hadlock.h>
*Author:Shuheng Li
*Date:12/12/2014
*Description:Achieve Hadlock Algorithm to find path from source to sink
*/
#ifndef _HADLOCK_BASE_H_
#define _HADLOCK_BASE_H_

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
    class Hadlock{
        private:
            Map* map;
            int number; //number of source = number of sink = number of path
            int cross; //set value allow new path to pass old path or not
            vector<Path*> paths;
            vector<Connection> connection;
            vector<Node*> source;        
            vector<Node*> sink;
            
            void reset_map();        
        public:
            Hadlock(Map* m);
          //  ~Hadlock();

            void run();
            bool set_cross();
            void traceback(Path* path);
            int direction(Point source,Point sink);//get direction
            Map* get_map();
            vector<Path*> get_paths();
	    vector<Connection> get_connection();
    };
}
#endif
