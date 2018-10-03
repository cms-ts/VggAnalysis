#!/bin/sh

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/macros

cd $WORKDIR

export ROOT_HIST=0

for F in `ls root/Run*.root`; do
  Y=`basename $F .root | awk -F_ '{print $1}' | sed -e 's/Run//'`
  G=`basename $F .root`
  root-6.12 -l -q -b WeightCalculatorFromHistogram.C+\(\"root/pileup_mc_$Y.root\",\"$F\",true,false,\"root/ratio_$G.root\"\)
done

exit
