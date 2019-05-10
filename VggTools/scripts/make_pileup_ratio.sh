#!/bin/sh

if [ -r $CMS_PATH/slc6_amd64_gcc700/cms/cmssw/CMSSW_10_3_2 ]; then
  cd $CMS_PATH/slc6_amd64_gcc700/cms/cmssw/CMSSW_10_3_2
  eval `scramv1 runtime -sh`
  cd $OLDPWD
  alias root-6.12=root
fi

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/scripts
cd $WORKDIR

export ROOT_HIST=0

for F in `ls root/pileup_*.root | grep -v mc | grep 14Dec2018`; do
  Y=`basename $F .root | sed -e 's/Run//' -e 's/_up_/_/' -e 's/_down_/_/' | awk -F_ '{print $2}'`
  G=`basename $F .root`
  root-6.12 -l -q -b WeightCalculatorFromHistogram.C+\(\"root/pileup_mc_$Y.root\",\"$F\",true,false,\"root/ratio_$G.root\"\)
done

for F in `ls root/pileup_*.root | grep -v mc | grep 22Jan2019`; do
  Y=`basename $F .root | sed -e 's/Run//' -e 's/_up_/_/' -e 's/_down_/_/' | awk -F_ '{print $2}'`
  G=`basename $F .root`
  root-6.12 -l -q -b WeightCalculatorFromHistogram.C+\(\"root/pileup_mc_$Y.root\",\"$F\",true,false,\"root/ratio_$G.root\"\)
done

exit
