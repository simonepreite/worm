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

};

struct user_list{
	player user;
	struct user_list *next;

}user_list;

extern int enqueue_player(struct user_list *tail, char name[], int id);
#endif