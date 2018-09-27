#!/bin/sh

WORKDIR=/home/dellaric/work/cms/proof/ALT1

for L in `ls $WORKDIR/lists`; do
  root-6.12 -l -b -q $WORKDIR/evtcount.C\(\"$WORKDIR/lists/$L\"\) | \
  grep -v 'Processing'
done

exit
