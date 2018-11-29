#!/bin/sh

if [ -z "$2" ]; then
  echo "ERROR: missing version !!"
  exit
fi

YEARS="2016 2017 2018"

if [ ! -z "$1" ]; then
  if [ "$1" == "all" ]; then
    YEARS="2016 2017 2018"
  else
    YEARS=$1
  fi
fi

VERSION="v04"

if [ ! -z "$2" ]; then
  VERSION=$2
fi

FLAGS="nolog,amcatnlo nolog,madgraph"

if [ ! -z "$3" ]; then
  FLAGS=$3
fi

for YEAR in $YEARS; do

  for FLAG in $FLAGS; do

    ( ./plot1.sh $YEAR $VERSION $FLAG ; ./plot0.sh $YEAR $VERSION $FLAG",qcd,nofit" ; ./plot0.sh $YEAR $VERSION $FLAG ) &

  done

done

exit
