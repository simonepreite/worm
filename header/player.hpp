#ifndef PLAYER_HPP_
#define PLAYER_HPP_

class player {
protected:
	/* informazioni utente */
	char name[MAXNOME];
	int id;
	int x;
	int y;
	int worms;
	node* cur;

public:
	//lista
	player* next;
	
	//constructor 
	player();

	//actions
	void decrease_worms(int n);

	void increase_worms(int n);

	void attack(player *p);

	void set(int id_user, char player[], node* place);

	void set_pos(int lat, int lon, node* pos);

	//information
	int print_id();

	void print_name();

	int n_worms();

	int lan();

	int lon();

	node* cur_pos();

};

#endif