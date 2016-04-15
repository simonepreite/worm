#include "header.hpp"

ptr_user enqueue_player(ptr_user tail, char name[], int id){
	ptr_user tmp;
	if(tail == NULL){
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
	if(tail==NULL) { std::cout << "lista vuota\n";}
	else{
		int app = tail->user.print_id() -1;
		for(ptr_user scan = tail->next; tmp!=tail; tmp = scan, scan = scan->next){
			//std::cout << "scan: " << scan << "\n";
			std::cout << "id: " << scan->user.print_id() << "	nome: ";
			//std::cout << "id giocatore " << scan->user.print_id() << "\n";
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

void kill(ptr_user tail, int id){
//utilizzo tail_copy in modo da lasciare inalterato il turno
	ptr_user tmp, tail_copy;
	tail_copy = tail;
//mi posiziono sull'elemento precedente all'elemento da eliminare
	while (tail_copy->next->user.print_id() != id){
		tail_copy = tail_copy->next;
	}

//eliminazione dell'elemento in questiione
	tmp = tail_copy->next;
	tail_copy->next = tmp->next;
	delete tmp;
}