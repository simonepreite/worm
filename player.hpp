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
	ptr_maps cur;

public:
	player(){
		x = 0;
		y = 0;
		id = 0;
		worms = 0;
	}

	void set(int id_user, char player[], ptr_maps place){
		id = id_user;
		strcpy(name, player);
		cur = place;
	}

	void set_pos(int lat, int lon, ptr_maps pos){
		x = lat;
		y = lon;
		cur = pos; 
	}

	int print_id(){
		return id;
	}

	void print_name(){
		std::cout << name;
	}

	int n_worms(){
		return worms;
	}

	void decrease_worms(int n){
		worms = worms - n;
	}

	void increase_worms(int n){
		worms = worms + n;
	}

	void attack(player *p){
		if (p->n_worms() > worms){
			//defeat
			worms = worms - p->n_worms();
		}
		else {
			//victory
			p->decrease_worms(worms);
		}
	}

	int lan(){
		return x;
	}

	int lon(){
		return y;
	}

	ptr_maps cur_pos(){
		return cur;
	}

};

struct user_list{
	player user;
	struct user_list *next;
};

typedef user_list* ptr_user;


#endif