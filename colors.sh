#!/bin/bash

for i in $(seq 0 100)
do
 tput setab $i
 echo "HI"
done
