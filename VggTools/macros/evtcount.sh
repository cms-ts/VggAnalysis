#!/bin/sh

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/macros

cd $WORKDIR

for L in `ls lists/`; do
  root-6.12 -l -b -q evtcount.C\(\"lists/$L\"\) | \
  grep -v 'Processing'
done

exit
