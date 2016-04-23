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
	//lista
	node *next;

public:
	
	//constructor
	node();

	void set(int lat, int lon);

	//information
	int read_x();

	int read_y();

	node* ptr_n(); 

	node* ptr_s(); 

	node* ptr_e();

	node* ptr_w();

	bool is_dug() ;

	void* busy() ;

	node* get_next();

	//set node
	void n(node *p);

	void s(node *p);

	void e(node *p);

	void w(node *p);

	void set_list(node* p);

	//action
	void dig() ;

	void reactivate();

	void set_wih(void *p) ;

};

#endif