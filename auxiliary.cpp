#include "header.hpp"

ptr_user enqueue_player(ptr_user tail, char name[], int id, ptr_maps p){
	ptr_user tmp;
	if(tail == NULL){
		tail = new user_list;
		tail->next = tail;
		tail->user.set(id, name, p);
	} else {
		tmp = new user_list;
		tmp->next = tail->next;
		tail->next = tmp;
		tail = tmp;
		tmp->user.set(id, name, p);
	}	
	return tail;
}
/*  direzione n: nord, s: sud, e: est, w: ovest questa funzione viene
	chiamata solo se ci si è accertati che il nodo non esiste
*/
ptr_maps new_node(ptr_maps tail, ptr_maps cur_pos, char direzione){
	int x, y;
	ptr_maps tmp;
	switch (direzione){
		case 's' : 
			x = cur_pos->place.read_x();
			y = cur_pos->place.read_y();
			tmp = new maps();
			tmp->place.set(x-1, y);
			tmp->place.n(&cur_pos->place);
			cur_pos->place.s(&tmp->place);
 			tail = enqueue_map(tail, tmp);
			break;
		case 'e' :
			x = cur_pos->place.read_x();
			y = cur_pos->place.read_y();
			tmp = new maps();
			tmp->place.set(x, y-1);
			tmp->place.w(&cur_pos->place);
			cur_pos->place.e(&tmp->place);
			tail = enqueue_map(tail, tmp);
			break;
		case 'w' :
			x = cur_pos->place.read_x();
			y = cur_pos->place.read_y();
			tmp = new maps();
			tmp->place.set(x, y+1);
			tmp->place.e(&cur_pos->place);
			cur_pos->place.w(&tmp->place);
			tail = enqueue_map(tail, tmp);
			break;
		default ://va a nord
			x = cur_pos->place.read_x();
			y = cur_pos->place.read_y();
			tmp = new maps();
			tmp->place.set(x+1, y);
			tmp->place.s(&cur_pos->place);
			cur_pos->place.n(&tmp->place);
			tail = enqueue_map(tail, tmp);
			break;
	}
	return tail;
}

ptr_maps enqueue_map(ptr_maps tail, ptr_maps p){
		p->next = tail->next;
		tail->next = p;
		tail = p;
	return tail;
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
