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

    for (int i = 0;i <this->number;i++){
        int flag = 0;
        int value = 0;

	queue<Node*> q1,q2;
        q1.push(this->source.at(i));
        while(flag != 1){
   	    int f1 = 0;
	    int f2 = 0;
            while(!q1.empty()){
                if(flag == 1){
                    break;
                }
                f1++;
                if(f1 == 1){
                    if(q2.empty()){
                        value++;
                    }
                }
                Node* temp = q1.front();
                q1.pop();
                for(int j = 0; j < temp->connections_size();j++){                
                    Node* neibor = (temp->connections_at(j))->get_end(temp);
                   if(neibor->get_cost() == -3){
//                        j = temp->connections_size();
                        flag = 1;
//                        Path* new_path = new Path();
//                        PathSegment* new_segment = new PathSegment(neibor->get_coord(),temp->get_coord());
//                        new_path->add_segment(new_segment);
//                        this->paths.push_back(new_path);
                        break;
//                    
//                   cout << "this is "<< j << "time" << endl;
                    }
                    if(neibor->get_cost() == 0){
                        (this->map->get_node(neibor->get_coord()))->set_cost(value);
                        map->display_map();
                        q2.push(neibor);
                    }//if
                }//for
             }//whileq1

             while(!q2.empty()){
               if(flag == 1){
                    break;
                }
                f2++;
                if (f2 == 1){
                    if(q1.empty()){
                        value++;
                    }
                }
                Node* temp = q2.front();
                q2.pop();
                for(int j = 0; j < temp->connections_size();j++){                
                    Node* neibor = (temp->connections_at(j))->get_end(temp);
                    if(neibor->get_cost() == -3){
//                        j = temp->connections_size();
                        flag = 1;
//                        Path* new_path = new Path();
//                        PathSegment* new_segment = new PathSegment(neibor->get_coord(),temp->get_coord());
//                        new_path->add_segment(new_segment);
//                        this->paths.push_back(new_path);
                        break;
//                   map->display(); 
//                   cout << "this is "<< j << "time" << endl;
                    }
                    if(neibor->get_cost() == 0){
                        (this->map->get_node(neibor->get_coord()))->set_cost(value);
                        map->display_map();
                        q1.push(neibor);
                    }//if
                }//for
             }//whileq2
        }//while flag
    }//for path number
    return this->paths; 
}
Map* Algorithm::Lee::get_map(){
    return this->map;
}
