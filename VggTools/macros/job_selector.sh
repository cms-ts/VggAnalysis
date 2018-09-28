#!/bin/sh

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/macros

cd $WORKDIR

VERSION=$1
LIST=$2

FILE=$WORKDIR/data/$VERSION/`basename $2 | sed -e 's;.list;;'`.root
LOG=$WORKDIR/data/$VERSION/`basename $2 | sed -e 's;.list;;'`.log

root-6.12 -l -b -q $WORKDIR/run.C\(\"$LIST\",\"$FILE\"\) > $LOG 2>&1

exit
