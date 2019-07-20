#!/bin/sh

if [ -r $CMS_PATH/slc6_amd64_gcc700/cms/cmssw/CMSSW_10_5_0 ]; then
  cd $CMS_PATH/slc6_amd64_gcc700/cms/cmssw/CMSSW_10_5_0
  eval `scramv1 runtime -sh`
  cd $OLDPWD
  alias root-6.12=root
fi

WORKDIR=$HOME/work/cms/VggAnalysis/VggTools/macros
cd $WORKDIR

VERSION=$1
LIST=$2
FLAG=$3

FILE=data/$VERSION/$FLAG/`basename $LIST .list`.root
LOG=data/$VERSION/$FLAG/`basename $LIST .list`.log

export ROOT_HIST=0

root-6.12 -l -b -q run.C\(\"$LIST\",\"$FILE\",\"$FLAG\"\) > $LOG 2>&1

exit
