#include "header.hpp"

/*  direzione w: nord, s: sud, d: est, a: ovest questa funzione viene
	chiamata solo se ci si è accertati che il nodo non esiste
*/
node* move(node* tail, node* cur_pos, char direzione, player* cur_player, int i) {
	node* app;
	switch (direzione){
		case 's' :
			tail = direction(tail, cur_pos->ptr_s(), cur_pos, cur_player, 0, -1, i);
			break;
		case 'd' :
			tail = direction(tail, cur_pos->ptr_e(), cur_pos, cur_player, 1, 0, i);
			break;
		case 'a' :
			tail = direction(tail, cur_pos->ptr_w(), cur_pos, cur_player, -1, 0, i);
			break;
		default ://va a nord anche nel caso in cui prema un qualsiasi tasto diverso da 'a', 's' o 'd'
			tail = direction(tail, cur_pos->ptr_n(), cur_pos, cur_player, 0, 1, i);
			break;
	}
	return tail;
}

node* direction(node* tail, node* app, node* cur_pos, player* cur_player, int x, int y, int i) {
	player* p;
	if(app != NULL){
		//se il nodo in cui mi voglio spostare è già stato istanziato
		if ((p=(player*)app->busy())!=NULL) {
			std::cout << "node busy\n";
			if ((MAXTURNI - i) < 4) {
				std::cout << "primi 3 turni\n";
				//siamo nei primi 3 turni, non è ammesso l'attacco
				tail = random_movement(tail, cur_pos, cur_player);
			}
			else {
				std::cout << "attacco\n";
				//non siamo nei primi 3 turni, attacco e sposto su un nodo a caso il perdente
				cur_player->attack(p);
				//controllo se devo eliminare qualche uno dei due giocatori
				if (cur_player->n_worms() < p->n_worms()) {
					std::cout << "cur_player perde\n";
					//cur_player ha perso
					if (cur_player->n_worms() < 0) {
						cur_pos->set_wih(NULL);
						cur_player->print_name();
						std::cout << " muore\n";
						kill(cur_player);
					}
					else {
						std::cout << "cur_player perde random_movement\n";
						tail = random_movement(tail, cur_pos, cur_player);
					}
				}
				else if (cur_player->n_worms() > p->n_worms()) {
					std::cout << "p perde\n";
					//app ha perso
					if (p->n_worms() < 0) {
						app->set_wih(NULL);
						p->print_name();
						std::cout <<" muore\n";
						kill(p);
					}
					else {
						std::cout << "p perde random_movement\n";
						tail = random_movement(tail, app, p);
					}
				}
			}
		}
		//mi sposto normalmente perchè il nodo esiste e non è occupato
		else {
			std::cout << "mi sposto normalmente\n";
			movement(cur_player, cur_pos, app, x, y);
		}
	}
	//il nodo non è ancora stato istanziato, lo creo e ci sposto il giocatore
	else {
		std::cout << "nuovo nodo\n";
		tail = set_new_node(x, y, tail, cur_pos, cur_player);
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
	cur_pos->set_wih(NULL);
	tmp->set_wih(cur_player);
	//scavo il nuovo nodo dove si sta spostando il giocatore
	cur_player->increase_worms(random(MAX_WORMS, 0));
	tmp->dig();
	//RICOLLEGAMENTO NODI ADIACENTI A QUELLO APPENA CREATO
	foreach(tail, scan, tmp2){
		if(scan->read_x() == tmp->read_x() && scan->read_y() == tmp->read_y()-1){
			//c'è un nodo a sud
			//std::cout << "sud\n";
			tmp->s(scan);
			scan->n(tmp);
		}
		if(scan->read_x() == tmp->read_x() && scan->read_y() == tmp->read_y()+1){
			//c'è un nodo a nord
			//std::cout << "nord\n";
			tmp->n(scan);
			scan->s(tmp);
		}
		if(scan->read_x() == tmp->read_x()+1 && scan->read_y() == tmp->read_y()){
			//c'è un nodo a est
      //std::cout << "est\n";
			tmp->e(scan);
			scan->w(tmp);
		}
		if(scan->read_x() == tmp->read_x()-1 && scan->read_y() == tmp->read_y()){
			//c'è un nodo a ovest
      //std::cout << "ovest\n";
			tmp->w(scan);
			scan->e(tmp);
		}
	}
	return tail;
}

void movement(player* cur_player, node* cur_pos, node* scan, int x_offset, int y_offset){
	cur_pos->set_wih(NULL);
	cur_player->set_pos(cur_player->lon() + x_offset, cur_player->lon() + y_offset, scan);
	scan->set_wih(cur_player);
	cur_pos = scan;
	if (!cur_pos->is_dug()) {
		cur_player->increase_worms(random(MAX_WORMS, 0));
		cur_pos->dig();
	}
}

//sposta cur_player in un nodo casuale
node* random_movement(node* tail, node* cur_pos, player* cur_player) {
	node* tmp;
	node* scan;
	int spostato = 0, x_offset, y_offset;
	bool found = 0;
	while(!spostato){
		std::cout << "random movement\n";
		x_offset = random(5, 1);
		y_offset = random(4, 1);

		foreach(tail, scan, tmp){
			if((scan->read_x() == (x_offset + cur_player->lon())) && (scan->read_y() == (y_offset + cur_player->lan()))) {
				found = true;
				//se il nodo estratto esiste già e non è occupato eseguo lo spostamento
				if(scan->busy() == NULL){
					std::cout << "foreach movement\n";
					movement(cur_player, cur_pos, scan, x_offset, y_offset);
					spostato = 1;
					break;
				}
			}
		}
		//non ho trovato nessun nodo libero già creato, ne creo uno nuovo e ci sposto cur_player
		if(!found){
			//non trovo il nodo estratto, ne creo uno nuovo
			x_offset += cur_player->lon();
			y_offset += cur_player->lan();
			tail = set_new_node(x_offset, y_offset, tail, cur_pos, cur_player);
			spostato = 1;
		}
	}
	return tail;
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

//stampa del riquadro riguardante le informazioni del giocatore corrente e del turno in corso
void info_giocatore(player* scan, int turno){
	std::cout << "------------------------------------------------------------------------------------------------------------------\n";
	std::cout << "|                                                                                 |                              |\n";
	std::cout << "|         gioca: ";
	scan->print_name();
	std::cout << "                                                          |            |w|               |\n";
	std::cout << "|         posizione attuale: " ;
	std::cout << "  (";
	set_space(scan->lan());
	std::cout << scan->lan() << ",";
	set_space(scan->lon());
	std::cout << scan->lon() << ")                                        |          |a|s|d|             |\n";
	std::cout << "|         vermi: " << scan->n_worms();
	set_space(scan->n_worms());
	std::cout << "                                                             |                              |\n|        ";
	if(turno <= 5) std::cout << "ATTENZIONE MANCANO  " << turno << "  TURNI ALLA CONCLUSIONE!!!";
	else std::cout << "                                                ";
	std::cout << "                         |                              |\n";
	std::cout << "------------------------------------------------------------------------------------------------------------------\n";
	std::cout << "posizione: " << scan->cur_pos() << " x: " << scan->cur_pos()->read_x() << " y: " << scan->cur_pos()->read_y() << "\n";
}

//funzione da richiamare quando, dopo un attacco, il numero di vermi di uno dei due giocatori è < 0
void kill(player* tail){
//utilizzo tail_copy in modo da lasciare inalterato il turno
	player* tmp;
	player* tail_copy;
	tail_copy = tail;
//mi posiziono sull'elemento precedente all'elemento da eliminare
	//va in loop
	while (tail_copy->get_next()->print_id() != tail->print_id()){
		std::cout << "kill\n";
		tail_copy = tail_copy->get_next();
	}
	/*do{
		std::cout << "kill\n";
		tail_copy = tail_copy->get_next();
	} while (tail_copy->get_next()->print_id() != tail->print_id());*/
//eliminazione dell'elemento in questiione
	tmp = tail_copy->get_next();
	tail_copy->set_list(tmp->get_next());
	delete tmp;
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
	if((n > -1) && (n < 10)) std::cout << "   ";
	else if(((n > 9) && (n < 100)) || ((n < 0) && (n > -10))) std::cout << "  ";
	else if (((n > 99) && (n < 1000)) || ((n > -100) && (n < -9))) std::cout << " ";
}

int random(int n, bool segno){
	int x=0;
	srand(time(0));
	if(segno) x = rand() % n - n/2;
	else x = (rand() % n);
	return x;
}
