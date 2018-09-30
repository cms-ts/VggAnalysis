#!/bin/sh

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/scripts

cd $WORKDIR

export ROOT_HIST=0

root-6.12 -l -q -b plot0.C+\(\"h_Z_ele\"\)
root-6.12 -l -q -b plot0.C+\(\"h_Z_muo\"\)

exit
