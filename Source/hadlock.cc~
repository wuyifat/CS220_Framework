	#include "../Headers/hadlock.h"
	#include <iostream>
	#include <cmath>
	#include <stack>
	using std::cout;
	using std::endl;
	using std::stack;

	Algorithm::Hadlock::Hadlock(Map* m){
	    this->map = m;
	    this->connection = m->get_connection();
	    this->number = m->get_connection().size();
	    for (int i = 0; i < this->number; i++){
		this->source.push_back(this->map->get_node(this->connection.at(i).source));
		this->sink.push_back(this->map->get_node(this->connection.at(i).sink));
	    }
	}

	//Algorithm::Hadlock::~Hadlock(){

	//empty destory function
	//}

	void Algorithm::Hadlock::reset_map(){
	    for(int y = 0; y < this->map->get_height();y++){
		for(int x = 0; x < this->map->get_width();x++){
		    if(this->map->get_node(x,y)->get_cost()!=-1){
			this->map->get_node(x,y)->set_cost(0);//reset cost to 0
			this->map->get_node(x,y)->set_flag(0);
			this->map->get_node(x,y)->set_m_d(0);
			this->map->get_node(x,y)->set_detour(100);
		    }
		}
	     }
	}

	void Algorithm::Hadlock::forward(){
	    for(int i = 0;i <this->number;i++){//if we have i pair of sources and sinks, we need to do i times to find the path;

	//------------------------reset the map ------------------------------------------
	//if this is the first time to do the algorithm, we don't need to reset the map, if not, we need to reset every node's cost to 0 except blocker
		if(i != 0){
		    this->reset_map();
		}


	//------------------------set source and sink------------------------

		this->source.at(i)->set_detour(-2);//set source cost to -2
		this->sink.at(i)->set_detour(-3);//set sink cost to -3
		this->source.at(i)->set_cost(-2);//set source cost to -2
		this->sink.at(i)->set_cost(-3);//set sink cost to -3
		Point md = this->sink.at(i)->get_coord();//use for compute manhuatan distance
		double min_d = abs(md.x-source.at(i)->get_x())+abs( md.y - source.at(i)->get_y());
		int flag = 0;// this flag use to break while loop, if we found sink, the flag = 1 and break loop
		int first = 0;
		int value = 0;// ues for cost
int debug = 0;
		vector<Node*> small;
	//the basic ideal of this algorithm is use 2 queue to set the cost
		stack<Node*> q1,q2;
		q1.push(this->source.at(i));
		while(flag != 1){// while flag !=1 keep found sink

		    while(!q1.empty()){
/*
	if(debug==16)
  {
        flag==1;
break;
}		//if first =1 means this is first time run it
debug++;
*/
			Node* temp = q1.top();
			first++;
			q1.pop();
cout<<"get q1 is ";
temp->display_node();
			temp->set_flag(1);//this flag to check the node can only in to vector once
			for(int j = 0; j < temp->connections_size();j++){ 
			    Node* neibor = (temp->connections_at(j))->get_end(temp);
			    if(neibor->get_cost() == -3){//if we found sink we use traceback function to save the path
				flag = 1;
cout<<"!!!!!!!!!!!!!!!!!!!!!!now it's the time to trace back!!!"<<endl;
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
			    if(neibor->get_flag()!=1){ 
			        if (neibor->get_cost()==0){
                                if(first == 1){
		                    neibor->set_cost(1);
			        }
			        else{
                                    neibor->set_cost(temp->get_cost()+1);
				}
	//---------------------------set detour---------------------------
				    neibor->set_m_d(md,1);
				    int detour;
				    detour = neibor->get_md()-min_d;
				    if ( detour <= 0){
					neibor->set_detour(0);
				    }
				    else{
					 neibor->set_detour(detour/2);
				    }
			    }
cout<<" now push number into it small";
neibor->display_node();
			    small.push_back(neibor);
			    }//if get_flag()!=1
			}//for

			if(flag == 1){//if found sink 
			    break;
			}
			if(!small.empty()){
			    for(int kkk = 0;kkk < small.size();kkk++){
				    Node* tt = small.at(kkk);
if(temp->get_detour()==-2){

				    if (tt->get_detour() ==0){
			                q1.push(tt);
				    }
				   if( tt->get_detour() == 1 ){
					q2.push(tt);
				    }
}else{
				    if (tt->get_detour() == temp->get_detour()){
			                q1.push(tt);
				    }
				   if( tt->get_detour() == temp->get_detour()+1 ){
					q2.push(tt);
				    }
}				    //debug			cout<< "Push it from SMALL to OTHERS"<<endl;
			    }
			    small.clear();
			}
cout<<endl<< "cost   :";
			    this->map->display_map();

cout<< endl<<"manhatton :";
			    this->map->display_hantan();

cout<< endl<<"detour:";
			    this->map->display_detour();
		     }//whileq1

		    while(!q2.empty()){
			if(flag == 1){//if found sink 
			    break;
			}
			Node* temp = q2.top();
			q2.pop();
			temp->set_flag(1);//this flag to check the node can only in to vector once
			for(int j = 0; j < temp->connections_size();j++){                
			    Node* neibor = (temp->connections_at(j))->get_end(temp);
			    if(neibor->get_cost() == -3){//if we found sink we use traceback function to save the path
				flag = 1;
				// add a path to vector
				Path* new_path = new Path();
				PathSegment* new_segment = new PathSegment(neibor->get_coord(),temp->get_coord());
				this->map->display_md();
				this->map->display_detour();
				new_path->add_segment(new_segment);
				new_path->set_source(neibor->get_coord());
				new_path->set_sink(temp->get_coord());
				this->traceback(new_path);
				break;
			    }
			    if(neibor->get_flag()!=1){ 
				if(neibor->get_cost()==0){
                                    neibor->set_cost(temp->get_cost()+1);
	//---------------------------set detour---------------------------
				    neibor->set_m_d(md,1);
				    int detour;
				    detour = neibor->get_md()-min_d;
				    if ( detour <= 0){
					neibor->set_detour(0);
				    }
				    else{
					 neibor->set_detour(detour/2);
				    }
			    }
			    small.push_back(neibor);
			    }//if get_flag()!=1
			}//for

			if(!small.empty()){
			    for(int kkk = 0;kkk < small.size();kkk++){
				    Node* tt = small.at(kkk);
				    if (tt->get_detour() == temp->get_detour()){
			                q2.push(tt);
				    }
				    if( tt->get_detour() == temp->get_detour()+1 ){
					q1.push(tt);
				    }
				    //debug			cout<< "Push it from SMALL to OTHERS"<<endl;
			    }
			    small.clear();
			}//small empty
			    this->map->display_map();
			    this->map->display_md();
			    this->map->display_detour();
		     }//whileq2
        }//while flag
    }//for path number
}


Map* Algorithm::Hadlock::get_map(){
    return this->map;
}


void Algorithm::Hadlock::traceback(Path* path){
    int flag = 0;
    vector<Node*> small;
    stack<PathSegment*> q1,q2;
    q1.push(path->at(0)); 
    int first = 0;
    int need = 0;
int debug =0;
    int check = 0;//if check = 1 need to remove some path
    while(flag!=1){           
//--------------------------------------------------Q1--------------------
while(!q1.empty()){

debug++;
this->map->display_flag();
	if(check == 1){
	    check = 0;
	    need= 0;
cout<<"the size of q1 is "<< q1.size()<<endl<<endl;
	    Point branch = q1.top()->get_source();

int test = (path->get_sink()!=branch);

cout << "if the value is 1 then they are not equal     "<< test<<endl;
	    while(path->get_sink()!=branch){
cout<< "before remove:";
path->display_path();
		path->remove_segment(path->at(path->size()-1));
	        path->set_sink( path->at(path->size()-1)->get_sink());
cout<<endl<<"after";
path->display_path();
	    }
	    path->add_segment(q1.top());
	}
	Node* tail = this->map->get_node(q1.top()->get_sink()); 

	this->map->get_node(q1.top()->get_source())->set_flag(2); 
	q1.pop();
	tail->set_flag(2);
	need = 0;
cout<< "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!this is q1 and the tial is :";
tail->display_node();
cout<< endl;
	//if we found the last point flag = 1
	for(int i = 0; i< tail->connections_size();i++){
	    Node* neibor = tail->connections_at(i)->get_end(tail);
	    if(neibor->get_flag()==2){
cout<<"enter flag ==2 do nothing"<<endl;
	need++;
cout<< "now need is "<<need<<endl;
	    }
	    else{
	        if(neibor->get_cost()==-2){//if we found sink
		    PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
		    path->add_segment(new_segment);
		    path->set_sink(neibor->get_coord());
cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++I got the source@@@@@@@@@@@@@@@@@@"<<endl;
neibor->display_node();
		    flag = 1;
break;
		}//if neibor = -2
		else{

		    if(neibor->get_flag()==1){
			small.push_back(neibor);
			cout<< "push back in to small vetor"<<endl<<endl;}
		    else{
			need++;
		    }
		}
	    }

	}//end neibor size

if(flag==1){
break;
}



	    if(!small.empty()){

                    int get_pos = 0;
            	    int get_min = small.at(0)->get_detour();
   		    for(int kkk = 0;kkk < small.size();kkk++){
         		if(small.at(kkk)->get_detour() < get_min){
              		    get_min = small.at(kkk)->get_detour();
              		    get_pos = kkk;
         		}//if		
      		    }               



cout<<" small is not empty"<<endl<<endl;
		for(int kkk = 0;kkk < small.size();kkk++){
		    Node* tt = small.at(kkk);
cout<<"get a element in smalli "<<kkk<< " " ;
tt->display_node();
cout<<"and it's detour is "<<tt->get_detour();
cout<<endl<<endl;
cout<< "the get_pos is "<<get_pos<<endl;
                    if(kkk!= get_pos){
 cout<< "now enter kkk!=get_pos"<<endl;
			    if (tt->get_detour() == tail->get_detour()){

				    PathSegment* new_segment = new PathSegment(tail->get_coord(),tt->get_coord());
				    q2.push(new_segment);
				    tt->display_node();
				    cout<<" detour value equel push in q2  "<<tt->get_detour()<< endl;
			    }
			    if( tt->get_detour() == tail->get_detour()-1){
				    PathSegment* new_segment = new PathSegment(tail->get_coord(),tt->get_coord());

				    q1.push(new_segment);

				    tt->display_node();
				    cout<<"value is -1 so push in q1"<<tt->get_detour()<<endl;
			    }

			    if( tt->get_detour() == tail->get_detour()+1){
need++;
cout<<"tt=tail+1 so need is "<<need<<endl;
}
		    }//kkk!=pos
		}//endfor

		    Node* tt = small.at(get_pos);
			PathSegment* new_segment = new PathSegment(tail->get_coord(),tt->get_coord());
			path->add_segment(new_segment);
			path->set_sink(tt->get_coord());
cout<<"add a new path is ";
path->display_path();
cout<< "push the minin pathsegment to q1";
		    q1.push(new_segment);
		small.clear();
	    }//small empty
cout<<endl<<"the need value is "<< need<<" the check value is "<< check<<endl;
	    if(need == tail->connections_size()){
		    check++;
	    }
    }//end while q1

//--------------------------------------------------Q2--------------------
while(!q2.empty()){

this->map->display_flag();
	if(check == 1){
	    check = 0;
	    need= 0;
cout<<"t!!!!!!!!!!!!!!he size of q2      is "<< q2.size()<<endl<<endl;
	    Point branch = q2.top()->get_source();

int test = (path->get_sink()!=branch);
cout << "this test is "<< test;
	    while(path->get_sink()!=branch){

		path->remove_segment(path->at(path->size()-1));
	        path->set_sink( path->at(path->size()-1)->get_sink());
	    }
	    path->add_segment(q2.top());
	}
	first++;
	Node* tail = this->map->get_node(q2.top()->get_sink()); 
	q2.pop();
	tail->set_flag(2);
	need = 0;
cout<< "!------------------------------!this is q2 and the tial is :";
tail->display_node();
cout<< endl;
	//if we found the last point flag = 1
	for(int i = 0; i< tail->connections_size();i++){
	    Node* neibor = tail->connections_at(i)->get_end(tail);
	    if(neibor->get_flag()==2){
cout<<"enter flag ==2 do nothing"<<endl;
	need++;
	    }
	    else{
	        if(neibor->get_cost()==-2){//if we found sink
		    PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
		    path->add_segment(new_segment);
		    path->set_sink(neibor->get_coord());
cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++I got the source@@@@@@@@@@@@@@@@@@"<<endl;
neibor->display_node();
		    flag = 1;
break;
		}//if neibor = -2
		else{
		    if(neibor->get_flag()==1){
			small.push_back(neibor);
			cout<< "push back in to small vetor"<<endl<<endl;}
		    else{
			need++;
		    }
		}
	    }//else flag!=2

	}//end neibor size

if(flag==1){
break;
}

	    if(need == tail->connections_size()){
		    check++;
	    }

	    if(!small.empty()){

                    int get_pos = 0;
            	    int get_min = small.at(0)->get_detour();
   		    for(int kkk = 0;kkk < small.size();kkk++){
         		if(small.at(kkk)->get_detour() < get_min){
              		    get_min = small.at(kkk)->get_detour();
              		    get_pos = kkk;
         		}//if		
      		    }               



cout<<" small is not empty"<<endl<<endl;
		for(int kkk = 0;kkk < small.size();kkk++){
		    Node* tt = small.at(kkk);
cout<<"get a element in smalli "<<kkk<< "   ";
tt->display_node();
cout<<endl<<endl;
if(kkk!= get_pos){
		  if (tt->get_detour() == tail->get_detour()){

		        PathSegment* new_segment = new PathSegment(tail->get_coord(),tt->get_coord());
			q1.push(new_segment);
tt->display_node();
cout<<"push in q2  "<<tt->get_detour()<< endl;
		    }
		    if( tt->get_detour() == tail->get_detour()-1){
			PathSegment* new_segment = new PathSegment(tail->get_coord(),tt->get_coord());

			q2.push(new_segment);

tt->display_node();
cout<<"push in q1"<<tt->get_detour()<<endl;

			    if( tt->get_detour() == tail->get_detour()+1){
need++;
cout<<"tt=tail+1 so need is "<<need<<endl;
}
		    }
}//kkk!=pos

	}//endfor

		    Node* tt = small.at(get_pos);
			PathSegment* new_segment = new PathSegment(tail->get_coord(),tt->get_coord());
			path->add_segment(new_segment);
			path->set_sink(tt->get_coord());
		    q2.push(new_segment);
		small.clear();
	    }//small empty
    
}//whileq2
}//whili
    this->paths.push_back(path);
}


vector<Connection> Algorithm::Hadlock::get_connection(){
       return this->connection ;
}

vector<Path*> Algorithm::Hadlock::get_paths(){
    return this->paths;
}

