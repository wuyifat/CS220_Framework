#include "../Headers/bidirection.h"
#include <iostream>

using std::cout;
using std::endl;
using std::queue;
using std::vector;

Algorithm::Bidirection::Bidirection(Map *m) {
    map = m;
    connection = m->get_connection();
    number = m->get_connection().size();
    for (int i= 0; i < number; i++) {
        source.push_back(map->get_node(connection.at(i).source));
        sink.push_back(map->get_node(connection.at(i).sink));
    }
    // make the value of isVisited of all block nodes into -1
    for(int y = 0; y < map->get_height(); y++) {
        for(int x = 0; x < map->get_width(); x++) {
            if(map->get_node(x,y)->get_cost()==-1) {
                map->get_node(x,y)->set_is_visited(-1); // block
            }//if
            else
                map->get_node(x,y)->set_is_visited(0); // visible nodes
        }//for x
    }//for y
    // debug function: check whether isVisited function is correct
/*    for(int y = 0; y < map->get_height(); y++) {
        for(int x = 0; x < map->get_width(); x++) {
            cout<<map->get_node(x,y)->get_is_visited()<<"\t";
        }//for x
        cout<<endl;
    }//for y*/
}

Algorithm::Bidirection::~Bidirection() {
    //no need to destruct since there is no new allocated space
}

