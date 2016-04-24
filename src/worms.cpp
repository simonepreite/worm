#include "header.hpp"

using namespace std;

int main(){
	int i, num_players, primo, n;
	char name_player[MAXNOME];
	player* tail = NULL;
	player* scan = NULL;
	player* tmp = NULL;
	node* tmp_map = NULL;
	node* scan_map = NULL;
	node* map_tail = new node();
	map_tail->set(0,0);
	enqueue_map(map_tail, map_tail);
	std::cout << "Inserire numero di giocatori (almeno 2 giocatori): \n";
	std::cin >> num_players;	//inserire il controllo che vengano inseriti soltanto numeri
	for(i = 0; i < num_players; i++){
		std::cout << "nome_giocatore " << i + 1 << "(max 8 caratteri): \n";
  		std::cin >> setw(MAXNOME) >> name_player;
		tail = enqueue_player(tail, name_player, i, map_tail); // inizializza lista dei giocatori
		cin.clear();
		cin.ignore(1000,'\n');
	}
	std::cout << "\n\n";
	foreach(tail, scan, tmp){
		std::cout << "id: " << scan->print_id() << "	nome: ";
		scan->print_name();
		info_giocatore(scan);
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
	for(i = MAXTURNI; i >= 0; i--){//loop turni
		char scelta;
		char dir;
		int y = 0;
		int x = 0;
		foreach(tail, scan, tmp){
			int giocato = 0;
			std::cout << "è il turno di: "; 
			scan->print_name();
			info_giocatore(scan);
			do{
				std::cout << "scegli azione: \n" << "1 - muovi (implica la fine del turno)\n2 - stampa mappa \n";
				std::cin >> scelta;
				switch (scelta){
					case '1' : 
						if(giocato != 1){
						std::cout << "inserisci direzione:  ";
						std::cin >> dir;
						map_tail = move(map_tail, scan->cur_pos(), dir, scan);
						giocato = 1;
						//situazioni
						//scelta della direzione
						//controllo se la casella esiste ed è occupata implica attacco
						//se non è occupata implica spostamento con check della casella se scavabile o no e scava all'occorrenza
						//se il nodo non esesite viene creato avviene lo spostamento e viene scavato
						}
						break;
					case '2' : 
						/*foreach(map_tail, scan_map, tmp_map) {
							int print_x = 0; 
							int print_y = 0;		
							node* appoggio = NULL;
							std::cout << "\n(" << scan_map->read_x() << ", " << scan_map->read_y() << ")" << " occuped: "; 
							if((player*)scan_map->busy()!=NULL) ((player*)scan_map->busy())->print_name();
							else std::cout << 0;
							print_map(scan_map->ptr_n(), "  nord: ");
							print_map(scan_map->ptr_s(), "  sud: ");
							print_map(scan_map->ptr_e(), "  est: ");
							print_map(scan_map->ptr_w(), "  ovest: ");
						}
						std::cout << "\n";*/
						
						for(y = scan->lon() + 5; y >= scan->lon() - 5; y--){
							for(x = scan->lan() - 5; x <= scan->lan() + 5; x++){
								foreach(map_tail, scan_map, tmp_map){
									if(x == scan_map->read_x() && y == scan_map->read_y()){
										if (y == scan->lon() && x == scan->lan()) 
											std::cout << "|(" << scan_map->read_x() << ", " << scan_map->read_y() << ")| "; 
										else if (scan_map->busy() != NULL) 
											std::cout << " (" << scan_map->read_x() << ", " << scan_map->read_y() << ")* "; 
										else std::cout << " (" << scan_map->read_x() << ", " << scan_map->read_y() << ")  "; 
										break;
									}
								}
								if(tmp_map == map_tail) {
									std::cout << "    0      ";
								}
							}
							std::cout << "\n";
						}
						break;
					default: 
						std::cout << "scelta non consentita\n";
						break;
				}
				if(!giocato) std::cout << "non hai ancora giocato!\n";
				//else  std::cout << "scelta non consentita\n";
				std::cout << "\n";
			}while(giocato != 1);
		}
		if(i <= 5){
			std::cout << "ATTENZIONE MANCANO  " << i << "  TURNI ALLA CONCLUSIONE!!" << "\n";
		}
		std::cout << "fine turno: " << n << "\n\n";
		n++;
	}
	return 1;
}
