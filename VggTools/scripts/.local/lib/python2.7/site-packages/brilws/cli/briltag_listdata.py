"""    
Usage:
  briltag listdata [options]

Options:
      -h --help                Show this screen.
      -c CONNECT               Service name [default: offline]
      -p AUTHPATH              Authentication file

"""

import os
from docopt import docopt
from schema import Schema
from brilws.cli import clicommonargs

def validate(optdict):
    myvalidables = ['-c',str]
    argdict = dict((k,v) for k,v in clicommonargs.argvalidators.iteritems() if k in myvalidables)
    s = Schema(argdict)
    result = s.validate(optdict)
    return result

if __name__ == '__main__':
    print docopt(__doc__,options_first=True)
    

