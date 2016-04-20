#ifndef AUXILIARY_HPP_
#define AUXILIARY_HPP_

extern void dig(node* cur_pos, player* cur_player, node* app);
extern void print_map(node* appoggio, const char* dir);
extern player* enqueue_player(player* tail, char name[], int id, node* p);
extern node* enqueue_map(node* tail, node* p);
extern node* set_new_node(int x_offset, int y_offset, node* tail, node* cur_pos, player* cur_player);
extern node* move(node* tail, node* cur_pos, char direzione, player* cur_player);
extern void print_list(player* tail);
extern int random(int n);
extern void kill(player* tail, int id);

#endif
