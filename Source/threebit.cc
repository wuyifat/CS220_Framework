/* Filename: threebit.cc
 * Author: Deen Ma
 * Date: 12/12/2014
 * Description:
 run(): is to run the whole program. The general steps includes initialization, expansion, termination. See function comments for details
 traceback(Path* path): Retrieve the path back to the original point (source or sink). See function comments for details when we don't consider the min-turn.
 traceback(Path* path, int i): Retrieve the path back to the original point (source or sink). See function comments for details when we  consider the min-turn.
 min_node(): return the surrounding node with the minimal cost value.
 direction(): return the direction of two nodes. 0 up, 1 left, 2 down, 3 right
 */

#include "../Headers/threebit.h"
#include <iostream>
using std::cout;
using std::endl;
using std::cin;

Algorithm::Threebit::Threebit(Map* m) {
    while(set_cross()) {
        cout << "Invalid cross value. Input again." << endl << endl;
    }
    while(set_min_turn()) {
        cout << "Invalid min_turn value. Input again." << endl << endl;
    }
    this->map = m;
    this->connection = m->get_connection();
    this->number = m->get_connection().size();
    for (int i = 0; i < this->number; i++) {
        this->source.push_back(this->map->get_node(this->connection.at(i).source));
        this->sink.push_back(this->map->get_node(this->connection.at(i).sink));
    }
}

//Algorithm::Threebit::~Threebit() {

//empty destory function
//}


