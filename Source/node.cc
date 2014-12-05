#include "../Headers/edge.h"
#include "../Headers/node.h"
#include "../Headers/claim.h"
#include <iostream>
using std::cout;
using std::endl;

void Utilities::Node::updata_d(){
      this->distance = this->cost + this->m_d;
}


Utilities::Node::Node(int x, int y, int cost):coord(x,y){
      this->cost = cost;
      this->updata_d();
}

Utilities::Node::Node(Point coord, int cost):coord(coord.x,coord.y){
      this->cost = cost;
      this->updata_d();
}

Utilities::Node::~Node() {
      for(int i=0; i < connections.size(); i++) {
            Edge* edge_to_remove = this->connections.at(i);
            //Remove the edge from the node at the other end of the edge's connection list
			if (edge_to_remove) { 
				edge_to_remove->get_end(this)->remove_connection(edge_to_remove);
				//Remove the edge from the current object's connection list
				this->remove_connection(edge_to_remove);
				//Delete edge
				delete edge_to_remove;
			}
      }
}

Utilities::Point Utilities::Node::get_coord() {
      return this->coord;
}

int Utilities::Node::get_flag() {
      return this->flag;
}
int Utilities::Node::get_x() {
      return this->coord.x;
}
int Utilities::Node::get_y() {
      return this->coord.y;
}

unsigned Utilities::Node::connections_size() {
      return this->connections.size(); 
}

bool Utilities::Node::connections_empty() {
      return this->connections.empty();
}

bool Utilities::Node::connections_contains(Edge* edge) {
      for(int i = 0; i < this->connections.size(); i++) {
            if(this->connections.at(i) == edge) {
                  return true;
            }
      }
      return false;
}

Utilities::Edge* Utilities::Node::connections_at(unsigned index) {
      if(index >= connections.size()) {
            claim("Attemping to access connection outside of the connection list's range", kError);
      }
      return this->connections.at(index);          //at(...) will throw an out of range exception
}

int Utilities::Node::get_cost() {
      return this->cost;
}

int Utilities::Node::get_distance() {
      return this->distance;
}

void Utilities::Node::set_coord(int x, int y) {
      this->coord.x = x;
      this->coord.y = y;
}

void Utilities::Node::set_coord(Point coord) {
      this->coord = coord;
}

void Utilities::Node::set_flag(int x) {
      this->flag = x;
}
void Utilities::Node::set_x_coord(int x) {
      this->coord.x = x;
}
void Utilities::Node::set_y_coord(int y) {
      this->coord.y = y;
}

void Utilities::Node::set_connections(vector<Edge*> connections) {
      this->connections = connections;
}

void Utilities::Node::add_connection_mirrored(Edge* connection) {
      if (this-> connections_contains(connection) == 0){
          this->connections.push_back(connection);
      }
}

void Utilities::Node::add_connection(Edge* connection) {
       if (this-> connections_contains(connection) == 0){
          this->connections.push_back(connection);
          connection->get_end(this)->add_connection_mirrored(connection);
      }           
}

void Utilities::Node::set_cost(int cost) {
      this->cost = cost;
}
void Utilities::Node::set_m_d(Point sink){
      if(sink.x > this->coord.x){
          if(sink.y > this->coord.y){
              this->m_d = sink.x - coord.x + sink.y - coord.y;
          }
          else{
              this->m_d = sink.x - coord.x + coord.y - sink.y;
          }
      }
      else      
          if(sink.y > this->coord.y){
              this->m_d = coord.x - sink.x + sink.y - coord.y;
          }
          else{
              this->m_d = coord.x - sink.x + coord.y - sink.y;
          }
      this->updata_d();
}
//If an edge occurs multiple times in the connection list, all instances will be removed
void Utilities::Node::remove_connection(Edge* connection) {
      bool nothing_removed = true;
	  vector<Edge*>::iterator connections_it = connections.begin();
      //for(int i = 0; i < this->connections.size(); i++) {
      for(/* connections_it */;connections_it != connections.end();connections_it++) {
            if((*connections_it) == connection) {
                  nothing_removed = false;
				  connections.erase(connections_it);
				  if (connections_it == connections.end()) { break; }
            }
      }
      if(nothing_removed) {

//            claim("The edge is not connect to this point, nothing removed", kWarning);
      }
}

void Utilities::Node::display_node() {

        cout  <<"Node ("<<coord.x<<", "<<coord.y<<")";
}

void Utilities::Node::display_edges() {
    for(int i = 0; i < this->connections_size();i++){
        cout << endl <<"The number "<< i <<" is :";
        this->connections_at(i)->display_edge();
    }
    if ( this->connections_size() == 0){
        cout << " this node no connections" << endl;
    }
}
void Utilities::Node::remove_m_connection(Node* node){
        for(int i= 0; i < this->connections_size();i++){
            if( (this->connections_at(i)->get_end(this))->get_coord()==node->get_coord()){
            this->remove_connection(connections_at(i));
             }
         }

}  
