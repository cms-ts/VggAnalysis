#!/bin/sh

VERSION="v03"

if [ ! -z "$1" ]; then
  if [ "$1" == "all" ]; then
    VERSION="*"
  elif [ "$1" == "last" ]; then
    VERSION=`ls -tr data/ | tail -1`
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

running=0
errors=0
done=0
nofiles=0

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
  printf "Checking %-132s : " `basename \`dirname $L\``/`basename $L`
  if [ -z "$O" ]; then
    echo -n "GOOD"
    if grep -q "processed events" $L ; then
      echo " - done"
      done=$((done+1))
    else
      echo " - running"
      running=$((running+1))
    fi
  else
    if [ "$2" == "-d" ]; then
      echo "$O"
    else
      if [ "$O" == "no files to process" ]; then
        echo "$O"
        nofiles=$((nofiles+1))
      else
        echo "ERROR"
        errors=$((errors+1))
      fi
    fi
  fi
done

echo
echo "Running: "$running" - Done: "$done" - Errors: "$errors" - No files: "$nofiles
echo

exit
