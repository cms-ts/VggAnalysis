#!/bin/sh

QUEUE=normal
export USE_LSF_STARTER=no

VERSION=v00

if [ ! -z "$1" ]; then
  VERSION=$1
fi

WORKDIR=/home/dellaric/work/cms/VggAnalysis/VggTools/macros

LISTS=`ls $WORKDIR../scripts/lists`

if [ ! -z "$2" ]; then
  LISTS=$2
fi

$WORKDIR/compile.sh

for L in $LISTS; do
  JOBDIR=$WORKDIR/data/$VERSION/`basename $L | sed -e 's;.list;;'`
  mkdir -p $JOBDIR
  cd $JOBDIR
  bsub -q $QUEUE -J $L -e /dev/null -o /dev/null $WORKDIR/job_selector.sh $WORKDIR/lists/$L
done

exit
