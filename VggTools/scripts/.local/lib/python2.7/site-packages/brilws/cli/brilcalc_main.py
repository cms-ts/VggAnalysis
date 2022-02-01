import sys
import os
sys.path.insert(0,os.path.dirname(sys.executable)+'/../lib/python2.7/site-packages/') #ignore other PYTHONPATH

import logging
import docopt
import schema
import brilws
import prettytable
import pandas as pd
import numpy as np
import ast
from brilws import api,params,display,lumiParameters,corrector
from brilws.cli import clicommonargs
import brilws.formatter as fm
import re,time, csv
from datetime import datetime
from sqlalchemy import *
import math
from itertools import izip_longest
from dateutil import tz
import pytz
log = logging.getLogger('brilws')
logformatter = logging.Formatter('%(levelname)s %(name)s %(message)s')
log.setLevel(logging.ERROR)
ch = logging.StreamHandler()
ch.setFormatter(logformatter)
log.addHandler(ch)

lumip = lumiParameters.ParametersObject()
lslengthsec= lumip.lslengthsec
utctmzone = tz.gettz('UTC')
cerntmzone = tz.gettz('CEST')

class Unbuffered(object):
    def __init__(self, stream):
        self.stream = stream
    def write(self, data):
        self.stream.write(data)
        self.stream.flush()
    def __getattr__(self, attr):
        return getattr(self.stream.attr)
sys.stdout = Unbuffered(sys.stdout)

np.seterr(divide='ignore', invalid='ignore')

def xing_indexfilter(arr,constfactor=1.,xingMin=0.,xingTr=0.,xingId=[]):
    vidx = None    
    if xingTr:
        vidx = np.argwhere( np.logical_and( (arr*constfactor)>xingMin, arr>xingTr*np.max(arr) ) ).ravel()
    else:
        vidx = np.argwhere( (arr*constfactor)>xingMin ).ravel()
    if xingId :
        posidx = np.array(xingId)-1 #array position index is bunch index - 1
        return np.intersect1d(np.array(posidx),vidx)    
    return vidx

def totalprescaleNEW(hltprescval,l1seedlogic,l1prescvals):
    '''
    1) if ONE single seed, take it
    2) if OR:  (A.1 OR A.2 OR A.3 ...) ignore the triggers with prescale 0, and take the minimum of the remaining prescale values:
        if max(A.i) == 0
                A = 0
        else
                A = min(A.i | A.i > 0)
    3) if AND: A AND B AND C ... take the product of the prescale values A * B * C ...
    4) (optional)
       if (A.1 OR A.2 OR A.3 ...) AND (B.1 OR B.2 OR ...) AND ...
       - for each group, take the lowest non-zero prescale, or 0 if they are all zero
         if max(A.i) = 0
                A =
         else
                A = min(A.i | A.i > 0)
       - take the product of the prescales thus obtained:
         P = A * B * ...
       users still take their own risk and should use their own judgement.
    5)  if NOT, or a combination of AND/OR and NOT, reject
    '''
    totpresc = 0
    if not hltprescval or not l1prescvals or not l1seedlogic:
        return totpresc
    if np.all( np.array(l1prescvals)==1 ):
        totpresc = hltprescval        
    elif l1seedlogic=='ONE':
        totpresc = hltprescval*l1prescvals[0]
    elif l1seedlogic=='OR':
        if np.max( np.array(l1prescvals) ) == 0:
            return totpresc
        else:
            l = np.array(l1prescvals)
            l1p = np.min( l[l>0] )
        totpresc = hltprescval*l1p
    elif l1seedlogic=='AND':
        if np.max( np.array(l1prescvals) ) == 0:
            return totpresc
        l1p = np.prod( np.array(l1prescvals) )
        totpresc = hltprescval*l1p    
    return totpresc

    
def totalprescale(hltprescval,l1seedlogic,l1prescvals):
    totpresc = 0
    if not hltprescval or not l1prescvals or not l1seedlogic:
        return totpresc
    if np.all( np.array(l1prescvals)==1 ):
        totpresc = hltprescval
    elif l1seedlogic=='ONE':
        totpresc = hltprescval*l1prescvals[0]
    elif l1seedlogic=='OR':
        
        totpresc = hltprescval*np.min(l1prescvals)
    elif l1seedlogic=='AND':
        totpresc = hltprescval*np.max(l1prescvals)    
    return totpresc

