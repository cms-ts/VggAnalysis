#!/bin/sh

WORKDIR=$HOME/work/cms/VggAnalysis/VggTools/macros
cd $WORKDIR

if [ `ls ../scripts/lists/ | wc -l` -ne 0 ]; then

  echo
  echo './xsec.dat* => ../scripts/lists/'
  echo

  DATASETS=`grep -v \# ./xsec.dat* | awk -F: '{print $2}' | awk '{print $1}' | sort | uniq`

  check=0
  for D in $DATASETS; do

    [ -z "${D##*WG_WJetsToLNu*}" ] && continue
    [ -z "${D##*WGG_WJetsToLNu*}" ] && continue
    [ -z "${D##*WTauNu_WJetsToLNu*}" ] && continue
    [ -z "${D##*WG_WToLNu*}" ] && continue
    [ -z "${D##*WGG_WToLNu*}" ] && continue
    [ -z "${D##*WTauNu_WToLNu*}" ] && continue
    [ -z "${D##*ZG_DYJetsToLL*}" ] && continue
    [ -z "${D##*ZGG_DYJetsToLL*}" ] && continue
    [ -z "${D##*ZTauTau_DYJetsToLL*}" ] && continue
    [ -z "${D##*ZG_DYToLL*}" ] && continue
    [ -z "${D##*ZGG_DYToLL*}" ] && continue
    [ -z "${D##*ZTauTau_DYToLL*}" ] && continue

    if [ ! -e ../scripts/lists/$D.list ]; then
      echo "missing in ../scripts/lists/ : "$D
      check=1
    fi
  done

  [ $check -eq 0 ] && echo "ok"

fi

echo
echo './xsec.dat* => ./lists/'
echo

DATASETS=`grep -v \# ./xsec.dat* | awk -F: '{print $2}' | awk '{print $1}' | sort | uniq`

check=0
for D in $DATASETS; do

  if [ ! -e lists/$D.list ]; then
    echo "missing in ./lists/ : "$D
    check=1
  fi

done

[ $check -eq 0 ] && echo "ok"

if [ `ls ../scripts/lists/ | wc -l` -ne 0 ]; then

  echo
  echo '../scripts/lists/ => ./xsec.dat*'
  echo

  DATASETS=`ls ../scripts/lists/ | sort | uniq | sed -e 's/.list//' | grep RunII`

  check=0
  for D in $DATASETS; do

    [ -z "${D##*WG_WJetsToLNu*}" ] && continue
    [ -z "${D##*WGG_WJetsToLNu*}" ] && continue
    [ -z "${D##*WTauNu_WJetsToLNu*}" ] && continue
    [ -z "${D##*WG_WToLNu*}" ] && continue
    [ -z "${D##*WGG_WToLNu*}" ] && continue
    [ -z "${D##*WTauNu_WToLNu*}" ] && continue
    [ -z "${D##*ZG_DYJetsToLL*}" ] && continue
    [ -z "${D##*ZGG_DYJetsToLL*}" ] && continue
    [ -z "${D##*ZTauTau_DYJetsToLL*}" ] && continue
    [ -z "${D##*ZG_DYToLL*}" ] && continue
    [ -z "${D##*ZGG_DYToLL*}" ] && continue
    [ -z "${D##*ZTauTau_DYToLL*}" ] && continue

    [ -z "${D##*RunIISummer16NanoAODv5*}" ] && continue
    [ -z "${D##*RunIIFall17NanoAODv5*}" ] && continue
    [ -z "${D##*RunIIAutumn18NanoAODv5*}" ] && continue

    X=`grep $D ./xsec.dat*`
    if [ -z "$X" ]; then
      echo "missing in ./xsec.dat* : "$D
      check=1
    fi

  done

  [ $check -eq 0 ] && echo "ok"

fi

echo
echo './lists/ => ./xsec.dat*'
echo

DATASETS=`ls ./lists/ | sort | uniq | sed -e 's/.list//' | grep RunII`

check=0
for D in $DATASETS; do

  [ -z "${D##*RunIISummer16NanoAODv5*}" ] && continue
  [ -z "${D##*RunIIFall17NanoAODv5*}" ] && continue
  [ -z "${D##*RunIIAutumn18NanoAODv5*}" ] && continue

  X=`grep $D ./xsec.dat*`
  if [ -z "$X" ]; then
    echo "missing in ./xsec.dat* : "$D
    check=1
  fi

done

[ $check -eq 0 ] && echo "ok"

echo
echo './xsec.dat* => ./amcatnlo*/ ./madgraph*/'
echo

DATASETS=`grep -v \# ./xsec.dat* | awk -F: '{print $2}' | awk '{print $1}' | sort | uniq`

check=0
for D in $DATASETS; do

  [ -z "${D##*DY[1234]JetsToLL*}" ] && continue
  [ -z "${D##*W[1234]JetsToLNu*}" ] && continue

  [ -z "${D##*ZGJetsToLLG_012nlo3lo_13TeV-sherpa*}" ] && continue

  X=`grep $D ./amcatnlo*/*.dat* ./madgraph*/*.dat*`
  if [ -z "$X" ]; then
    echo "not used in ./amcatnlo*/ or ./madgraph*/ : "$D
    check=1
  fi

