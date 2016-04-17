#include "header.hpp"

using namespace std;

int main(){
	int i, num_players, primo;
	char name_player[MAXNOME];
	ptr_user tail = NULL;
	ptr_user scan = NULL;
	ptr_user tmp = NULL;
	std::cout << "Inserire numero di giocatori (almeno 2 giocatori): \n";
	std::cin >> num_players;	//inserire il controllo che vengano inseriti soltanto numeri
	for(i=0; i < num_players; i++){
		std::cout << "nome_giocatore " << i+1 << "(max 8 caratteri): \n";
  		std::cin >> setw(MAXNOME) >> name_player;
		std::cout << "lunghezza stringa: " << strlen(name_player) << "\n";
		tail = enqueue_player(tail, name_player, i); // inizializza lista dei giocatori
		std::cout << tail << "\n";
		cin.clear();
		cin.ignore(1000,'\n');
	}

	foreach(tail, scan, tmp){
		std::cout << "id: " << scan->user.print_id() << "	nome: ";
		scan->user.print_name();
		std::cout << "\n";
	}
	//estrazione del primo giocatore
	primo = random(num_players - 1);
	std::cout << "numero estratto: " << primo << "\n";
	//posizionamento della tail su quel giocatore con scan
	foreach(tail, scan, tmp){
		if(scan->user.print_id() == primo) break;
	}
	std::cout << "la prima mossa è di ";
	scan->user.print_name();
	std::cout << "\n\n";

	return 1;
}