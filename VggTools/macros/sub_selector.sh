#!/bin/sh

QUEUE=normal
export USE_LSF_STARTER=no

VERSION=v00

if [ ! -z "$1" ]; then
  VERSION=$1
fi

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/macros

cd $WORKDIR

mkdir -p $WORKDIR/data/$VERSION

LISTS=`ls $WORKDIR/../scripts/lists`

if [ ! -z "$2" ]; then
  LISTS=$2
fi

$WORKDIR/compile.sh

for L in $LISTS; do
  bsub -q $QUEUE -J $L -e /dev/null -o /dev/null $WORKDIR/job_selector.sh $VERSION $WORKDIR/../scripts/lists/$L
done

exit
