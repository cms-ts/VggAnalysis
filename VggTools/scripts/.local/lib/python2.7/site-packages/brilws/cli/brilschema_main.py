import sys
import os
sys.path.insert(0,os.path.dirname(sys.executable)+'/../lib/python2.7/site-packages/') #ignore other PYTHONPATH

import logging
import docopt
import schema
import brilws
import yaml
from sqlalchemy import *
from ConfigParser import SafeConfigParser
from brilws import api
import pandas as pd

log = logging.getLogger('brilschema')
logformatter = logging.Formatter('%(levelname)s %(message)s')
ch = logging.StreamHandler()
ch.setLevel(logging.WARNING)
#fh = logging.FileHandler('/tmp/brilschema.log')
ch.setFormatter(logformatter)
#fh.setFormatter(logformatter)
log.addHandler(ch)
#log.addHandler(fh)


def brilschema_main(progname=sys.argv[0]):
    docstr='''


    usage:
      brilschema (-h|--help) 
      brilschema --version
      brilschema --checkforupdate
      brilschema [--debug|--nowarning] <command> [<args>...]

    commands:
      create      generate table creat/drop sql
      loadmap     load map data  
      loaddata    load data
      loadresult  load result

    See 'brilschema <command> --help' for more information on a specific command.

    '''

    args = {}
    argv = sys.argv[1:]
    args = docopt.docopt(docstr,argv,help=True,version=brilws.__version__,options_first=True)
    
    if '--debug' in sys.argv:
       log.setLevel(logging.DEBUG)
       ch.setLevel(logging.DEBUG)
    if args['--version'] : print brilws.__version__
    log.debug('global arguments: %s',args)
    cmmdargv = [args['<command>']] + args['<args>']

    log.debug('command arguments: %s',cmmdargv)
    parseresult = {}

    try:
      if args['<command>'] == 'create':
         import brilschema_create
         parseresult = docopt.docopt(brilschema_create.__doc__,argv=cmmdargv)
         parseresult = brilschema_create.validate(parseresult)
         columntypemap={}
         schemadatadef={}
         infile = parseresult['-i']
         infilenamebase = os.path.basename(infile.name).split('.')[0]         
         suffix = parseresult['--suffix']             
         writeraccount = ''
         if parseresult['-f']=='oracle':
              columntypemap = api.oracletypemap
              if parseresult.has_key('--writer'):                  
                  writeraccount = parseresult['--writer']
         else:
              columntypemap = api.sqlitetypemap
         schemadatadef = yaml.load(parseresult['-i'])
         print 'Creating drop sql file for: %s'%infilenamebase
         api.drop_tables_sql(infilenamebase,schemadatadef,suffix=suffix,dbflavor=parseresult['-f'])
         print 'Creating create sql file for: %s'%infilenamebase
         api.create_tables_sql(infilenamebase,schemadatadef,suffix=suffix,dbflavor=parseresult['-f'],writeraccount=writeraccount)
         print 'Done'

      elif args['<command>'] == 'loadmap':
         import brilschema_loadmap         
         parseresult = docopt.docopt(brilschema_loadmap.__doc__,argv=cmmdargv)
         parseresult = brilschema_loadmap.validate(parseresult)
         inengine = os.path.expanduser(parseresult['-i'])
         outengine = os.path.expanduser(parseresult['-o'])
         iniparser = SafeConfigParser()
         if parseresult['--name'] == 'datatable':
             d = api.DatatableMap()
         elif parseresult['--name'] == 'amodetag':
             d = api.AmodetagMap()
         elif parseresult['--name'] == 'beamstatus':
             d = api.BeamStatusMap()
             result = d.from_sourcedb(inengine)
         elif parseresult['--name'] == 'trgbit':
             d = api.TrgBitMap()
         elif parseresult['--name'] == 'hltconfig':
             d = api.HltConfigMap()
         elif parseresult['--name'] == 'l1seed':
             d = api.L1SeedMap()
         elif parseresult['--name'] == 'hltpath':
             d = api.HLTPathMap()
         elif parseresult['--name'] == 'trghltseed':
             d = api.TrgHltSeedMap()
         elif parseresult['--name'] == 'dataset':
             d = api.DatasetMap()
         elif parseresult['--name'] == 'hltstreamdataset':
             d = api.HLTStreamDatasetMap()
         if not os.path.isfile(inengine):
             sourceurl = inengine
             if sourceurl.find('oracle') != -1:
                 iniparser.read(os.path.join(parseresult['-p'],'readdb2.ini'))
                 sourcepasswd = parser.get(outengine,'pwd')
                 sourceschema = parser.get(outengine,'schema')
                 idx = sourceengine.find('@')
                 sourceurl = sourceengine[:idx]+':'+sourcepasswd.decode('base64')+sourceengine[idx:]
             inengine = create_engine(soureceurl)
         result = d.from_sourcedb(inengine)
         print result
         if os.path.isfile(outengine):
             d.to_csv(outengine,result)
         else:
             desturl = outengine
             if desturl.find('oracle') != -1:
                 iniparser.read(os.path.join(parseresult['-p'],'authentication.ini'))
                 destpasswd = parser.get(outengine,'pwd')
                 idx = outengine.find('@')
                 desturl = outengine[:idx]+':'+destpasswd.decode('base64')+outengine[idx:]             
             outengine = create_engine(desturl)
             d.to_brildb(outengine,result)
      elif args['<command>'] == 'loaddata':
         import brilschema_loaddata         
         parseresult = docopt.docopt(brilschema_loadmap.__doc__,argv=cmmdargv)
         parseresult = brilschema_loaddata.validate(parseresult)
         incsv = os.path.expanduser(parseresult['-i'])
         c = api.get_filepath_or_buffer(incsv)
         if os.path.isfile(c):
             pass
         else:
             pass
         outengine = os.path.expanduser(parseresult['-o'])
         iniparser = SafeConfigParser()
         if parseresult['--name'] == 'fillinfo':
             d = api.FillInfo()
             if parseresult['--lumidb']:
                 d.from_lumidb(lumidbengine,fillnum)
                 print d
      elif args['<command>'] == 'loadresult':
         import brilschema_loadresult
         iniparser = SafeConfigParser()
         parseresult = docopt.docopt(brilschema_loadresult.__doc__,argv=cmmdargv)
         parseresult = brilschema_loadresult.validate(parseresult)
         incsv = os.path.expanduser(parseresult['-i'])
         runlsselect = api.parsecmsselectJSON(runlsselect)
         lumidb  = api.get_filepath_or_buffer(parseresult['--lumidb'])
         if os.path.isfile(lumidb):
             print lumidb
         else:
             lumidburl = lumidb
             if lumidburl.find('oracle') != -1:
                 iniparser.read(os.path.join(parseresult['-p'],'authentication.ini'))
                 lumidbpasswd = parser.get(lumidburl,'pwd')
                 idx = lumidburl.find('@')
                 lumidburl = lumidburl[:idx]+':'+lumidbpasswd.decode('base64')+lumidburl[idx:]             
             lumidbengine = create_engine(lumidburl)
         datasourcename = parseresult['--name'].lower()
         d = api.LumiResult(datasourcename)
         for run,lss in runlsselect:
             print run,lss
         #d.from_lumidb(lumidbengine,)
         
      else:
         exit("%r is not a brilschema command. See 'brilschema --help'."%args['<command>'])
    except docopt.DocoptExit:
      raise docopt.DocoptExit('Error: incorrect input format for '+args['<command>'])
    except schema.SchemaError as e:
      exit(e)

    if not parseresult.has_key('--debug'):
       if parseresult.has_key('--nowarning'):
          log.setLevel(logging.ERROR)
          ch.setLevel(logging.ERROR)
    else:
        log.setLevel(logging.DEBUG)
        ch.setLevel(logging.DEBUG)
    log.debug('create arguments: %s',parseresult)

    
if __name__ == '__main__':
    brilschema_main()
