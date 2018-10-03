#!bin/sh

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/macros

cd $WORKDIR

export ROOT_HIST=0

root-6.12 -l -q -b WeightCalculatorFromHistogram.C+\(\"root/pileup_mc_2016.root\",\"root/Run2016_DoubleEG_22Aug2018.root\",true,false,\"root/pileup_ratio_2016.root\"\)

exit
