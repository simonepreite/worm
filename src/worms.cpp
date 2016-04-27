#include "header.hpp"

using namespace std;

int main(){
	int i, num_players, primo, n, z;
	char name_player[MAXNOME];
	player* tail = NULL;
	player* scan = NULL;
	player* tmp = NULL;
	node* tmp_map = NULL;
	node* scan_map = NULL;
	node* map_tail = new node();
	map_tail->set(0,0);
	enqueue_map(map_tail, map_tail);
	std::cout << "#######################################################################\n";
	std::cout << "#                         BENVENUTI IN:                               #\n";
	std::cout << "#                                                                     #\n";
	std::cout << "#            ██╗    ██╗ ██████╗ ██████╗ ███╗   ███╗███████╗           #\n";
	std::cout << "#            ██║    ██║██╔═══██╗██╔══██╗████╗ ████║██╔════╝           #\n";
	std::cout << "#            ██║ █╗ ██║██║   ██║██████╔╝██╔████╔██║███████╗           #\n";
	std::cout << "#            ██║███╗██║██║   ██║██╔══██╗██║╚██╔╝██║╚════██║           #\n";
	std::cout << "#            ╚███╔███╔╝╚██████╔╝██║  ██║██║ ╚═╝ ██║███████║           #\n";
	std::cout << "#             ╚══╝╚══╝  ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝           #\n";
	std::cout << "#                                                                     #\n";
	std::cout << "#                                                                     #\n";
	std::cout << "#######################################################################\n";
	std::cout << "Inserire numero di giocatori (almeno 2 giocatori): \n";
	std::cin >> num_players;	//inserire il controllo che vengano inseriti soltanto numeri
	for(i = 0; i < num_players; i++){
		int len;
		std::cout << "nome_giocatore " << i + 1 << "(max 8 caratteri): \n";
  		std::cin >> setw(MAXNOME) >> name_player;
  		len = strlen(name_player);
  		if(len < 8){
  			for(z = len; z < MAXNOME - 1; z++){
  				name_player[z] = ' ';
  			}
  			name_player[MAXNOME - 1] = '\0';
  		}
		tail = enqueue_player(tail, name_player, i, map_tail); // inizializza lista dei giocatori
		cin.clear();
		cin.ignore(1000,'\n');
	}
	std::cout << "\n\n";
	foreach(tail, scan, tmp){
		std::cout << "id: " << scan->print_id() << "	nome: ";
		scan->print_name();
		std::cout << "\n";
		info_giocatore(scan, 100); //passo 100 per non far stampare l'alert dei turni mancanti
	}
	if(num_players > 1){
		//estrazione del primo giocatore
		primo = random(num_players - 1);
		std::cout << "numero estratto: " << primo << "\n";
		//posizionamento della tail su quel giocatore con scan
		foreach(tail, scan, tmp){
			if(scan->print_id() == primo) break;
		}
		if(primo == 0) tmp = tail;	// BUG risolto ma sembra una patch migliorabile

	}
	else{
		std::cout << "Non puoi giocare da solo!\n";
		return 0;
	}
	tail = tmp;
	std::cout << "La prima mossa è di ";
	scan->print_name();
	std::cout << "\n\n";
	n = 1;
	for(z = 4; z > 0 ; z--){
		std::cout << z << "\n";
		if (z == 1) std::cout << "START\n";
		sleep(1);
	}
	for(i = MAXTURNI; i >= 0; i--){//loop turni
		char scelta;
		char dir;
		int y = 0;
		int x = 0;

		foreach(tail, scan, tmp){
			system("clear");

			// INIZIO STAMPA MAPPA
			std::cout << "---------------------------------------------------------------------------------------------------------------\n";
			std::cout << "|                                                                                                             |\n";
			for(y = scan->lon() + 3; y >= scan->lon() - 3; y--){
				std::cout << "| ";
				for(x = scan->lan() - 3; x <= scan->lan() + 3; x++){
					foreach(map_tail, scan_map, tmp_map){
						if(x == scan_map->read_x() && y == scan_map->read_y()){
							//nodo corrente, dove si trova il player che sta giocando
							if (y == scan->lon() && x == scan->lan()) {
								std::cout << " |(";
								set_space(scan_map->read_x());
								std::cout << scan_map->read_x() << ",";
								set_space(scan_map->read_y());
								std::cout << scan_map->read_y() << ")| ";
							}
							else if (scan_map->busy() != NULL) {
								//nodo nel quale è presente un altro giocatore
								std::cout << " *(";
								set_space(scan_map->read_x());
								std::cout << scan_map->read_x() << ",";
								set_space(scan_map->read_y());
								std::cout << scan_map->read_y() << ")* ";
							}
							else {
								//nodo già creato ma non busy
								std::cout << "  (";
								set_space(scan_map->read_x());
								std::cout << scan_map->read_x() << ",";
								set_space(scan_map->read_y());
								std::cout << scan_map->read_y() << ")  ";
							}
							break;
						}
					}
					if(tmp_map == map_tail) {
						std::cout << "       0       ";
					}
				}
				std::cout << "   |\n";
				std::cout << "|                                                                                                             |\n";
			}
			std::cout << "|                                                                                                             |\n";
			std::cout << "---------------------------------------------------------------------------------------------------------------\n";
			//FINE STAMPA MAPPA

			info_giocatore(scan, i);
			std::cin >> dir;
			map_tail = move(map_tail, scan->cur_pos(), dir, scan);
		}
		if(i == 0) {
		std::cout << "▄▄▄█████▓ ██░ ██ ▓█████    ▓█████  ███▄    █ ▓█████▄ \n";
		std::cout << "▓  ██▒ ▓▒▓██░ ██▒▓█   ▀    ▓█   ▀  ██ ▀█   █ ▒██▀ ██▌\n";
		std::cout << "▒ ▓██░ ▒░▒██▀▀██░▒███      ▒███   ▓██  ▀█ ██▒░██   █▌\n";
		std::cout << "░ ▓██▓ ░ ░▓█ ░██ ▒▓█  ▄    ▒▓█  ▄ ▓██▒  ▐▌██▒░▓█▄   ▌\n";
		std::cout << "  ▒██▒ ░ ░▓█▒░██▓░▒████▒   ░▒████▒▒██░   ▓██░░▒████▓ \n";
		std::cout << "  ▒ ░░    ▒ ░░▒░▒░░ ▒░ ░   ░░ ▒░ ░░ ▒░   ▒ ▒  ▒▒▓  ▒ \n";
		std::cout << "    ░     ▒ ░▒░ ░ ░ ░  ░    ░ ░  ░░ ░░   ░ ▒░ ░ ▒  ▒ \n";
		std::cout << "  ░       ░  ░░ ░   ░         ░      ░   ░ ░  ░ ░  ░ \n";
		std::cout << "          ░  ░  ░   ░  ░      ░  ░         ░    ░    \n";
		std::cout << "                                              ░      \n";
			std::cout << "WINNER:  ";
			if(scan->get_next() == scan)
				scan->print_name();	//il giocatore vincitore è l'ultimo rimasto
			else {
				//il giocatore non è l'ultimo rimasto. Il vincitore è un giocatore a caso tra coloro che hanno più vermi
				int max = 0;
				player* winner;

				foreach(tail, scan, tmp) {
					if(scan->n_worms() > max) {
						max = scan->n_worms();
						winner = scan;
					}
				}
				winner->print_name();
			}
			std::cout << "\n";
		}
	}
	return 1;
}
