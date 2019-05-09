#!/bin/sh

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/macros
cd $WORKDIR

VERSION="v10"

if [ ! -z "$1" ]; then
  VERSION=$1
fi

./process.sh $VERSION all "default" reference,nolog

./process.sh $VERSION all "default,test" reference,nolog

./process.sh $VERSION all "default,new" reference,nolog

./process.sh $VERSION all "default,jet" reference,nolog

exit
