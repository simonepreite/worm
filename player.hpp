#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#define MAXNOME 8

class player {
protected:
	/* informazioni utente */
	char name[MAXNOME];
	int id;
	int x;
	int y;	

public:
	player(){
		x = 0;
		y = 0;
		id = 0;
	}
	void set(int id_user, char player[]){
		id = id_user;
		strcpy(name, player);
	}
	char* print_name(){
		return name;
	}

};

struct user_list{
	player user;
	struct user_list *next;
};

typedef user_list* ptr_user;

extern ptr_user enqueue_player(ptr_user tail, char name[], int id);
#endif