#!/bin/sh

if [ -r $CMS_PATH/slc6_amd64_gcc700/cms/cmssw/CMSSW_10_5_0 ]; then
  cd $CMS_PATH/slc6_amd64_gcc700/cms/cmssw/CMSSW_10_5_0
  eval `scramv1 runtime -sh`
  cd $OLDPWD
fi

WORKDIR=$HOME/work/cms/VggAnalysis/VggTools/tools
cd $WORKDIR

LIST=$1

FILE=data/`basename $LIST .list`.root
LOG=data/$FLAG/`basename $LIST .list`.log

export ROOT_HIST=0

root.exe -l -b -q run.C\(\"$LIST\",\"$FILE\"\) > $LOG 2>&1

exit
