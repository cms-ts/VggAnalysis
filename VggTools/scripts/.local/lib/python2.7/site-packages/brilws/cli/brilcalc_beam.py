"""Usage: brilcalc beam [options] 

options:
  -h,  --help                  Show this screen.
  -c CONNECT                   DB Service name [default: offline]
  -p AUTHPATH                  Authentication file
  -n SCALEFACTOR               Scale factor on results [default: 1.0]
  -f FILL                      Fill number
  -r RUN                       Run number
  -i INPUTFILE                 Input selection file
  -o OUTPUTFILE                Output csv file. Special file '-' for stdout.
  -b BEAMSTATUS                Beam mode. FLAT TOP,SQUEEZE,ADJUST,STABLE BEAMS
  --amodetag AMODETAG          Accelerator mode 
  --beamenergy BEAMENERGY      Target single beam energy in GeV  
  --datatag DATATAG            Data tag name
  --begin BEGIN                Min start time/fill/run
  --end END                    Max start time/fill/run
  --output-style OSTYLE        Screen output style. tab, html, csv [default: tab]
  --xing                       Show result in bx granularity
  --cerntime                   Show time in CERN local time
  --tssec                      Show time as second since Epoch
 
"""

import os
from docopt import docopt
from schema import Schema
from brilws.cli import clicommonargs

def validate(optdict):
    result={}
    argdict = clicommonargs.argvalidators
    #extract sub argdict here
    myvalidables = ['-c','-n','-f','-r','-i','-o','--amodetag','-b','--beamenergy','--datatag','--begin','--end','--output-style',str]
    argdict = dict((k,v) for k,v in clicommonargs.argvalidators.iteritems() if k in myvalidables)
    schema = Schema(argdict)
    result = schema.validate(optdict)
    return result

if __name__ == '__main__':
    print(docopt(__doc__))