void Algorithm::Bidirection::run() {
    for(int curConnection = 0; curConnection<number; curConnection++) {
        // if it is not the first time to do the algorithm, we need to initialize the costs of all nodes in the map
        if(curConnection != 0) {
            for(int y = 0; y < map->get_height();y++) {
                for(int x = 0; x < map->get_width();x++) {
                    if(map->get_node(x,y)->get_cost()!=-1) {
                        map->get_node(x,y)->set_cost(0); //reset cost to 0
                        map->get_node(x,y)->set_is_visited(0); //reset isVisited to 0
                    }//if
                }//for x
            }//for y
        }// if curConnection
        
        // set the cost of source and sink -2 and -3, respectively
        source.at(curConnection)->set_cost(-2);
        sink.at(curConnection)->set_cost(-3);
        map->get_node(source.at(curConnection)->get_x(), source.at(curConnection)->get_y())->set_is_visited(1);
        map->get_node(sink.at(curConnection)->get_x(), sink.at(curConnection)->get_y())->set_is_visited(2);
        
        // use a flag to determine whether source and sink expansion meets. If yes then flag==true, vice versa.
        bool flag = false;
        
        // everything here is same to the corresponding part of lee.cc, the only difference is that I copied all
        //temporary parameters into two parts. One is for source expansion and another one is for sink expansion
        int valueSource = 0;
        int valueSink = 0;
        
        
        // to optimize: to write all four similar expansions into one function
        queue<Node*> q1Source,q1Sink,q2Source,q2Sink;
        Node* meetPointsSource=0;
        Node* meetPointsSink=0;
        
        // Source expansion using q1
        q1Source.push(source.at(curConnection));
        q1Sink.push(sink.at(curConnection));
        
        while(flag != true) {
            int f1Source=0;
            int f1Sink=0;
            int f2Source=0;
            int f2Sink=0;
//            map->display_map();
            
            while(!q1Source.empty()) { // Source black box first
                if(flag == true) { // if source and sink expansions meet
                    break;
                }
                f1Source++;
                if(f1Source == 1) {
                    if(q2Source.empty()) {
                        valueSource++;
                    }
                }
                Node *tempSource = q1Source.front();
                q1Source.pop();
                for(int j = 0; j<tempSource->connections_size(); j++) {
                    Node* neiborSource = tempSource->connections_at(j)->get_end(tempSource);
                    // if this node is visited by sink expansion
                    if(map->get_node(neiborSource->get_x(),neiborSource->get_y())->get_is_visited() == 2) {
                        flag = true;
                        this->meetPointsSource.push_back(tempSource);
                        this->meetPointsSink.push_back(neiborSource);
                        break;
                    } // trace back will be done later
                    // visited by source expansion, therefore set as 1
                    if(map->get_node(neiborSource->get_x(),neiborSource->get_y())->get_is_visited() == 0) {
                        map->get_node(neiborSource->get_x(),neiborSource->get_y())->set_is_visited(1);
                        map->get_node(neiborSource->get_coord())->set_cost(valueSource);
                        
                        q2Source.push(neiborSource);
                    } //if
                } // for
            } // whileq1Source
//            map->display_map();
            
            while(!q1Sink.empty()) { // Sink black box second
                if(flag == true) { // if source and sink expansions meet
                    break;
                }
                f1Sink++;
                if(f1Sink == 1) {
                    if(q2Sink.empty()) {
                        valueSink++;
                    }
                }
                Node *tempSink = q1Sink.front();
                q1Sink.pop();
                for(int j = 0; j<tempSink->connections_size(); j++) {
                    Node* neiborSink = tempSink->connections_at(j)->get_end(tempSink);
                    // if this node is visited by source expansion
                    if(map->get_node(neiborSink->get_x(),neiborSink->get_y())->get_is_visited() == 1) {
                        flag = true;
                        this->meetPointsSink.push_back(tempSink);
                        this->meetPointsSource.push_back(neiborSink);
                        break;
                    } // trace back will be done later
                    // visited by sink expansion, therefore set as 2
                    if(map->get_node(neiborSink->get_x(),neiborSink->get_y())->get_is_visited() == 0) {
                        map->get_node(neiborSink->get_x(),neiborSink->get_y())->set_is_visited(2);
                        map->get_node(neiborSink->get_coord())->set_cost(valueSink);
                        //                        map->display_map();
                        q2Sink.push(neiborSink);
                    } //if
                } // for
            } // whileq1Sink
//            map->display_map();
            
            while(!q2Source.empty()) { // Source white box third
                if(flag == true) { // if source and sink expansions meet
                    break;
                }
                f2Source++;
                if(f2Source == 1) {
                    if(q1Source.empty()) {
                        valueSource++;
                    }
                }
                Node *tempSource = q2Source.front();
                q2Source.pop();
                for(int j = 0; j<tempSource->connections_size(); j++) {
                    Node* neiborSource = tempSource->connections_at(j)->get_end(tempSource);
                    // if this node is visited by sink expansion
                    if(map->get_node(neiborSource->get_x(),neiborSource->get_y())->get_is_visited() == 2) {
                        flag = true;
                        this->meetPointsSource.push_back(tempSource);
                        this->meetPointsSink.push_back(neiborSource);
                        break;
                    } // trace back will be done later
                    // visited by source expansion, therefore set as 1
                    if(map->get_node(neiborSource->get_x(),neiborSource->get_y())->get_is_visited() == 0) {
                        map->get_node(neiborSource->get_x(),neiborSource->get_y())->set_is_visited(1);
                        
                        map->get_node(neiborSource->get_coord())->set_cost(valueSource);
                        q1Source.push(neiborSource);
                    } //if
                } // for
            } // whileq2Source
//            map->display_map();
            
            while(!q2Sink.empty()) { // Sink white box fourth
                if(flag == true) { // if source and sink expansions meet
                    break;
                }
                f2Sink++;
                if(f2Sink == 1) {
                    if(q1Sink.empty()) {
                        valueSink++;
                    }
                }
                Node *tempSink = q2Sink.front();
                q2Sink.pop();
                for(int j = 0; j<tempSink->connections_size(); j++) {
                    Node* neiborSink = tempSink->connections_at(j)->get_end(tempSink);
                    // if this node is visited by source expansion
                    if(map->get_node(neiborSink->get_x(),neiborSink->get_y())->get_is_visited() == 1) {
                        flag = true;
                        this->meetPointsSink.push_back(tempSink);
                        this->meetPointsSource.push_back(neiborSink);
                        break;
                    } // trace back will be done later
                    // visited by sink expansion, therefore set as 2
                    if(map->get_node(neiborSink->get_x(),neiborSink->get_y())->get_is_visited() == 0) {
                        map->get_node(neiborSink->get_x(),neiborSink->get_y())->set_is_visited(2);
                        
                        map->get_node(neiborSink->get_coord())->set_cost(valueSink);
                        q1Sink.push(neiborSink);
                    } //if
                } // for
            } // whileq2Sink
//            map->display_map();
        }//whileq2sink
        map->display_map();
        traceback(curConnection);
    }//forconnection
}

