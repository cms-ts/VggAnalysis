#!/bin/sh

WORKDIR=/home/dellaric/work/cms/VggAnalysis/VggTools/macros

for L in `ls $WORKDIR/../scripts/lists`; do
  root-6.12 -l -b -q $WORKDIR/evtcount.C\(\"$WORKDIR/../scripts/lists/$L\"\) | \
  grep -v 'Processing'
done

exit