def lumi_per_normtag(shards,lumiquerytype,dbengine,dbschema,runtot,formatter,datasource=None,normtag=None,withBX=False,byls=None,fh=None,csvwriter=None,ptable=None,scalefactor=1,totz=utctmzone,fillmin=None,fillmax=None,runmin=None,runmax=None,amodetagid=None,egev=None,beamstatusid=None,tssecmin=None,tssecmax=None,runlsSeries=None,hltl1map={},ignorel1mask=False,xingMin=0.,xingTr=0.,xingId=[],checkjson=False,datatagnameid=None,withfileinput = False):
   
    if withfileinput:
        from brilws import fileapi

    validitychecker = None
    lastvalidity = None
    if normtag and normtag is not 'withoutcorrection':
        normdata = api.iov_gettagdata(dbengine, normtag,schemaname=dbschema)
        if not normdata: raise ValueError('normtag %s does not exist'%normtag)
        validitychecker = ValidityChecker(normdata)

    for shard in shards:              
        lumiiter = None
        if lumiquerytype == 'bestresultonline':
            if withfileinput:
               lumiiter = fileapi.resultIter(shards,datasource,fillmin=fillmin,fillmax=fillmax,runmin=runmin,runmax=runmax,amodetagid=amodetagid,targetegev=egev,beamstatusid=beamstatusid,tssecmin=tssecmin,tssecmax=tssecmax,runlsselect=runlsSeries,withBX=withBX)
            else:
                tablename = 'online_result_'+str(shard)
                shardexists = api.table_exists(dbengine,tablename,schemaname=dbschema)
                if not shardexists: continue
                rfields = ['fillnum','runnum','lsnum','timestampsec','cmson','beamstatusid','targetegev','delivered','recorded','avgpu','datasource','numbxbeamactive']
                if withBX: rfields = rfields+['bxdeliveredblob']                    
                lumiiter = api.online_resultIter(dbengine,tablename,schemaname=dbschema,fields=rfields,fillmin=fillmin,fillmax=fillmax,runmin=runmin,runmax=runmax,amodetagid=amodetagid,targetegev=egev,beamstatusid=beamstatusid,tssecmin=tssecmin,tssecmax=tssecmax,runlsselect=runlsSeries,sorted=True)
            
        elif lumiquerytype in ['detresultonline','detraw']:   
            datatype = 'raw'
            if lumiquerytype=='detresultonline':
                datatype = 'result'
            if withfileinput:
                lumiiter = fileapi.resultIter(shards,datasource,datatype=datatype,fillmin=fillmin,fillmax=fillmax,runmin=runmin,runmax=runmax,amodetagid=amodetagid,targetegev=egev,beamstatusid=beamstatusid,tssecmin=tssecmin,tssecmax=tssecmax,runlsselect=runlsSeries,withBX=withBX)   
            else:                
                tablename = datasource.lower()+'_'+datatype+'_'+str(shard)
                shardexists = api.table_exists(dbengine,tablename,schemaname=dbschema)
                if not shardexists: continue
                rfields = ['avglumi']
                idfields = ['fillnum','runnum','lsnum','timestampsec','beamstatusid','cmson','deadtimefrac','targetegev','numbxbeamactive']
                if withBX: rfields = rfields+['bxlumiblob']
                lumiiter = api.dataIter(dbengine,datasource,datatype,shard,datafields=rfields,idfields=idfields,schemaname=dbschema,fillmin=fillmin,fillmax=fillmax,runmin=runmin,runmax=runmax,amodetagid=amodetagid,targetegev=egev,beamstatusid=beamstatusid,tssecmin=tssecmin,tssecmax=tssecmax,runlsselect=runlsSeries,sorted=True,datatagnameid=datatagnameid)                    
                  
        if lumiiter is None:
            continue
        
        g_run_old = 0
        g_ls_trglastscaled_old = 0
        prescale_map = {} # for global scope
        g_hltconfigid = 0
        for row in lumiiter:
            fillnum = row['fillnum']
            runnum = row['runnum']
            lsnum = row['lsnum']            
            cmslsnum = lsnum
            timestampsec = row['timestampsec']
            cmson = row['cmson']
            
            if not cmson:
                cmslsnum = 0
            if hltl1map:
                if cmslsnum==0: continue  #cms is not running, skip.                
                if g_run_old!=runnum:     #on new run boundary, get hltconfigid
                    hltrunconfig = api.get_hltrunconfig(dbengine,runnum=runnum,schemaname=dbschema) #[['runnum','hltconfigid','hltkey']]
                    if not hltrunconfig:
                        continue
                    g_hltconfigid = [h[1] for h in hltrunconfig][0]
                    if not g_hltconfigid:
                        continue      
                    presc = api.get_prescidx_change(dbengine,runnum,schemaname=dbschema)#{runnum:[[lslastscaler,prescidx]] }
                    if presc.has_key(runnum):
                        presc = presc[runnum]
                this_prescidx = None
                if not presc:                    
                    ls_trglastscaled = 1
                else:
                    b = [ i[0] for i in presc if i[0]<=cmslsnum ] 
                    if not b:
                        ls_trglastscaled = 1
                        this_prescidx = None                        
                    else:
                        ls_trglastscaled = np.max( b )
                        this_prescidx = [t[1] for t in presc if t[0]==ls_trglastscaled][0]
                if (g_ls_trglastscaled_old != ls_trglastscaled) or (g_run_old != runnum): #on prescale change lumi section or new run
                    prescale_map = {} #clear prescaleindex change map on new prescale index value
                    if not hltl1map.has_key(g_hltconfigid):
                        continue
                    this_hltl1map = hltl1map[g_hltconfigid]#[[hltpathid,hltpathname,l1seedtype,l1seedbits]]
                    for grouped in this_hltl1map:
                        this_hltpathid = grouped[0]
                        hltpathname = grouped[1]
                        l1seedlogic = grouped[2]
                        l1candidates = grouped[3]
                        if this_prescidx is None:
                            hltprescval = 1
                            totpresc = 1
                        else:
                            hltprescval = api.get_hltprescale(dbengine,runnum,ls_trglastscaled,g_hltconfigid,this_prescidx,this_hltpathid,schemaname=dbschema)
                            rl = api.get_l1prescale(dbengine,runnum,ls_trglastscaled,l1candidates=l1candidates,prescidxs=this_prescidx,ignorel1mask=ignorel1mask ,schemaname=dbschema)
                            if not rl: continue
                            l1keys = [ k for k in rl.keys() if k[0]==this_prescidx ]
                            l1vals = [ rl[k] for k in l1keys ]                       
                            l1prescvals = [ v[0] for v in l1vals ]                            
                            totpresc = totalprescaleNEW(hltprescval,l1seedlogic,l1prescvals)
                            if not totpresc:
                                continue
                        prescale_map[hltpathname] = totpresc   
                    g_ls_trglastscaled_old = ls_trglastscaled
                g_run_old = runnum
            beamstatusid = row['beamstatusid']
            beamstatus = params._idtobeamstatus[beamstatusid]
            if beamstatus not in ['FLAT TOP','STABLE BEAMS','SQUEEZE','ADJUST']: continue
            tegev = row['targetegev']
            dtime = str(timestampsec)
            if totz is not None:
                d = datetime.fromtimestamp(int(timestampsec),tz=pytz.utc)
                dtime = d.astimezone(totz).strftime(params._datetimefm)
            delivered = recorded = avgpu = livefrac = 0.
            if checkjson:
                g_returnedls.append((runnum,lsnum))
            if lumiquerytype == 'bestresultonline': ##bestlumi                                
                if row.has_key('delivered') and row['delivered']:                    
                    delivered = np.true_divide(row['delivered']*lslengthsec,scalefactor)             
                if delivered>0 and row.has_key('recorded') and row['recorded']:
                    recorded = np.true_divide(row['recorded']*lslengthsec,scalefactor)
                if delivered>0 and row.has_key('avgpu') and row['avgpu']:
                    avgpu = row['avgpu']
                ds = 'UNKNOWN' 
                if row.has_key('datasource') and row['datasource']:
                    ds = row['datasource']
                livefrac = np.true_divide(recorded,delivered)
                if withBX:    #--xing
                    bxlumi = None
                    bxlumistr = '[]'
                    
                    if row.has_key('bxdeliveredblob') and row['bxdeliveredblob'] is not None:
                        if withfileinput:
                            bxdeliveredarray = row['bxdeliveredblob']
                        else:
                            bxdeliveredarray = np.array(api.unpackBlobtoArray(row['bxdeliveredblob'],'f'))                        
                        totfactor = np.true_divide(lslengthsec,scalefactor)
                        bxidx = xing_indexfilter(bxdeliveredarray,constfactor=totfactor,xingMin=xingMin,xingTr=xingTr,xingId=xingId)
                        if bxidx is not None and bxidx.size>0:
                            bxdelivered = bxdeliveredarray[bxidx]*totfactor
                            bxlumi = np.transpose( np.array([bxidx+1,bxdelivered,bxdelivered*livefrac]) )
                        del bxdeliveredarray
                        del bxidx
                        if hltl1map: #--hltpath bx display
                            for pth in prescale_map.keys():                                
                                thispresc = prescale_map[pth]
                                if bxlumi is not None:
                                    a = map(formatter.bxlumi,bxlumi/thispresc)  
                                    bxlumistr = '['+' '.join(a)+']'                                
                                display.add_row( ['%d:%d'%(runnum,fillnum),'%d:%d'%(lsnum,cmslsnum),dtime,pth,myformatter.lumi(np.true_divide(delivered,thispresc)),formatter.lumi(np.true_divide(recorded,thispresc)),ds,'%s'%bxlumistr] , fh=fh, csvwriter=csvwriter, ptable=ptable)                                
                        else:        #normal bx display                   
                            if bxlumi is not None:
                                a = map(formatter.bxlumi,bxlumi)
                                bxlumistr = '['+' '.join(a)+']'                            
                            display.add_row( ['%d:%d'%(runnum,fillnum),'%d:%d'%(lsnum,cmslsnum),dtime,beamstatus,'%d'%tegev,formatter.lumi(delivered),formatter.lumi(recorded),'%.1f'%(avgpu),ds,'%s'%bxlumistr] , fh=fh, csvwriter=csvwriter, ptable=ptable)                            
                    del bxlumi
                    
                elif byls:      #--byls
                    if hltl1map:#--hltpath display
                        for pth in prescale_map.keys():
                            thispresc = prescale_map[pth]
                            display.add_row( ['%d:%d'%(runnum,fillnum),'%d:%d'%(lsnum,cmslsnum), dtime, pth, formatter.lumi(np.true_divide(delivered,thispresc)),formatter.lumi(np.true_divide(recorded,thispresc)),'%.1f'%(avgpu),ds] , fh=fh, csvwriter=csvwriter, ptable=ptable)                            
                    else:       #normal display
                        display.add_row( ['%d:%d'%(runnum,fillnum),'%d:%d'%(lsnum,cmslsnum),dtime,beamstatus,'%d'%tegev,formatter.lumi(delivered),formatter.lumi(recorded),'%.1f'%(avgpu),ds] , fh=fh, csvwriter=csvwriter, ptable=ptable)                        
            else:               ###lumisource
                if row.has_key('deadtimefrac') :
                    if row['deadtimefrac'] is not None:
                        livefrac = 1.-row['deadtimefrac']
                    else:
                        if cmslsnum!=0:
                            g_nulldeadtime.setdefault(runnum,[]).append(lsnum)
                        livefrac = 0.
                uncorrectedavglumi = row['avglumi'] #uncorrected, hz/ub
                avglumi = uncorrectedavglumi
                ncollidingbx = row['numbxbeamactive']
                uncorrectedbxlumi = None
                if row.has_key('bxlumiblob') and row['bxlumiblob'] is not None:                    
                    if withfileinput:
                        uncorrectedbxlumi = row['bxlumiblob']
                    else:
                        uncorrectedbxlumi = np.array(api.unpackBlobtoArray(row['bxlumiblob'],'f'))                
                bxlumi = uncorrectedbxlumi
                if validitychecker is not None:
                    if not lastvalidity or not validitychecker.isvalid(runnum,lastvalidity):
                        lastvalidity = validitychecker.getvalidity(runnum)
                    [normfunc,normparam] = validitychecker.getvaliddata(lastvalidity[0])
                    if withBX:
                        (avglumi,bxlumi) = corrector.applyCorrectionStr( normfunc,normparam, corrector.FunctionRoot(uncorrectedbxlumi,avglumi,ncollidingbx) )
                    else:
                        avglumi = corrector.applyCorrectionStr( normfunc,normparam, corrector.FunctionRoot(avglumi,avglumi,ncollidingbx) )[0]

                totfactor = np.true_divide(lslengthsec,scalefactor)
                delivered = avglumi*totfactor
                recorded = delivered*livefrac
                avgpu = lumip.avgpu( avglumi,ncollidingbx,g_minbias)

                if withBX:      #--xing
                    bxlumistr = '[]'
                    if bxlumi is not None:
                        bxidx = xing_indexfilter(bxlumi,constfactor=totfactor,xingMin=xingMin,xingTr=xingTr,xingId=xingId)          
                        if bxidx is not None and bxidx.size>0:                                      
                            bxdelivered =  bxlumi[bxidx]*totfactor
                            bxlumi = np.transpose( np.array([bxidx+1,bxdelivered,bxdelivered*livefrac]) )
                        else:
                            bxlumi = None                       
                        del uncorrectedbxlumi
                        del bxidx
                    if hltl1map:#--hltpath xing display
                        for pth in prescale_map.keys():
                            thispresc = prescale_map[pth]                            
                            if bxlumi is not None:
                                a = map(formatter.bxlumi,bxlumi/thispresc)  
                                bxlumistr = '['+' '.join(a)+']'                            
                            display.add_row( ['%d:%d'%(runnum,fillnum),'%d:%d'%(lsnum,cmslsnum),dtime,pth,formatter.lumi(np.true_divide(delivered,thispresc)),formatter.lumi(np.true_divide(recorded,thispresc)),datasource.upper(),'%s'%bxlumistr] , fh=fh, csvwriter=csvwriter, ptable=ptable)                            
                    else:       #normal xing display
                        if bxlumi is not None:
                            a = map(formatter.bxlumi,bxlumi)                            
                            bxlumistr = '['+' '.join(a)+']'
                        display.add_row( ['%d:%d'%(runnum,fillnum),'%d:%d'%(lsnum,cmslsnum),dtime,beamstatus,'%d'%tegev,formatter.lumi(delivered),formatter.lumi(recorded),'%.1f'%(avgpu),datasource.upper(),'%s'%bxlumistr] , fh=fh, csvwriter=csvwriter, ptable=ptable)                        
                    del bxlumi
                elif byls:       #--byls
                    if hltl1map: #--hltpath display
                        for pth in prescale_map.keys():
                            thispresc = prescale_map[pth]                            
                            display.add_row( ['%d:%d'%(runnum,fillnum),'%d:%d'%(lsnum,cmslsnum),dtime,pth,formatter.lumi(np.true_divide(delivered,thispresc)),formatter.lumi(np.true_divide(recorded,thispresc)),'%.1f'%(avgpu),datasource.upper()] , fh=fh, csvwriter=csvwriter, ptable=ptable)                            
                    else:        #normal display
                        display.add_row( ['%d:%d'%(runnum,fillnum),'%d:%d'%(lsnum,cmslsnum),dtime,beamstatus,'%d'%tegev,formatter.lumi(delivered),formatter.lumi(recorded),'%.1f'%(avgpu),datasource.upper()] , fh=fh, csvwriter=csvwriter, ptable=ptable)    
            if not hltl1map:     #normal statistic collect
                if not runtot.has_key( ('',runnum) ):
                    runtot[('',runnum)] = {'fill':fillnum,'dtime':dtime,'nls':0,'ncms':0,'delivered':0,'recorded':0} 
                runtot[ ('',runnum)]['nls']+=1                
                if cmson: runtot[ ('',runnum) ]['ncms']+=1
                runtot[ ('',runnum) ]['delivered']+=delivered
                runtot[ ('',runnum) ]['recorded']+=recorded                                
            else:                #hltpath statistic collect
                if not cmson:
                    continue
                for pth in prescale_map.keys():
                    thispresc = prescale_map[pth]
                    if not runtot.has_key( (pth,runnum) ):
                        runtot[(pth,runnum)] = {'fill':fillnum,'dtime':dtime,'nls':0,'ncms':0,'delivered':0,'recorded':0}                        
                    runtot[ (pth,runnum)]['nls']+=1                
                    if cmson: runtot[ (pth,runnum) ]['ncms'] += 1
                    runtot[ (pth,runnum) ]['delivered'] += np.true_divide(delivered,thispresc)
                    runtot[ (pth,runnum) ]['recorded'] += np.true_divide(recorded,thispresc)      
                
