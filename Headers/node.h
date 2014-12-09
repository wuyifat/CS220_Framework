#ifndef _NODE_BASE_H_
#define _NODE_BASE_H_

#include "../Headers/point.h"
#include <vector>
#include <iostream>

using std::vector;
using std::cerr;
using std::endl;

namespace Utilities {
    class Edge;

    class Node {
        private:
            Point coord;
            vector<Edge*> connections;
            int cost;
	    int is_visited; // This is used mainly in bidirection: -1: block; 0: not visited yet; 1: visited by source
                            // expansion; 2: visited by sink expansion.
            double distance;
            double m_d;
            int flag;
            int detour;
            /* Private Mutators */
            void add_connection_mirrored(Edge*);
            void updata_d();
        public:
            /* Constructors/Destructors */
            Node(int x, int y, int cost=0);
            Node(Point coord, int cost=0);
            ~Node();

            /* Accessors */
            Point get_coord();
            int get_x();
            int get_y();
            int get_flag();
            int get_detour();
            unsigned connections_size();
            bool connections_empty();
            bool connections_contains(Edge* edge);
	    Edge* connections_at(unsigned index);
            int get_cost();
	    int get_is_visited();
            double get_distance();

            /* Mutators */
            void set_flag(int i);
            void set_detour(int i);
            void set_coord(int x, int y);
            void set_x_coord(int x);
            void set_y_coord(int y);
            void set_coord(Point coord);
            void set_connections(vector<Edge*> connections);
            void add_connection(Edge* connection);
            void set_cost(int cost);
	    void set_is_visited(int isVisited);
            void remove_connection(Edge* connection);
            void display_node();
            void display_edges();
            void remove_m_connection(Node* node);
            void set_m_d(Point sink,double i);
            void set_m_d(double i);
    };
}

#endif  //_NODE_BASE_H_
