#!/bin/sh

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/scripts

cd $WORKDIR

export ROOT_HIST=0

for F in `ls root/pileup_Run*.root`; do
  Y=`basename $F .root | awk -F_ '{print $2}' | sed -e 's/Run//'`
  G=`basename $F .root`
  root-6.12 -l -q -b WeightCalculatorFromHistogram.C+\(\"root/pileup_mc_$Y.root\",\"$F\",true,false,\"root/ratio_$G.root\"\)
done

exit
