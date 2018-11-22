#!/bin/sh

[ $# -lt 2 ] && exit

cp -rp -v data/$1 data/$2

cp -rp -v html/$1 html/$2

exit
