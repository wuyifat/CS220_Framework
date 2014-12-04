#include "../Headers/ruben.h"
#include <iostream>
using std::cout;
using std::endl;

Algorithm::Ruben::Ruben(Map* m){
    this->map = m;
    this->connection = m->get_connection();
    this->number = m->get_connection().size();
    for (int i = 0; i < this->number; i++){
        this->source.push_back(this->map->get_node(this->connection.at(i).source));
        this->sink.push_back(this->map->get_node(this->connection.at(i).sink));
    }
}

//Algorithm::Ruben::~Ruben(){

//empty destory function
//}


void Algorithm::Ruben::forward(){
    for(int i = 0;i <this->number;i++){//if we have i pair of sources and sinks, we need to do i times to find the path;
        if(i != 0){//if this is the first time to do the algorithm, we don't need to reset the map, if not, we need to reset every node's cost to 0 except blocker
            for(int y = 0; y < this->map->get_height();y++){
                for(int x = 0; x < this->map->get_width();x++){
                    if(this->map->get_node(x,y)->get_cost()!=-1){
                        this->map->get_node(x,y)->set_cost(0);//reset cost to 0
                    }//if
                }//for x
            }//for y
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
                        value++;
                    }
                }
                Node* temp = q1.front();
                q1.pop();
                for(int j = 0; j < temp->connections_size();j++){                
                    Node* neibor = (temp->connections_at(j))->get_end(temp);
                   if(neibor->get_cost() == -3){//if we found sink we use traceback function to save the path
                        flag = 1;
                        map->display_map();
                        Path* new_path = new Path();
                        PathSegment* new_segment = new PathSegment(neibor->get_coord(),temp->get_coord());
                        cout<< " this is the last node !!!!!!!!!!!!!!!!!!!!!!!"<<endl;
                        temp->display_node();
                        new_path->add_segment(new_segment);
                        new_path->set_source(neibor->get_coord());
                        new_path->set_sink(temp->get_coord());
                        this->traceback(new_path);
//                        this->paths.push_back(new_path);
                        break;
                    }
                    if(neibor->get_cost() == 0){
                        (this->map->get_node(neibor->get_coord()))->set_cost(value);
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
                        flag = 1;
                        map->display_map();
                        Path* new_path = new Path();
                        PathSegment* new_segment = new PathSegment(neibor->get_coord(),temp->get_coord());
                         cout<< " this is the last node !!!!!!!!!!!!!!!!!!!!!!!"<<endl;
                        temp->display_node();
                        new_path->add_segment(new_segment);
                        new_path->set_source(neibor->get_coord());
                        new_path->set_sink(temp->get_coord());
                        this->traceback(new_path);
//                        this->paths.push_back(new_path);
                        break;
                    }
                    if(neibor->get_cost() == 0){
                        (this->map->get_node(neibor->get_coord()))->set_cost(value);

                        q1.push(neibor);
                    }//if
                }//for
             }//whileq2
        }//while flag
    }//for path number
}


Map* Algorithm::Ruben::get_map(){
    return this->map;
}


