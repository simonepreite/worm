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
	num_players = num_players;
	for(i=0; i < num_players; i++){
		std::cout << "nome_giocatore " << i+1 << "(max 8 caratteri): \n";
		std::cin >> name_player; // inserire controllo lunghezza
		tail = enqueue_player(tail, name_player, i); // inizializza lista dei giocatori
		std::cout << tail << endl;
	}

	foreach(tail, scan){
		std::cout << "id: " << scan->user.print_id() << "	nome: ";
		scan->user.print_name();
		std::cout << "\n";
	}
	//print_list(tail);

	//estrazione del primo giocatore e posizionamento della tail su quel giocatore
	primo = random(num_players - 1);
	std::cout << "numero estratto: " << primo << "\n";
	/*while(tail->user.print_id() != primo) {
		tail = tail->next;
	}*/
	foreach(tail, scan){
		if(scan->user.print_id() == primo) break;
	}
	std::cout << "la prima mossa è di ";
	scan->user.print_name();
	std::cout << "\n\n";

	return 1;
}