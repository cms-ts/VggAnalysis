#!/bin/sh

if [ -r $CMS_PATH/slc7_amd64_gcc820/cms/cmssw/CMSSW_11_0_0 ]; then
  cd $CMS_PATH/slc7_amd64_gcc820/cms/cmssw/CMSSW_11_0_0
  eval `scramv1 runtime -sh`
  cd $OLDPWD
fi

WORKDIR=$HOME/work/cms/VggAnalysis/VggTools/macros
cd $WORKDIR

LIST=$1
FILE=$2

LOG=data/auto_pu/`basename $FILE .root`.log

export ROOT_HIST=0

root.exe -l -b -q auto_pu.C+\(\"$LIST\"\,\"$FILE\"\) > $LOG 2>&1

exit