done

[ $check -eq 0 ] && echo "ok"

echo
echo './amcatnlo*/ ./madgraph*/ => ./xsec.dat*'
echo

DATASETS=`cat ./amcatnlo*/*.dat* ./madgraph*/*.dat* | grep RunII | grep -v \# | awk '{print $1}' | sort | uniq`

check=0
for D in $DATASETS; do

  X=`grep -v \# ./xsec.dat* | grep $D`
  if [ -z "$X" ]; then
    echo "missing in ./xsec.dat* : "$D
    check=1
  fi

done

[ $check -eq 0 ] && echo "ok"

echo
echo './amcatnlo*/ ./madgraph*/ => ./lists/'
echo

DATASETS=`cat ./amcatnlo*/*.dat* ./madgraph*/*.dat* | grep RunII | grep -v \# | awk '{print $1}' | sort | uniq`

check=0
for D in $DATASETS; do

  if [ ! -e lists/$D.list ]; then
    echo "missing in ./lists/ : "$D
    check=1
  fi

done

[ $check -eq 0 ] && echo "ok"

if [ `ls ../scripts/lists/ | wc -l` -ne 0 ]; then

  echo
  echo './lists/ <=> ../scripts/lists/'
  echo

  DATASETS=`ls ./lists/ | sort | uniq | sed -e 's/.list//'`

  check=0
  for D in $DATASETS; do

    [ -z "${D##*WG_WJetsToLNu*}" ] && continue
    [ -z "${D##*WGG_WJetsToLNu*}" ] && continue
    [ -z "${D##*WTauNu_WJetsToLNu*}" ] && continue
    [ -z "${D##*WG_WToLNu*}" ] && continue
    [ -z "${D##*WGG_WToLNu*}" ] && continue
    [ -z "${D##*WTauNu_WToLNu*}" ] && continue
    [ -z "${D##*ZG_DYJetsToLL*}" ] && continue
    [ -z "${D##*ZGG_DYJetsToLL*}" ] && continue
    [ -z "${D##*ZTauTau_DYJetsToLL*}" ] && continue
    [ -z "${D##*ZG_DYToLL*}" ] && continue
    [ -z "${D##*ZGG_DYToLL*}" ] && continue
    [ -z "${D##*ZTauTau_DYToLL*}" ] && continue

    if [ ! -e ../scripts/lists/$D.list ]; then
      echo "missing in ../scripts/lists/ : "$D
      check=1
    else
      X=`diff ../scripts/lists/$D.list ./lists/$D.list`
      if [ ! -z "$X" ]; then
        echo "different between ../scripts/lists/ and ../lists/ : "$D" ("`wc -l ../scripts/lists/$D.list | awk '{print $1}'`" files / "`wc -l lists/$D.list | awk '{print $1}'`" files)"
        check=1
      fi
    fi

  done

  [ $check -eq 0 ] && echo "ok"

  echo
  echo '../scripts/lists/ => empty'
  echo

  DATASETS=`ls ../scripts/lists/ | sort | uniq | sed -e 's/.list//'`

  check=0
  for D in $DATASETS; do

    if [ -e ../scripts/lists/$D.list ]; then
      if [ ! -s ../scripts/lists/$D.list ]; then
        echo "empty : ../scripts/lists/"$D".list"
        check=1
      fi
    fi

  done

  [ $check -eq 0 ] && echo "ok"

fi

echo
echo './lists/ => empty'
echo

DATASETS=`ls ./lists/ | sort | uniq | sed -e 's/.list//'`

check=0
for D in $DATASETS; do

  [ -z "${D##*WG_WJetsToLNu*}" ] && continue
  [ -z "${D##*WGG_WJetsToLNu*}" ] && continue
  [ -z "${D##*WTauNu_WJetsToLNu*}" ] && continue
  [ -z "${D##*WG_WToLNu*}" ] && continue
  [ -z "${D##*WGG_WToLNu*}" ] && continue
  [ -z "${D##*WTauNu_WToLNu*}" ] && continue
  [ -z "${D##*ZG_DYJetsToLL*}" ] && continue
  [ -z "${D##*ZGG_DYJetsToLL*}" ] && continue
  [ -z "${D##*ZTauTau_DYJetsToLL*}" ] && continue
  [ -z "${D##*ZG_DYToLL*}" ] && continue
  [ -z "${D##*ZGG_DYToLL*}" ] && continue
  [ -z "${D##*ZTauTau_DYToLL*}" ] && continue

  if [ -e ./lists/$D.list ]; then
    if [ ! -s ./lists/$D.list ]; then
      echo "empty : ./lists/"$D".list"
      check=1
    fi
  fi

done

[ $check -eq 0 ] && echo "ok"

echo

exit
