"""
Usage:
  brilcalc lumi [options] 

Options:
  -h, --help                    Show this screen
  -c CONNECT                    Service name [default: offline]
  -p AUTHPATH                   Authentication file
  -n SCALEFACTOR                Scale factor to results [default: 1.0]
  -f FILLNUM                    Fill number
  -r RUNNUMBER                  Run number
  -i INPUTFILE                  Input selection json file or string
  -o OUTPUTFILE                 Output csv file. Special file '-' for stdout.
  -b BEAMSTATUS                 Beam mode. FLAT TOP,SQUEEZE,ADJUST,STABLE BEAMS
  -u UNIT                       Lumi unit. hz/ub,1e30/cm2s,/nb,1e33/cm2 [default: /ub]
  --filedata FILEDATA           Lumi data hdf5 file or directory 
  --precision PRECISION         Use result precision [default: 9f]
  --amodetag AMODETAG           Accelerator mode 
  --beamenergy BEAMENERGY       Target single beam energy in GeV
  --minBiasXsec MINBIASXSEC     Minbias cross-section in ub
  --datatag DATATAG             Data tag name
  --normtag NORMTAG             correction tag or combined correction tag selection file or string
  --begin BEGIN                 Min start time (MM/DD/YY HH24:MI:SS)/fill/run 
  --end END                     Max start time (MM/DD/YY HH24:MI:SS)/fill/run
  --output-style OSTYLE         Screen output style. tab, html, csv [default: tab]
  --type LUMITYPE               Luminosity type. hfoc,bcm1f,bcm1fsi,bcm1futca,pltzero,pxl,dt,hfet,radmmon,ramses
  --hltpath HLTPATH             HLT path name or fnmatch pattern
  --byls                        Show result in ls granularity
  --xing                        Show result in bx granularity
  --without-correction          Show raw data without calibration
  --ignore-mask                 Ignore l1 trgger bit mask for --hltpath specific luminosity
  --cerntime                    Show time in CERN local time
  --tssec                       Show time as second since Epoch
  --xingId BXID                 Filter bunches by id, "1,2,3" or file
  --xingTr BXTHRESHOLD          Filter bunches by percentage of max lumi, 0-1 
  --xingMin XINGMIN             Filter bunches by min lumi value   
  --without-checkjson           Do not check total returned lumi sections against input json file.  

"""

import os,sys
from docopt import docopt
from schema import Schema
from brilws.cli import clicommonargs

def validate(optdict):
    result={}
    #extract sub argdict here
    myvalidables = ['-c','-n','-f','-r','-i','-o','--amodetag','-b','--beamenergy','--minBiasXsec','--datatag','--normtag','--begin','--end','--output-style','--type','--hltpath','--xingId','--xingTr','--xingMin','--precision','--filedata',str]
    argdict = dict((k,v) for k,v in clicommonargs.argvalidators.iteritems() if k in myvalidables)
    
    schema = Schema(argdict)
    result = schema.validate(optdict)
    if not result['-i'] and not result['-f'] and not result['-r'] and not result['--begin']:
        print 'Error: at least one time selection option in %s is required'%(','.join(['-i','-f','-r','--begin']))
        sys.exit(0)
    if result['--filedata'] and not result['--byls']:
        print 'Error: --filedata can only be used with --byls'
        sys.exit(0)            
    return result    
if __name__ == '__main__':
    args = docopt(__doc__,options_first=True)
    print args

