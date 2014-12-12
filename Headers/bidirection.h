/* Filename: bidirection.h
* Author: Deen Ma
* Date: 12/12/2014
* Description:
Note that minimum turn and whether allowing cross are disabled in this function
data:
 path: the output of the function. it contains a vector of paths. 
 connection: the input of the function, the source-sink pairs information included
 meetPointsSource: a vector of points when source expansion meet sink expansion
 meetPointsSink: a vector of points when sink expansion meet source expansion
methods:
 run(): the complete step for bidirection, from the expansion of source and sink, and the trackback.
 traceback(): the traceback process, included in run().
*/

#ifndef _BIDIRECTION_BASE_H_
#define _BIDIRECTION_BASE_H_

#include "edge.h"
#include "node.h"
#include "path.h"
#include "map.h"
#include "problem_object.h"
#include "point.h"
#include <queue>
#include <vector>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;
using std::queue;

using Utilities::Node;
using Utilities::Path;
using Utilities::Map;

namespace Algorithm{
    class Bidirection{
    private:
        Map* map;
        int number; //number of source = number of sink = number of path
        vector<Path*> paths; // output
        vector<Connection> connection; // input, source-sink pair information included
        vector<Node*> source;
        vector<Node*> sink;
        vector<Node*> meetPointsSource; // the point when source expansion meet sink expansion
        vector<Node*> meetPointsSink; // the point when source expansion meet sink expansion
    public:
        Bidirection(Map* m);
        ~Bidirection();
        void run();
        void traceback(int curConnection);
        vector<Path*> get_paths();
        //        void display();
    };
}
#endif
