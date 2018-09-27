#!/bin/sh

VERSION=v00

if [ ! -z "$1" ]; then
  VERSION=$1
fi

DATADIR=/home/dellaric/work/cms/VggAnalysis/VggTools/macros

cat $DATADIR/data/$VERSION/*/job.log | \
grep [a-z,A-Z] | \
grep -v 'Processing' | \
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
grep -v '#' | \
sed -e 's;'$DATADIR'/lists/;;'

exit
