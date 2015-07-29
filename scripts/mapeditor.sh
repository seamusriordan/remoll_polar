#!/bin/bash
input=~/gitdir/remoll_polar/SolenoidFieldmap.dat

while read -r line
do
	read -r f1 f2 f3 f4 f5 <<<"$line"
	num="0.0000000"
	tab=$'\t'
	c=$num$tab"num"
	c=$f1$tab$num$tab$f2$tab$f3$tab$f4$tab$f5
	echo "$c" >> ~/gitdir/remoll_polar/SolenoidMap.dat
done <"$input"
