#!/bin/sh
mydir=`pwd`
export LD_LIBRARY_PATH=$mydir/lib:$LD_LIBRARY_PATH
export TERMINFO=$mydir
export TERM=xterm

$mydir/lynx -cfg=$mydir/lynx.cfg -lss=$mydir/lynx.lss $mydir/about_lynx.html.gz
