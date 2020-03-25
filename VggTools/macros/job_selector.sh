#!/bin/sh

if [ -r $CMS_PATH/slc7_amd64_gcc820/cms/cmssw/CMSSW_11_0_0 ]; then
  cd $CMS_PATH/slc7_amd64_gcc820/cms/cmssw/CMSSW_11_0_0
  eval `scramv1 runtime -sh`
  cd $OLDPWD
fi

WORKDIR=$HOME/work/cms/VggAnalysis/VggTools/macros
cd $WORKDIR

VERSION=$1
LIST=$2
FLAG=$3

FILE=data/$VERSION/$FLAG/`basename $LIST .list`.root
LOG=data/$VERSION/$FLAG/`basename $LIST .list`.log

export ROOT_HIST=0

root.exe -l -b -q run.C\(\"$LIST\",\"$FILE\",\"$FLAG\"\) > $LOG 2>&1

exit
