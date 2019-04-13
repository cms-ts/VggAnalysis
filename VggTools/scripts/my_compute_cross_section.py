# EXAMPLE ON HOW TO RUN
# python ./compute_cross_section.py -f datasets.txt 

from optparse import OptionParser
import os
import sys
import commands
import re
import datetime
from time import sleep

def str_to_bool(s):
    if s == 'True':
         return True
    elif s == 'False':
         return False

if __name__ == "__main__":

    parser = OptionParser()
    parser.add_option('-f', '--datasets'      , dest="inputdataset",  default='/DYToLL_2J_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM',   help='dataset names')
    parser.add_option('-n', '--events'        , dest="events",        default=int(1e6),         help='number of events to calculate the cross section')
    parser.add_option(      '--debug'         , dest="debug",         default=False,            help='use debug options (debug couts...)')

    (args, opts) = parser.parse_args(sys.argv)
    debug = str_to_bool(str(args.debug))
    if debug: print 'debug is True!'
    
    if debug:
        print
        print 'RUNNING PARAMS: '
        print '                debug                 = ' + str(debug)
        print '                dataset               = ' + args.inputdataset
        print '                number of events      = ' + str(args.events)
        print

    das_cmd = "/cvmfs/cms.cern.ch/common/dasgoclient"

    # search parent dataset name
    command=das_cmd+" --limit=0 --query=\"parent dataset="+args.inputdataset+"\""
    dataset_used = commands.getstatusoutput(command)[1].split("\n")
    if debug: print 'command',command,'\n'
    dataset_used = [x.strip() for x in dataset_used][0]
    
    if debug: print 'dataset_used',dataset_used
    # pick up only the first dataset of the list
    if debug: print 'dataset_used',dataset_used
    # retrieve filelist
    command=das_cmd+" --limit=100 --query=\"file status=* dataset="+dataset_used+"\" "
    if debug: print 'command',command
    filelist_used = "/store"+commands.getstatusoutput(command)[1].replace("\n",",").split("/store",1)[1] 
    filelist_used = filelist_used.replace("/store","root://xrootd-cms.infn.it:1194//store");
    if debug: 
        print 'filelist_used',filelist_used.split(',')[0]
        filelist_used = filelist_used.split(',')[0]
    # compute cross section
    command = 'cmsRun genXsec_cfg.py inputFiles=\"'+filelist_used+'\" maxEvents='+str(args.events)+" > xsec_"+args.inputdataset.split('/')[1]+"-"+args.inputdataset.split('/')[2]+".log 2>&1"
    print command
