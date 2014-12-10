#include "../Headers/korn.h"
#include <iostream>
#include <cmath>
#include <stack>
using std::cout;
using std::endl;
using std::stack;
Algorithm::Korn::Korn(Map* m) {
    this->map = m;
    this->connection = m->get_connection();
    this->number = m->get_connection().size();
    for (int i = 0; i < this->number; i++) {
        this->source.push_back(this->map->get_node(this->connection.at(i).source));
        this->sink.push_back(this->map->get_node(this->connection.at(i).sink));
    }
}

//Algorithm::Korn::~Korn() {

//empty destory function
//}

void Algorithm::Korn::reset_map() {
    for(int y = 0; y < this->map->get_height();y++) {
        for(int x = 0; x < this->map->get_width();x++) {
            if(this->map->get_node(x,y)->get_cost()!=-1) {
                this->map->get_node(x,y)->set_cost(0);//reset cost to 0
                this->map->get_node(x,y)->set_flag(0);
                this->map->get_node(x,y)->set_m_d(0);
            }
        }
    }
}

void Algorithm::Korn::run() {

    // iteration through the source-sink list
    for(int i = 0;i <this->number;i++) {

        // before searching each pair of source-sink, reset the map's cost=0 except for the blockers          
            this->reset_map();
        // set source and sink
        this->source.at(i)->set_cost(-2);//set source cost to -2
        this->sink.at(i)->set_cost(-3);//set sink cost to -3
        Point md = this->sink.at(i)->get_coord();//use for compute manhuatan distance
        double min_d = abs(md.x+md.y-source.at(i)->get_x()-source.at(i)->get_y()) * 2;
        int flag = 0;    // this flag use to break while loop, if we found sink, the flag = 1 and break loop
        int direction;
        int x = 0;
        int y = 0;
        int check = 0;
        int debug = 0;
        //the basic ideal of this algorithm is use 2 queue to set the cost
        stack<Node*> q1;
        vector<Node*> others,small;
        q1.push(this->source.at(i));
        Node* last = new Node(0,0);
        Node* temp = new Node(0,0);
        int f1 = 0;    //fi for check wether the first time in queue
        while(flag != 1) {    // while flag !=1 keep finding sink
            while(!q1.empty()) {

  /*              if(debug == 5) {    //if found sink 
flag =1;
                    break;
                }
debug++;
*/
                if(flag == 1) {    //if found sink 
                    break;
                }
                temp = q1.top();
		x = temp->get_x();
		y = temp->get_y();
                q1.pop();
                temp->set_flag(1);    //this flag to check the node can only in to vector once
		Node* neibor = new Node(0,0);

if(f1 != 0){                
                switch (direction){
//---------------------------------up situation---------------------------------
                case  0:
                     if(y-1 >= 0&&this->map->get_node(x,y-1)->get_cost()!=-1){
                        neibor = this->map->get_node(x,y-1);
		     }//if 
                    else{
			    check = 1;
                    }//else
			    break;
//---------------------------------down situation---------------------------------
                case 2 :
                    if(y+1 < this->map->get_height()&&this->map->get_node(x,y+1)->get_cost()!=-1){
                        neibor = this->map->get_node(x,y+1);
                        }//if 
                    else{
			    check = 1;
                    }//else
			    break;
//---------------------------------left situation---------------------------------
                case 1 :
                     if(x-1 >= 0&&this->map->get_node(x-1,y)->get_cost()!=-1){
                       neibor = this->map->get_node(x-1,y);
		     }//if 
                    else{
			    check = 1;
                    }//else
			    break;
//---------------------------------right situation---------------------------------
                case 3:
                     if(x+1 <this->map->get_width()&&this->map->get_node(x+1,y)->get_cost()!=-1){
                       neibor = this->map->get_node(x+1,y);
		     }//if 
                    else{
			    check = 1;
                    }//else
			    break;
                }
///////////////////////////////////////////////////////cc/////////////////////////////

               if(check == 0){
		       if(neibor->get_flag()!=1) { 
			       if(neibor->get_cost() == -3) {
				       flag = 1;
				       // add a path to vector
				       Path* new_path = new Path();
				       PathSegment* new_segment = new PathSegment(neibor->get_coord(),temp->get_coord());
				       this->map->display_md();
				       new_path->add_segment(new_segment);
				       new_path->set_source(neibor->get_coord());
				       new_path->set_sink(temp->get_coord());
				       //traceback
				       this->traceback(new_path);
				       break;
			       }

			       if(neibor->get_cost() == 0) {    //for normal point 
				       if(f1!=0 ) {
					       neibor->set_cost(temp->get_cost()+1);
				       }
				       else {
					       neibor->set_cost(1);
				       }
				       neibor->set_m_d(md,2);
			       }
cout<< "this is cost"<<endl;
			       this->map->display_map();
cout << "this is distance"<<endl;
			       this->map->display_md();
			       if (neibor->get_distance() <= min_d) {
				       small.push_back(neibor);
			       }//if md=distance
			       else{
				       check = 1;
				       others.push_back(neibor);//if the distance not min number, save it to vector
			       }//else
		       }//if get_flag()!=1
	       }//check == 0
}
               if(check == 1 || f1 == 0){
		       check = 0;
		       for(int j = 0; j < temp->connections_size();j++) {                
			       neibor = (temp->connections_at(j))->get_end(temp);
			       if(neibor->get_flag()!=1) {
				       //if we found sink we use traceback function to save the path   
				       if(neibor->get_cost() == -3) {
					       flag = 1;
					       // add a path to vector
					       Path* new_path = new Path();
					       PathSegment* new_segment = new PathSegment(neibor->get_coord(),temp->get_coord());
cout <<"this is distance from check = 1"<<endl;
					       this->map->display_md();
					       new_path->add_segment(new_segment);
					       new_path->set_source(neibor->get_coord());
					       new_path->set_sink(temp->get_coord());
					       //traceback
					       this->traceback(new_path);
					       break;
				       }

				       if(neibor->get_cost() == 0) {    //for normal point 
					       if(f1!=0 ) {
						       neibor->set_cost(temp->get_cost()+1);
					       }
					       else {
						       neibor->set_cost(1);
					       }
					       neibor->set_m_d(md,2);
				       }

cout<< "this is cost from check =1"<<endl;
				       this->map->display_map();
				       this->map->display_md();
				       if (neibor->get_distance() <= min_d) {
					       small.push_back(neibor);
				       }//if md=distance
				       else{
					       others.push_back(neibor);//if the distance not min number, save it to vector
				       }//else
			       }//if get_flag()!=1
		       }//for
	       }
                f1++;
                if(!small.empty()) {
                    int get_pos = 0;
            	    int get_min = small.at(0)->get_distance();
                    for(int kkk = 0;kkk < small.size();kkk++) {
                        if(small.at(kkk)->get_distance() < get_min) {
                            get_min = small.at(kkk)->get_distance();
              	            get_pos = kkk;
                        }//if		
      	            }               

                    Node* tt = small.at(get_pos);
                    min_d = tt->get_distance();
		    direction = this->direction(last->get_coord(),tt->get_coord());
		    last = temp;
                    q1.push(tt);
                    small.erase ( small.begin() + get_pos );
                    for(int kkk = 0;kkk < small.size();kkk++) {
                        Node* tt = small.at(kkk);
                        others.push_back(tt);	
                    }
                    small.clear();
		}//small is not empty
            }//whileq1

            if(q1.empty()) {//if q1 empty q2 empty, found element in vector
                int get_pos = 0;
                int get_min = others.at(0)->get_distance();
                for(int kkk = 0;kkk < others.size();kkk++) {
                    if(others.at(kkk)->get_distance() < get_min) {
                        get_min = others.at(kkk)->get_distance();
                        get_pos = kkk;
                    }
                }
                Node* tt = others.at(get_pos);
                others.erase ( others.begin() + get_pos );
                min_d = tt->get_distance();
		direction = this->direction(last->get_coord(),tt->get_coord());
		last = temp;
                q1.push(tt);
            }//if q1 q2 empty             
        }//while flag
    }//for path number
}


