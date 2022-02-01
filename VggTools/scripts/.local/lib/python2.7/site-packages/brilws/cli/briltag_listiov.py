"""    
Usage:
  briltag listiov [options]


Options:
      -h --help                Show this screen.
      -c CONNECT               Service name [default: offline]
      -p AUTHPATH              Authentication file
      --name TAGNAME           IOV tag name 
      --type DATASOURCE        Data source type. bcm1f,bcm1fsi,bcm1futca,plt,pxl,hfoc,hfet
      --applyto APPLYTO        Type of correction applied. lumi
      --isdefault              Show only default tags [default: False]

"""

from docopt import docopt
from schema import Schema
from brilws.cli import clicommonargs

def validate(optdict):
    myvalidables = ['-c','-p','--name','--applyto','--type',str]
    argdict = dict((k,v) for k,v in clicommonargs.argvalidators.iteritems() if k in myvalidables)
    s = Schema(argdict)
    result = s.validate(optdict)
    return result

if __name__ == '__main__':
    print docopt(__doc__,options_first=True)


