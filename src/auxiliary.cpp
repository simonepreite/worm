#include "header.hpp"

/*  direzione w: nord, s: sud, d: est, a: ovest questa funzione viene */

//richiama la funione di spostamento (direction) a seconda dell'input di spostamento dell'utente
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

//analizza lo spostamento controllando se ci troviamo in una situazione di attacco o di spostamento normale
//Se abbiamo uno spostamento normale richiamma la movement, altrimenti richiama la random_movement
node* direction(node* tail, node* app, node* cur_pos, player* cur_player, int x, int y, int i) {
	player* p;
	if(app != NULL){
		//se il nodo in cui mi voglio spostare è già stato istanziato
		if ((p=(player*)app->busy())!=NULL) {
			if ((MAXTURNI - i) < 4) {
				//siamo nei primi 3 turni, non è ammesso l'attacco
				tail = random_movement(tail, cur_pos, cur_player);
			}
			else {
				//non siamo nei primi 3 turni, attacco e sposto su un nodo a caso il perdente
				cur_player->attack(p);
				//controllo se devo eliminare qualche uno dei due giocatori
				if (cur_player->n_worms() < p->n_worms()) {
					//cur_player ha perso
					if (cur_player->n_worms() < 0) {
						cur_pos->set_wih(NULL);
						cout << "Giocatore eliminato: ";
						cur_player->print_name();
						kill(cur_player);
					}
					else {
						tail = random_movement(tail, cur_pos, cur_player);
					}
				}
				else if (cur_player->n_worms() > p->n_worms()) {
					//app ha perso
					if (p->n_worms() < 0) {
						app->set_wih(NULL);
						cout << "Giocatore eliminato: ";
						p->print_name();
						kill(p);
					}
					else {
						tail = random_movement(tail, app, p);
					}
				}
			}
		}
		//mi sposto normalmente perchè il nodo esiste e non è occupato
		else {
			movement(cur_player, cur_pos, app, x, y);
		}
	}
	//il nodo non è ancora stato istanziato, lo creo e ci sposto il giocatore
	else {
		tail = set_new_node(x, y, tail, cur_pos, cur_player);
	}
	return tail;
}

//instanzia un nuovo nodo della mappa e lo ricongiunge con nodi già creati limitrofi (nel caso questi siano già stati istanziati)
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
			tmp->s(scan);
			scan->n(tmp);
		}
		if(scan->read_x() == tmp->read_x() && scan->read_y() == tmp->read_y()+1){
			//c'è un nodo a nord
			tmp->n(scan);
			scan->s(tmp);
		}
		if(scan->read_x() == tmp->read_x()+1 && scan->read_y() == tmp->read_y()){
			//c'è un nodo a est
			tmp->e(scan);
			scan->w(tmp);
		}
		if(scan->read_x() == tmp->read_x()-1 && scan->read_y() == tmp->read_y()){
			//c'è un nodo a ovest
			tmp->w(scan);
			scan->e(tmp);
		}
	}
	return tail;
}

void movement(player* cur_player, node* cur_pos, node* scan, int x_offset, int y_offset){
	cur_pos->set_wih(NULL);
	cur_player->set_pos(cur_player->lon() + x_offset, cur_player->lat() + y_offset, scan);
	scan->set_wih(cur_player);
	cur_pos = scan;
	if (!cur_pos->is_dug()) {
		cur_player->increase_worms(random(MAX_WORMS, 0));
		cur_pos->dig();
	}
}

//sposta cur_player in un nodo casuale. Richiamata sul perdente di uno scontro o nei primi 3 turni iniziali
node* random_movement(node* tail, node* cur_pos, player* cur_player) {
	node* tmp;
	node* scan;
	int spostato = 0, x_offset, y_offset;
	bool found = 0;
	while(!spostato){
		//cout << "random movement\n";
		x_offset = random(5, 1);
		y_offset = random(4, 1);

		foreach(tail, scan, tmp){
			if((scan->read_x() == (x_offset + cur_player->lon())) && (scan->read_y() == (y_offset + cur_player->lat()))) {
				found = true;
				//se il nodo estratto esiste già e non è occupato eseguo lo spostamento
				if(scan->busy() == NULL){
					//cout << "foreach movement\n";
					movement(cur_player, cur_pos, scan, x_offset, y_offset);
					spostato = 1;
				}
				break;
			}
		}
		//non ho trovato nessun nodo libero già creato, ne creo uno nuovo e ci sposto cur_player
		if(!found){
			//non trovo il nodo estratto, ne creo uno nuovo
			x_offset += cur_player->lon();
			y_offset += cur_player->lat();
			tail = set_new_node(x_offset, y_offset, tail, cur_pos, cur_player);
			spostato = 1;
		}
	}
	return tail;
}

