#!/bin/sh

if [ -r $CMS_PATH/slc7_amd64_gcc820/cms/cmssw/CMSSW_11_0_0 ]; then
  cd $CMS_PATH/slc7_amd64_gcc820/cms/cmssw/CMSSW_11_0_0
  eval `scramv1 runtime -sh`
  cd $OLDPWD
fi

WORKDIR=$HOME/work/cms/VggAnalysis/VggTools/macros
cd $WORKDIR

export ROOT_HIST=0

for L in `ls lists/`; do
  [ -z "${L##*WG_WJetsToLNu*}" ] && continue
  [ -z "${L##*WGG_WJetsToLNu*}" ] && continue
  [ -z "${L##*WTauNu_WJetsToLNu*}" ] && continue
  [ -z "${L##*WG_WToLNu*}" ] && continue
  [ -z "${L##*WGG_WToLNu*}" ] && continue
  [ -z "${L##*WTauNu_WToLNu*}" ] && continue
  [ -z "${L##*ZG_DYJetsToLL*}" ] && continue
  [ -z "${L##*ZGG_DYJetsToLL*}" ] && continue
  [ -z "${L##*ZTauTau_DYJetsToLL*}" ] && continue
  [ -z "${L##*ZG_DYToLL*}" ] && continue
  [ -z "${L##*ZGG_DYToLL*}" ] && continue
  [ -z "${L##*ZTauTau_DYToLL*}" ] && continue
  [ -z "${L##*RunIISummer16NanoAODv4_*}" ] && continue
  [ -z "${L##*RunIIFall17NanoAODv4_*}" ] && continue
  [ -z "${L##*RunIIAutumn18NanoAODv4_*}" ] && continue
  root.exe -l -b -q evtcount.C\(\"lists/$L\"\) | \
  grep -v 'Processing'
done

exit
