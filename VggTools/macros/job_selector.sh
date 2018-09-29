#!/bin/sh

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/macros

cd $WORKDIR

VERSION=$1
LIST=$2

FILE=data/$VERSION/`basename $2 | sed -e 's;.list;;'`.root
LOG=data/$VERSION/`basename $2 | sed -e 's;.list;;'`.log

root-6.12 -l -b -q run.C\(\"$LIST\",\"$FILE\"\) > $LOG 2>&1

exit
