#include "../Headers/lee.h"
#include <iostream>
using std::cout;
using std::endl;

Algorithm::Lee::Lee(Map* m){
    this->map = m;
    this->source = m->get_sources();
    this->sink = m->get_sinks();
    this->number = m->get_sources().size();
}

//Algorithm::Lee::~Lee(){

//empty destory function
//}


vector<Path*> Algorithm::Lee::forward(){
    int t;
                   this->map->display();
                   cout << "this is0  time" << endl;

    for (int i = 0;i <this->number;i++){
        int flag = 0;
        int value = 0;
	queue<Node*> q;
        q.push(this->source.at(i));
        while(flag != 1){
            Node* temp = q.front();
            q.pop();
            for(int j = 0; j < temp->connections_size();j++){
               Node* neibor = (temp->connections_at(j))->get_end(temp);
               if(neibor->get_cost() != -3){
                   (this->map->get_node(neibor->get_coord()))->set_cost(value++);
//                   map->display(); 
//                   cout << "this is "<< j << "time" << endl;
                   /*------------got the neibor-----------*/   /*set cost-----*/
                   q.push(neibor);
               }
               else{
                   Path* new_path = new Path();
                   flag = 1;
                   PathSegment* new_segment = new PathSegment(neibor->get_coord(),temp->get_coord());
                   new_path->add_segment(new_segment);
                   this->paths.push_back(new_path);
                   return this->paths;
               }
            }
        }
    }
}
Map* Algorithm::Lee::get_map(){
    return this->map;
}
