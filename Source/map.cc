#include "../Headers/map.h"
#include "../Headers/edge.h"
#include "../Headers/claim.h"
#include "../Headers/problem_object.h"
#include <iostream>
using std::cout;
using std::endl;
//Takes an x and y coordinate as input and creates a grid of that size filled with default nodes
Utilities::Map::Map(int width, int height) {
    for(int y = 0; y < height; y++) {
        vector<Node*> temp_row;
        for(int x = 0; x < width; x++) {
	    Node* new_node = new Node(x,y);
	    if (x > 0) {
                Edge* west = new Edge(new_node,temp_row.at(temp_row.size()-1));
		new_node->add_connection(west);
	     }
	     if (y > 0) {
		Edge* north = new Edge(new_node,map.at(y-1).at(x));
	        new_node->add_connection(north);
	      }
	      temp_row.push_back(new_node);
          }
          this->map.push_back(temp_row);
      }
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
void Utilities::Map::replace_node(Node* replacement_node) {
      delete this->map.at(replacement_node->get_y()).at(replacement_node->get_x());
      this->map.at(replacement_node->get_y()).at(replacement_node->get_x()) = replacement_node;
}

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
        int x,y;//blocker location
        for ( int blocker_num = 0; blocker_num < b.size(); blocker_num++){
                x = b.at(blocker_num).location.x;
                y = b.at(blocker_num).location.y;
                if(x < 0 && x > this->get_width()){//check x boundary
                        claim( "x coord is not valid",kError); }
                if( y < 0 && y > this->get_height()){//check y boundary
                        claim( "y coord is not valid",kError);
                }
                for( int i = 0; i < b.at(blocker_num).height;i++ ){//blocker height point
                        x = b.at(blocker_num).location.x;
                        for( int j = 0; j < b.at(blocker_num).width;j++ ){//blocker width point
                                this->map.at(y).at(x)->set_cost(-1);
                                while(this->map.at(y).at(x)->connections_empty()!=1){
                                    this->map.at(y).at(x)->connections_at(0)->get_end(this->map.at(y).at(x))->remove_m_connection(this->map.at(y).at(x));
                                    this->map.at(y).at(x)->remove_connection(this->map.at(y).at(x)->connections_at(0));
                //                    this->display_size();
                                }
 
                                x++;
                         }
                         y++;
                 }
       }
}

void Utilities::Map::display_map(){
      cout << endl << endl;
      for(int i = 0; i < this->get_height();i++){
          cout << endl;
          for(int j = 0; j < this->get_width();j++){
              cout << " "<< (this->map.at(i).at(j))->get_cost();
          }
      }
      cout << endl << endl;
}
void Utilities::Map::display_size(){
        for(int i = 0; i< this->get_height();i++){
                cout << endl;
                for(int j = 0; j < this->get_width();j++){
                        cout<<" "<< this->get_node(j,i)->connections_size();
                }
        }
        cout << endl;

}
void Utilities::Map::set_connection(vector<Connection> c){
       this->connection = c;
}

vector<Connection> Utilities::Map::get_connection(){
       return this->connection ;
}
