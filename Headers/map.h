/*Filename:<map.h>
*Author:Shuheng Li
*Date:12/12/2014
*Description:Placing the map, blocker,source and sink
*/
#ifndef _MAP_BASE_H_
#define _MAP_BASE_H_

#include "node.h"
#include "path.h"
#include <vector>
#include "problem_object.h"

using std::cerr;
using std::endl;
using std::string;
using Utilities::Node;
using Utilities::Path;

namespace Utilities {
    class Map{
        private:
            vector<vector<Node*> > map;
            vector<Connection> connection;
            vector<Path*> paths;

        public:
            Map(ProblemObject* problem);
            ~Map();

            //Accessor
            int get_width();
            int get_height();
            Node* get_node(int x, int y);
            Node* get_node(Point coord);
            vector<Path*> get_paths();
            Path* get_path(int i);
            vector<Connection> get_connection();

            /* Mutators */
            void set_paths(vector<Path*> paths);
            void add_path(Path* path);
            void replace_path(int i, Path* path);
            void remove_path(int i);
            void set_blocker(vector<Blocker> b);
	    void add_blocker(Path* p);//Use for adding old path as a blocker
            void display_map();    //display cost
            void display_size();   //display connection size
            void display_md();     //display distance
            void display_manhattan();    //display manhantan distance
            void display_flag();    // display whether a node is visited
            void display_detour();    //display detour use for hadlock algorithm 
            void set_connection(vector<Connection> c);
    };
}
#endif //_MAP_BASE_H_
