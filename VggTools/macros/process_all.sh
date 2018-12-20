#!/bin/sh

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/macros

cd $WORKDIR

if [ ! -z "$1" ]; then
  VERSION=$1
fi

./process.sh $VERSION all "nolog,amcatnlo nolog,madgraph"

./process.sh $VERSION all "nolog,amcatnlo,test nolog,madgraph,test"

exit
