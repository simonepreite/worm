#ifndef PLAYER_HPP_
#define PLAYER_HPP_

class player {
protected:
	/* informazioni utente */
	string nome;
	int id;
	int x;
	int y;	

public:
	player(){
		x = 0;
		y = 0;
		id = 0;
		nome = "\0";
	}

};
#endif