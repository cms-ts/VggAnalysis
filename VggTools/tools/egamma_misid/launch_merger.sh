#!/bin/bash

rm RunIISummer16NanoAODv6_DYToLL_13TeV-amcatnloFXFX-pythia8.root
rm RunIIFall17NanoAODv6_DYJetsToLL_TuneCP5_13TeV-amcatnloFXFX-pythia8.root
rm RunIIAutumn18NanoAODv6_DYJetsToLL_TuneCP5_13TeV-amcatnloFXFX-pythia8.root

YEARS="2016 2017 2018"

for YEAR in $YEARS; do

  root-6.12 -l -b -q merger.C+\($YEAR,\"h_Z_ele\"\);

done

for YEAR in $YEARS; do

  for NUMBER in {1..20}; do

    root-6.12 -l -b -q merger.C+\($YEAR,\"h_WG_ele_fake_${NUMBER}\"\);
    root-6.12 -l -b -q merger.C+\($YEAR,\"h_WG_ele_fake_${NUMBER}_qcd\"\);
    root-6.12 -l -b -q merger.C+\($YEAR,\"h_WG_ele_fake_truthmatch_${NUMBER}\"\);
    root-6.12 -l -b -q merger.C+\($YEAR,\"h_WG_ele_fake_truthmatch_${NUMBER}_qcd\"\);

  done

done
