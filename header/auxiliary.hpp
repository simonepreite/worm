#ifndef AUXILIARY_HPP_
#define AUXILIARY_HPP_

extern void set_space(int n);
extern void movement(player* cur_player, node* cur_pos, node* scan, int x_offset, int y_offset);
extern void print_map(node* appoggio, const char* dir);
extern void info_giocatore(player* scan, int turno);
extern void kill(player* tail, int id);
extern node* move(node* tail, node* cur_pos, char direzione, player* cur_player, int i);
extern node* random_movement(node* tail, node* cur_pos, player* cur_player);
extern node* direction(node* tail, node* app, node* cur_pos, player* cur_player, int x, int y, int i);
extern node* set_new_node(int x_offset, int y_offset, node* tail, node* cur_pos, player* cur_player);
extern node* enqueue_map(node* tail, node* p);
extern player* enqueue_player(player* tail, char name[], int id, node* p);
extern int random(int n, bool segno);

#endif