void Algorithm::Ruben::traceback(Path* path){
    int direction;//0 up      1 left      2 down        3 right
    direction = this->direction(path->get_source(),path->get_sink());
    int flag = 0;
    int x,y;
    while(flag!=1){           
	    Node* tail = this->map->get_node(path->get_sink()); 
            x = tail->get_x();
            y = tail->get_y();
//if we found the last point flag = 1
            if(tail->get_cost()==1){
                for(int i = 0; i< tail->connections_size();i++){
                    Node* neibor = tail->connections_at(i)->get_end(tail);
		    if(neibor->get_cost()==-2){
			PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
			path->add_segment(new_segment);
			path->set_sink(neibor->get_coord());
                        flag = 1;
		    }//if neibor = -2
		}//for 
             }//if tail ==1
//else we need do know the direction
            else{
                switch(direction){
//---------------------------------up situation---------------------------------
                case  0:
//check bounday
                     if(y-1 >= 0){
                        Node* neibor = this->map->get_node(x,y-1);
                       if(neibor->get_cost()==tail->get_cost()-1){//if in seme direction the next node's cost is less one than sink then add it in path
                                PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
		       	        path->add_segment(new_segment);
		  	        path->set_sink(neibor->get_coord());
                                direction = this->direction(tail->get_coord(),neibor->get_coord());
                        }//if 

                    else{
                        for(int i = 0; i< tail->connections_size();i++){
                            Node* neibor = tail->connections_at(i)->get_end(tail);
                            if(neibor->get_cost() == tail->get_cost()-1){
		                PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
		                path->add_segment(new_segment);
		                path->set_sink(neibor->get_coord());
                                direction = this->direction(tail->get_coord(),neibor->get_coord());
		             }//if neibor == tail-1
	                 }//for
                    }//else

                    }//if y-1>0
                    else{
                        for(int i = 0; i< tail->connections_size();i++){
                            Node* neibor = tail->connections_at(i)->get_end(tail);
                            if(neibor->get_cost() == tail->get_cost()-1){
		                PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
		                path->add_segment(new_segment);
		                path->set_sink(neibor->get_coord());
                                direction = this->direction(tail->get_coord(),neibor->get_coord());
		             }//if neibor == tail-1
	                 }//for
                    }//else

                break;

//---------------------------------down situation---------------------------------
                case 2 :
                    if(y+1 <= this->map->get_height()){
                        Node* neibor = this->map->get_node(x,y+1);
                        if(neibor->get_cost()==tail->get_cost()-1){//if in seme direction the next node's cost is less one than sink then add it in path
                                PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
		       	        path->add_segment(new_segment);
		  	        path->set_sink(neibor->get_coord());
                                direction = this->direction(tail->get_coord(),neibor->get_coord());
                        }//if 

                    else{
                        for(int i = 0; i< tail->connections_size();i++){
                            Node* neibor = tail->connections_at(i)->get_end(tail);
                            if(neibor->get_cost() == tail->get_cost()-1){
		                PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
		                path->add_segment(new_segment);
		                path->set_sink(neibor->get_coord());
                                direction = this->direction(tail->get_coord(),neibor->get_coord());
		             }//if neibor == tail-1
	                 }//for
                    }//else
                    }//if y-1>0
                   else{
                        for(int i = 0; i< tail->connections_size();i++){
                            Node* neibor = tail->connections_at(i)->get_end(tail);
                            if(neibor->get_cost() == tail->get_cost()-1){
		                PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
		                path->add_segment(new_segment);
		                path->set_sink(neibor->get_coord());
                                direction = this->direction(tail->get_coord(),neibor->get_coord());
		             }//if neibor == tail-1
	                 }//for
                    }//else
                   break;

//---------------------------------left situation---------------------------------
                case 1 :
//check bounday
                     if(x-1 >= 0){
                        Node* neibor = this->map->get_node(x-1,y);
                        if(neibor->get_cost()==tail->get_cost()-1){//if in seme direction the next node's cost is less one than sink then add it in path
                                PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
		       	        path->add_segment(new_segment);
		  	        path->set_sink(neibor->get_coord());
                                direction = this->direction(tail->get_coord(),neibor->get_coord());
                        }//if 

                    else{
                        for(int i = 0; i< tail->connections_size();i++){
                            Node* neibor = tail->connections_at(i)->get_end(tail);
                            if(neibor->get_cost() == tail->get_cost()-1){
		                PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
		                path->add_segment(new_segment);
		                path->set_sink(neibor->get_coord());
                                direction = this->direction(tail->get_coord(),neibor->get_coord());
		             }//if neibor == tail-1
	                 }//for
                    }//else
                    }//if x-1>0
                    else{
                        for(int i = 0; i< tail->connections_size();i++){
                            Node* neibor = tail->connections_at(i)->get_end(tail);
                            if(neibor->get_cost() == tail->get_cost()-1){
		                PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
		                path->add_segment(new_segment);
		                path->set_sink(neibor->get_coord());
                                direction = this->direction(tail->get_coord(),neibor->get_coord());
		             }//if neibor == tail-1
	                 }//for
                    }//else

                   break;
//---------------------------------right situation---------------------------------
                case 4:
//check bounday
                     if(x+1 <= this->map->get_width()){
                        Node* neibor = this->map->get_node(x+1,y);
                        if(neibor->get_cost()==tail->get_cost()-1){//if in seme direction the next node's cost is less one than sink then add it in path
                                PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
		       	        path->add_segment(new_segment);
		  	        path->set_sink(neibor->get_coord());
                                direction = this->direction(tail->get_coord(),neibor->get_coord());
                        }//if 

                    else{
                        for(int i = 0; i< tail->connections_size();i++){
                            Node* neibor = tail->connections_at(i)->get_end(tail);
                            if(neibor->get_cost() == tail->get_cost()-1){
		                PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
		                path->add_segment(new_segment);
		                path->set_sink(neibor->get_coord());
                                direction = this->direction(tail->get_coord(),neibor->get_coord());
		             }//if neibor == tail-1
	                 }//for
                    }//else
                    }//if x+1<width
                    else{
                        for(int i = 0; i< tail->connections_size();i++){
                            Node* neibor = tail->connections_at(i)->get_end(tail);
                            if(neibor->get_cost() == tail->get_cost()-1){
		                PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
		                path->add_segment(new_segment);
		                path->set_sink(neibor->get_coord());
                                direction = this->direction(tail->get_coord(),neibor->get_coord());
		             }//if neibor == tail-1
	                 }//for
                    }//else

                    break;
                }//switch case
            }//else for tail!=1
    }//whilie
    this->paths.push_back(path);
}

vector<Path*> Algorithm::Ruben::get_paths(){
    return this->paths;
}


vector<Connection> Algorithm::Ruben::get_connection(){
       return this->connection ;
}
int Algorithm::Ruben::direction(Point source,Point sink){
    int direction;//0 up      1 left      2 down        3 right
    if (sink.x == source.x){
        if (sink.y > source.y){
            direction = 2;//backtrace to down
        }
        else{
            direction = 0;//up
        }
    }
    else{
        if (sink.x > source.x){
            direction = 3;//right
        }
        else{
            direction = 1;//left
        }
    }
    return direction;
}


