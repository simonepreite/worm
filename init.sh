#!/bin/bash
case "$(uname -s)" in

   Darwin)
     echo 'Mac OS X'
	 open -a Terminal.app ./worms
     ;;

   Linux)
     echo 'Linux'
     #xterm -geometry 800x600 -e ./worms
     mate-terminal --geometry=150x50 -e ./worms
     ;;


   *)
esac
