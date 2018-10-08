#!/bin/sh

WORKDIR=/home/$USER/work/cms/VggAnalysis/VggTools/scripts

cd $WORKDIR

for F in `ls pileup/ratio_pileup_Run*`; do
  [ -z "${F##*DoubleEG_05Feb2018*}"       ] && cp -p $F ../macros/root/
  [ -z "${F##*DoubleMuon_05Feb2018*}"     ] && cp -p $F ../macros/root/
  [ -z "${F##*SingleElectron_05Feb2018*}" ] && cp -p $F ../macros/root/
  [ -z "${F##*SingleMuon_05Feb2018*}"     ] && cp -p $F ../macros/root/
  [ -z "${F##*MuonEG_05Feb2018*}"         ] && cp -p $F ../macros/root/
done

for F in `ls pileup/ratio_pileup_Run*`; do
  [ -z "${F##*DoubleEG_22Aug2018*}"       ] && cp -p $F ../macros/root/
  [ -z "${F##*DoubleMuon_22Aug2018*}"     ] && cp -p $F ../macros/root/
  [ -z "${F##*SingleElectron_22Aug2018*}" ] && cp -p $F ../macros/root/
  [ -z "${F##*SingleMuon_22Aug2018*}"     ] && cp -p $F ../macros/root/
  [ -z "${F##*MuonEG_22Aug2018*}"         ] && cp -p $F ../macros/root/
done

for F in `ls pileup/ratio_pileup_Run*`; do
  [ -z "${F##*DoubleEG_31Mar2018*}"       ] && cp -p $F ../macros/root/
  [ -z "${F##*DoubleMuon_31Mar2018*}"     ] && cp -p $F ../macros/root/
  [ -z "${F##*SingleElectron_31Mar2018*}" ] && cp -p $F ../macros/root/
  [ -z "${F##*SingleMuon_31Mar2018*}"     ] && cp -p $F ../macros/root/
  [ -z "${F##*MuonEG_31Mar2018*}"         ] && cp -p $F ../macros/root/
done

for F in `ls pileup/ratio_pileup_Run*`; do
  [ -z "${F##*EGamma_14Sep2018*}"         ] && cp -p $F ../macros/root/
  [ -z "${F##*DoubleMuon_14Sep2018*}"     ] && cp -p $F ../macros/root/
  [ -z "${F##*SingleMuon_14Sep2018*}"     ] && cp -p $F ../macros/root/
  [ -z "${F##*MuonEG_14Sep2018*}"         ] && cp -p $F ../macros/root/
done

exit
