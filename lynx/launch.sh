#!/bin/sh
mydir=`pwd`
miyoodir=/mnt/SDCARD/miyoo

export HOME=$mydir
export PATH=$mydir:$PATH

cd $mydir
HOME=$mydir
./st -e $mydir/launchenv.sh
