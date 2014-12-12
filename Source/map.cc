/* Filename: map.cc
 * Author: Deen Ma
 * Date: 12/12/2014
 * Description:
 Map::Map(): constructor. Connection and Blockers are set. In each node of the map, the connection of this node is set. The node is connected with all its neibor nodes except for block nodes.
 Map::~Map(): destructor. We need not only delete the map itself, but delete all the nodes as well.
 set_blocker():  Set blockers inside the map.
 set_connection(): Read the source-sink pair from the c, which is a vector of pairs, to the map.
 add_blocker(): This function is to treat the completed path as blocker. When we don't allow the intersection between paths, our method is just to treat the previous connected paths as blockers.
 display_md(): return the distance = manhattan distance + the already-expanded distance
 display_manhattan(): return the manhattan distance
 */

#include "../Headers/map.h"
#include "../Headers/edge.h"
#include "../Headers/claim.h"
#include "../Headers/problem_object.h"
#include <iostream>
using std::cout;
using std::endl;
//Takes an x and y coordinate as input and creates a grid of that size filled with default nodes
Utilities::Map::Map(ProblemObject* problem) {
    for(int y = 0; y < problem->get_height(); y++) {
        vector<Node*> current_row;
        for(int x = 0; x < problem->get_width(); x++) {
            Node* new_node = new Node(x,y);
            if (x > 0) {
                Edge* west = new Edge(new_node,current_row.at(current_row.size()-1));
                new_node->add_connection(west);
            }
            if (y > 0) {
                Edge* north = new Edge(new_node,map.at(y-1).at(x));
                new_node->add_connection(north);
            }
            current_row.push_back(new_node);
        }
        this->map.push_back(current_row);
    }
    this->set_blocker(problem->get_blockers());//set blockers
    this->set_connection(problem->get_connections());//set connetions
}

//Destructs the grid by deleting each node individually, the node destructors will delete their own set of edges
Utilities::Map::~Map() {
    int width = this->get_width();
    int height = this->get_height();
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            delete map.at(y).at(x);
        }
    }
}

int Utilities::Map::get_width() {
    return map.empty()?0:map.at(0).size();
}

int Utilities::Map::get_height() {
    return this->map.size();
}

Node* Utilities::Map::get_node(int x, int y) {
    if(y >= this->map.size()) {
        claim("Attemping to access a node outside of the grid's range (y-value out of range)", kError);
            return NULL;
    }
    if(x >= this->map.at(y).size()) {
        claim("Attemping to access a node outside of the map's range (x-value out of range)", kError);
            return NULL;
    }
    return this->map.at(y).at(x);      //at(...) will throw an out of range exception
}

Node* Utilities::Map::get_node(Point coord) {
    return this->get_node(coord.x, coord.y);
}

vector<Path*> Utilities::Map::get_paths() {
    return this->paths;
}

Path* Utilities::Map::get_path(int i) {
    if(i >= paths.size()) {
        claim("Attempting to access a path outside of the path list's range", kError);
    }
    return this->paths.at(i);           //at(...) will throw an out of range exception
}


/*
Since each node has an x/y coordinate, if you pass a Node* into replace node, it will take the node at the passed in
Nodes location, delete it, and then place the passed in node into the map at its proper location.
*/

void Utilities::Map::set_paths(vector<Path*> paths) {
    this->paths = paths;
}

void Utilities::Map::add_path(Path* path) {
    this->paths.push_back(path);
}

void Utilities::Map::replace_path(int i, Path* path) {
    if(i >= this->paths.size()) {
        claim("Attemping to replace path outside of the path list's range", kError);
    }
    paths.at(i) = path;
}

void Utilities::Map::remove_path(int i) {
    if(i >= paths.size()) {
          claim("Attempting to remove a path outside of the path list's range", kError);
    }
    vector<Path*>::iterator it = this->paths.begin();
    it += i;
    paths.erase(it);
}

