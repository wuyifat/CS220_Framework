	#include "../Headers/hadlock.h"
	#include <iostream>
	#include <cmath>
	#include <stack>
	using std::cout;
	using std::endl;
	using std::stack;

	Algorithm::Hadlock::Hadlock(Map* m) {
	    this->map = m;
	    this->cross = 0;
	    this->connection = m->get_connection();
	    this->number = m->get_connection().size();
	    for (int i = 0; i < this->number; i++) {
		this->source.push_back(this->map->get_node(this->connection.at(i).source));
		this->sink.push_back(this->map->get_node(this->connection.at(i).sink));
	    }
	}

	//Algorithm::Hadlock::~Hadlock() {

	//empty destory function
	//}

	void Algorithm::Hadlock::reset_map() {
	    for(int y = 0; y < this->map->get_height();y++) {
		for(int x = 0; x < this->map->get_width();x++) {
		    if(this->map->get_node(x,y)->get_cost()!=-1) {
			this->map->get_node(x,y)->set_cost(0);//reset cost to 0
			this->map->get_node(x,y)->set_flag(0);
			this->map->get_node(x,y)->set_m_d(0);
			this->map->get_node(x,y)->set_detour(100);
		    }
		}
	     }
	}

	void Algorithm::Hadlock::run() {
	    for(int i = 0;i <this->number;i++) {//if we have i pair of sources and sinks, we need to do i times to find the path;

	//------------------------reset the map ------------------------------------------
	//if this is the first time to do the algorithm, we don't need to reset the map, if not, we need to reset every node's cost to 0 except blocker
		if(i != 0) {
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

		int direction;
		int x = 0;
		int y = 0;
		int check = 0;
		int debug = 0;
		//the basic ideal of this algorithm is use 2 queue to set the cost

		stack<Node*> q1,q2;
		vector<Node*> others;
		q1.push(this->source.at(i));
		Node* last = new Node(0,0);
		Node* temp = new Node(0,0);
		int first = 0;
	//the basic ideal of this algorithm is use 2 queue to set the cost

		while(flag != 1) {// while flag !=1 keep found sink

		    while(!q1.empty()) {
/*
	if(debug==16)
  {
        flag==1;
break;
}		//if first =1 means this is first time run it
debug++;
*/
			temp = q1.top();
			x = temp->get_x();
			y = temp->get_y();
			q1.pop();
cout<<"get q1 is ";
temp->display_node();
			temp->set_flag(1);//this flag to check the node can only in to vector once
			Node* neibor = new Node(0,0);

if(first != 0){                
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
		if (check == 0){
			if(neibor->get_flag()!=1) { 
				if(neibor->get_cost() == -3) {//if we found sink we use traceback function to save the path
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
				if (neibor->get_cost()==0) {
					if(first == 0) {
						neibor->set_cost(1);
					}
					else{
						neibor->set_cost(temp->get_cost()+1);
					}
					//---------------------------set detour---------------------------
					neibor->set_m_d(md,1);
					int detour;
					detour = neibor->get_distance()-min_d;
					if ( detour <= 0) {
						neibor->set_detour(0);
					}
					else{
						neibor->set_detour(detour/2);
					}
				}
				if (neibor->get_detour() == temp->get_detour()) {
					direction = this->direction(temp->get_coord(),neibor->get_coord());
					last = temp;
					q1.push(neibor);
				}
				if( neibor->get_detour() == temp->get_detour()+1 ) {
					others.push_back(neibor);
					check = 1;
				}
			}//if get_flag()!=1
		}//check
}//switch
		if(check == 1 || first == 0){

			for(int j = 0; j < temp->connections_size();j++) { 
				neibor = (temp->connections_at(j))->get_end(temp);

				if(neibor->get_flag()!=1) { 
					if(neibor->get_cost() == -3) {//if we found sink we use traceback function to save the path
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

					if (neibor->get_cost()==0) {
						if(first == 0) {
							neibor->set_cost(1);
						}
						else{
							neibor->set_cost(temp->get_cost()+1);
						}
						//---------------------------set detour---------------------------
						neibor->set_m_d(md,1);
						int detour;
						detour = neibor->get_distance()-min_d;
						if ( detour <= 0) {
							neibor->set_detour(0);
						}
						else{
							neibor->set_detour(detour/2);
						}
					}
					cout<<" now push number into it small";
					neibor->display_node();

					if(temp->get_detour()==-2) {

						if (neibor->get_detour() ==0) {

							direction = this->direction(temp->get_coord(),neibor->get_coord());
							last = temp;
							q1.push(neibor);
						}
						if( neibor->get_detour() == 1 ) {
							others.push_back(neibor);
						}
					}else{
						if (neibor->get_detour() == temp->get_detour()) {

							direction = this->direction(temp->get_coord(),neibor->get_coord());
							last = temp;
							q1.push(neibor);
						}
						if( neibor->get_detour() == temp->get_detour()+1 ) {
							others.push_back(neibor);
						}
					}				    //debug			cout<< "Push it from SMALL to OTHERS"<<endl;
				}//if get_flag()!=1
			}//for
		}//check =1

			if(flag == 1) {//if found sink 
			    break;
			}
			first++;
		     }//whileq1

             if(q1.empty() ){//if q1 empty q2 empty, found element in vector
		 int get_pos = 0;
		 int get_min = others.at(0)->get_distance();
		 for(int i = 0;i < others.size();i++){
			 if(others.at(i)->get_distance() <= get_min){
				 get_min = others.at(i)->get_distance();
				 get_pos = i;
			 }
		 }
		 Node* tt = others.at(get_pos);
		 others.erase ( others.begin() + get_pos );
		 min_d = tt->get_distance();
		 direction = this->direction(last->get_coord(),tt->get_coord());
                 last = temp;
cout<< "now from OTHERS0 push to Q1"<<endl;
tt->display_node();
                 q1.push(tt);
             }//if q1 q2 empty             
        }//while flag

        if(this->cross == 0) {
		Path* t = this->paths.at(i);
            this->map->add_blocker(t);
        }
    }//for path number
}


Map* Algorithm::Hadlock::get_map() {
    return this->map;
}


void Algorithm::Hadlock::traceback(Path* path) {
    int flag = 0;
    vector<Node*> small;
    stack<PathSegment*> q1,q2;
    q1.push(path->at(0)); 
    int first = 0;
    int need = 0;
int debug =0;
    int check = 0;//if check = 1 need to remove some path
    while(flag!=1) {           
//--------------------------------------------------Q1--------------------
while(!q1.empty()) {

debug++;
this->map->display_flag();
	if(check == 1) {
	    check = 0;
	    need= 0;
cout<<"the size of q1 is "<< q1.size()<<endl<<endl;
	    Point branch = q1.top()->get_source();

int test = (path->get_sink()!=branch);

cout << "if the value is 1 then they are not equal     "<< test<<endl;
	    while(path->get_sink()!=branch) {
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
	for(int i = 0; i< tail->connections_size();i++) {
	    Node* neibor = tail->connections_at(i)->get_end(tail);
	    if(neibor->get_flag()==2) {
cout<<"enter flag ==2 do nothing"<<endl;
	need++;
cout<< "now need is "<<need<<endl;
	    }
	    else{
	        if(neibor->get_cost()==-2) {//if we found sink
		    PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
		    path->add_segment(new_segment);
		    path->set_sink(neibor->get_coord());
cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++I got the source@@@@@@@@@@@@@@@@@@"<<endl;
neibor->display_node();
		    flag = 1;
break;
		}//if neibor = -2
		else{

		    if(neibor->get_flag()==1) {
			small.push_back(neibor);
			cout<< "push back in to small vetor"<<endl<<endl;}
		    else{
			need++;
		    }
		}
	    }

	}//end neibor size

if(flag==1) {
break;
}



	    if(!small.empty()) {

                    int get_pos = 0;
            	    int get_min = small.at(0)->get_detour();
   		    for(int kkk = 0;kkk < small.size();kkk++) {
         		if(small.at(kkk)->get_detour() < get_min) {
              		    get_min = small.at(kkk)->get_detour();
              		    get_pos = kkk;
         		}//if		
      		    }               



cout<<" small is not empty"<<endl<<endl;
		for(int kkk = 0;kkk < small.size();kkk++) {
		    Node* tt = small.at(kkk);
cout<<"get a element in smalli "<<kkk<< " " ;
tt->display_node();
cout<<"and it's detour is "<<tt->get_detour();
cout<<endl<<endl;
cout<< "the get_pos is "<<get_pos<<endl;
                    if(kkk!= get_pos) {
 cout<< "now enter kkk!=get_pos"<<endl;
			    if (tt->get_detour() == tail->get_detour()) {

				    PathSegment* new_segment = new PathSegment(tail->get_coord(),tt->get_coord());
				    q2.push(new_segment);
				    tt->display_node();
				    cout<<" detour value equel push in q2  "<<tt->get_detour()<< endl;
			    }
			    if( tt->get_detour() == tail->get_detour()-1) {
				    PathSegment* new_segment = new PathSegment(tail->get_coord(),tt->get_coord());

				    q1.push(new_segment);

				    tt->display_node();
				    cout<<"value is -1 so push in q1"<<tt->get_detour()<<endl;
			    }

			    if( tt->get_detour() == tail->get_detour()+1) {
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
	    if(need == tail->connections_size()) {
		    check++;
	    }
    }//end while q1

//--------------------------------------------------Q2--------------------
while(!q2.empty()) {

this->map->display_flag();
	if(check == 1) {
	    check = 0;
	    need= 0;
cout<<"t!!!!!!!!!!!!!!he size of q2      is "<< q2.size()<<endl<<endl;
	    Point branch = q2.top()->get_source();

int test = (path->get_sink()!=branch);
cout << "this test is "<< test;
	    while(path->get_sink()!=branch) {

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
	for(int i = 0; i< tail->connections_size();i++) {
	    Node* neibor = tail->connections_at(i)->get_end(tail);
	    if(neibor->get_flag()==2) {
cout<<"enter flag ==2 do nothing"<<endl;
	need++;
	    }
	    else{
	        if(neibor->get_cost()==-2) {//if we found sink
		    PathSegment* new_segment = new PathSegment(tail->get_coord(),neibor->get_coord());
		    path->add_segment(new_segment);
		    path->set_sink(neibor->get_coord());
cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++I got the source@@@@@@@@@@@@@@@@@@"<<endl;
neibor->display_node();
		    flag = 1;
break;
		}//if neibor = -2
		else{
		    if(neibor->get_flag()==1) {
			small.push_back(neibor);
			cout<< "push back in to small vetor"<<endl<<endl;}
		    else{
			need++;
		    }
		}
	    }//else flag!=2

	}//end neibor size

if(flag==1) {
break;
}

	    if(need == tail->connections_size()) {
		    check++;
	    }

	    if(!small.empty()) {

                    int get_pos = 0;
            	    int get_min = small.at(0)->get_detour();
   		    for(int kkk = 0;kkk < small.size();kkk++) {
         		if(small.at(kkk)->get_detour() < get_min) {
              		    get_min = small.at(kkk)->get_detour();
              		    get_pos = kkk;
         		}//if		
      		    }               



cout<<" small is not empty"<<endl<<endl;
		for(int kkk = 0;kkk < small.size();kkk++) {
		    Node* tt = small.at(kkk);
cout<<"get a element in smalli "<<kkk<< "   ";
tt->display_node();
cout<<endl<<endl;
if(kkk!= get_pos) {
		  if (tt->get_detour() == tail->get_detour()) {

		        PathSegment* new_segment = new PathSegment(tail->get_coord(),tt->get_coord());
			q1.push(new_segment);
tt->display_node();
cout<<"push in q2  "<<tt->get_detour()<< endl;
		    }
		    if( tt->get_detour() == tail->get_detour()-1) {
			PathSegment* new_segment = new PathSegment(tail->get_coord(),tt->get_coord());

			q2.push(new_segment);

tt->display_node();
cout<<"push in q1"<<tt->get_detour()<<endl;

			    if( tt->get_detour() == tail->get_detour()+1) {
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


vector<Connection> Algorithm::Hadlock::get_connection() {
       return this->connection ;
}

vector<Path*> Algorithm::Hadlock::get_paths() {
    return this->paths;
}


int Algorithm::Hadlock::direction(Point source,Point sink){
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

void Algorithm::Hadlock::set_cross(int i){
    this->cross = i;
}
