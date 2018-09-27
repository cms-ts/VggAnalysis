#!/bin/sh

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/macros

for L in `ls $WORKDIR/../scripts/lists`; do
  root-6.12 -l -b -q $WORKDIR/evtcount.C\(\"$WORKDIR/../scripts/lists/$L\"\) | \
  grep -v 'Processing'
done

exit
