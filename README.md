#######################################################################
#                                                                     #
#                                                                     #
#            ██╗    ██╗ ██████╗ ██████╗ ███╗   ███╗███████╗           #
#            ██║    ██║██╔═══██╗██╔══██╗████╗ ████║██╔════╝           #
#            ██║ █╗ ██║██║   ██║██████╔╝██╔████╔██║███████╗           #
#            ██║███╗██║██║   ██║██╔══██╗██║╚██╔╝██║╚════██║           #
#            ╚███╔███╔╝╚██████╔╝██║  ██║██║ ╚═╝ ██║███████║           #
#             ╚══╝╚══╝  ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝           #
#                                                                     #
#                                                                     #
#######################################################################
#######################################################################
#                                                                     #
#  AUTHORS:                                                           #
#                                                                     #  
#  Gabriele Orazi             gabriele.orazi@studio.unibo.it          #                
#  Michelangelo Monoriti      michelangel.monoriti@studio.unibo.it    #                       
#  Simone Preite              simone.preite@studio.unibo.it           #               
#                                                                     #  
#                                                                     #  
#######################################################################
#######################################################################
#                                                                     #
#  COMPILAZIONE:                                                      #
#                                                                     #
#          cd /percorso/cartella/worm                                 #
#                                                                     #
#          ./init.sh                                                  #
#                                                                     #
#          enjoy                                                      #
#                                                                     #
#  PULIZIA:                                                           #
#                                                                     #
#          make clean                                                 #
#                                                                     #
#######################################################################
#######################################################################
#                                                                     #
#  REGOLE DEL GIOCO:                                                  #
#                                                                     #
#     - Il gioco inizia con l'inserimento del numero di giocatori.    #
#     - Successivamente a turno vengono inseriti da tastiera i nomi.  #
#     - l'unica azione consentita è lo spostamento che comprende      #
#       alcune azioni automatiche a seconda della situazione:         #
# 		   1 - Per i primi tre turni non è consentito l'attacco per     #
#              permettere a tutti i giocatori di ottenere vermi,      #
#              se la casella è occupata quindi il giocatore che cerca #
#              di spostarsi su di essa viene sbalzato in una casella  #
#              selezionata in maniera casuale                         #
#          2 - Superati i tre turni se la casella in cui ci si vuole  #
#              spostare è occupata si entra in fase di ATTACCO, essa  #
#              si svolge contrllando quale giocatore abbia meno vermi #
#              (il giocatore corrente non conosce il numero di vermi  #
#              dell'avversario). Al perdente vengono sottratti un     #
#              numero di vermi pari alla differenza tra i vermi dei   #
#              due giocatori, il giocatore perdente, per evitare      #
#              inseguimenti viene sbalzato in una casella random.     #
#          3 - I giocatori che presentano un numero pari a 0 o        #
#              o negativo di vermi vengono eliminati e sono fuori dal #
#              gioco.                                                 #
#          4 - Il gioco termina quando resta un solo giocatore o al   #
#              termine dei turni di gioco (che sono settati a 30)     #
#                                                                     #
#######################################################################
