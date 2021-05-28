#!/bin/sh

echo ""
echo "**********************************************"
echo "Will start singularity for hepdata_lib        "
echo "visit: https://github.com/HEPData/hepdata_lib "
echo "                                              "
echo "To generate the sumbission file:              "
echo "> python SMP-19-013.py                          "
echo "**********************************************"
echo ""

export SINGULARITY_CACHEDIR="/tmp/$(whoami)/singularity"
singularity shell -B /afs -B /eos docker://clelange/hepdata_lib bash

echo ""
echo "**********************************************************"
echo "For details on the HEPData library and other stuff        "
echo "visit: https://twiki.cern.ch/twiki/bin/view/CMS/SMPHepData"
echo "**********************************************************"
echo ""

exit 0
