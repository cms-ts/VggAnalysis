#!/bin/bash

# dasgoclient -query="dataset site=T3_IT_Trieste" > T3_IT_Trieste.txt
# my_compute_cross_section.sh -f datasets.txt -n 1000000

FILE='T3_IT_Trieste.txt'
EVENTS='1000000'

DEBUG=False
# DEBUG=True

if [ `voms-proxy-info --timeleft` == "0" ]; then
  echo
  echo "refresh your grid proxy"
  echo
  exit
fi

if [ -r $CMS_PATH/slc7_amd64_gcc820/cms/cmssw/CMSSW_11_0_0 ]; then
  cd $CMS_PATH/slc7_amd64_gcc820/cms/cmssw/CMSSW_11_0_0
  eval `scramv1 runtime -sh`
  cd $OLDPWD
fi

while getopts f:c:d:n:m:s option
do
  case "${option}"
  in
    f) FILE=${OPTARG};;
    n) EVENTS=${OPTARG};;
  esac
done

while read -r dataset
do
  output="$(python my_compute_cross_section.py -f "${dataset}" -n "${EVENTS}" --debug "${DEBUG}")"
  if [ "${DEBUG}" != "True" ]; then
    if [[ $output == *"cmsRun"* ]]; then
      eval ${output}
    fi
  else
    exit 1
  fi
done < "$FILE"

exit
