#include "header.hpp"

ptr_user enqueue_player(ptr_user tail, char name[], int id){
	ptr_user tmp;
	if(tail == NULL) {
		tail = new user_list;
		tail->next = tail;
		tail->user.set(id, name);
	} else {
		tmp = new user_list;
		tmp->next = tail->next;
		tail->next = tmp;
		tail = tmp;
		tmp->user.set(id, name);
	}	
return tail;
}

void print_list(ptr_user tail){
	ptr_user tmp = NULL;
	if(tail==NULL) std::cout << "lista vuota\n";
	else{
		for(ptr_user scan = tail->next; tmp!=tail; tmp = scan, scan = scan->next){
			std::cout << "scan: " << scan << "\n";
			std::cout << "id giocatore " << scan->user.print_id() << "\n";
			scan->user.print_name();
			std::cout << "\n";
		}
	}
}

int random(int n){
	int x=0;
	srand(time(0));
	x = (rand() % n);
	return x;
}

void kill(){
	//da implementare, devo eliminare un giocatore dalla lista circolare
	//non so tramite che parametro arrivare al giocatore da eliminare. Inoltre ci serve anche il puntatore del giocatore precedente nella lista per poterlo cancellare.
	//Mi sa che a run-time avremo bisogno di due puntatori in grado di scorrere la lista
}