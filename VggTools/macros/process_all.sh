#!/bin/sh

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/macros
cd $WORKDIR

VERSION="v10"

if [ ! -z "$1" ]; then
  VERSION=$1
fi

./process.sh $VERSION all "nolog,default" reference

./process.sh $VERSION all "nolog,default,test" reference

./process.sh $VERSION all "nolog,default,new" reference

./process.sh $VERSION all "nolog,default,jet" reference

exit
