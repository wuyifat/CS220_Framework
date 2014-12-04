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
            vector<Node*> source;
            vector<Node*> sink;
        public:
            Map(int width, int height);
            ~Map();

            //Accessor
            int get_width();
            int get_height();
            Node* get_node(int x, int y);
            Node* get_node(Point coord);
            vector<Path*> get_paths();
            Path* get_path(int i);
	    bool is_blocker(int x,int y);
            bool is_blocker(Point coord);
            vector<Connection> get_connection();
            /* Mutators */
            void replace_node(Node* replacement_node);
            void set_paths(vector<Path*> paths);
            void add_path(Path* path);
            void replace_path(int i, Path* path);
            void remove_path(int i);
            void set_blocker(vector<Blocker> b);
            void display_map();
            void display_size();
            void set_connection(vector<Connection> c);
    };
}
#endif //_MAP_BASE_H_
