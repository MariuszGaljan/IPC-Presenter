#!/bin/bash

if [ $# -ne 3 ]; then
    echo "processLaunchScript: Wrong number of parameters"
    exit 2
fi

process1="$1"
echo "bash -c \"$2; read\""

gnome-terminal -e "bash -c \"$2; read\"" --title="process2" --geometry 90x28+1100+10
gnome-terminal -e "bash -c \"$3; read\"" --title="process3" --geometry 90x28+150+500
gnome-terminal -e "bash -c \"$1; read\"" --title="process1" --geometry 90x28+1100+500

# using valgrind
# gnome-terminal -e "bash -c \"valgrind $2; read\"" --title="process2" --geometry 90x28+1100+10
# gnome-terminal -e "bash -c \"valgrind $3; read\"" --title="process3" --geometry 90x28+150+500
# gnome-terminal -e "bash -c \"valgrind $1; read\"" --title="process1" --geometry 90x28+1100+500
