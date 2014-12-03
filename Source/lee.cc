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
		cout << endl <<" q1 working"<< endl;
                f1++;
                if(f1 == 1){
                    if(q2.empty()){
                        value++;
                    }
                }
                Node* temp = q1.front();
                temp->display_node();
                q1.pop();
                for(int j = 0; j < temp->connections_size();j++){                
                    Node* neibor = (temp->connections_at(j))->get_end(temp);
                    cout<< "this is neibor::";
                    neibor->display_node();
                    cout << "it's neibor size is "<< temp->connections_size();
                   if(neibor->get_cost() == -3){
                        cout << "now is sink time !!"<<endl;
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
                        cout << "now seting the node ("<<neibor->get_x()<<", "<< neibor->get_y()<<" ) cost to "<< value<< endl;
                        map->display_map();
                        q2.push(neibor);
                    }//if
                    else{
                        cout << "Don't need to seting the node ("<<neibor->get_x()<<", "<< neibor->get_y()<<" ) cost,its cost "<< neibor->get_cost() << endl;
                    }//else
                }//for
             }//whileq1

		cout << endl <<"now swich to q2"<< endl;
             while(!q2.empty()){
               if(flag == 1){
                    break;
                }
		cout << endl <<" q2 working"<< endl;
                f2++;
                if (f2 == 1){
                    if(q1.empty()){
                        value++;
                    }
                }
                Node* temp = q2.front();
                temp->display_node();
                cout << "it's neibor size is "<< temp->connections_size();
                q2.pop();
                for(int j = 0; j < temp->connections_size();j++){                
                    Node* neibor = (temp->connections_at(j))->get_end(temp);
                    cout<< "this is neibor::";
                    neibor->display_node();
                    if(neibor->get_cost() == -3){
                        cout << "now is sink time !!"<<endl;
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
                        cout << "now seting the node ("<<neibor->get_x()<<", "<< neibor->get_y()<<" ) cost to "<< value<< endl;
                        (this->map->get_node(neibor->get_coord()))->set_cost(value);

                        map->display_map();
                        q1.push(neibor);
                    }//if
		    else{
                        cout << "Don't need to seting the node ("<<neibor->get_x()<<", "<< neibor->get_y()<<" ) cost,its cost "<< neibor->get_cost() << endl;
                    }//else

                }//for
             }//whileq2

		cout << endl <<"now swich to q1"<< endl;
        }//while flag
    }//for path number
    return this->paths; 
}
Map* Algorithm::Lee::get_map(){
    return this->map;
}
