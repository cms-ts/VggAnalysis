#!/bin/sh

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/macros
cd $WORKDIR

VERSION="v05"

if [ ! -z "$1" ]; then
  VERSION=$1
fi

if [ -z "$1" ]; then
  echo "ERROR: missing version !!"
  exit
fi

YEARS="2016"

if [ ! -z "$2" ]; then
  if [ "$2" == "all" ]; then
    YEARS="2016 2017 2018"
  else
    YEARS=$2
  fi
fi

FLAGS="nolog,amcatnlo nolog,madgraph"

if [ ! -z "$3" ]; then
  FLAGS=$3
fi

for YEAR in $YEARS; do

  for FLAG in $FLAGS; do

    ( \
      ./plot1.sh $VERSION $YEAR $FLAG ; \
      ./plot0.sh $VERSION $YEAR $FLAG",qcd,nofit" ; \
      ./plot0.sh $VERSION $YEAR $FLAG ; \
      ./plot2.sh $VERSION $YEAR $FLAG \
    ) &

  done

done

exit