Map* Algorithm::Korn::get_map() {
    return this->map;
}


void Algorithm::Korn::traceback(Path* path) {
    int direction;//0 up      1 left      2 down        3 right
    direction = this->direction(path->get_source(),path->get_sink());
    int flag = 0;
    int x,y;
    while(flag!=1) {           
        Node* tail = this->map->get_node(path->get_sink()); 
        x = tail->get_x();
        y = tail->get_y();
        //if we found the last point flag = 1
        if(tail->get_cost()==1) {
            for(int i = 0; i< tail->connections_size();i++) {
                Node* neibor = tail->connections_at(i)->get_end(tail);
                if(neibor->get_cost()==-2) {
                    PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
                    path->add_segment(new_segment);
                    path->set_sink(neibor->get_coord());
                    flag = 1;
                }//if neibor = -2
            }//for 
        }//if tail ==1
//else we need do know the direction
        else {
            switch(direction) {
//---------------------------------up situation---------------------------------
            case  0:
//check bounday
                if(y-1 >= 0) {
                    Node* neibor = this->map->get_node(x,y-1);
                    //if in seme direction the next node's cost is less one than sink then add it in path
                    if(neibor->get_cost()==tail->get_cost()-1) {
                        PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
		       	path->add_segment(new_segment);
		  	path->set_sink(neibor->get_coord());
                        direction = this->direction(tail->get_coord(),neibor->get_coord());
                    }//if 

                    else {
                        for(int i = 0; i< tail->connections_size();i++) {
                            Node* neibor = tail->connections_at(i)->get_end(tail);
                            if(neibor->get_cost() == tail->get_cost()-1) {
                                PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
                                path->add_segment(new_segment);
                                path->set_sink(neibor->get_coord());
                                direction = this->direction(tail->get_coord(),neibor->get_coord());
                            }//if neibor == tail-1
	                }//for
                    }//else
                }//if y-1>0

                else {
                    for(int i = 0; i< tail->connections_size();i++) {
                        Node* neibor = tail->connections_at(i)->get_end(tail);
                        if(neibor->get_cost() == tail->get_cost()-1) {
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
                if(y+1 <= this->map->get_height()) {
                    Node* neibor = this->map->get_node(x,y+1);
                    //if in seme direction the next node's cost is less one than sink then add it in path
                    if(neibor->get_cost()==tail->get_cost()-1) {
                        PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
                        path->add_segment(new_segment);
                        path->set_sink(neibor->get_coord());
                        direction = this->direction(tail->get_coord(),neibor->get_coord());
                    }//if 

                    else {
                        for(int i = 0; i< tail->connections_size();i++) {
                            Node* neibor = tail->connections_at(i)->get_end(tail);
                            if(neibor->get_cost() == tail->get_cost()-1) {
                                PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
                                path->add_segment(new_segment);
                                path->set_sink(neibor->get_coord());
                                direction = this->direction(tail->get_coord(),neibor->get_coord());
		            }//if neibor == tail-1
                        }//for
                    }//else

                }

                else {
                    for(int i = 0; i< tail->connections_size();i++) {
                        Node* neibor = tail->connections_at(i)->get_end(tail);
                        if(neibor->get_cost() == tail->get_cost()-1) {
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
                if(x-1 > 0) {
                    Node* neibor = this->map->get_node(x-1,y);
                    // if in seme direction the next node's cost is less one than sink then add it in path
                    if(neibor->get_cost()==tail->get_cost()-1) {
                        PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
                        path->add_segment(new_segment);
  	                path->set_sink(neibor->get_coord());
                        direction = this->direction(tail->get_coord(),neibor->get_coord());
                    }//if 

                    else {
                        for(int i = 0; i< tail->connections_size();i++) {
                            Node* neibor = tail->connections_at(i)->get_end(tail);
                            if(neibor->get_cost() == tail->get_cost()-1) {
                                PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
                                path->add_segment(new_segment);
                                path->set_sink(neibor->get_coord());
                                direction = this->direction(tail->get_coord(),neibor->get_coord());
                            }//if neibor == tail-1
                        }//for
                    }//else
                }//if x-1>0

                else {
                    for(int i = 0; i< tail->connections_size();i++) {
                        Node* neibor = tail->connections_at(i)->get_end(tail);
                        if(neibor->get_cost() == tail->get_cost()-1) {
                            PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
                            path->add_segment(new_segment);
                            path->set_sink(neibor->get_coord());
                            direction = this->direction(tail->get_coord(),neibor->get_coord());
                        }//if neibor == tail-1
                    }//for
                }//else

                break;
//---------------------------------right situation---------------------------------
            case 3:
//check bounday
                if(x+1 < this->map->get_width()) {
                    Node* neibor = this->map->get_node(x+1,y);
                    //if in seme direction the next node's cost is less one than sink then add it in path
                    if(neibor->get_cost()==tail->get_cost()-1) {
                        PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
       	                path->add_segment(new_segment);
  	                path->set_sink(neibor->get_coord());
                        direction = this->direction(tail->get_coord(),neibor->get_coord());
                    }//if 

                    else {
                        for(int i = 0; i< tail->connections_size();i++) {
                            Node* neibor = tail->connections_at(i)->get_end(tail);
                            if(neibor->get_cost() == tail->get_cost()-1) {
                                PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
                                path->add_segment(new_segment);
                                path->set_sink(neibor->get_coord());
                                direction = this->direction(tail->get_coord(),neibor->get_coord());
                            }//if neibor == tail-1
                        }//for
                    }//else

                }//if x+1<width

                else {
                    for(int i = 0; i< tail->connections_size();i++) {
                            Node* neibor = tail->connections_at(i)->get_end(tail);
                            if(neibor->get_cost() == tail->get_cost()-1) {
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

vector<Path*> Algorithm::Korn::get_paths() {
    return this->paths;
}


vector<Connection> Algorithm::Korn::get_connection() {
    return this->connection ;
}

int Algorithm::Korn::direction(Point source,Point sink) {
    int direction;//0 up      1 left      2 down        3 right
    if (sink.x == source.x) {
        if (sink.y > source.y) {
            direction = 2;//backtrace to down
        }
        else {
            direction = 0;//up
        }
    }
    else {
        if (sink.x > source.x) {
            direction = 3;//right
        }
        else {
            direction = 1;//left
        }
    }
    return direction;
}

