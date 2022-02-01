"""
Usage:
  brilschema create [options] 

Options:
  -h, --help       Show this screen
  -i INPUTFILE     Input schema definition file
  -f DBFLAVOR      Database flavor [default: sqlite]
  --writer WRITER  DB Account with write permission
  --suffix SUFFIX  Table suffix 
"""

dbflavors=['oracle','sqlite']

import os
from docopt import docopt
from schema import Schema, And, Or, Use

def validate(optdict):
    result={}
    schema = Schema({ 
     '-i': Use(open, error='-i INPUTFILE should be readable'),
     '-f': And(str,lambda s: s.lower() in dbflavors, error='-f must be in '+str(dbflavors)),
     '--writer': Or(None,Use(str.upper)),
     '--suffix': Or(None,Use(str.upper)),
     str:object # catch all
    })
    result=schema.validate(optdict)
    return result

if __name__ == '__main__':
    print docopt(__doc__,options_first=True)
