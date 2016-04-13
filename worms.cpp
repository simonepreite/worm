#include <string.h>
#include <iostream>
#include "node.hpp"
#include "player.hpp"
using namespace std;

//int enque_player(user_list *tail, char name[], int id);

int main(){
	int i, num_players;
	char name_player[MAXNOME];
	struct user_list *tail = NULL;
	cout << "inserire numero di giocatori: \n";
	cin >> num_players;
	for(i=0; i<num_players; i++){
		cout << "nome_giocatore (max 8 caratteri): \n";
		cin >> name_player;
		enqueue_player(tail, name_player, i); //inizializza lista dei giocatori
	}

	return 1;
}

int enqueue_player(struct user_list *tail, char name[], int id){
	ptr_user tmp;

	if(tail == NULL) {
		tail = new user_list;
		tail->next = tail;
		tail->user.set(id, name);
	} else {
		tmp = new user_list;
		tail->next = tmp;
		tmp->next = tail;
		tail = tmp;
		tmp->user.set(id, name);
	}	

return 1;
}
