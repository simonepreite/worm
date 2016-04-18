#include "header.hpp"

using namespace std;

int main(){
	int i, num_players, primo, n;
	char name_player[MAXNOME];
	ptr_user tail = NULL;
	ptr_user scan = NULL;
	ptr_user tmp = NULL;
	ptr_maps tmp_map = NULL;
	ptr_maps scan_map = NULL;
	ptr_maps map_tail = new maps();
	map_tail->place.set(0,0);
	enqueue_map(map_tail, map_tail);
	//map_tail->next = map_tail;
	std::cout << "Inserire numero di giocatori (almeno 2 giocatori): \n";
	std::cin >> num_players;	//inserire il controllo che vengano inseriti soltanto numeri
	for(i=0; i < num_players; i++){
		std::cout << "nome_giocatore " << i+1 << "(max 8 caratteri): \n";
  		std::cin >> setw(MAXNOME) >> name_player;
		tail = enqueue_player(tail, name_player, i, map_tail); // inizializza lista dei giocatori
		cin.clear();
		cin.ignore(1000,'\n');
	}
	std::cout << "\n\n";
	foreach(tail, scan, tmp){
		std::cout << "id: " << scan->user.print_id() << "	nome: ";
		scan->user.print_name();
		std::cout << "\n";
		std::cout << "posizione: (" << scan->user.lan() << ", " << scan->user.lon() << ")" << "\n";
		std::cout << "pointer cur_pos: " << scan->user.cur_pos() << "\n";
		std::cout << "this:  " << scan << "  next:  " << scan->next;
		std::cout << "\n";
	}
	std::cout << "\n";
	if(num_players > 1){
		//estrazione del primo giocatore
		primo = random(num_players - 1);
		std::cout << "numero estratto: " << primo << "\n";
		//posizionamento della tail su quel giocatore con scan
		foreach(tail, scan, tmp){
			if(scan->user.print_id() == primo) break;
		}
		if(primo == 0) tmp = tail;	// BUG risolto ma sembra una patch migliorabile

	}
	else{
		std::cout << "non puoi giocare da solo!";
		return 0;
	}
	tail = tmp; 
	std::cout << "la prima mossa è di ";
	scan->user.print_name();
	std::cout << "\n\n";
	n = 1;
	for(i = MAXTURNI; i >= 0; i--){//loop turni
		int scelta = 0;
		char dir;
		foreach(tail, scan, tmp){
		std::cout << "è il turno di: "; scan->user.print_name();
		std::cout << "\n";
		std::cout << "posizione: (" << scan->user.lan() << ", " << scan->user.lon() << ")" << "\n";
		std::cout << "pointer cur_pos: " << scan->user.cur_pos() << "\n";
		std::cout << "this:  " << scan << "  next:  " << scan->next;
		std::cout << "\n";
		do{
			std::cout << "scegli azione: \n" << "1 - muovi \n" << "2 - stampa mappa \n";
			std::cin >> scelta;
		}while(scelta != 1 && scelta != 2);
		if(scelta == 1) {//servono solo a provare che la new_node funziona 
			std::cout << "inserisci direzione:  ";
			std::cin >> dir;
			map_tail = new_node(map_tail, scan->user.cur_pos(), dir);
			//situazioni
			//scelta della direzione
			//controllo se la casella esiste ed è occupata implica attacco
			//se non è occupata implica spostamento con check della casella se scavabile o no e scava all'occorrenza
			//se il nodo non esesite ciene creato avviene lo spostamento e viene scavato
		}
		else if(scelta == 2){
			foreach(map_tail, scan_map, tmp_map) {
				std::cout << "\n(" << scan_map->place.read_x() << ", " << scan_map->place.read_y() << ")";
				std::cout << "this:  " << scan_map << "  next:  " << scan_map->next;
			}
			std::cout << "\n";
		}
		std::cout << "\n";
		}
		if(i <= 5){
			std::cout << "ATTENZIONE MANCANO  " << i << "  TURNI ALLA CONCLUSIONE!!" << "\n";
		}
		std::cout << "fine turno: " << n << "\n\n";
		n++;
	}
	return 1;
}