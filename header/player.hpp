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

	player();

	void set(int id_user, char player[], node* place);

	void set_pos(int lat, int lon, node* pos);

	int print_id();

	void print_name();

	int n_worms();

	void decrease_worms(int n);

	void increase_worms(int n);

	void attack(player *p);

	int lan();

	int lon();

	node* cur_pos();

};

#endif