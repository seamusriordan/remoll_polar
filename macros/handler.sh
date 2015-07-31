#!/bin/bash
#
location=$HOME/gitdir/remoll_polar/build/output/
cd $location

for i in `seq 1 16`;
do
	name="out$i"
	mkdir $name
	cd $name
	qsub ../../macros/runscript.sh
	cd ..
done