void Utilities::Map::set_blocker(vector<Blocker> b) {
/*
 Set blockers inside the map. 
 input: the vector of blockers
 output: the value of get_cost and is_visited of those blocked nodes are set to -1.
 We not only set the property of blocked nodes, but also checked whether the block is out-of-bound, and whether two blocks overlaps (In our program, it will return an error).
 When we add a block, we remove some connections (for example, the connection between a normal node and a blocked node).
 */
    int x,y;    //blocker location
    for ( int blocker_num = 0; blocker_num < b.size(); blocker_num++) {
        x = b.at(blocker_num).location.x;
        y = b.at(blocker_num).location.y;

        //check x boundary   
        if(x < 0 || x > this->get_width()) {
            claim( "blocker x coord is not valid",kError);
        }
        //check y boundary 
        if( y < 0 || y > this->get_height()) {
            claim( "blocker y coord is not valid",kError);
        }
        
        //check block boundary
        if(x+b.at(blocker_num).width>this->get_width()) {
            claim("Current block is too big",kError);
            exit(0);
        }
        if(y+b.at(blocker_num).height>this->get_height()) {
            claim("Current block is too big",kError);
            exit(0);
        }


        // set each element in a blocker cost = -1 and delete its connections with adjacent cells
        for( int i = 0; i < b.at(blocker_num).height;i++ ) {
            x = b.at(blocker_num).location.x;
            for( int j = 0; j < b.at(blocker_num).width;j++ ) {
                if(this->map.at(y).at(x)->get_cost()==-1) {
                    claim("The block overlaps",kError);
                }
                this->map.at(y).at(x)->set_cost(-1);
                while(this->map.at(y).at(x)->connections_empty() != 1) {
                    this->map.at(y).at(x)->connections_at(0)->get_end(this->map.at(y).at(x))->
                        remove_m_connection(this->map.at(y).at(x));
                    this->map.at(y).at(x)->remove_connection(this->map.at(y).at(x)->connections_at(0));
                }
                x++;
            }
            y++;
        }
    }
}

// display each node's cost
void Utilities::Map::display_map() {
    cout << endl << endl;
    for(int i = 0; i < this->get_height();i++) {
        cout << endl;
        for(int j = 0; j < this->get_width();j++) {
            cout << " "<< (this->map.at(i).at(j))->get_cost();
        }
    }
    cout << endl << endl;
}

// display each node's connection size
void Utilities::Map::display_size() {
    for(int i = 0; i< this->get_height();i++) {
        cout << endl;
        for(int j = 0; j < this->get_width();j++) {
            cout<<" "<< this->get_node(j,i)->connections_size();
        }
    }
    cout << endl;
}

void Utilities::Map::set_connection(vector<Connection> c) {
/*
 Read the source-sink pair from the c, which is a vector of pairs, to the map.
 input: the vector of source-sink pairs
 output: the value of get_cost of source and sink nodes are set to -2 and -3, respectively.
 We firstly check whether the source or sink nodes are legal, then check whether source or sink are at the boundary of the map. We firstly add those pairs with neither source nor sink on the boundary, then add those pairs with source or sink on the boundary. The reason we do this is to try our best to avoid path intersections.
 */
    int source_x, source_y, sink_x, sink_y;
    for(int connection_num = 0; connection_num < c.size(); connection_num++) {
        source_x = c.at(connection_num).source.x;
        source_y = c.at(connection_num).source.y;
        sink_x = c.at(connection_num).sink.x;
        sink_y = c.at(connection_num).sink.y;
        
        //check x boundary
        if(source_x < 0 || source_x > this->get_width()) {
            claim( "source x coord is not valid",kError);
        }
        //check y boundary
        if(sink_x < 0 || sink_x > this->get_width()) {
            claim( "sink x coord is not valid",kError);
        }
        if(source_y < 0 || source_y > this->get_height()) {
            claim( "source y coord is not valid",kError);
        }
        //check y boundary
        if(sink_y < 0 || sink_y > this->get_height()) {
            claim( "sink y coord is not valid",kError);
        }
    }
    
    vector<bool> c_bound(c.size());
    for(int i=0; i<c.size(); i++) {
        if(this->get_node(c.at(i).source)->get_y()==0 ||
           this->get_node(c.at(i).source)->get_x()==0 ||
           this->get_node(c.at(i).source)->get_y()==get_height()-1 ||
           this->get_node(c.at(i).source)->get_x()==get_width()-1 ||
           this->get_node(c.at(i).sink)->get_y()==0 ||
           this->get_node(c.at(i).sink)->get_x()==0 ||
           this->get_node(c.at(i).sink)->get_y()==get_height()-1 ||
           this->get_node(c.at(i).sink)->get_x()==get_width()-1) {
            c_bound.at(i)=true;
        }
        else {
            c_bound.at(i)=false;
        }
    }
    // reorder
    for(int i = 0; i < c.size(); i++) {
        if(c_bound.at(i)==false) {
            connection.push_back(c.at(i));
        }
    }
    for(int i = 0; i < c.size(); i++) {
        if(c_bound.at(i)==true) {
            connection.push_back(c.at(i));
        }
    }
    for(int i = 0; i < connection.size(); i++) {
        if(this->get_node(connection.at(i).source)->get_cost()==-1) {
            claim("The source of current path is inside the block, program exits", kError);
            exit(0);
        }
        if(this->get_node(connection.at(i).sink)->get_cost()==-1) {
            claim("The sink of current path is inside the block, program exits", kError);
            exit(0);
        }
    }
}