void Algorithm::Bidirection::traceback(int curConnection) {
    // trace back the path from meetPointsSource to Source, known isVisited matrix and map matrix
    bool flag=false;
    
    Node* curNode = this->meetPointsSource.at(curConnection);
    Node* nxtNode = 0;
    // start tracing back of source expansion
    Path* newPathSource = new Path();
    while(curNode != this->source.at(curConnection)) {
        for(int i = 0; i < curNode->connections_size(); i++) {
            // find the adjacent node
            nxtNode = curNode->connections_at(i) -> get_end(curNode);
            // visited by source, and less distance to the source
            
            if(map->get_node(nxtNode->get_x(),nxtNode->get_y())->get_is_visited() == 1 &&
               ((nxtNode->get_cost() == curNode ->get_cost()-1) || (nxtNode->get_cost() == -2))) {
                PathSegment* new_segment = new PathSegment(curNode->get_coord(),nxtNode->get_coord());
                newPathSource->add_segment(new_segment);
//                cout<<"Current source path: \n";
//                newPathSource->display_path();
//                cout<<"\n";
                curNode = nxtNode;
                if(curNode->get_cost() ==-2) {
                    break;
                }
            } //if
        } //for
    } // while
    // start tracing back from tail expansion
    
    curNode = this->meetPointsSink.at(curConnection);
    nxtNode = 0;
    // start tracing back of sink expansion
    Path* newPathSink = new Path();
    while(curNode != this->sink.at(curConnection)) {
        for(int i = 0; i < curNode->connections_size(); i++) {
            // find the adjacent node
            nxtNode = curNode->connections_at(i) -> get_end(curNode);
            // visited by source, and less distance to the source
            if(map->get_node(nxtNode->get_x(),nxtNode->get_y())->get_is_visited() == 2 &&
               ((nxtNode->get_cost() == curNode ->get_cost()-1) || (nxtNode->get_cost() == -3))) {
                PathSegment* new_segment = new PathSegment(curNode->get_coord(),nxtNode->get_coord());
                newPathSink->add_segment(new_segment);
//                cout<<"Current sink path: \n";
//                newPathSink->display_path();
//                cout<<"\n";
                curNode = nxtNode;
                if(curNode->get_cost() ==-3) {
                    break;
                }
            } //if
        } //for
    } // while
    
    // concatenate them, note that the sequence of sink expansion should be reversed
    Path* newPath = new Path();
    for(int i = newPathSink->get_length()-1; i>-1; i--) {
        newPathSink->at(i)->reverse();
        newPath->add_segment(newPathSink->at(i));
    }
    
    PathSegment* conc = new PathSegment(meetPointsSink.at(curConnection)->
                                        get_coord(),meetPointsSource.at(curConnection)->get_coord());
    newPath->add_segment(conc);
    
    for(int i = 0; i<newPathSource->get_length(); i++) {
        newPath->add_segment(newPathSource->at(i));
    }
    this->paths.push_back(newPath);
    
//    cout<<"Path "<<curConnection+1<<": ";
//    newPath->display_path();
/*    while(!newPathSource->empty()) {
        newPathSource->remove_segment(0);
    }
    while(!newPathSink->empty()) {
        newPathSink->remove_segment(0);
    }*/
}

vector<Path*> Algorithm::Bidirection::get_paths() {
    return paths;
}

