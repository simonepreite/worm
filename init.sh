#!/bin/bash

make

case "$(uname -s)" in

   Darwin)
     echo 'Mac OS X'
	 open -a Terminal.app ./worms
	 osascript -e "tell application \"Terminal\"" -e "tell application \"System Events\"" -e "keystroke \"f\" using {control down, command down}" -e "end tell" -e "end tell"
     ;;

   Linux)
     echo 'Linux'
     lxterminal --geometry=180x100 -e ./worms ||konsole --fullscreen -e ./worms || xfce4-terminal --fullscreen -e ./worms || mate-terminal --full-screen -e ./worms || xterm -max -e ./worms || gnome-terminal --full-screen -e ./worms 
     ;;


   *)
esac
