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
	bool dug;
	//puntatore al player che occupa il nodo. Se a NULL il nodo è libero
	void *who_is_here;
	

public:
	//lista
	node* next;

	node();

	void set(int lat, int lon);

	int read_x();

	int read_y();

	node* ptr_n(); 

	node* ptr_s(); 

	node* ptr_e();

	node* ptr_w();

	void n(node *p);

	void s(node *p);

	void e(node *p);

	void w(node *p);

	void dig() ;

	void reactivate();

	bool is_dug() ;

	void* busy() ;

	void set_wih(void *p) ;

};

#endif