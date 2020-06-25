#!/bin/bash

mkdir -p "../../macros/html/egamma_v7/scale_factors"

YEARS="2016 2017 2018"

for YEAR in $YEARS; do
  root-6.12 -l -b -q make_sf.C+\($YEAR,false\)
  root-6.12 -l -b -q make_sf.C+\($YEAR,true\)
done
