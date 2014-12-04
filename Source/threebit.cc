#include "../Headers/threebit.h"
#include <iostream>
using std::cout;
using std::endl;

Algorithm::Threebit::Threebit(Map* m){
    this->map = m;
    this->connection = m->get_connection();
    this->number = m->get_connection().size();
    for (int i = 0; i < this->number; i++){
        this->source.push_back(this->map->get_node(this->connection.at(i).source));
        this->sink.push_back(this->map->get_node(this->connection.at(i).sink));
    }
}

//Algorithm::Threebit::~Threebit(){

//empty destory function
//}


void Algorithm::Threebit::forward(){
    for(int i = 0;i <this->number;i++){//if we have i pair of sources and sinks, we need to do i times to find the path;
        if(i != 0){//if this is the first time to do the algorithm, we don't need to reset the map, if not, we need to reset every node's cost to 0 except blocker
            map->initialize();
        }// if not 1
        this->source.at(i)->set_cost(-2);//set source cost to -2
        this->sink.at(i)->set_cost(-3);//set sink cost to -3

        int flag = 0;// this flag use to break while loop, if we found sink, the flag = 1 and break loop
        int value = 0;// ues for cost

//the basic ideal of this algorithm is use 2 queue to set the cost
	queue<Node*> q1,q2;
        q1.push(this->source.at(i));
        while(flag != 1){// while flag !=1 keep found sink
   	    int f1 = 0;
	    int f2 = 0;
            while(!q1.empty()){
                if(flag == 1){//if found sink 
                    break;
                }
                f1++;

                if(f1 == 1){//the key point to increase cost
                    if(q2.empty()){
                        if(value == 3){
                            value = 1;
                         }
                         else{
                             value++;
                         }
                    }
                }
                Node* temp = q1.front();
                q1.pop();
                for(int j = 0; j < temp->connections_size();j++){                
                    Node* neibor = (temp->connections_at(j))->get_end(temp);
                   if(neibor->get_cost() == -3){//if we found sink we use traceback function to save the path
                        flag = 1;
                        Path* new_path = new Path();
                        PathSegment* new_segment = new PathSegment(neibor->get_coord(),temp->get_coord());
                        new_path->add_segment(new_segment);
                        new_path->set_source(neibor->get_coord());
                        new_path->set_sink(temp->get_coord());
                        cout<< "!!!!!!!!!!!!!!!!NOW I FOUND THE SINK!!!!!!!!!!!!!!!!!!!!"<<endl;
                        this->map->display_map();
                        this->traceback(new_path);
//                        this->paths.push_back(new_path);
                        break;
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
                        if(value == 3){
                            value = 1;
                         }
                         else{
                             value++;
                         }
                    }
                }
                Node* temp = q2.front();
                q2.pop();
                for(int j = 0; j < temp->connections_size();j++){                
                    Node* neibor = (temp->connections_at(j))->get_end(temp);
                    if(neibor->get_cost() == -3){
                        flag = 1;
                        Path* new_path = new Path();
                        PathSegment* new_segment = new PathSegment(neibor->get_coord(),temp->get_coord());
                        new_path->add_segment(new_segment);
                        new_path->set_source(neibor->get_coord());
                        new_path->set_sink(temp->get_coord());
                        cout<< "!!!!!!!!!!!!!!!!NOW I FOUND THE SINK!!!!!!!!!!!!!!!!!!!!"<<endl;
                        this->map->display_map();
                        this->traceback(new_path);
//                        this->paths.push_back(new_path);
                        break;
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
}


Map* Algorithm::Threebit::get_map(){
    return this->map;
}

void Algorithm::Threebit::traceback(Path* path){
    int flag = 0;
    while(flag!=1){
	    for(int i = 0; i< this->map->get_node(path->get_sink())->connections_size();i++){
	        Node* tail = this->map->get_node(path->get_sink());
		Node* neibor = tail->connections_at(i)->get_end(tail);
		if(tail->get_cost()==1){
                    if(neibor->get_cost()==3){
			PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
			path->add_segment(new_segment);
			path->set_sink(neibor->get_coord());
		    }
		    if(neibor->get_cost()==-2){
			PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
			path->add_segment(new_segment);
			path->set_sink(neibor->get_coord());
                        flag = 1;
		    }
		}//if is call for last point
		else if(neibor->get_cost() == tail->get_cost()-1){
		    PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
		    path->add_segment(new_segment);
		    path->set_sink(neibor->get_coord());
		}//if neibor == tail-1
	    }//for
    }//whilie
    this->paths.push_back(path);
}

vector<Path*> Algorithm::Threebit::get_paths(){
    return this->paths;
}


vector<Connection> Algorithm::Threebit::get_connection(){
       return this->connection ;
}

