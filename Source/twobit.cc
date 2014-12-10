#include "../Headers/twobit.h"
#include <iostream>
using std::cout;
using std::endl;

Algorithm::Twobit::Twobit(Map* m) {
    this->cross = 0;
    this->ruben_trace = 1;
    this->map = m;
    this->connection = m->get_connection();
    this->number = m->get_connection().size();
    for (int i = 0; i < this->number; i++) {
        this->source.push_back(this->map->get_node(this->connection.at(i).source));
        this->sink.push_back(this->map->get_node(this->connection.at(i).sink));
    }
}

//Algorithm::Twobit::~Twobit() {

//empty destory function
//}


void Algorithm::Twobit::run() {
    // iterate through the source-sink list
    for(int i = 0;i <this->number;i++) {
        // before searching each pair of source-sink, reset the map's cost=0 except for the blockers
        for(int y = 0; y < this->map->get_height();y++) {
            for(int x = 0; x < this->map->get_width();x++) {
                if(this->map->get_node(x,y)->get_cost()!=-1) {
                    this->map->get_node(x,y)->set_cost(0);    //reset cost to 0
                }//if
            }//for x
        }//for y
        
        this->source.at(i)->set_cost(-2);//set source cost to -2
        this->sink.at(i)->set_cost(-3);//set sink cost to -3
        
        int flag = 0;// this flag use to break while loop, if we found sink, the flag = 1 and break loop
        int value = 0;// ues for cost
        int fl1 = 1; // use for check value flipflop
        
        //the basic ideal of this algorithm is to use 2 queues to set the cost
        queue<Node*> q1,q2;
        q1.push(this->source.at(i));
        while(flag != 1) {    // while flag !=1 keep searching for sink
            int f1 = 0;
            int f2 = 0;
            while(!q1.empty()) {
                if(flag == 1) {    //if found sink
                    break;
                }
                f1++;
                if(f1 == 1) {    //the key point to increase cost
                    if(q2.empty()) {
                        if(fl1<1) {
                            fl1++;
                        }
                        else {
                            if(value == 1) {
                                value++;
                            }
                            else {
                                value = 1;
                            }
                            fl1 = 0;
                        }
                    }
                }
                Node* temp = q1.front();
                q1.pop();
                for(int j = 0; j < temp->connections_size();j++) {
                    Node* neibor = (temp->connections_at(j))->get_end(temp);
                    //if we found sink we use traceback function to save the path
                    if(neibor->get_cost() == -3) {
                        flag = 1;
                        Path* new_path = new Path();
                        PathSegment* new_segment = new PathSegment(neibor->get_coord(),temp->get_coord());
                        new_path->add_segment(new_segment);
                        new_path->set_source(neibor->get_coord());
                        new_path->set_sink(temp->get_coord());
                        cout<< "!!!!!!!!!!!!!!!!NOW I FOUND THE SINK!!!!!!!!!!!!!!!!!!!!"<<endl;
                        this->map->display_map();
                        if(ruben_trace == 1) {
                            this->traceback(fl1,new_path,ruben_trace);
                        }
                        else {
                            this->traceback(fl1,new_path);
                        }
                        break;
                    }
                    if(neibor->get_cost() == 0) {
                        neibor->set_cost(value);
                        map->display_map();
                        q2.push(neibor);
                    }//if
                }//for
            }//whileq1
            
            while(!q2.empty()) {
                if(flag == 1) {
                    break;
                }
                f2++;
                if (f2 == 1) {
                    if(q1.empty()) {
                        if(fl1 <1) {
                            fl1++;
                        }
                        else{
                            if(value == 1 ) {
                                value++;
                            }
                            else {
                                value = 1;
                            }
                            fl1 = 0;
                        }
                    }
                }
                Node* temp = q2.front();
                q2.pop();
                for(int j = 0; j < temp->connections_size();j++) {
                    Node* neibor = (temp->connections_at(j))->get_end(temp);
                    if(neibor->get_cost() == -3) {
                        flag = 1;
                        Path* new_path = new Path();
                        PathSegment* new_segment = new PathSegment(neibor->get_coord(),temp->get_coord());
                        new_path->add_segment(new_segment);
                        new_path->set_source(neibor->get_coord());
                        new_path->set_sink(temp->get_coord());
                        if(ruben_trace == 1) {
                            this->traceback(fl1,new_path,ruben_trace);
                        }
                        else{
                            this->traceback(fl1,new_path);
                        }
                        break;
                    }
                    if(neibor->get_cost() == 0) {
                        neibor->set_cost(value);
                        map->display_map();
                        q1.push(neibor);
                    }//if
                }//for
            }//whileq2
        }//while flag
        if(this->cross == 0) {
            Path* t = this->paths.at(i);
            this->map->add_blocker(t);
        }
    }//for path number
}


