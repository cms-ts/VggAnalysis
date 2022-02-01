"""

Usage:
  brilschema loadresult [options] 

Options:
  -h, --help       Show this screen
  -i INSELECT      Input run, ls selection json file or dict string 
  -o OUTPUT        Output csv file or bril database 
  -p AUTH          Path to authentication.ini 
  --name NAME      Result: hfoclumi,pixellumi
  --lumdb LUMIDB   Source lumi database or csv file

"""


import os,re
from docopt import docopt
from schema import Schema, And, Or, Use
choices_resultdata = ['hfoclumi','pixellumi']


def validate(optdict):
    result={}
    schema = Schema({ 
     '-i': str,
     '-o': Or(None,And(str,lambda s: os.path.isfile(os.path.expanduser(s)) or s.find('sqlite:')!=-1 or s.find('oracle:')!=-1) ,error='-o OUTPUT should be a csv file or database connect string'),     
     '--name': And(str,lambda s: s.lower() in choices_mapdata, error='NAME must be in '+str(choices_resultdata)),
     '--lumidb': And(str,lambda s: os.path.isfile(os.path.expanduser(s)) or s.find('sqlite:')!=-1 or s.find('oracle:')!=-1 ,error='-o LUMIDB should be a csv file or database connect string'),  
     '-p': Or(None,And(str,lambda s: os.path.isfile(os.path.join(os.path.expanduser(s),'authentication.ini'))) ,error='-p AUTH should contain authentication.ini'),   
     str:object # catch all
    })
    result=schema.validate(optdict)    
    return result

if __name__ == '__main__':
    print docopt(__doc__,options_first=True)
