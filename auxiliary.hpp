#ifndef AUXILIARY_HPP_
#define AUXILIARY_HPP_

extern ptr_user enqueue_player(ptr_user tail, char name[], int id, ptr_maps p);
extern ptr_maps enqueue_map(ptr_maps tail, ptr_maps p);
extern void print_list(ptr_user tail);
extern int random(int n);
extern void kill(ptr_user tail, int id);

#endif