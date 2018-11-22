#!/bin/sh

[ $# -lt 2 ] && exit

mv -v data/$1 data/$2

mv -v html/$1 html/$2

exit
