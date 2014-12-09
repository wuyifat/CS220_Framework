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
        vector<Path*> paths;
        vector<Connection> connection;
        vector<Node*> source;
        vector<Node*> sink;
        vector<Node*> meetPointsSource; // the point when source expansion meet sink expansion
        vector<Node*> meetPointsSink; // the point when source expansion meet sink expansion
    public:
        Bidirection(Map* m);
        ~Bidirection();
        void forward();
        void traceback(int curConnection);
        vector<Path*> get_paths();
        //        void display();
    };
}
#endif
