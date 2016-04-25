#include "header.hpp"

void movement(player* cur_player, node* cur_pos, node* scan, int x_offset, int y_offset){
	cur_player->set_pos(cur_pos->read_x() + x_offset, cur_pos->read_y() + y_offset, scan);
	cur_pos->set_wih(NULL);
	scan->set_wih(cur_player);
	cur_pos = scan;
	if (!cur_pos->is_dug()) {
		cur_player->increase_worms(random(MAX_WORMS));
		cur_pos->dig();
	}
}

void print_map(node* appoggio, const char* dir){
	int print_x = 0;
	int print_y = 0;
	if((appoggio)!=NULL){
		print_x = appoggio->read_x();
		print_y = appoggio->read_y();
		std::cout << dir << "(" << print_x << ", " << print_y << ")";
	}
	else std::cout << dir << 0;
}

void info_giocatore(player* scan){
	std::cout << "-------------------------------------------------------------------------------------------------\n";
	std::cout << "|                                                                    |                          |\n";
	std::cout << "| gioca: ";
	scan->print_name();
	std::cout << "                                                     |          |w|             |\n";
	if(scan->lan() >= 0 && scan->lon() >= 0)
		std::cout << "| posizione attuale: " << " ( " << scan->lan() << ",  " << scan->lon() << ")" << "                                       |        |a|s|d|           |\n";
	else if(scan->lan() < 0 && scan-> lon() >= 0)
		std::cout << "| posizione attuale: " << " (" << scan->lan() << ",  " << scan->lon() << ")" << "                                       |        |a|s|d|           |\n";
	else if(scan->lan() >= 0 && scan->lon() < 0)
		std::cout << "| posizione attuale: " << " ( " << scan->lan() << ", " << scan->lon() << ")" << "                                       |        |a|s|d|           |\n";
	else std::cout << "| posizione attuale: " << " (" << scan->lan() << ", " << scan->lon() << ")" << "                                       |        |a|s|d|           |\n";
	std::cout << "| vermi: " << scan->n_worms();
	set_space(scan->n_worms());
	std::cout << "                                                         |                          |\n";
	std::cout << "|                                                                    |                          |\n";
	std::cout << "-------------------------------------------------------------------------------------------------\n";
	/*std::cout << "\n";
	std::cout << "Posizione: (" << scan->lan() << ", " << scan->lon() << ")" << "\n";
	std::cout << "pointer cur_pos: " << scan->cur_pos() << "\n";
	std::cout << "vermi: " << scan->n_worms() << "\n";
	std::cout << "this:  " << scan << "  next:  " << scan->get_next();
	std::cout << "\n\n";*/
}

void kill(player* tail){
//utilizzo tail_copy in modo da lasciare inalterato il turno
	player* tmp;
	player* tail_copy;
	tail_copy = tail;
//mi posiziono sull'elemento precedente all'elemento da eliminare
	while (tail_copy->get_next()->print_id() != tail->print_id()){
		tail_copy = tail_copy->get_next();
}

//eliminazione dell'elemento in questiione
	tmp = tail_copy->get_next();
	tail_copy->set_list(tmp->get_next());
	delete tmp;
}

/*  direzione w: nord, s: sud, d: est, a: ovest questa funzione viene
	chiamata solo se ci si è accertati che il nodo non esiste
*/
node* move(node* tail, node* cur_pos, char direzione, player* cur_player){
	node* app;
	switch (direzione){
		case 's' :
			tail = direction(tail, cur_pos->ptr_s(), cur_pos, cur_player, 0, -1);
			break;
		case 'd' :
			tail = direction(tail, cur_pos->ptr_e(), cur_pos, cur_player, 1, 0);
			break;
		case 'a' :
			tail = direction(tail, cur_pos->ptr_w(), cur_pos, cur_player, -1, 0);
			break;
		default ://va a nord
			tail = direction(tail, cur_pos->ptr_n(), cur_pos, cur_player, 0, 1);
			break;
	}
	return tail;
}

node* direction(node* tail, node* app, node* cur_pos, player* cur_player, int x, int y){
	player* p;
	node* scan;
	node* tmp;
	int found = 0;
	int spostato = 0;
	if(app != NULL){
		if (app->busy()) {
			//SPOSTAMENTO CASUALE
			if(cur_player->n_worms() <= p->n_worms()){
				while(spostato != 1){
					int x_offset = random(3);
					int y_offset = random(3);
					foreach(tail, scan, tmp){
						if((scan->read_x() == (x_offset + x)) && (scan->read_y() == (y_offset + y))){
							if(scan->busy() == NULL){
								movement(cur_player, cur_pos, scan, x_offset, y_offset);
								spostato = 1;
							}
							found = 1;
							break;
						}
					}
					if(!found){
						tail = set_new_node(x_offset, y_offset, tail, cur_pos, cur_player);
						spostato = 1;
					}
				}
			}
			// ATTACCO
			else{
				std::cout << "\n FASE DI ATTACCO \n";
				cur_player->attack((player*)app->busy());
				if (cur_player->n_worms() < 0) {
					kill(cur_player);
				}
				if (((player*)app->busy())->n_worms() < 0) {
					kill((player*)app->busy());
				}
			}
		}
		else {
			// MI MUOVO
			std::cout << "\n FASE DI MOVIMENTO \n";
			movement(cur_player, cur_pos, app, x, y);
		}
	}
	else tail = set_new_node(x, y, tail, cur_pos, cur_player);
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
	cur_pos->set_wih(NULL);
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

node* enqueue_map(node* tail, node* p){
		p->set_list(tail->get_next());
		tail->set_list(p);
		tail = p;
	return tail;
}



player* enqueue_player(player* tail, char name[], int id, node* p){
	player* tmp;
	if(tail == NULL){
		tail = new player;
		tail->set_list(tail);
		tail->set(id, name, p);
	} else {
		tmp = new player;
		tmp->set_list(tail->get_next());
		tail->set_list(tmp);
		tail = tmp;
		tmp->set(id, name, p);
	}
	return tail;
}

void set_space(int n) {
	if(n < 10) std::cout << "  ";
	else if(n < 100) std::cout << " ";
}

int random(int n){
	int x=0;
	srand(time(0));
	x = (rand() % n);
	return x;
}
