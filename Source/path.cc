#include "../Headers/path.h"
#include "../Headers/claim.h"
#include <iostream>

using std::cout;
using std::endl;

Utilities::Path::Path() {
    /* Empty Constructor */
}

Utilities::Path::~Path() {
    /* Emptry Destructor */
}

Point Utilities::Path::get_source() {
    return this->source;
}

Point Utilities::Path::get_sink() {
    return this->sink;
}

void Utilities::Path::set_source(Point source) {
    this->source = source;
}

void Utilities::Path::set_sink(Point sink) {
    this->sink = sink;
}

void Utilities::Path::display_path() {
	cout << "        ";
	for (unsigned j = 0;j < this->size();j++) {
	    cout << "(" << this->at(j)->get_source().x << "," << this->at(j)->get_source().y << ") ";
	    if(j==this->size()-1) {
		cout << "(" << this->at(j)->get_sink().x << "," << this->at(j)->get_sink().y << ") ";
	    }
	}
	cout << endl << endl;

}
