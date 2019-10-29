#!/bin/sh

YEARS="2016 2017 2018"

for YEAR in $YEARS; do

  ./fitter.sh $YEAR false CB reference &
  ./fitter.sh $YEAR false BW reference &
  ./fitter.sh $YEAR false TP reference &
  
  ./fitter.sh $YEAR true CB reference &
  ./fitter.sh $YEAR true BW reference &
  ./fitter.sh $YEAR true TP reference &

done

wait

for YEAR in $YEARS; do

  root-6.12 -l -b -q compare.C\($YEAR,true,\"data\",\"reference\",\"CB\",\"BW\"\)
  root-6.12 -l -b -q compare.C\($YEAR,false,\"data\",\"reference\",\"CB\",\"BW\"\)

done
