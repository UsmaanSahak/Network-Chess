#!/bin/bash


#Get the cursor position code 
#>>>
exec < /dev/tty
oldstty=$(stty -g)
stty raw -echo min 0
# on my system, the following line can be replaced by the line below it
echo -en "\033[6n" > /dev/tty
# tput u7 > /dev/tty    # when TERM=xterm (and relatives)
IFS=';' read -r -d R -a pos
stty $oldstty
# change from one-based to zero based so they work with: tput cup $row $col
row=$((${pos[0]:2} - 1))    # strip off the esc-[
col=$((${pos[1]} - 1))

echo "(row,col): $row,$col"
#<<<


#ensure that we have enough space for the board.
lala="$((8-row))"
echo $lala
if [ $lala -gt 0 ]
then
 while [ $lala -gt 0 ]
 do
  echo -e "\n"
  lala="$((lala-1))"
 done
fi
