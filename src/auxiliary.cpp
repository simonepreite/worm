#include "header.hpp"

player* enqueue_player(player* tail, char name[], int id, node* p){
	player* tmp;
	if(tail == NULL){
		tail = new player;
		tail->next = tail;
		tail->set(id, name, p);
	} else {
		tmp = new player;
		tmp->next = tail->next;
		tail->next = tmp;
		tail = tmp;
		tmp->set(id, name, p);
	}	
	return tail;
}

node* set_new_node(int x_offset, int y_offset, node* tail, node* cur_pos, player* cur_player){
	int x = cur_pos->read_x();
	int y = cur_pos->read_y();
	node* tmp = NULL;
	node* scan = NULL;
	node* tmp2 = NULL;
	tmp = new node();
	tmp->set(x + x_offset, y + y_offset);
	tail = enqueue_map(tail, tmp);
	cur_player->set_pos(x + x_offset, y + y_offset, tmp);
	tmp->set_wih(cur_player);
	//scavo il nuovo nodo dove si sta spostando il giocatore
	cur_player->increase_worms(random(MAX_WORMS));
	tmp->dig();
	//RICOLLEGAMENTO NODI ADIACENTI A QUELLO APPENA CREATO
	foreach(tail, scan, tmp2){
		if(scan->read_x() == tmp->read_x() && scan->read_y() == tmp->read_y()-1){
			//c'è un nodo a sud
			std::cout << "sud\n";
			tmp->s(scan);
			scan->n(tmp);
		}
		if(scan->read_x() == tmp->read_x() && scan->read_y() == tmp->read_y()+1){
			//c'è un nodo a nord
			std::cout << "nord\n";
			tmp->n(scan);
			scan->s(tmp);
		}
		if(scan->read_x() == tmp->read_x()+1 && scan->read_y() == tmp->read_y()){
			//c'è un nodo a est
            std::cout << "est\n";
			tmp->e(scan);
			scan->w(tmp);
		}
		if(scan->read_x() == tmp->read_x()-1 && scan->read_y() == tmp->read_y()){
			//c'è un nodo a ovest
            std::cout << "ovest\n";
			tmp->w(scan);
			scan->e(tmp);
		}
	}
	return tail;
}

/*  direzione n: nord, s: sud, e: est, w: ovest questa funzione viene
	chiamata solo se ci si è accertati che il nodo non esiste
*/
node* move(node* tail, node* cur_pos, char direzione, player* cur_player){
	node* app;
	switch (direzione){
		case 's' : 
			app = cur_pos->ptr_s();
			if(cur_pos->ptr_s() != NULL){
				if (app->busy()) {
					// ATTACCO
					std::cout << "\n FASE DI ATTACCO \n";
					cur_player->attack((player*)app->busy());
				}
				else {
					// MI MUOVO
					std::cout << "\n FASE DI MOVIMENTO \n";
					cur_player->set_pos(cur_pos->read_x() + 0, cur_pos->read_y() - 1, cur_pos->ptr_s());
					cur_pos->set_wih(NULL);
					app->set_wih(cur_player);
					cur_pos = app;
					//se il nodo in cui mi sto spostando non è ancora scavato lo scavo e aggiungo vermi al giocatore
					if (!cur_pos->is_dug()) {
						cur_player->increase_worms(random(MAX_WORMS));
						cur_pos->dig();
					}
				}
			}
			else tail = set_new_node(0, -1, tail, cur_pos, cur_player);
			break;
		case 'e' :
			app = cur_pos->ptr_e();
			if(cur_pos->ptr_e() != NULL){
				if (app->busy()) {
					// ATTACCO
					std::cout << "\n FASE DI ATTACCO \n";
					cur_player->attack((player*)app->busy());
				}
				else {
					// MI MUOVO
					std::cout << "\n FASE DI MOVIMENTO \n";
					cur_player->set_pos(cur_pos->read_x() + 1, cur_pos->read_y() + 0, cur_pos->ptr_e());
					cur_pos->set_wih(NULL);
					app->set_wih(cur_player);
					cur_pos = app;
					if (!cur_pos->is_dug()) {
						cur_player->increase_worms(random(MAX_WORMS));
						cur_pos->dig();
					}
				}
			}
			else tail = set_new_node(1, 0, tail, cur_pos, cur_player);
			break;
		case 'w' :
			app = cur_pos->ptr_w();
			if(cur_pos->ptr_w() != NULL){
				if (app->busy()) {
					// ATTACCO
					std::cout << "\n FASE DI ATTACCO \n";
					cur_player->attack((player*)app->busy());
				}
				else {
					// MI MUOVO
					std::cout << "\n FASE DI MOVIMENTO \n";
					cur_player->set_pos(cur_pos->read_x() - 1, cur_pos->read_y() + 0, cur_pos->ptr_w());
					cur_pos->set_wih(NULL);
					app->set_wih(cur_player);
					cur_pos = app;
					if (!cur_pos->is_dug()) {
						cur_player->increase_worms(random(MAX_WORMS));
						cur_pos->dig();
					}
				}			}
			else tail = set_new_node(-1, 0, tail, cur_pos, cur_player);
			break;
		default ://va a nord
			app = cur_pos->ptr_n();
			if(cur_pos->ptr_n() != NULL){
				if (app->busy()) {
					// ATTACCO
					std::cout << "\n FASE DI ATTACCO \n";
					cur_player->attack((player*)app->busy());
				}
				else {
					// MI MUOVO
					std::cout << "\n FASE DI MOVIMENTO \n";
					cur_player->set_pos(cur_pos->read_x() + 0, cur_pos->read_y() + 1, cur_pos->ptr_n());
					cur_pos->set_wih(NULL);
					app->set_wih(cur_player);
					cur_pos = app;
					if (!cur_pos->is_dug()) {
						cur_player->increase_worms(random(MAX_WORMS));
						cur_pos->dig();
					}
				}
			}
			else tail = set_new_node(0, 1, tail, cur_pos, cur_player);
			break;
	}
	return tail;
}

node* enqueue_map(node* tail, node* p){
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

void kill(player* tail, int id){
//utilizzo tail_copy in modo da lasciare inalterato il turno
	player* tmp;
	player* tail_copy;
	tail_copy = tail;
//mi posiziono sull'elemento precedente all'elemento da eliminare
	while (tail_copy->next->print_id() != id){
		tail_copy = tail_copy->next;
	}

//eliminazione dell'elemento in questiione
	tmp = tail_copy->next;
	tail_copy->next = tmp->next;
	delete tmp;
}
