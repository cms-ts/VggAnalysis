#!/bin/sh

VERSION=v00

if [ ! -z "$1" ]; then
  if [ "$1" == "all" ]; then
    VERSION="*"
  else
    VERSION=$1
  fi
fi

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/macros

cd $WORKDIR

LISTS=`ls data/$VERSION/*.log`

if [ ! -z "$2" ]; then
  LISTS=`ls data/$VERSION/$2.log`
fi

for L in $LISTS; do
  O=`cat $L | \
  grep [a-z,A-Z] | \
  grep -v 'Processing' | \
  grep -v 'input list' | \
  grep -v 'Starting PROOF-Lite' | \
  grep -v 'Opening connections to workers:' | \
  grep -v 'Setting up worker servers:' |
  grep -v 'PROOF set to parallel mode' | \
  grep -v 'Info' | \
  grep -v "Looking up for exact location of files:" | \
  grep -v 'Validating files:' | \
  grep -v 'entries' | \
  grep -v 'TProof::Progress' | \
  grep -v 'Query processing time' | \
  grep -v 'Lite-0' | \
  grep -v '+++' | \
  grep -v '(M)' | \
  grep -v '#'`
  printf "Checking %-110s : " `basename $L`
  if [ -z "$O" ]; then
    echo -n "GOOD"
    grep -q "processed events" $L && echo " - done" || echo " - running"
  else
    if [ "$2" == "-d" ]; then
      echo "$O"
    else
      if [ "$O" == "no files to process" ]; then
        echo "$O"
      else
        echo "ERROR"
      fi
    fi
  fi
done

exit
