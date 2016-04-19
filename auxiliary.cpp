#include "header.hpp"

ptr_user enqueue_player(ptr_user tail, char name[], int id, ptr_maps p){
	ptr_user tmp;
	if(tail == NULL){
		tail = new user_list;
		tail->next = tail;
		tail->user.set(id, name, p);
	} else {
		tmp = new user_list;
		tmp->next = tail->next;
		tail->next = tmp;
		tail = tmp;
		tmp->user.set(id, name, p);
	}	
	return tail;
}

ptr_maps set_new_node(int x_offset, int y_offset, ptr_maps tail, ptr_maps cur_pos, ptr_user cur_player){
	int x = cur_pos->place.read_x();
	int y = cur_pos->place.read_y();
	ptr_maps tmp, scan, tmp2;
	tmp = new maps();
	tmp->place.set(x + x_offset, y + y_offset);
	tail = enqueue_map(tail, tmp);
	cur_player->user.set_pos(x + x_offset, y + y_offset, tmp);
	tmp->place.set_wih(cur_player);

	//scavo il nuovo nodo dove si sta spostando il giocatore
	cur_player->user.increase_worms(random(MAX_WORMS));
	tmp->place.dig();

	//RICOLLEGAMENTO NODI ADIACENTI A QUELLO APPENA CREATO
	foreach(tail, scan, tmp2){
		if(scan->place.read_x() == tmp->place.read_x() && scan->place.read_y() == tmp->place.read_y()-1){
			//c'è un nodo a sud
			std::cout << "sud\n";
			tmp->place.s(&scan->place);
			scan->place.n(&tmp->place);
		}
		if(scan->place.read_x() == tmp->place.read_x() && scan->place.read_y() == tmp->place.read_y()+1){
			//c'è un nodo a nord
			std::cout << "nord\n";
			tmp->place.n(&scan->place);
			scan->place.s(&tmp->place);
		}
		if(scan->place.read_x() == tmp->place.read_x()+1 && scan->place.read_y() == tmp->place.read_y()){
			//c'è un nodo a est
            std::cout << "est\n";
			tmp->place.e(&scan->place);
			scan->place.w(&tmp->place);
		}
		if(scan->place.read_x() == tmp->place.read_x()-1 && scan->place.read_y() == tmp->place.read_y()){
			//c'è un nodo a ovest
            std::cout << "ovest\n";
			tmp->place.w(&scan->place);
			scan->place.e(&tmp->place);
		}
	}
	return tail;
}

/*  direzione n: nord, s: sud, e: est, w: ovest questa funzione viene
	chiamata solo se ci si è accertati che il nodo non esiste
*/
ptr_maps move(ptr_maps tail, ptr_maps cur_pos, char direzione, ptr_user cur_player){
	ptr_maps app;
	switch (direzione){
		case 's' : 
			app = (ptr_maps)cur_pos->place.ptr_s();
			if(cur_pos->place.ptr_s() != NULL){
				if (app->place.busy()) {
					// ATTACCO
					cur_player->user.attack((player*)app->place.busy());
				}
				else {
					// MI MUOVO
					cur_player->user.set_pos(cur_pos->place.read_x() + 0, cur_pos->place.read_y() - 1, (maps*)cur_pos->place.ptr_s());
					cur_pos->place.set_wih(NULL);
					app->place.set_wih(cur_player);
					//la vecchia cur_pos non mi serve, assegno la nuova
					cur_pos = app;
					//se il nodo in cui mi sto spostando non è ancora scavato lo scavo e aggiungo vermi al giocatore
					if (!cur_pos->place.is_dug()) {
						cur_player->user.increase_worms(random(MAX_WORMS));
						cur_pos->place.dig();
					}
				}
			}
			else tail = set_new_node(0, -1, tail, cur_pos, cur_player);
			break;
		case 'e' :
			app = (ptr_maps)cur_pos->place.ptr_e();
			if(cur_pos->place.ptr_e() != NULL){
				if (app->place.busy()) {
					// ATTACCO
					cur_player->user.attack((player*)app->place.busy());
				}
				else {
					// MI MUOVO
					cur_player->user.set_pos(cur_pos->place.read_x() + 1, cur_pos->place.read_y() + 0, (maps*)cur_pos->place.ptr_e());
					cur_pos->place.set_wih(NULL);
					app->place.set_wih(cur_player);
					cur_pos = app;
					if (!cur_pos->place.is_dug()) {
						cur_player->user.increase_worms(random(MAX_WORMS));
						cur_pos->place.dig();
					}
				}
			}
			else tail = set_new_node(1, 0, tail, cur_pos, cur_player);
			break;
		case 'w' :
			app = (ptr_maps)cur_pos->place.ptr_w();
			if(cur_pos->place.ptr_w() != NULL){
				if (app->place.busy()) {
					// ATTACCO
					cur_player->user.attack((player*)app->place.busy());
				}
				else {
					// MI MUOVO
					cur_player->user.set_pos(cur_pos->place.read_x() - 1, cur_pos->place.read_y() + 0, (maps*)cur_pos->place.ptr_w());
					cur_pos->place.set_wih(NULL);
					app->place.set_wih(cur_player);
					cur_pos = app;
					if (!cur_pos->place.is_dug()) {
						cur_player->user.increase_worms(random(MAX_WORMS));
						cur_pos->place.dig();
					}
				}
			}
			else tail = set_new_node(-1, 0, tail, cur_pos, cur_player);
			break;
		default ://va a nord
			app = (ptr_maps)cur_pos->place.ptr_n();
			if(cur_pos->place.ptr_n() != NULL){
				if (app->place.busy()) {
					// ATTACCO
					cur_player->user.attack((player*)app->place.busy());
				}
				else {
					// MI MUOVO
					cur_player->user.set_pos(cur_pos->place.read_x() + 0, cur_pos->place.read_y() + 1, (maps*)cur_pos->place.ptr_n());
					cur_pos->place.set_wih(NULL);
					app->place.set_wih(cur_player);
					cur_pos = app;
					if (!cur_pos->place.is_dug()) {
						cur_player->user.increase_worms(random(MAX_WORMS));
						cur_pos->place.dig();
					}
				}
			}
			else tail = set_new_node(0, 1, tail, cur_pos, cur_player);
			break;
	}
	return tail;
}

ptr_maps enqueue_map(ptr_maps tail, ptr_maps p){
		p->next = tail->next;
		tail->next = p;
		tail = p;
	return tail;
}

int random(int n){
	int x=0;
	srand(time(0));
	x = (rand() % n);
	return x;
}

void kill(ptr_user tail, int id){
//utilizzo tail_copy in modo da lasciare inalterato il turno
	ptr_user tmp, tail_copy;
	tail_copy = tail;
//mi posiziono sull'elemento precedente all'elemento da eliminare
	while (tail_copy->next->user.print_id() != id){
		tail_copy = tail_copy->next;
	}

//eliminazione dell'elemento in questiione
	tmp = tail_copy->next;
	tail_copy->next = tmp->next;
	delete tmp;
}
