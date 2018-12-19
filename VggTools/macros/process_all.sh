#!/bin/sh

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/macros

cd $WORKDIR

./process.sh v06 all "nolog,amcatnlo nolog,madgraph"

./process.sh v06 all "nolog,amcatnlo,test nolog,madgraph,test"

exit
