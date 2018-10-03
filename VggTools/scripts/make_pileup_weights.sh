#!/bin/sh

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/scripts

cd $WORKDIR

export ROOT_HIST=0

for F in `ls pileup/pileup_Run*.root`; do
  Y=`basename $F .root | awk -F_ '{print $2}' | sed -e 's/Run//'`
  G=`basename $F .root`
  root-6.12 -l -q -b WeightCalculatorFromHistogram.C+\(\"pileup/pileup_mc_$Y.root\",\"$F\",true,false,\"pileup/ratio_$G.root\"\)
done

exit
