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

	node n(){
		return nord;
	} 

	node s(){
		return sud;
	} 

	node e(){
		return east;
	} 

	node w(){
		return west;
	} 

	void dig {
		digged = true;
	}

	void reactivate {
		digged = false;
	}

};

#endif