class ValidityChecker(object):
    def __init__(self, normdata):
        self.normdata = normdata
        self.allsince = np.array([x[0] for x in normdata])
        
    def getvalidity(self,runnum):
        if self.allsince.size == 0 : return None
        since = 1
        if self.allsince[self.allsince<=runnum].size>0:
            since = self.allsince[self.allsince<=runnum].max()
        till = 999999
        if self.allsince[self.allsince>runnum].size>0:
            till = self.allsince[self.allsince>runnum].min()
        return (since,till)
    
    def isvalid(self,runnum,validity):
        if runnum>=validity[0] and runnum<validity[1]:
            return True
        return False

    def getvaliddata(self,since):
        s = np.where(self.allsince==since)
        if s[0].size>0:
            sinceindex = s[0][0]
            func = self.normdata[sinceindex][1]
            params = self.normdata[sinceindex][2]
            return [func,params]
        return None

def findtagname(dbengine,datatagname,dbschema):
    '''
    output: (datatagname,datatagnameid)
    '''
    datatagnameid=0
    if datatagname:
        datatagnameid = api.datatagnameid(dbengine,datatagname=datatagname,schemaname=dbschema)
    else:
        r = api.max_datatagname(dbengine,schemaname=dbschema)
        if not r:
            raise RuntimeError('no tag found')
        datatagname = r[0]
        datatagnameid = r[1]
    if not datatagnameid:
        raise RuntimeError('No tag %s found'%datatagname)   
    return (datatagname,datatagnameid)

          
