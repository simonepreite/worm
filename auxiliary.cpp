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

ptr_maps set_new_node(int x_offset, int y_offset, ptr_maps tail, ptr_maps cur_pos, ptr_user cur_player){
	int x = cur_pos->place.read_x();
	int y = cur_pos->place.read_y();
	ptr_maps tmp, scan, tmp2;
	tmp = new maps();
	tmp->place.set(x + x_offset, y + y_offset);
	tail = enqueue_map(tail, tmp);
	cur_player->user.set_pos(x + x_offset, y + y_offset, tmp);
	foreach(tail, scan, tmp2){
		if(scan->place.read_x() == tmp->place.read_x() && scan->place.read_y() == tmp->place.read_y()-1){
			//c'è un nodo a sud
			std::cout << "sud\n";
			tmp->place.s(&scan->place);
			scan->place.n(&tmp->place);
		}
		if(scan->place.read_x() == tmp->place.read_x() && scan->place.read_y() == tmp->place.read_y()+1){
			//c'è un nodo a nord
			std::cout << "nord\n";
			tmp->place.n(&scan->place);
			scan->place.s(&tmp->place);
		}
		if(scan->place.read_x() == tmp->place.read_x()+1 && scan->place.read_y() == tmp->place.read_y()){
			//c'è un nodo a est
            std::cout << "est\n";
			tmp->place.e(&scan->place);
			scan->place.w(&tmp->place);
		}
		if(scan->place.read_x() == tmp->place.read_x()-1 && scan->place.read_y() == tmp->place.read_y()){
			//c'è un nodo a ovest
            std::cout << "ovest\n";
			tmp->place.w(&scan->place);
			scan->place.e(&tmp->place);
		}
	}
	return tail;
}

/*  direzione n: nord, s: sud, e: est, w: ovest questa funzione viene
	chiamata solo se ci si è accertati che il nodo non esiste
*/
ptr_maps new_node(ptr_maps tail, ptr_maps cur_pos, char direzione, ptr_user cur_player){
	switch (direzione){
		case 's' : 
			if(cur_pos->place.ptr_s() != NULL){
				cur_player->user.set_pos(cur_pos->place.read_x() + 0, cur_pos->place.read_y() - 1, (maps*)cur_pos->place.ptr_s());
			}
			else tail = set_new_node(0, -1, tail, cur_pos, cur_player);
			break;
		case 'e' :
			if(cur_pos->place.ptr_e() != NULL){
				cur_player->user.set_pos(cur_pos->place.read_x() + 1, cur_pos->place.read_y() + 0, (maps*)cur_pos->place.ptr_e());
			}
			else tail = set_new_node(1, 0, tail, cur_pos, cur_player);
			break;
		case 'w' :
			if(cur_pos->place.ptr_w() != NULL){
				cur_player->user.set_pos(cur_pos->place.read_x() - 1, cur_pos->place.read_y() + 0, (maps*)cur_pos->place.ptr_w());
			}
			else tail = set_new_node(-1, 0, tail, cur_pos, cur_player);
			break;
		default ://va a nord
			if(cur_pos->place.ptr_n() != NULL){
				cur_player->user.set_pos(cur_pos->place.read_x() + 0, cur_pos->place.read_y() + 1, (maps*)cur_pos->place.ptr_n());
			}
			else tail = set_new_node(0, 1, tail, cur_pos, cur_player);
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
