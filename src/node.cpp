#include "header.hpp"
	
	node::node() {
		nord = NULL;
		sud = NULL;
		west = NULL;
		east = NULL;
		dug = false;
	}

	void node::set(int lat, int lon){
		x = lat;
		y = lon;
	}

	int node::read_x() {
		return x;
	}

	int node::read_y() {
		return y;
	}

	node* node::ptr_n(){
		return nord;
	} 

	node* node::ptr_s(){
		return sud;
	} 

	node* node::ptr_e(){
		return east;
	} 

	node* node::ptr_w(){
		return west;
	}

	bool node::is_dug() {
		return dug;
	}

	void* node::busy() {
		return who_is_here;
	}

	void node::n(node *p){
		nord = p;
	} 

	void node::s(node *p){
		sud = p;
	} 

	void node::e(node *p){
		east = p;
	} 

	void node::w(node *p){
		west = p;
	} 

	void node::dig() {
		dug = true;
	}

	void node::reactivate(){
		dug = false;
	}

	void node::set_wih(void *p) {
		if(p == NULL) who_is_here = NULL;
		else who_is_here = p;
	}
