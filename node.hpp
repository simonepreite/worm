#ifndef NODE_HPP_
#define NODE_HPP_

class node {
protected:
	/* coordinate della mappa */
	int x;
	int y;
	/* puntatori alle direzioni */
	node *nord;
	node *sud;
	node *west;
	node *east;
	/* true = nodo scavato */
	bool digged;

public:
	node() {
		nord = NULL;
		sud = NULL;
		west = NULL;
		east = NULL;
		digged = false;
	}
	void set(int lat, int lon){
		x = lat;
		y = lon;
	}

	int read_x() {
		return x;
	}

	int read_y() {
		return y;
	}

	node* ptr_n(){
		return nord;
	} 

	node* ptr_s(){
		return sud;
	} 

	node* ptr_e(){
		return east;
	} 

	node* ptr_w(){
		return west;
	} 

	void n(node *p){
		nord = p;
	} 

	void s(node *p){
		sud = p;
	} 

	void e(node *p){
		east = p;
	} 

	void w(node *p){
		west = p;
	} 

	void dig() {
		digged = true;
	}

	void reactivate(){
		digged = false;
	}

};

struct maps{
	node place;
	struct maps *next;
};

typedef maps* ptr_maps;


#endif