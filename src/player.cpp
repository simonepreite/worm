
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

	void player::set_pos(int lon, int lat, node* pos){
		x = lon;
		y = lat;
		cur = pos;
	}

	void player::set_list(player *p){
		next = p;
	}


	int player::print_id(){
		return id;
	}

	void player::print_name(){
		cout << name;
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
			worms = worms - (p->n_worms() - worms);
		}
		else if (p->n_worms() < worms) {
			//victory
			p->decrease_worms(worms - p->n_worms());
		}
	}

	int player::lon(){
		return x;
	}

	int player::lat(){
		return y;
	}

	node* player::cur_pos(){
		return cur;
	}

	player* player::get_next(){
		return next;
	}
