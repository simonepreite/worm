#######################################################################
#                                                                     #
#                                                                     # 
#                 ██╗    ██╗ ██████╗ ██████╗ ███╗   ███╗              # 
#                 ██║    ██║██╔═══██╗██╔══██╗████╗ ████║              # 
#                 ██║ █╗ ██║██║   ██║██████╔╝██╔████╔██║              # 
#                 ██║███╗██║██║   ██║██╔══██╗██║╚██╔╝██║              #  
#                 ╚███╔███╔╝╚██████╔╝██║  ██║██║ ╚═╝ ██║              #                    
#                  ╚══╝╚══╝  ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝              #                                      
#                                                                     #                  
#                                                                     #    
#######################################################################
#######################################################################
#                                                                     #  
#                            Gabriele Orazi                           #                
#                            Michelangelo Monoriti                    #                       
#                            Simone Preite                            #               
#                                                                     #  
#                                                                     #  
#######################################################################


[CLASSE node]	
		Variabili:
			2 interi per le coordinate nella mappa
			4 puntatori per le direzioni ai nodi limitrofi
			1 booleano, se il nodo è già stato scavato o no
		Metodi:
			Scava: se il nodo non è già scavato ritorna al giocatore il numero di vermi ottenuti (generazione numero random da 0 a 4) e setta a scavato il nodo
			Riattiva: dopo un certo numero di turni i nodi ritornano scavabili

L'idea è quella di tenere le coordinate di ogni nodo in una lista e tramite confronto, decidere se esistono nodi adiacenti ed eventualmente collegarli.

[CLASSE giocatore]
		Variabili:
			nome
			id
			coordinate
		Metodi:
			muovi
			attacca

Ogni giocatore può compiere una mossa per turno.

[Struttura del gioco]
	All'inizio del gioco si parte tutti da un nodo zero.
	Per la gestione dei giocatori viene creata una lista di giocatori lunga n giocatori (n definito all'inizio della partita).
	La lista è di struttura circolare, in modo da rendere più semplice la gestione dei turni. Sarà comunque possibile contare i turni (turno = tutti i giocatori ancora in gioco hanno compiuto la loro mossa).
	Per ogni giocatore che viene eliminato si libera il posto in memoria e il precedente punterà al giocatore successivo a quello eliminato.
	La gestione della classifica può essere effettuata tramite un vettore di n elementi istanziato al momento dell'avvio del gioco.
	La scelta del primo giocatore viene fatta estraendo un numero random da 1 a n e a seguire tutti gli altri in circolo.
	Le posizioni sulla mappa dei giocatori sono visibili agli altri giocatori (sono visibili solo le posizioni e non il numero di vermi ottenuti).

	[ATTACCO]
		un movimento genera un attacco se la casella è occupata da un altro giocatore. Vince chi ha più vermi.
		Il perdente perde (n vermi vincitore - numero vermi perdente) e inoltre viene spostato sulla mappa in una casella random vuota non scavata.
		Se non ci sono caselle non scavate una a caso viene riabilitata automaticamente e il giocatore viene spostato lì. Questo è un meccanismo per evitare che il vincitore cerchi di riattaccare subito il perdente.




