#!/bin/sh

WORKDIR=$HOME/work/cms/VggAnalysis/VggTools/tools
cd $WORKDIR

LISTS=`find -L ./data/ -type f -name '*.log' | sort`

total=0
running=0
errors=0
done=0

echo

for L in $LISTS; do
  total=$((total+1))
  O=`cat $L | \
  grep '[a-z,A-Z]' | \
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
  grep -v 'Temporary failure in name resolution' | \
  grep -v '+++' | \
  grep -v '(M)' | \
  grep -v '#'`
  if [ -z "$O" ]; then
    printf "GOOD  - "
    grep -q "processed events" $L
    if [ $? -eq 0 ]; then
      printf "done       "
      done=$((done+1))
    else
      printf "running    "
      running=$((running+1))
    fi
  else
    printf "ERROR - "
    if [ -z "${O##*no files to process*}" ]; then
      printf "(no files) "
    elif [ -z "${O##*unable to open file*}" ]; then
      printf "(bad file) "
    elif [ -z "${O##*does not have a branch*}" ]; then
      printf "(version)  "
    else
      printf "           "
    fi
    errors=$((errors+1))
  fi
  printf ": ./%s \n" `basename \`dirname $L\``/`basename $L`
done

echo
printf "Total: %3d - Running: %3d - Done: %3d - Errors: %3d\n" $total $running $done $errors
echo

exit
