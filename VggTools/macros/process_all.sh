#!/bin/sh

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/macros
cd $WORKDIR

VERSION="v09"

if [ ! -z "$1" ]; then
  VERSION=$1
fi

./process.sh $VERSION all "nolog,default"

./process.sh $VERSION all "nolog,default,test"

./process.sh $VERSION all "nolog,default,new"

exit
