#!/bin/sh

if [ -r $CMS_PATH/slc7_amd64_gcc820/cms/cmssw/CMSSW_11_0_0 ]; then
  cd $CMS_PATH/slc7_amd64_gcc820/cms/cmssw/CMSSW_11_0_0
  eval `scramv1 runtime -sh`
  cd $OLDPWD
fi

WORKDIR=$HOME/work/cms/VggAnalysis/VggTools/scripts
cd $WORKDIR

export ROOT_HIST=0

for F in `ls root/pileup_*.root | grep -v mc | grep 02Apr2020`; do
  Y=`basename $F .root | sed -e 's/Run//' -e 's/_up_/_/' -e 's/_down_/_/' | awk -F_ '{print $2}'`
  G=`basename $F .root`
  root.exe -l -q -b WeightCalculatorFromHistogram.C+\(\"root/pileup_mc_$Y.root\",\"$F\",true,false,\"root/ratio_$G.root\"\)
done

exit
