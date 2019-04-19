#!/bin/bash
Xaxis=$(xrandr --current | grep '*' | uniq | awk '{print $1}' | cut -d 'x' -f1)
Yaxis=$(xrandr --current | grep '*' | uniq | awk '{print $1}' | cut -d 'x' -f2)
resize -s $Xaxis $Yaxis
make clean
make
./jeu
make clean
exit 0
 
