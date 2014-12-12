/* Filename: threebit.h
 * Author: Deen Ma
 * Date: 12/12/2014
 * Description:
 data:
 number: the number of pairs of source and sink
 ruben-trace: whether we choose minimum turn or not. 1 is min-turn and 0 is not
 cross: whether we allow cross among paths or not. 1 allows while 0 not allow
 path: the output of the function. it contains a vector of paths.
 connection: the input of the function, the source-sink pairs information included
 methods:
 run(): the complete step for bidirection, from the expansion of source and sink, and the trackback.
 traceback(Path* path): this is the trackback when we do NOT consider min-turn.
 traceback(Path* path, int i): this is the trackback when we CONSIDER min-turn.
 min_node(): return the surrounding node with the minimal cost value.
 direction(): return the direction of two nodes. 0 up, 1 left, 2 down, 3 right
 */

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

namespace Algorithm{
    class Twobit{
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
        Twobit(Map* m);
        //  ~Twobit();
                
        bool set_cross();
        bool set_min_turn();
        void run();
        void traceback(int fl,Path* path); // not min-turn
        void traceback(int fl,Path* path,int i) ; // min-turn
        Map* get_map();
        vector<Path*> get_paths();
        vector<Connection> get_connection();
        Node* min_node(vector<Node*> others); //return the surrounding node with the minimal cost value.
        int direction(Point source,Point sink); // return the direction of two nodes. 0 up, 1 left, 2 down, 3 right.
    };
}
#endif
