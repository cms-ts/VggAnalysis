#!/bin/sh

WORKDIR=/home/dellaric/work/cms/VggAnalysis/VggTools/macros

LIST=$1

FILE=$PWD.root

ln -s $WORKDIR/mainSelector* .

#root-6.12 -l -b -q $WORKDIR/run5.C\(\"$LIST\",\"$FILE\"\) > job.log 2>&1
root-6.12 -l -b -q $WORKDIR/run7.C\(\"$LIST\",\"$FILE\"\) > job.log 2>&1

rm -f mainSelector*

exit
