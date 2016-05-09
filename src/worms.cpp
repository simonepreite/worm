#include "header.hpp"

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
	cout << "########################################################################\n";
	cout << "#                         BENVENUTI IN:                                #\n";
	cout << "#                                                                      #\n";
	cout << "#            ██╗    ██╗ ██████╗ ██████╗ ███╗   ███╗███████╗            #\n";
	cout << "#            ██║    ██║██╔═══██╗██╔══██╗████╗ ████║██╔════╝            #\n";
	cout << "#            ██║ █╗ ██║██║   ██║██████╔╝██╔████╔██║███████╗            #\n";
	cout << "#            ██║███╗██║██║   ██║██╔══██╗██║╚██╔╝██║╚════██║            #\n";
	cout << "#            ╚███╔███╔╝╚██████╔╝██║  ██║██║ ╚═╝ ██║███████║            #\n";
	cout << "#             ╚══╝╚══╝  ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝            #\n";
	cout << "#                                                                      #\n";
	cout << "#                                                                      #\n";
	cout << "########################################################################\n";
	cout << "#                                                                      #\n";
	cout << "#               USE FULL SCREEN OR 115x34 TERMINAL SIZE                #\n";
	cout << "#                                                                      #\n";
	cout << "#             Per i movimenti utilizzare i tasti w-a-s-d               #\n";
	cout << "#                                                                      #\n";
	cout << "########################################################################\n\n";
	cout << "Inserire numero di giocatori (almeno 2 giocatori): \n\n";
	cin >> num_players;
	for(i = 0; i < num_players; i++){
		int len;
		cout << "nome_giocatore " << i + 1 << "(max 8 caratteri): \n";
  		cin >> setw(MAXNOME) >> name_player;
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
	cout << "\n\n";

	foreach(tail, scan, tmp) {
		info_giocatore(scan, MAXTURNI);
	}

	if(num_players > 1){
		//estrazione del primo giocatore
		primo = random(num_players - 1, 0);
		cout << "numero estratto: " << primo << "\n";
		//posizionamento della tail su quel giocatore con scan
		foreach(tail, scan, tmp){
			if(scan->print_id() == primo) break;
		}
		if(primo == 0) tmp = tail;
	}
	else{
		cout << "Non puoi giocare da solo!\n";
		return 0;
	}

	tail = tmp;
	cout << "La prima mossa è di ";
	scan->print_name();
	cout << "\n\n";
	n = 1;

	for(z = 4; z > 0 ; z--){
		cout << z << "\n";
		if (z == 1)	cout << "START\n";
		sleep(1);
	}

	for(i = MAXTURNI; i > 0; i--){//loop turni
		char scelta;
		char dir;

		if(!(i%5)){
			foreach(map_tail, scan_map, tmp_map){
				scan_map->reactivate();
			}
		}

		foreach(tail, scan, tmp){
			system("clear");
			//stampa_mappa(scan, map_tail);
			stampa_mappa(map_tail, scan);
			info_giocatore(scan, i);
			cout << "inserire direzione: ";
			cin >> dir;
			map_tail = move(map_tail, scan->cur_pos(), dir, scan, i);
			if(scan == scan->get_next()) break;
		}

		if(i == 1 || scan == scan->get_next()) {
		int count = 0;
		system("clear");
		cout << "\n\n";
		cout << "▄▄▄█████▓ ██░ ██ ▓█████    ▓█████  ███▄    █ ▓█████▄ \n";
		cout << "▓  ██▒ ▓▒▓██░ ██▒▓█   ▀    ▓█   ▀  ██ ▀█   █ ▒██▀ ██▌\n";
		cout << "▒ ▓██░ ▒░▒██▀▀██░▒███      ▒███   ▓██  ▀█ ██▒░██   █▌\n";
		cout << "░ ▓██▓ ░ ░▓█ ░██ ▒▓█  ▄    ▒▓█  ▄ ▓██▒  ▐▌██▒░▓█▄   ▌\n";
		cout << "  ▒██▒ ░ ░▓█▒░██▓░▒████▒   ░▒████▒▒██░   ▓██░░▒████▓ \n";
		cout << "  ▒ ░░    ▒ ░░▒░▒░░ ▒░ ░   ░░ ▒░ ░░ ▒░   ▒ ▒  ▒▒▓  ▒ \n";
		cout << "    ░     ▒ ░▒░ ░ ░ ░  ░    ░ ░  ░░ ░░   ░ ▒░ ░ ▒  ▒ \n";
		cout << "  ░       ░  ░░ ░   ░         ░      ░   ░ ░  ░ ░  ░ \n";
		cout << "          ░  ░  ░   ░  ░      ░  ░         ░    ░    \n";
		cout << "                                              ░      \n";
		cout << "WINNER:  ";
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
		cout << "\n";
		while(count < 5){
			sleep(1);
			count ++;
		}
		return 0;
		}
	}
	return 0;
}
