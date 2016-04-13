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
	node(int lat, int lon) {
		x = lat;
		y = lon;
		nord = NULL;
		sud = NULL;
		west = NULL;
		east = NULL;
		digged = false;
	}

	int read_x() {
		return x;
	}

	int read_y() {
		return y;
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

	void dig {
		digged = true;
	}

	void reactivate {
		digged = false;
	}

};

struct maps{
	node place;
	struct maps *next;
}maps;

#endif