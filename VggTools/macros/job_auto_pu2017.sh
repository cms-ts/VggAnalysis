#!/bin/sh

if [ -r $CMS_PATH/slc6_amd64_gcc700/cms/cmssw/CMSSW_10_3_2 ]; then
  cd $CMS_PATH/slc6_amd64_gcc700/cms/cmssw/CMSSW_10_3_2
  eval `scramv1 runtime -sh`
  cd $OLDPWD
  alias root-6.12=root
fi

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/macros
cd $WORKDIR

LIST=$1

FILE=$2
LOG=data/auto_pu2017/`basename $FILE .root`.log

export ROOT_HIST=0

root-6.12 -l -b -q auto_pu2017.C+\(\"$LIST\"\,\"$FILE\"\) > $LOG 2>&1

exit
