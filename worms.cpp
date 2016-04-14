#include "header.hpp"

using namespace std;

int main(){
	int i, num_players, primo;
	ptr_user scan;
	char name_player[MAXNOME];
	ptr_user tail = NULL;
	std::cout << "Inserire numero di giocatori (almeno 2 giocatori): \n";
	std::cin >> num_players;
	num_players = num_players;
	for(i=0; i < num_players; i++){
		std::cout << "nome_giocatore (max 8 caratteri): \n";
		std::cin >> name_player; // inserire controllo lunghezza
		tail = enqueue_player(tail, name_player, i); // inizializza lista dei giocatori
		std::cout << tail << endl;
	}
	print_list(tail);
	primo = random(num_players - 1);
	std::cout << "il primo ad iniziare è il giocatore numero: ";
	std::cout << primo << "\n";
	scan = tail->next;
	for(i = 0; i < primo; i++){
		scan = scan->next;
	}
	std::cout << "di nome: ";
	scan->user.print_name();
	return 1;
}