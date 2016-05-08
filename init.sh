#!/bin/bash
case "$(uname -s)" in

   Darwin)
     echo 'Mac OS X'
	 open -a Terminal.app ./worms; ccf
     ;;

   Linux)
     echo 'Linux'
	
     lxterminal --geometry=180x100 -e ./worms ||konsole --fullscreen -e ./worms || xfce4-terminal --fullscreen -e ./worms || mate-terminal --full-screen -e ./worms || xterm -max -e ./worms
     ;;


   *)
esac
