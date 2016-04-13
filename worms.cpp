#include <string.h>
#include <iostream>
#include "node.hpp"
#include "player.hpp"
using namespace std;

int  print_list(ptr_user tail){
	ptr_user tmp = NULL;
	cout << "print\n";
	if(tail==NULL) cout << "lista vuota\n";
	else{
		for(ptr_user scan = tail->next; tmp!=scan; scan = scan->next,  tmp = tail){
			cout << "scan: " << scan << endl;
			cout << "id giocatore " << scan->user.print_id() << endl;
		}
	}
return 1;
}
int main(){
	int i, num_players;
	char name_player[MAXNOME];
	ptr_user tail = NULL;
	cout << "inserire numero di giocatori: \n";
	cin >> num_players;
	for(i=0; i<num_players; i++){
		cout << "nome_giocatore (max 8 caratteri): \n";
		cin >> name_player; // inserire controllo lunghezza
		tail = enqueue_player(tail, name_player, i); // inizializza lista dei giocatori
		cout << tail << endl;
		//cout << "id giocatore " << tail->user.print_id() << endl;
		}
	print_list(tail);

	return 1;
}

ptr_user enqueue_player(ptr_user tail, char name[], int id){
	ptr_user tmp;
	cout << "init enqueue\n";
	if(tail == NULL) {
		cout << "primo elemento\n";
		tail = new user_list;
		tail->next = tail;
		tail->user.set(id, name);
	} else {
		cout << "altri elementi\n";
		tmp = new user_list;
		tail->next = tmp;
		tmp->next = tail;
		tail = tmp;
		tmp->user.set(id, name);
	}	
	cout << "l'ultimo giocatore inserito: ";
	cout << tail;
	cout << "\n";

return tail;
}
