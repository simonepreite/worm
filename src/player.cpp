
#include "header.hpp"

	player::player(){
		x = 0;
		y = 0;
		id = 0;
		worms = 0;
	}

	void player::set(int id_user, char player[], node* place){
		id = id_user;
		strcpy(name, player);
		cur = place;
	}

	void player::set_pos(int lat, int lon, node* pos){
		x = lat;
		y = lon;
		cur = pos; 
	}

	int player::print_id(){
		return id;
	}

	void player::print_name(){
		std::cout << name;
	}

	int player::n_worms(){
		return worms;
	}

	void player::decrease_worms(int n){
		worms = worms - n;
	}

	void player::increase_worms(int n){
		worms = worms + n;
	}

	void player::attack(player *p){
		if (p->n_worms() > worms){
			//defeat
			worms = worms - p->n_worms();
		}
		else {
			//victory
			p->decrease_worms(worms);
		}
	}

	int player::lan(){
		return x;
	}

	int player::lon(){
		return y;
	}

	node* player::cur_pos(){
		return cur;
	}
