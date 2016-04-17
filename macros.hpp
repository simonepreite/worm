#ifndef MACROS_HPP_
#define MACROS_HPP_

#define foreach(tail, scan)\
tmp = NULL;\
if(tail != NULL)\
for (scan = tail->next; tmp!=tail; tmp = scan, scan = scan->next)

#endif