vector<Connection> Utilities::Map::get_connection() {
    return this->connection ;
}

void Utilities::Map::display_detour() {
    for(int i = 0; i< this->get_height();i++) {
        cout << endl;
        for(int j = 0; j < this->get_width();j++) {
            cout<<" "<< this->map.at(i).at(j)->get_detour();
        }
    }
    cout << endl;
}

void Utilities::Map::display_md() {
/* this function is to return the distance = manhattan distance + the already-expanded distance*/
    for(int i = 0; i< this->get_height();i++) {
        cout << endl;
        for(int j = 0; j < this->get_width();j++) {
            cout<<" "<< this->map.at(i).at(j)->get_distance();
        }
    }
    cout << endl;
}

void Utilities::Map::display_flag() {
    for(int i = 0; i< this->get_height();i++) {
        cout << endl;
        for(int j = 0; j < this->get_width();j++) {
            cout<<" "<< this->map.at(i).at(j)->get_flag();
        }
    }
    cout << endl;
}

void Utilities::Map::display_manhattan() {
/* this function is to return the manhattan distance*/
    for(int i = 0; i< this->get_height();i++) {
        cout << endl;
        for(int j = 0; j < this->get_width();j++) {
            cout<<" "<< this->map.at(i).at(j)->get_distance();
        }
    }
    cout << endl;
}

void Utilities::Map::add_blocker(Path* path) {
/* This function is to treat the completed path as blocker. When we don't allow the intersection between paths, our method is just to treat the previous connected paths as blockers. 
 input: path
 output: the costs of the nodes on this path are set to -1, that means these nodes are now treated as blocked nodes.
*/
    int x = path->get_sink().x; 
    int y = path->get_sink().y;
    this->map.at(y).at(x)->set_cost(-1);
    this->map.at(y).at(x)->set_detour(-100);
    while(this->map.at(y).at(x)->connections_empty()!=1) {
        this->map.at(y).at(x)->connections_at(0)->get_end(this->map.at(y).at(x))->remove_m_connection(this->map.at(y).at(x));
        this->map.at(y).at(x)->remove_connection(this->map.at(y).at(x)->connections_at(0));
    }
    for(int i = 0;i < path->size();i++) {
        x = path->at(i)->get_source().x; 
        y = path->at(i)->get_source().y;
        this->map.at(y).at(x)->set_cost(-1);
        this->map.at(y).at(x)->set_detour(-100);
        while(this->map.at(y).at(x)->connections_empty()!=1) {
            this->map.at(y).at(x)->connections_at(0)->get_end(this->map.at(y).at(x))->remove_m_connection(this->map.at(y).at(x));
            this->map.at(y).at(x)->remove_connection(this->map.at(y).at(x)->connections_at(0));
        }
    }
}