void Algorithm::Threebit::run() {
    /*
     input: source-sink pair and block information included in the map.
     output: vector of paths.
     steps:
     1. Initialization of costs.
     At our program, source has a cost of -2, sink -3, block nodes -1, unvisited nodes 0.
     2. For expansion of source and sink: we set two queues as data structure to store the expanded nodes. Just like the black and white pixels on a grid. The adjacent nodes have different color. When we expand the white nodes in the first iteration, we have to expand black nodes in the second expansion. q1 and q2 represents the black and white pixels.
     3. The end criteria is when we find neibor.cost==-3, which means we find the sink.
     */
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
                        if(value == 3) {
                            value = 1;
                        }
                        else {
                            value++;
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
//                        cout<< "!!!!!!!!!!!!!!!!NOW I FOUND THE SINK!!!!!!!!!!!!!!!!!!!!"<<endl;
                        if(ruben_trace == 1) {
                            this->traceback(new_path,ruben_trace);
                        }
                        else {
                            this->traceback(new_path);
                        }
                        break;
                    }
                    if(neibor->get_cost() == 0) {
                        neibor->set_cost(value);
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
                        if(value == 3) {
                            value = 1;
                        }
                        else {
                            value++;
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
                            this->traceback(new_path,ruben_trace);
                        }
                        else{
                            this->traceback(new_path);
                        }
                        break;
                    }
                    if(neibor->get_cost() == 0) {
                        neibor->set_cost(value);
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


Map* Algorithm::Threebit::get_map() {
    return this->map;
}

void Algorithm::Threebit::traceback(Path* path,int i) {
    /* Retrieve the path back to the original point (source or sink) considering the minimum turn.
     output: a path
     input: source-sink pair.
     steps:
     1. We find the direction of the first path segment (sink and a node neibor to sink)
     2. Try to move on this direction as long as possible, unless we cannot move further (several factors can lead to this: 1. The cost in this direction no longer decrease, 2. hit the block or the bound of the map)
     3. Switch direction when we have to. (See the factors described on 2)
     4. Repeat 2 and 3 until find source.
     */
    
//    cout<<"use ruben!!!!!!!!!!"<<endl;
    int direction;//0 up      1 left      2 down        3 right
    direction = this->direction(path->get_source(),path->get_sink());
    int flag = 0;
    int x,y;
    bool arg;
    while(flag!=1) {
        Node* tail = this->map->get_node(path->get_sink());
        x = tail->get_x();
        y = tail->get_y();
        
        //if we found the last point flag = 1
        // differ from lee here
        arg = false; // arg is true when tail is next to source, otherwise false;
        if(tail->get_cost()==1) {
            for(int i = 0; i< tail->connections_size();i++) {
                Node* neibor = tail->connections_at(i)->get_end(tail);
                if(neibor->get_cost()==-2) { // tail next to source
                    arg=true;
                    break;
                }
            }
        }
        
        if(arg) {
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
                        //if in seme direction the next node's cost is less one than sink then add it in path
                        if(neibor->get_cost()==tail->get_cost()-1 || (neibor->get_cost()==3 && tail->get_cost()==1)) {
//                            cout<<"direction is "<<direction<<", checking tail "<<tail->get_y()<<" "<<tail->get_x()<<", checking neibor "<<neibor->get_y()<<" "<<neibor->get_x()<<endl;
                            PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
                            path->add_segment(new_segment);
                            path->set_sink(neibor->get_coord());
                            direction = this->direction(tail->get_coord(),neibor->get_coord());
                        }//if
                        
                        else{
                            for(int i = 0; i< tail->connections_size();i++) {
                                Node* neibor = tail->connections_at(i)->get_end(tail);
                                if(neibor->get_cost()==tail->get_cost()-1 || (neibor->get_cost()==3 && tail->get_cost()==1)) {
                                    PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
                                    path->add_segment(new_segment);
                                    path->set_sink(neibor->get_coord());
                                    direction = this->direction(tail->get_coord(),neibor->get_coord());
                                }//if neibor == tail-1
                            }//for
                        }//else
                    }//if y-1>0
                    
                    else{
                        for(int i = 0; i< tail->connections_size();i++) {
                            Node* neibor = tail->connections_at(i)->get_end(tail);
                            if(neibor->get_cost()==tail->get_cost()-1 || (neibor->get_cost()==3 && tail->get_cost()==1)) {
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
                    if(y+1 < this->map->get_height()) {
                        Node* neibor = this->map->get_node(x,y+1);
                        //if in seme direction the next node's cost is less one than sink then add it in path
                        if(neibor->get_cost()==tail->get_cost()-1 || (neibor->get_cost()==3 && tail->get_cost()==1)) {
                            PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
                            path->add_segment(new_segment);
                            path->set_sink(neibor->get_coord());
                            direction = this->direction(tail->get_coord(),neibor->get_coord());
                        }//if
                        
                        else {
                            for(int i = 0; i< tail->connections_size();i++) {
                                Node* neibor = tail->connections_at(i)->get_end(tail);
                                if(neibor->get_cost()==tail->get_cost()-1 || (neibor->get_cost()==3 && tail->get_cost()==1)) {
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
                            if(neibor->get_cost()==tail->get_cost()-1 || (neibor->get_cost()==3 && tail->get_cost()==1)) {
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
                        //if in seme direction the next node's cost is less one than sink then add it in path
                        if(neibor->get_cost()==tail->get_cost()-1 || (neibor->get_cost()==3 && tail->get_cost()==1)) {
                            PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
                            path->add_segment(new_segment);
                            path->set_sink(neibor->get_coord());
                            direction = this->direction(tail->get_coord(),neibor->get_coord());
                        }//if
                        
                        else {
                            for(int i = 0; i< tail->connections_size();i++) {
                                Node* neibor = tail->connections_at(i)->get_end(tail);
                                if(neibor->get_cost()==tail->get_cost()-1 || (neibor->get_cost()==3 && tail->get_cost()==1)) {
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
                            if(neibor->get_cost()==tail->get_cost()-1 || (neibor->get_cost()==3 && tail->get_cost()==1)) {
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
                        if(neibor->get_cost()==tail->get_cost()-1 || (neibor->get_cost()==3 && tail->get_cost()==1)) {
                            PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
                            path->add_segment(new_segment);
                            path->set_sink(neibor->get_coord());
                            direction = this->direction(tail->get_coord(),neibor->get_coord());
                        }//if
                        
                        else {
                            for(int i = 0; i< tail->connections_size();i++) {
                                Node* neibor = tail->connections_at(i)->get_end(tail);
                                if(neibor->get_cost()==tail->get_cost()-1 || (neibor->get_cost()==3 && tail->get_cost()==1)) {
                                    PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
                                    path->add_segment(new_segment);
                                    path->set_sink(neibor->get_coord());
                                    direction = this->direction(tail->get_coord(),neibor->get_coord());
                                }//if neibor == tail-1
                            }//for
                        }//else
                    }//if x+1<width
                    
                    else{
                        for(int i = 0; i< tail->connections_size();i++) {
                            Node* neibor = tail->connections_at(i)->get_end(tail);
                            if(neibor->get_cost()==tail->get_cost()-1 || (neibor->get_cost()==3 && tail->get_cost()==1)) {
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




void Algorithm::Threebit::traceback(Path* path) {
    /* Retrieve the path back to the original point (source or sink) without considering the minimum turn.
     output: a path
     input: source-sink pair.
     steps:
     1. Back tracing: Find the neibor node, with the same is_visited value and with cost one less than current node. After finding it, create a path segment to store this pair
     2. Stop criteria: when finding the source (cost -2).
   */

//    cout<<"use reguler way"<<endl;
    int flag = 0;
    while(flag!=1) {
        for(int i = 0; i< this->map->get_node(path->get_sink())->connections_size();i++) {
            Node* tail = this->map->get_node(path->get_sink());
            Node* neibor = tail->connections_at(i)->get_end(tail);
            if(tail->get_cost()==1) {
                if(neibor->get_cost()==3) {
                    PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
                    path->add_segment(new_segment);
                    path->set_sink(neibor->get_coord());
                }
                if(neibor->get_cost()==-2) {
                    PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
                    path->add_segment(new_segment);
                    path->set_sink(neibor->get_coord());
                    flag = 1;
                }
            }//if is call for last point
            else if(neibor->get_cost() == tail->get_cost()-1) {
                PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
                path->add_segment(new_segment);
                path->set_sink(neibor->get_coord());
            }//if neibor == tail-1
        }//for
    }//whilie
    this->paths.push_back(path);
}

vector<Path*> Algorithm::Threebit::get_paths() {
    return this->paths;
}


vector<Connection> Algorithm::Threebit::get_connection() {
    return this->connection ;
}


int Algorithm::Threebit::direction(Point source,Point sink) {
    /* direction(): return the direction of two nodes. 0 up, 1 left, 2 down, 3 right
  */
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



Node* Algorithm::Threebit::min_node(vector<Node*> others) {
/*
 min_node(): return the surrounding node with the minimal cost value.
 */
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


bool Algorithm::Threebit::set_cross() {
    int temp_cross;
    cout << "Input 0 or 1 to choose if paths are allowed to cross. 0 = not allowed. 1 = allow" << endl;
    cin >> temp_cross;
    if ((temp_cross==1)||(temp_cross==0)) {
        this->cross = temp_cross;
        return false;
    }
    else 
        return true;
}

bool Algorithm::Threebit::set_min_turn() {
    int temp_turn;
    cout << "Input 0 or 1 to choose if need min number of turns in the path. 0 = don't care. 1 = min turn" << endl;
    cin >> temp_turn;
    if ((temp_turn==1)||(temp_turn==0)) {
        this->ruben_trace = temp_turn;
        return false;
    }
    else 
        return true;
}
