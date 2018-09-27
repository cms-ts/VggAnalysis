#!/bin/sh

VERSION=v00

if [ ! -z "$1" ]; then
  VERSION=$1
fi

DATADIR=/home/$USER/work/cms/VggAnalysis/VggTools/macros

cat $DATADIR/data/$VERSION/*/job.log | \
grep [a-z,A-Z] | \
grep -v 'Processing' | \
grep -v 'Info' | \
sed -e 's;'$DATADIR'/lists/;;'

exit
