#!/bin/sh

if [ -r $CMS_PATH/slc6_amd64_gcc700/cms/cmssw/CMSSW_10_5_0 ]; then
  cd $CMS_PATH/slc6_amd64_gcc700/cms/cmssw/CMSSW_10_5_0
  eval `scramv1 runtime -sh`
  cd $OLDPWD
  alias root-6.12=root
fi

WORKDIR=$HOME/work/cms/VggAnalysis/VggTools/macros
cd $WORKDIR

export ROOT_HIST=0

for L in `ls lists/`; do
  root-6.12 -l -b -q evtcount.C\(\"lists/$L\"\) | \
  grep -v 'Processing'
done

exit
