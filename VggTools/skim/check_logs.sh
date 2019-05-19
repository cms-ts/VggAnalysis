#!/bin/sh

WORKDIR=$HOME/work/cms/VggAnalysis/VggTools/skim

cd $WORKDIR

cat logs/*_Skim.log | \
grep -v 'Will\|Pre-select\|Selected\|Done\|Hz\|going\|copied' | \
grep -v 'TClass::Init:0: RuntimeWarning: no dictionary for class ROOT::TIOFeatures is available' | \
grep [a-z]

exit