Map* Algorithm::Twobit::get_map() {
    return this->map;
}

void Algorithm::Twobit::traceback(int fl, Path* path,int i) {
    cout<<"use ruben!!!!!!!!!!"<<endl;
    int direction;//0 up      1 left      2 down        3 right
    direction = this->direction(path->get_source(),path->get_sink());
    cout <<"the direction value is 0up 1left 2down 3right    "<<direction<<endl;
    int same = fl;
    int flag = 0;
    int x,y;
    bool arg1, arg2; // arg1 is to determine whether current node is next to source. arg2 is to determine whether current path needs to be included into the path.
    // include rule: in these four cases, current path segment (tail and neibor pair) should be included.
    /*
     case 1: same==1, tail==2 (the cost of tail is 2, same below); neibor==1; after included, same=0
     case 2: same==1, tail==1; neibor==2; after included, same=0
     case 3: same==0, tail==1; neibor==1; after included, same=1
     case 4: same==0, tail==2; neibor==2; after included, same=1
     */
    while(flag!=1) {
        Node* tail = this->map->get_node(path->get_sink());
        cout<< endl<<"the tail is "<<endl;
        tail->display_node();
        cout <<"the direction value is 0up 1left 2down 3right    "<<direction<<endl;
        this->map->display_map();
        x = tail->get_x();
        y = tail->get_y();
        
        //if we found the last point flag = 1
        // differ from lee here
        arg1=false; // arg is true when tail is next to source, otherwise false;
        if(tail->get_cost()==1) {
            for(int i = 0; i< tail->connections_size();i++) {
                Node* neibor = tail->connections_at(i)->get_end(tail);
                if(neibor->get_cost()==-2) { // tail next to source
                    arg1=true;
                    break;
                }
            }
        }
        
        if(arg1) {
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
        else{
            switch(direction) {
                    //---------------------------------up situation---------------------------------
                case  0:
                    //check bounday
                    if(y-1 >= 0) {
                        Node* neibor = this->map->get_node(x,y-1);
                        arg2=((same==1 && tail->get_cost()==2 && neibor->get_cost()==1) || (same==1 && tail->get_cost()==1 && neibor->get_cost()==2) || (same==0 && tail->get_cost()==2 && neibor->get_cost()==2) || (same==0 && tail->get_cost()==1 && neibor->get_cost()==1));
                        //if in seme direction the next node's cost is less one than sink then add it in path
                        if(arg2) {
                            cout<<"direction is "<<direction<<", checking tail "<<tail->get_y()<<" "<<tail->get_x()<<", cost "<<tail->get_cost()<<", checking neibor "<<neibor->get_y()<<" "<<neibor->get_x()<<", cost "<<neibor->get_cost()<<", same value"<<same<<endl;
                            PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
                            path->add_segment(new_segment);
                            path->set_sink(neibor->get_coord());
                            direction = this->direction(tail->get_coord(),neibor->get_coord());
                            same=1-same;
                            cout<<"1"<<endl;
                        }//if
                        
                        else{
                            for(int i = 0; i< tail->connections_size();i++) {
                                Node* neibor = tail->connections_at(i)->get_end(tail);
                                arg2=((same==1 && tail->get_cost()==2 && neibor->get_cost()==1) || (same==1 && tail->get_cost()==1 && neibor->get_cost()==2) || (same==0 && tail->get_cost()==2 && neibor->get_cost()==2) || (same==0 && tail->get_cost()==1 && neibor->get_cost()==1));
                                if(arg2) {
                                    cout<<"direction is "<<direction<<", checking tail "<<tail->get_y()<<" "<<tail->get_x()<<", cost "<<tail->get_cost()<<", checking neibor "<<neibor->get_y()<<" "<<neibor->get_x()<<", cost "<<neibor->get_cost()<<", same value"<<same<<endl;
                                    PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
                                    path->add_segment(new_segment);
                                    path->set_sink(neibor->get_coord());
                                    direction = this->direction(tail->get_coord(),neibor->get_coord());
                                    same=1-same;
                                    cout<<"2"<<endl;
                                    break;
                                }//if neibor == tail-1
                            }//for
                        }//else
                    }//if y-1>0
                    
                    else{
                        for(int i = 0; i< tail->connections_size();i++) {
                            Node* neibor = tail->connections_at(i)->get_end(tail);
                            arg2=((same==1 && tail->get_cost()==2 && neibor->get_cost()==1) || (same==1 && tail->get_cost()==1 && neibor->get_cost()==2) || (same==0 && tail->get_cost()==2 && neibor->get_cost()==2) || (same==0 && tail->get_cost()==1 && neibor->get_cost()==1));
                            if(arg2) {
                                cout<<"direction is "<<direction<<", checking tail "<<tail->get_y()<<" "<<tail->get_x()<<", cost "<<tail->get_cost()<<", checking neibor "<<neibor->get_y()<<" "<<neibor->get_x()<<", cost "<<neibor->get_cost()<<", same value"<<same<<endl;
                                PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
                                path->add_segment(new_segment);
                                path->set_sink(neibor->get_coord());
                                direction = this->direction(tail->get_coord(),neibor->get_coord());
                                same=1-same;
                                cout<<"3"<<endl;
                                break;
                            }//if neibor == tail-1
                        }//for
                    }//else
                    
                    break;
                    
                    //---------------------------------down situation---------------------------------
                case 2 :
                    if(y+1 < this->map->get_height()) {
                        Node* neibor = this->map->get_node(x,y+1);
                        //if in seme direction the next node's cost is less one than sink then add it in path
                        arg2=((same==1 && tail->get_cost()==2 && neibor->get_cost()==1) || (same==1 && tail->get_cost()==1 && neibor->get_cost()==2) || (same==0 && tail->get_cost()==2 && neibor->get_cost()==2) || (same==0 && tail->get_cost()==1 && neibor->get_cost()==1));
                        cout<<arg2<<endl;
                        if(arg2) {
                            cout<<"direction is "<<direction<<", checking tail "<<tail->get_y()<<" "<<tail->get_x()<<", cost "<<tail->get_cost()<<", checking neibor "<<neibor->get_y()<<" "<<neibor->get_x()<<", cost "<<neibor->get_cost()<<", same value"<<same<<endl;
                            PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
                            path->add_segment(new_segment);
                            path->set_sink(neibor->get_coord());
                            direction = this->direction(tail->get_coord(),neibor->get_coord());
                            same=1-same;
                            cout<<"4"<<endl;
                        }//if
                        
                        else {
                            for(int i = 0; i< tail->connections_size();i++) {
                                Node* neibor = tail->connections_at(i)->get_end(tail);
                                arg2=((same==1 && tail->get_cost()==2 && neibor->get_cost()==1) || (same==1 && tail->get_cost()==1 && neibor->get_cost()==2) || (same==0 && tail->get_cost()==2 && neibor->get_cost()==2) || (same==0 && tail->get_cost()==1 && neibor->get_cost()==1));
                                if(arg2) {
                                    cout<<"direction is "<<direction<<", checking tail "<<tail->get_y()<<" "<<tail->get_x()<<", cost "<<tail->get_cost()<<", checking neibor "<<neibor->get_y()<<" "<<neibor->get_x()<<", cost "<<neibor->get_cost()<<", same value"<<same<<endl;
                                    PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
                                    path->add_segment(new_segment);
                                    path->set_sink(neibor->get_coord());
                                    direction = this->direction(tail->get_coord(),neibor->get_coord());
                                    same=1-same;
                                    cout<<"5"<<endl;
                                    break;
                                }//if neibor == tail-1
                            }//for
                        }//else
                    }//if y-1>0
                    
                    else {
                        for(int i = 0; i< tail->connections_size();i++) {
                            Node* neibor = tail->connections_at(i)->get_end(tail);
                            arg2=((same==1 && tail->get_cost()==2 && neibor->get_cost()==1) || (same==1 && tail->get_cost()==1 && neibor->get_cost()==2) || (same==0 && tail->get_cost()==2 && neibor->get_cost()==2) || (same==0 && tail->get_cost()==1 && neibor->get_cost()==1));
                            if(arg2) {
                                cout<<"direction is "<<direction<<", checking tail "<<tail->get_y()<<" "<<tail->get_x()<<", cost "<<tail->get_cost()<<", checking neibor "<<neibor->get_y()<<" "<<neibor->get_x()<<", cost "<<neibor->get_cost()<<", same value"<<same<<endl;
                                PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
                                path->add_segment(new_segment);
                                path->set_sink(neibor->get_coord());
                                direction = this->direction(tail->get_coord(),neibor->get_coord());
                                same=1-same;
                                cout<<"6"<<endl;
                                break;
                            }//if neibor == tail-1
                        }//for
                    }//else
                    
                    break;
                    
                    //---------------------------------left situation---------------------------------
                case 1 :
                    //check bounday
                    if(x-1 > 0) {
                        Node* neibor = this->map->get_node(x-1,y);
                        //if in seme direction the next node's cost is less one than sink then add it in path
                        arg2=((same==1 && tail->get_cost()==2 && neibor->get_cost()==1) || (same==1 && tail->get_cost()==1 && neibor->get_cost()==2) || (same==0 && tail->get_cost()==2 && neibor->get_cost()==2) || (same==0 && tail->get_cost()==1 && neibor->get_cost()==1));
                        if(arg2) {
                            cout<<"direction is "<<direction<<", checking tail "<<tail->get_y()<<" "<<tail->get_x()<<", cost "<<tail->get_cost()<<", checking neibor "<<neibor->get_y()<<" "<<neibor->get_x()<<", cost "<<neibor->get_cost()<<", same value"<<same<<endl;
                            PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
                            path->add_segment(new_segment);
                            path->set_sink(neibor->get_coord());
                            direction = this->direction(tail->get_coord(),neibor->get_coord());
                            same=1-same;
                            cout<<"7"<<endl;
                        }//if
                        
                        else {
                            for(int i = 0; i< tail->connections_size();i++) {
                                Node* neibor = tail->connections_at(i)->get_end(tail);
                                arg2=((same==1 && tail->get_cost()==2 && neibor->get_cost()==1) || (same==1 && tail->get_cost()==1 && neibor->get_cost()==2) || (same==0 && tail->get_cost()==2 && neibor->get_cost()==2) || (same==0 && tail->get_cost()==1 && neibor->get_cost()==1));
                                if(arg2) {
                                    cout<<"direction is "<<direction<<", checking tail "<<tail->get_y()<<" "<<tail->get_x()<<", cost "<<tail->get_cost()<<", checking neibor "<<neibor->get_y()<<" "<<neibor->get_x()<<", cost "<<neibor->get_cost()<<", same value"<<same<<endl;
                                    PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
                                    path->add_segment(new_segment);
                                    path->set_sink(neibor->get_coord());
                                    direction = this->direction(tail->get_coord(),neibor->get_coord());
                                    same=1-same;
                                    cout<<"8"<<endl;
                                    break;
                                }//if neibor == tail-1
                            }//for
                        }//else
                    }//if x-1>0
                    
                    else {
                        for(int i = 0; i< tail->connections_size();i++) {
                            Node* neibor = tail->connections_at(i)->get_end(tail);
                            arg2=((same==1 && tail->get_cost()==2 && neibor->get_cost()==1) || (same==1 && tail->get_cost()==1 && neibor->get_cost()==2) || (same==0 && tail->get_cost()==2 && neibor->get_cost()==2) || (same==0 && tail->get_cost()==1 && neibor->get_cost()==1));
                            if(arg2) {
                                cout<<"direction is "<<direction<<", checking tail "<<tail->get_y()<<" "<<tail->get_x()<<", cost "<<tail->get_cost()<<", checking neibor "<<neibor->get_y()<<" "<<neibor->get_x()<<", cost "<<neibor->get_cost()<<", same value"<<same<<endl;
                                PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
                                path->add_segment(new_segment);
                                path->set_sink(neibor->get_coord());
                                direction = this->direction(tail->get_coord(),neibor->get_coord());
                                same=1-same;
                                cout<<"9"<<endl;
                                break;
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
                        arg2=((same==1 && tail->get_cost()==2 && neibor->get_cost()==1) || (same==1 && tail->get_cost()==1 && neibor->get_cost()==2) || (same==0 && tail->get_cost()==2 && neibor->get_cost()==2) || (same==0 && tail->get_cost()==1 && neibor->get_cost()==1));
                        if(arg2) {
                            cout<<"direction is "<<direction<<", checking tail "<<tail->get_y()<<" "<<tail->get_x()<<", cost "<<tail->get_cost()<<", checking neibor "<<neibor->get_y()<<" "<<neibor->get_x()<<", cost "<<neibor->get_cost()<<", same value"<<same<<endl;
                            PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
                            path->add_segment(new_segment);
                            path->set_sink(neibor->get_coord());
                            direction = this->direction(tail->get_coord(),neibor->get_coord());
                            same=1-same;
                            cout<<"10"<<endl;
                        }//if
                        
                        else {
                            for(int i = 0; i< tail->connections_size();i++) {
                                Node* neibor = tail->connections_at(i)->get_end(tail);
                                arg2=((same==1 && tail->get_cost()==2 && neibor->get_cost()==1) || (same==1 && tail->get_cost()==1 && neibor->get_cost()==2) || (same==0 && tail->get_cost()==2 && neibor->get_cost()==2) || (same==0 && tail->get_cost()==1 && neibor->get_cost()==1));
                                if(arg2) {
                                    cout<<"direction is "<<direction<<", checking tail "<<tail->get_y()<<" "<<tail->get_x()<<", cost "<<tail->get_cost()<<", checking neibor "<<neibor->get_y()<<" "<<neibor->get_x()<<", cost "<<neibor->get_cost()<<", same value"<<same<<endl;
                                    PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
                                    path->add_segment(new_segment);
                                    path->set_sink(neibor->get_coord());
                                    direction = this->direction(tail->get_coord(),neibor->get_coord());
                                    same=1-same;
                                    cout<<"11"<<endl;
                                    break;
                                }//if neibor == tail-1
                            }//for
                        }//else
                    }//if x+1<width
                    
                    else{
                        for(int i = 0; i< tail->connections_size();i++) {
                            Node* neibor = tail->connections_at(i)->get_end(tail);
                            arg2=((same==1 && tail->get_cost()==2 && neibor->get_cost()==1) || (same==1 && tail->get_cost()==1 && neibor->get_cost()==2) || (same==0 && tail->get_cost()==2 && neibor->get_cost()==2) || (same==0 && tail->get_cost()==1 && neibor->get_cost()==1));
                            if(arg2) {
                                cout<<"direction is "<<direction<<", checking tail "<<tail->get_y()<<" "<<tail->get_x()<<", cost "<<tail->get_cost()<<", checking neibor "<<neibor->get_y()<<" "<<neibor->get_x()<<", cost "<<neibor->get_cost()<<", same value"<<same<<endl;
                                PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
                                path->add_segment(new_segment);
                                path->set_sink(neibor->get_coord());
                                direction = this->direction(tail->get_coord(),neibor->get_coord());
                                same=1-same;
                                cout<<"12"<<endl;
                                break;
                            }//if neibor == tail-1
                        }//for
                    }//else
                    
                    break;
            }//switch case
        }//else for tail!=1
    }//whilie
    this->paths.push_back(path);
}




void Algorithm::Twobit::traceback(int fl, Path* path) {
    cout<<"use reguler way"<<endl;
    int flag = 0;
    int same = fl;
    while(flag!=1) {
        
	    for(int i = 0; i< this->map->get_node(path->get_sink())->connections_size();i++) {
	        Node* tail = this->map->get_node(path->get_sink());
            Node* neibor = tail->connections_at(i)->get_end(tail);
            if(same == 1) {
                if(neibor->get_cost()==-2) {
                    PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
                    path->add_segment(new_segment);
                    path->set_sink(neibor->get_coord());
                    flag = 1;
                    break;
                }
                
                if(tail->get_cost()==2) {
                    if(neibor->get_cost()==1) {
                        PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
                        path->add_segment(new_segment);
                        path->set_sink(neibor->get_coord());
                        same = 0;
                    }
                }
                
                if(tail->get_cost()==1) {
                    if(neibor->get_cost()==2) {
                        PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
                        path->add_segment(new_segment);
                        path->set_sink(neibor->get_coord());
                        same = 0;
                    }
                }
            }
            else{
                if(neibor->get_cost()==-2) {
                    PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
                    path->add_segment(new_segment);
                    path->set_sink(neibor->get_coord());
                    flag = 1;
                    break;
                }
                
                if(tail->get_cost()==2) {
                    if(neibor->get_cost()==2) {
                        PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
                        path->add_segment(new_segment);
                        path->set_sink(neibor->get_coord());
                        same = 1;
                    }
                }
                
                if(tail->get_cost()==1) {
                    if(neibor->get_cost()==1) {
                        PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
                        path->add_segment(new_segment);
                        path->set_sink(neibor->get_coord());
                        same = 1;
                    }
                }
            }
            
            
	    }//for
    }//whilie
    this->paths.push_back(path);
}

vector<Path*> Algorithm::Twobit::get_paths() {
    return this->paths;
}


vector<Connection> Algorithm::Twobit::get_connection() {
    return this->connection ;
}


int Algorithm::Twobit::direction(Point source,Point sink) {
    int direction;//0 up      1 left      2 down        3 right
    if (sink.x == source.x) {
        if (sink.y > source.y) {
            direction = 2;//backtrace to down
        }
        else{
            direction = 0;//up
        }
    }
    else{
        if (sink.x > source.x) {
            direction = 3;//right
        }
        else{
            direction = 1;//left
        }
    }
    return direction;
}



Node* Algorithm::Twobit::min_node(vector<Node*> others) {
    int get_pos = 0;
    int get_min = others.at(0)->get_distance();
    for(int i = 0;i < others.size();i++) {
        if(others.at(i)->get_distance() < get_min) {
            get_min = others.at(i)->get_distance();
            get_pos = i;
        }
    }
    Node* n = others.at(get_pos);
    others.erase ( others.begin() + get_pos );
    return n;
}


void Algorithm::Twobit::set_ruben_trace(int i) {
    this->ruben_trace = i;
}


void Algorithm::Twobit::set_cross(int i) {
    this->cross = i;
}