//stampa del riquadro riguardante le informazioni del giocatore corrente e del turno in corso
void info_giocatore(player* scan, int turno){
	cout << "------------------------------------------------------------------------------------------------------------------\n";
	cout << "|                                                                                 |                              |\n";
	cout << "|         gioca: ";
	scan->print_name();
	cout << "                                                          |            |w|               |\n";
	cout << "|         posizione attuale: " ;
	cout << "  (";
	set_space(scan->lon());
	cout << scan->lon() << ",";
	set_space(scan->lat());
	cout << scan->lat() << ")                                        |          |a|s|d|             |\n";
	cout << "|         vermi: " << scan->n_worms();
	set_space(scan->n_worms());
	cout << "                                                             |                              |\n|        ";
	if(turno <= 5) cout << "ATTENZIONE MANCANO  " << turno << "  TURNI ALLA CONCLUSIONE!!!";
	else cout << " turno: "<< turno <<"                                      ";
	cout << "                         |                              |\n";
	cout << "|                                                                                 |                              |\n";
	cout << "------------------------------------------------------------------------------------------------------------------\n";
	//cout << "posizione: " << scan->cur_pos() << " x: " << scan->cur_pos()->read_x() << " y: " << scan->cur_pos()->read_y() << "\n";
}

void stampa_mappa(node* map_tail, player* play){
	node* scan_map;
	node* tmp_map;
	int i, j;
	int min_lon = play->lon() - 3;
	int max_lon = play->lon() + 3;
	int min_lat = play->lat() - 3;
	int max_lat = play->lat() + 3;
	node* map[7][7];


	for(i=0; i<7; i++){
		for(j=0; j<7; j++){
			map[i][j]=NULL;
		}
	}

	foreach(map_tail, scan_map, tmp_map){
		if(scan_map->read_x() >= min_lon && scan_map->read_x() <= max_lon && scan_map->read_y() >= min_lat && scan_map->read_y() <= max_lat){
			map[scan_map->read_y()-play->lat()+3][scan_map->read_x()-play->lon()+3] = scan_map;
		}
	}


	for(i=6; i>=0; i--){
		cout << "\n------------------------------------------------------------------------------------------------------------------\n";
		cout << "|                |               |               |               |               |               |               |\n";
		cout << "| ";
		for(j=0; j<7; j++){
			if(i == 3 && j == 3){
				cout << " |(";
				set_space(map[i][j]->read_x());
				cout << map[i][j]->read_x() << ",";
				set_space(map[i][j]->read_y());
				cout << map[i][j]->read_y() << ")| ";
			}
			else if(map[i][j]!=NULL){
				if(map[i][j]->busy()==NULL){
					cout << "  (";
					set_space(map[i][j]->read_x());
					cout << map[i][j]->read_x() << ",";
					set_space(map[i][j]->read_y());
					cout << map[i][j]->read_y() << ")  ";
				}
				else{
					cout << " *(";
					set_space(map[i][j]->read_x());
					cout << map[i][j]->read_x() << ",";
					set_space(map[i][j]->read_y());
					cout << map[i][j]->read_y() << ")* ";
				}
			}
			else{
				cout << "       0       ";
			}
			cout << "|";
			//std::cout << " " << map[i][j] << " ";
		}
		cout << "\n";
		cout << "|                |               |               |               |               |               |               |";
		//std::cout << "\n";
	}
	cout << "\n------------------------------------------------------------------------------------------------------------------\n";
}

//funzione da richiamare quando, dopo un attacco, il numero di vermi di uno dei due giocatori è < 0
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

node* enqueue_map(node* tail, node* p){
		p->set_list(tail->get_next());
		tail->set_list(p);
		tail = p;
	return tail;
}

//aggiunge un giocatore sulla lista circolare
player* enqueue_player(player* tail, char name[], int id, node* p){
	player* tmp;
	if(tail == NULL){
		tail = new player;
		tail->set_list(tail);
		tail->set(id, name, p);
	}
	else {
		tmp = new player;
		tmp->set_list(tail->get_next());
		tail->set_list(tmp);
		tail = tmp;
		tmp->set(id, name, p);
	}
	return tail;
}

//serve per controlllare gli spazi all'interno della casella
void set_space(int n) {
	if((n > -1) && (n < 10)) cout << "   ";
	else if(((n > 9) && (n < 100)) || ((n < 0) && (n > -10))) cout << "  ";
	else if (((n > 99) && (n < 1000)) || ((n > -100) && (n < -9))) cout << " ";
}

//estrattore di numeri casuali. n rappresenta il numero max estraibile mentre segno permette l'estrazione di numeri anche negativi
int random(int n, bool segno){
	int x=0;
	srand(time(0));
	if(segno) x = rand() % n - n/2;
	else x = (rand() % n);
	return x;
}
