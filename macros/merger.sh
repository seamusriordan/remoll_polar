#!/bin/bash
#
dir=$HOME/gitdir/remoll_polar/build/output/
i=2
while [ $i -le 50 ];
do
	hadd $dir/result.root $dir/out$i/p2moller_magneticfield.root $dir/Result.root
	let i=i+1
	mv $dir/result.root $dir/Result.root
done
