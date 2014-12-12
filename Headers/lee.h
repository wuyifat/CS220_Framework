/*Filename:<lee.h>
*Author:Shuheng Li
*Date:12/12/2014
*Description:Achieve Lee Algorthm to found several paths among more than one pair of sources and sinks
*/
#ifndef _LEE_BASE_H_
#define _LEE_BASE_H_

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
    class Lee{
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
            Lee(Map* m);
          //  ~Lee();

            bool set_min_turn();//if the value is 1, use minimize turn traceback
            bool set_cross();//if value is 0 a new path can't get through old path
            void run();
            void traceback(Path* path);//regular trace back
            void traceback(Path* path,int i) ;//ruben trace back
            Map* get_map();
            vector<Path*> get_paths();
	    vector<Connection> get_connection();
	    Node* min_node(vector<Node*> others);//found minimize cost among all neigor
	    int direction(Point source,Point sink);//get direction
    };
}
#endif
