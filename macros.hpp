#ifndef MACROS_HPP_
#define MACROS_HPP_

#define MAXNOME 8

#define MAXTURNI 19

#define MAX_WORMS 4 

#define foreach(macros_tail, macros_scan, macros_tmp)\
macros_tmp = NULL;\
if(macros_tail != NULL)\
for (macros_scan = macros_tail->next; macros_tmp != macros_tail; macros_tmp = macros_scan, macros_scan = macros_scan->next)
	
#endif