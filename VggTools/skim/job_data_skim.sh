#!/bin/sh

cd /home/dellaric/work/cms/CMSSW_9_4_9/
eval `scramv1 runtime -sh`

cd /gpfs/cms/users/dellaric/tmp

F=`echo $1 | sed -e 's;/eos/infnts;root://eosinfnts.ts.infn.it//eos/infnts;'`
G=`basename $1 .root`_Skim
D=`dirname $1 | sed -e 's;data;user/dellaric/data;'`

if [ -e $D/$G.root ]; then
  exit
fi

if [ -z "${1##*Run2016*05Feb2018*}" ]; then
  python /home/dellaric/work/cms/VggAnalysis/VggTools/skim/nano_postproc.py \
  -P -J cert/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt \
  . $F > log/$G.log 2>&1
  eos cp $G.root $D/$G.root >> log/$G.log 2>&1
  rm $G.root >> log/$G.log 2>&1
fi

if [ -z "${1##*Run2016*22Aug2018*}" ]; then
  python /home/dellaric/work/cms/VggAnalysis/VggTools/skim/nano_postproc.py \
  -P -J cert/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt \
  . $F > log/$G.log 2>&1
  eos cp $G.root $D/$G.root >> log/$G.log 2>&1
  rm $G.root >> log/$G.log 2>&1
fi

if [ -z "${1##*Run2017*31Mar2018*}" ]; then
  python /home/dellaric/work/cms/VggAnalysis/VggTools/skim/nano_postproc.py \
  -P -J cert/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON_v1.txt \
  . $F > log/$G.log 2>&1
  eos cp $G.root $D/$G.root >> log/$G.log 2>&1
  rm $G.root >> log/$G.log 2>&1
fi

if [ -z "${1##*Run2018*14Sep2018*}" ]; then
  python /home/dellaric/work/cms/VggAnalysis/VggTools/skim/nano_postproc.py \
  -P -J cert/Cert_314472-322381_13TeV_PromptReco_Collisions18_JSON.txt \
  . $F > log/$G.log 2>&1
  eos cp $G.root $D/$G.root >> log/$G.log 2>&1
  rm $G.root >> log/$G.log 2>&1
fi

exit
