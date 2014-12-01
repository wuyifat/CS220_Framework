#include "../Headers/bidirection.h"
#include <iostream>

Algorithm::Bidirection::Bidirection(Map m){
    this->map = m;
    this->source = m.get_sources();
    this->sink = m.get_sinks();
    this->number = m.get_sources().size();
}

Algorithm::Bidirection::~Bidirection(Map m){
//empty destory function
}


Algorithm::Bidirection::result(){
    for (int i = 0;i < this->nubmer;i++){
        for()
        this->source.at(i);
    }
}
