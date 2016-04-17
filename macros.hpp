#ifndef MACROS_HPP_
#define MACROS_HPP_

#define MAXNOME 8

#define MAXTURNI 19

#define foreach(tail, scan, tmp)\
tmp = NULL;\
if(tail != NULL)\
for (scan = tail->next; tmp!=tail; tmp = scan, scan = scan->next)

#endif