def brilcalc_main(progname=sys.argv[0]):

    docstr='''

    usage:
      brilcalc (-h|--help|--version) 
      brilcalc [--debug|--warn] <command> [<args>...]

    commands:
      lumi Luminosity
      beam Beam 
      trg Trigger configurations      
    See 'brilcalc <command> --help' for more information on a specific command.

    '''
    args = {}
    argv = sys.argv[1:]
    args = docopt.docopt(docstr,argv,help=True,version=brilws.__version__,options_first=True)

    if args['--debug']:
        log.setLevel(logging.DEBUG)
    elif args['--warn']:
        log.setLevel(logging.WARNING)
        
    log.debug('global arguments: %s',args)
    cmmdargv = [args['<command>']] + args['<args>']

    log.debug('command arguments: %s',cmmdargv)
    parseresult = {}
    global g_returnedls #[(run,ls),...]
    global g_nulldeadtime #{run:[]}
    global g_minbias #minbias xsec    
    
    try:
      if args['<command>'] == 'lumi':
          import brilcalc_lumi          
          parseresult = docopt.docopt(brilcalc_lumi.__doc__,argv=cmmdargv)
          parseresult = brilcalc_lumi.validate(parseresult)
          if parseresult['--filedata'] is not None:
              if parseresult.has_key('-u') and parseresult['-u']!= 'hz/ub':
                  print '[WARN] output unit is hz/ub with option --filedata'
              parseresult['-u'] = 'hz/ub'
          ##parse selection params
          pargs = clicommonargs.parser(parseresult)
          dbschema = ''
          if not pargs.dbconnect.find('oracle')!=-1: dbschema = 'cms_lumi_prod'
          log.debug('connecturl: %s'%pargs.connecturl)
          dbengine = create_engine(pargs.connecturl)
          
          totz=utctmzone
          if pargs.cerntime:
              totz=cerntmzone
          elif pargs.tssec:
              totz=None          
        
          fillmin = pargs.fillmin
          fillmax = pargs.fillmax
          runmin = pargs.runmin
          runmax = pargs.runmax
          amodetagid = pargs.amodetagid
          egev = pargs.egev
          beamstatusid = pargs.beamstatusid
          tssecmin = pargs.tssecmin
          tssecmax = pargs.tssecmax
          selectionkwds = {}
          normtag = None          
          fh = None
          ptable = None
          ftable = None
          csvwriter = None
          myformat = pargs.oformat
          myprecision = pargs.precision
          myformatter = fm.Formatter(myformat,myprecision)
          vfunc_lumiunit = np.vectorize(myformatter.lumiunit)
          checkjson = True
          if parseresult['--without-checkjson'] or not parseresult['-i']:
              checkjson = False
          if parseresult['--normtag'] or parseresult['--type']:
              g_minbias = pargs.minbias or lumip.minbias
          else:
              if not pargs.minbias is None:
                  print 'Error: --minBiasXsec cannot be used without --normtag 0r --type, quit'
                  sys.exit(0)
                  
          g_returnedls = []
          g_nulldeadtime = {}
          g_headers = {}
          g_headers['runheader'] = ['run:fill','time','nls','ncms','delivered(/ub)','recorded(/ub)']
          g_headers['footer'] = ['nfill','nrun','nls','ncms','totdelivered(/ub)','totrecorded(/ub)']
          g_headers['bylsheader'] = ['run:fill','ls','time','beamstatus','E(GeV)','delivered(/ub)','recorded(/ub)','avgpu','source']
          g_headers['runheader_hltpath'] = ['run:fill','time','ncms','hltpath','delivered(/ub)','recorded(/ub)']
          g_headers['footer_hltpath'] = ['hltpath','nfill','nrun','ncms','totdelivered(/ub)','totrecorded(/ub)']
          g_headers['bylsheader_hltpath'] = ['run:fill','ls','time','hltpath','delivered(/ub)','recorded(/ub)','avgpu','source']          
          
          
          scalefactor = pargs.scalefactor          
          lumiunitstr = parseresult['-u']         
          if lumiunitstr not in myformatter.lumiunit_to_scalefactor.keys(): 
              raise ValueError('%s not recognised as lumi unit'%lumiunit)
          lumiunitconversion = myformatter.lumiunit_to_scalefactor[lumiunitstr]
          scalefactor = scalefactor*lumiunitconversion
         
          if pargs.withBX:
              if pargs.hltpath is None:
                  header = g_headers['bylsheader']+['[bxidx bxdelivered(/ub) bxrecorded(/ub)]']
                  footer = g_headers['footer']
              else:
                  header = g_headers['bylsheader_hltpath']+['[bxidx bxdelivered(/ub) bxrecorded(/ub)]']
                  footer = g_headers['footer_hltpath']
          elif pargs.byls:
              if pargs.hltpath is None:
                  header = g_headers['bylsheader']
                  footer = g_headers['footer']
              else:
                  header = g_headers['bylsheader_hltpath']
                  footer = g_headers['footer_hltpath']
          else:
              if pargs.hltpath is None:
                  header = g_headers['runheader']
                  footer = g_headers['footer']
              else:
                  header = g_headers['runheader_hltpath']
                  footer = g_headers['footer_hltpath']
                  
          header = vfunc_lumiunit(header,lumiunitstr).tolist()
          footer = vfunc_lumiunit(footer,lumiunitstr).tolist()
        
          
          (datatagname,datatagnameid) = findtagname(dbengine,pargs.datatagname,dbschema)
          if not pargs.totable:
              fh = pargs.ofilehandle
              print >> fh, '#Data tag : %s , Norm tag: %s'%(datatagname,normtag)
              print >> fh, '#'+','.join(header)
              csvwriter = csv.writer(fh)
          else:
              ptable = display.create_table(header,header=True,align='l')
              ftable = display.create_table(footer,header=True,align='l')          
              
          datasources = [] #[lumiquerytype,normtagname,datasource,runlsstr]          

          lumiquerytype = 'detraw'
          normtag = normtagname = 'withoutcorrection'
          parsediffruns = None
          parsediffls = None
          if not pargs.withoutcorrection:
              normtag = pargs.iovtagSelect
              if not normtag:                  
                  if pargs.lumitype:
                      lumiquerytype = 'detresultonline'
                      datasources.append( ['detresultonline',normtag,pargs.lumitype.lower(),pargs.runlsSeries] )
                      normtagname = 'onlineresult'
                  else:
                      lumiquerytype = 'bestresultonline'
                      normtagname = 'onlineresult'
                      datasources.append( ['bestresultonline',normtag,'best',pargs.runlsSeries] )
              else:
                  if isinstance(normtag,list): #normtag is list
                      if pargs.runlsSeries is None:
                          checkjson = False
                          #mergedselect = normtag
                          mergedselect = api.mergeiovrunlsWithDB(dbengine,normtag,runmin=runmin,runmax=runmax,fillmin=fillmin,fillmax=fillmax,tssecmin=tssecmin,tssecmax=tssecmax,schemaname=dbschema)                          
                      else:
                          (parsediffruns, parsediffls) = api.checksuperset([x[1] for x in normtag],pargs.runlsSeries)                         
                          mergedselect = api.mergeiovrunls(normtag,pargs.runlsSeries)
                      normtagname = 'composite'
                      for item in mergedselect:
                          iovtag = item[0]
                          runlsdict = item[1]
                          iovtag_meta = api.iov_gettag(dbengine,iovtag,schemaname=dbschema)
                          if not iovtag_meta: raise ValueError('requested iovtags do not exist')  
                          datasource = iovtag_meta[2].lower()
                          datasources.append( [lumiquerytype,iovtag,datasource,runlsdict] )
                  else:  #normtag is string (iov tag)
                      datasource = pargs.lumitype
                      normtagname = normtag
                      if datasource is None: #det lumi with correction
                          iovtag_meta = api.iov_gettag(dbengine,normtag,schemaname=dbschema)
                          if not iovtag_meta: raise ValueError('%s does not exist'%normtag)                   
                          datasource = iovtag_meta[2]
                      datasources.append( [lumiquerytype,normtag,datasource.lower(),pargs.runlsSeries ])
                     
          else:
              if not pargs.lumitype:
                  raise ValueError('--type is required with --without-correction')
              datasources.append( [lumiquerytype,None,pargs.lumitype.lower(),pargs.runlsSeries ])
          
          log.debug('lumiquerytype %s'%lumiquerytype)          
          log.debug('scalefactor: %.2f'%pargs.scalefactor)                    
          
          runtot = {} #{(hltpath,run): { 'fill':fillnum,'time':dtime,'nls':1,'ncms':int(cmson),'delivered':delivered,'recorded':recorded} }
                               
          hltl1map = None
          
          if pargs.hltpath is not None:
              hltl1map = api.get_hlttrgl1seedmap(dbengine,hltpath=pargs.hltpath,schemaname=dbschema)
              if not hltl1map:
                  print 'no hltpath to l1bit mapping found'
                  sys.exit(0)
          
          rselectrange = [] 
          if datasources :
              for [qt,nt,ds,rs] in datasources:
                  if rs is None: continue
                  for r,l in rs.iteritems():
                      if not r in rselectrange:
                          rselectrange.append(r)   
          withfileinput = False
          if pargs.filedata is not None:
              withfileinput = True
              from brilws import fileapi
              if os.path.isfile(pargs.filedata):
                  filenames = [ os.path.abspath(pargs.filedata) ]
              else:
                  filenames = [ os.path.join(os.path.abspath(pargs.filedata),f) for f in os.listdir(pargs.filedata) ]
              shards = fileapi.open_validfiles(filenames,pargs.lumitype or 'best')              
              if not shards:
                  print 'Failed to find data file for the requested time range.'
                  [f.close() for f in shards] 
                  sys.exit(1)
          else:          
              shards = api.locate_shards(dbengine,runmin=runmin,runmax=runmax,fillmin=fillmin,fillmax=fillmax,tssecmin=tssecmin,tssecmax=tssecmax,orrunlist=rselectrange,schemaname=dbschema)
              if not shards:
                  print 'Failed to find data table for the requested time range.'
                  sys.exit(1)
              log.debug('shards: '+str(shards))
          
          for [qtype,ntag,dsource,rselect] in datasources:
              lumi_per_normtag(shards,qtype,dbengine,dbschema,runtot,myformatter,datasource=dsource,normtag=ntag,withBX=pargs.withBX,byls=pargs.byls,fh=fh,csvwriter=csvwriter,ptable=ptable,scalefactor=scalefactor,totz=totz,fillmin=fillmin,fillmax=fillmax,runmin=runmin,runmax=runmax,amodetagid=amodetagid,egev=egev,beamstatusid=beamstatusid,tssecmin=tssecmin,tssecmax=tssecmax,runlsSeries=rselect,hltl1map=hltl1map,ignorel1mask=parseresult['--ignore-mask'],xingMin=pargs.xingMin,xingTr=pargs.xingTr,xingId=pargs.xingId,checkjson=checkjson,datatagnameid=datatagnameid,withfileinput=withfileinput)  
          if pargs.filedata:
              [f.close() for f in shards] 
          if pargs.hltpath is None:
              nruns = len(runtot.keys())
              nfills = len( set([v['fill'] for v in runtot.values()] ) )
              nls = np.sum( [v['nls'] for v in runtot.values()]  )
              ncmsls = np.sum( [v['ncms'] for v in runtot.values()] )
              totdelivered = np.sum( [v['delivered'] for v in runtot.values() ] )
              totrecorded =  np.sum( [v['recorded'] for v in runtot.values() ] )
              if not pargs.byls and not pargs.withBX: #run table
                  for hn,rn in sorted(runtot.keys()):
                      v = runtot[ (hn,rn) ]                      
                      display.add_row( ['%d:%d'%(rn,v['fill']),v['dtime'],v['nls'],v['ncms'],myformatter.lumi(v['delivered']),myformatter.lumi(v['recorded']) ] , fh=fh, csvwriter=csvwriter, ptable=ptable)
              if pargs.filedata is None:
                  display.add_row( [ '%d'%nfills, '%d'%nruns, '%d'%nls,'%d'%ncmsls,myformatter.lumi(totdelivered),myformatter.lumi(totrecorded)], fh=fh, csvwriter=None, ptable=ftable)
              
          else:
              hltpathSummary = []
              runtot_df = pd.DataFrame.from_dict(runtot,orient='index')
              grouped = runtot_df.groupby(level=0) #group by hltpath
              totalpathdelivered = 0
              totalpathrecorded = 0
              for hn,g in grouped:
                  nruns = g.index.size
                  nfills = int(g['fill'].nunique())
                  ncmsls =  int(g['ncms'].sum())
                  totdelivered = g['delivered'].sum()
                  totrecorded = g['recorded'].sum()
                  if pargs.filedata is None:
                      display.add_row( [ hn, '%d'%nfills, '%d'%nruns, '%d'%ncmsls,myformatter.lumi(totdelivered),myformatter.lumi(totrecorded)], fh=fh, csvwriter=None, ptable=ftable)                                 
                  if not pargs.byls and not pargs.withBX: #hltpath, run table 
                      for i,v in g.iterrows():
                          pname = i[0]
                          trun = i[1]
                          tfill = v['fill']
                          ttime = v['dtime']
                          tncmsls = v['ncms']
                          tdelivered = v['delivered']
                          trecorded = v['recorded']
                          display.add_row( [ '%d:%d'%(trun,tfill), ttime, tncmsls, pname, myformatter.lumi(tdelivered), myformatter.lumi(trecorded)], fh=fh, csvwriter=csvwriter, ptable=ptable )
                  hltpathSummary.append([hn,nfills,nruns,ncmsls,totdelivered,totrecorded])
                  totalpathdelivered =  totalpathdelivered+totdelivered
                  totalpathrecorded = totalpathrecorded+totrecorded
                   
              del runtot_df
          
          if pargs.totable:  #to screen              
              print '#Data tag : %s , Norm tag: %s'%(datatagname,normtagname)
              display.show_table(ptable,pargs.outputstyle)
              if pargs.filedata is None:
                  print "#Summary: "
                  display.show_table(ftable,pargs.outputstyle)
              del ptable
              del ftable
              if pargs.hltpath:
                  print '#Sum delivered : %s'%myformatter.lumi(totalpathdelivered)
                  print '#Sum recorded : %s'%myformatter.lumi(totalpathrecorded)
          else:              #to file
              print >> fh, '#Summary:'                  
              print >> fh, '#'+','.join(footer)
              if not pargs.hltpath:
                  print >> fh, '#'+','.join( [ '%d'%nfills,'%d'%nruns,'%d'%nls,'%d'%ncmsls,myformatter.lumi(totdelivered),myformatter.lumi(totrecorded)] )
              else:
                  totalpathdelivered = 0
                  totalpathrecorded = 0
                  for pentry in hltpathSummary:
                      #print >> fh, '#'+','.join( [ '%s'%pentry[0],'%d'%pentry[1],'%d'%pentry[2],'%d'%pentry[3],'%.6f'%pentry[4],'%.6f'%pentry[5] ] )
                      print >> fh, '#'+','.join( [ '%s'%pentry[0],'%d'%pentry[1],'%d'%pentry[2],'%d'%pentry[3], myformatter.lumi(pentry[4]),myformatter.lumi(pentry[5]) ] )
                      totalpathdelivered =  totalpathdelivered+pentry[4]
                      totalpathrecorded = totalpathrecorded+pentry[5]
                  print >> fh,'#'
                  print >> fh,'#Sum delivered  : %s'%myformatter.lumi(totalpathdelivered)
                  print >> fh,'#Sum recorded : %s'%myformatter.lumi(totalpathrecorded)
          if parsediffruns or parsediffls:
              print '\nWarning: problems found in merging -i and --normtag selections:'
              if parsediffruns:
                  print '  runs %s are not covered by normtag'%(parsediffruns)
              if parsediffls:
                  for r in parsediffls.keys():
                      print '  in run %d %s is not a superset of %s'%(r, parsediffls[r][0], parsediffls[r][1])
          print         

          if checkjson:
              selectlist = []
              for k,v in rselect.iteritems():
                  for vv in v:
                      rlist = api.expandrange(vv)
                      for r in rlist:
                          selectlist.append((k,r))
              arr_selectlist = np.array(selectlist,dtype=np.dtype('int,int'))
              arr_returnedls = np.array(g_returnedls,dtype=np.dtype('int,int'))
              clist = list(np.setdiff1d(arr_selectlist,arr_returnedls,assume_unique=True))
              if pargs.totable:
                  print '#Check JSON:'                  
                  print '#(run,ls) in json but not in results: %s'%(str(clist))
              else:
                  print >> fh, '#Check JSON:'
                  print >> fh, '#(run,ls) in json but not in results: %s'%(str(clist))

          if g_nulldeadtime:
              if pargs.totable:
                  print '#WARN: unknown deadtime while CMS is on'   
                  for rr,lss in g_nulldeadtime.items():
                      print '#%d %s'%(rr,str(lss))
              else:
                  print >> fh, '#WARN: unknown deadtime while CMS is on'
                  for rr,lss in g_nulldeadtime.items():
                      print >> fh, '#%d %s'%(rr,str(lss))
                      
          if fh and fh is not sys.stdout: fh.close()
          
          sys.exit(0)

      elif args['<command>'] == 'beam':
          import brilcalc_beam

          parseresult = docopt.docopt(brilcalc_beam.__doc__,argv=cmmdargv)
          parseresult = brilcalc_beam.validate(parseresult)
          ##parse selection params
          pargs = clicommonargs.parser(parseresult)

          ##db params
          dbschema = ''
          if not pargs.dbconnect.find('oracle')!=-1: dbschema = 'cms_lumi_prod'
          dbengine = create_engine(pargs.connecturl)
          totz=utctmzone
          if pargs.cerntime: totz=cerntmzone
          if pargs.tssec: totz=None
          ##display params          
          fh = None
          ptable = None
          csvwriter = None

          (datatagname,datatagnameid) = findtagname(dbengine,pargs.datatagname,dbschema)
          log.debug('datatagname: %s, datatagnameid: %d'%(datatagname,datatagnameid))    
          header = ['fill','run','ls','time','egev','intensity1','intensity2','ncollidingbx']
          if pargs.withBX:
              header = ['fill','run','ls','time','[bxidx intensity1 intensity2]']
          if not pargs.totable:
              fh = pargs.ofilehandle
              print >> fh, '#Data tag : %s'%(datatagname)
              print >> fh, '#'+','.join(header)
              csvwriter = csv.writer(fh)
          else:
              ptable = display.create_table(header,header=True,maxwidth=80,align='l')                        

          idfields = ['fillnum','runnum','lsnum','timestampsec','beamstatusid','numbxbeamactive']    
          fields = ['egev','intensity1','intensity2']
          if pargs.withBX:
              fields = ['bxidxblob','bxintensity1blob','bxintensity2blob']
              
          rselectrange = []
          if pargs.runlsSeries is not None:
              for r,l in pargs.runlsSeries.iteritems():
                  if not r in rselectrange:
                      rselectrange.append(r)          
          shards = api.locate_shards(dbengine,runmin=pargs.runmin,runmax=pargs.runmax,fillmin=pargs.fillmin,fillmax=pargs.fillmax,tssecmin=pargs.tssecmin,tssecmax=pargs.tssecmax,orrunlist=rselectrange,schemaname=dbschema)
          if not shards:
              print 'Failed to find data table for the requested time range.'
              sys.exit(1)
          log.debug('shards: '+str(shards))
          for shard in shards:
              beamIt = api.dataIter(dbengine,'beam','',shard,datafields=fields,idfields=idfields,schemaname=dbschema,fillmin=pargs.fillmin,fillmax=pargs.fillmax,runmin=pargs.runmin,runmax=pargs.runmax,amodetagid=pargs.amodetagid,targetegev=pargs.egev,beamstatusid=pargs.beamstatusid,tssecmin=pargs.tssecmin,tssecmax=pargs.tssecmax,runlsselect=pargs.runlsSeries,sorted=True,datatagnameid=datatagnameid)
              if not beamIt:
                  continue
              for row in beamIt:
                  fillnum = row['fillnum']
                  runnum = row['runnum']
                  lsnum = row['lsnum']                          
                  timestampsec = row['timestampsec']
                  dtime = str(timestampsec)
                  ncollidingbx = 0
                  if totz is not None:
                      d = datetime.fromtimestamp(int(timestampsec),tz=pytz.utc)
                      dtime = d.astimezone(totz).strftime(params._datetimefm) 
                  if pargs.withBX:
                      bxintensity = None
                      bxintensitystr = '[]'
                      if row.has_key('bxidxblob') and row['bxidxblob'] is not None:
                          bxidxarray = np.array(api.unpackBlobtoArray(row['bxidxblob'],'H'))                            
                          bxidxarray = bxidxarray[bxidxarray!=np.array(None)]
                          if bxidxarray is not None and bxidxarray.size>0:
                              bxintensity1array =  np.array(api.unpackBlobtoArray(row['bxintensity1blob'],'f'))
                              bxintensity2array =  np.array(api.unpackBlobtoArray(row['bxintensity2blob'],'f'))
                              bxintensity = np.transpose( np.array([bxidxarray+1,bxintensity1array,bxintensity2array]) )
                              a = map(fm.bxintensity,bxintensity)                          
                              bxintensitystr = '['+' '.join(a)+']'
                              del bxintensity1array
                              del bxintensity2array
                          del bxidxarray
                          display.add_row( ['%d'%fillnum,'%d'%runnum,'%d'%lsnum,dtime,'%s'%bxintensitystr], fh=fh, csvwriter=csvwriter, ptable=ptable )
                  else:
                      egev = row['egev']
                      intensity1 = row['intensity1']/pargs.scalefactor
                      intensity2 = row['intensity2']/pargs.scalefactor
                      ncollidingbx = row['numbxbeamactive'] 
                      display.add_row( ['%d'%fillnum,'%d'%runnum,'%d'%lsnum,dtime,'%.1f'%egev,'%.4e'%intensity1,'%.4e'%intensity2, '%d'%ncollidingbx],fh=fh, csvwriter=csvwriter, ptable=ptable)

          if pargs.totable:
              print '#Data tag : ',datatagname
              display.show_table(ptable,pargs.outputstyle)
              del ptable
                  
          if fh and fh is not sys.stdout: fh.close()
          sys.exit(0)
          
      elif args['<command>'] == 'trg':      
          import brilcalc_trg
          parseresult = docopt.docopt(brilcalc_trg.__doc__,argv=cmmdargv)
          parseresult = brilcalc_trg.validate(parseresult)
          ##parse selection params
          pargs = clicommonargs.parser(parseresult)
          
          ##db params
          dbschema = ''
          if not pargs.dbconnect.find('oracle')!=-1: dbschema = 'cms_lumi_prod'
          dbengine = create_engine(pargs.connecturl)
                  
          ##display params          
          fh = None
          ptable = None
          csvwriter = None

          is_pathinfo = parseresult['--pathinfo']
          is_prescale = parseresult['--prescale']
            
          if is_pathinfo:
              header = ['hltpath','logic','l1bit']
              hltrunconfig = []
              hltconfigids = []
              if pargs.hltconfigid or pargs.hltkey or pargs.runmin:
                  hltrunconfig = api.get_hltrunconfig(dbengine,hltconfigid=pargs.hltconfigid,hltkey=pargs.hltkey,runnum=pargs.runmin,schemaname=dbschema)  #[['runnum','hltconfigid','hltkey'],['runnum','hltconfigid','hltkey']]
                  if not hltrunconfig:
                      print 'hltconfig not found'
                      sys.exit(0)
                  hltconfigids = np.unique( [h[1] for h in hltrunconfig] )
                  
              hltl1map = api.get_hlttrgl1seedmap(dbengine,hltpath=pargs.hltpath,hltconfigids=hltconfigids,schemaname=dbschema)
              # {hltconfigid: [[hltpathid,hltpathname,seedtype,[seedvalues]]]}
              if not hltl1map:
                  print 'hltl1seed mapping not found'
                  sys.exit(0)                  

              if not pargs.totable:
                  fh = pargs.ofilehandle
                  print >> fh, '# '+','.join(header)
                  csvwriter = csv.writer(fh)
              else:
                  ptable = display.create_table(header,header=True,maxwidth=60,align='l')
                                
              for hid in hltl1map.keys():
                  hdata = hltl1map[hid]
                  for pathdata in hdata:
                      hltpathname = pathdata[1]
                      seedtype = pathdata[2]
                      seedvals = pathdata[3]
                      seedstr = ' '.join([str(i) for i in seedvals])
                      display.add_row( [ '%s'%hltpathname , '%s'%seedtype, '%s'%seedstr], fh=fh, csvwriter=csvwriter, ptable=ptable )                
              if ptable:
                  display.show_table(ptable,pargs.outputstyle)         
              del ptable
          elif is_prescale:                    
              header = ['run','cmsls','prescidx']
              if pargs.hltpath is not None: 
                  header = header+['totprescval','hltpath/prescval','logic','l1bit/prescval']

              hltrunconfig = api.get_hltrunconfig(dbengine,hltconfigid=pargs.hltconfigid,hltkey=pargs.hltkey,runnum=pargs.runmin,schemaname=dbschema)  #[['runnum','hltconfigid','hltkey'],['runnum','hltconfigid','hltkey']]
              runlist = [x[0] for x in hltrunconfig]
              hltconfigids = [x[1] for x in hltrunconfig]
              presc = api.get_prescidx_change(dbengine,runlist,schemaname=dbschema)
              #{runnum:[[lslastscaler,prescidx]]
                           
              if not pargs.totable:
                  fh = pargs.ofilehandle
                  print >> fh, '# '+','.join(header)
                  csvwriter = csv.writer(fh)
              else:
                  ptable = display.create_table(header,header=True,maxwidth=60,align='l')
                  
              if pargs.hltpath:                  
                  hltl1map = api.get_hlttrgl1seedmap(dbengine,hltpath=pargs.hltpath,hltconfigids=hltconfigids,schemaname=dbschema)
                  # {hltconfigid: [[hltpathid,hltpathname,seedtype,[seedvalues]]]}
                  if not hltl1map:
                      print 'No hltpathl1seed mapping found'
                      sys.exit(0)
                      
                  selected_hltconfigids = hltl1map.keys()
                  if not selected_hltconfigids:
                      print 'No hltconfig found '
                      sys.exit(0)
                  for [runnum,hltconfigid,hltkey] in [r for r in hltrunconfig if r[1] in selected_hltconfigids]:
                      if not hltl1map.has_key(hltconfigid):
                          continue
                      mdata = hltl1map[hltconfigid]
                      for [hltpathid,hltpathname,l1seedlogic,l1c] in mdata:                          
                          if not presc.has_key(runnum):
                              display.add_row( [ '%d'%runnum, '%s'%'None', '%s'%'None', '%d'%1,'%s'%hltpathname, '%s'%l1seedlogic, '%s'%' '.join(l1c)], fh=fh, csvwriter=csvwriter, ptable=ptable )
                          else:
                              hltpathnamemap = dict( [(h[0],[h[1],h[2]]) for h in mdata] )
                              if not hltpathnamemap.has_key(hltpathid):
                                  continue
                              for [lsnum,prescidx] in presc[runnum]:
                                  hltprescval = api.get_hltprescale(dbengine,runnum,lsnum,hltconfigid,prescidx,hltpathid,schemaname=dbschema)
                                  rl = api.get_l1prescale(dbengine,runnum,lsnum,l1candidates=l1c,prescidxs=prescidx,ignorel1mask=parseresult['--ignore-mask'] ,schemaname=dbschema)
                                  #{(prescidx,l1bitname):[l1prescval,bitmask]}
                                  if not rl: continue
                                  (hltpathname,l1seedlogic) = hltpathnamemap[hltpathid]                                  
                                  l1keys = [ k for k in rl.keys() if k[0]==prescidx ]
                                  l1bitnames = [ v[1] for v in l1keys ]
                                  l1vals = [ rl[k] for k in l1keys ]                       
                                  l1prescvals = [ v[0] for v in l1vals ]
                                  l1bits = zip(l1bitnames,l1prescvals)
                                  l1inner = map(fm.bitprescFormatter,l1bits)
                                  l1bitsStr = ' '.join(l1inner)                          
                                  hltpathStr = '/'.join([hltpathname,str(hltprescval)])
                                  totpresc = totalprescaleNEW(hltprescval,l1seedlogic,l1prescvals)
                                  display.add_row( [ '%d'%runnum, '%d'%lsnum, '%d'%prescidx, '%d'%totpresc,'%s'%hltpathStr, '%s'%l1seedlogic, '%s'%l1bitsStr], fh=fh, csvwriter=csvwriter, ptable=ptable )  
                  del hltl1map
              else:
                  if not presc:
                      print 'Not prescaled'
                      sys.exit(0)
                  for runnum in sorted(presc.keys()):
                      for plsdata in presc[runnum]:
                          lsnum = plsdata[0]
                          prescidx = plsdata[1]
                          display.add_row( [ '%d'%runnum, '%d'%lsnum, '%d'%prescidx ], fh=fh, csvwriter=csvwriter, ptable=ptable ) 
              if ptable:
                  display.show_table(ptable,pargs.outputstyle)         
                  del ptable          
          else:
              hltrunconfig = api.get_hltrunconfig(dbengine,hltconfigid=pargs.hltconfigid,hltkey=pargs.hltkey,runnum=pargs.runmin,schemaname=dbschema)
              if not hltrunconfig:
                  print 'hltconfig not found'
                  sys.exit(0)
              header = ['hltconfigid','hltkey','run']    
              if not pargs.totable:
                  fh = pargs.ofilehandle
                  print >> fh, '# '+','.join(header)
                  csvwriter = csv.writer(fh)
              else:
                  ptable = display.create_table(header,header=True,maxwidth=80,align='l')

              hltrunconfig_df = pd.DataFrame(hltrunconfig,columns=['runnum','hltconfigid','hltkey'])
              grouped = hltrunconfig_df.groupby(['hltconfigid','hltkey'])              
              for name,group in grouped:
                  hltconfigid = int(name[0])
                  hltkey = str(name[1])
                  runsStr = ','.join([str(i) for i in group['runnum'].values])
                  display.add_row( [ '%d'%hltconfigid, '%s'%hltkey , '%s'%runsStr], fh=fh, csvwriter=csvwriter, ptable=ptable )                
              if ptable:
                  display.show_table(ptable,pargs.outputstyle)         
                  del ptable                  
              del hltrunconfig_df
          if fh and fh is not sys.stdout: fh.close()
          sys.exit(0)
          
    except docopt.DocoptExit:
      raise docopt.DocoptExit('Error: incorrect input format for '+args['<command>'])            
    except schema.SchemaError as e:
      exit(e)    
    return

if __name__ == '__main__':
    brilcalc_main()
    exit(0)
