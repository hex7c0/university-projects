#!/bin/bash
#main del progetto

clear
echo $1 $2
dir=$1
user=$2

cd $dir

found=$(ls -l | grep -iw "$user" | cut -d ':' -f2 | cut -d ' ' -f2)

echo $found