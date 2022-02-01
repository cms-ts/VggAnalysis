import numpy as np
import pandas as pd
from sqlalchemy import exc,schema,types,Table,MetaData,Column
from datetime import datetime
import decimal
import os
import random
import time
#import yaml
import re
import contextlib
import sys
import ast
import logging
import string
import collections
import itertools
from brilws import params
#from ConfigParser import SafeConfigParser

decimalcontext = decimal.getcontext().copy()
decimalcontext.prec = 3

_lhcfill_fields=['amodetagid','targetegev','numbxbeamactive','norb','nbperls']

log = logging.getLogger('brilws')

oracletypemap={
'uint8':'number(3)',
'uint16':'number(5)',
'uint32':'number(10)',
'uint64':'number(20)',
'int8':'number(3)',
'int16':'number(5)',
'int32':'number(10)',
'int64':'number(20)',
'float':'binary_float',
'double':'binary_double',
'string':'varchar2(4000)',
'blob':'blob',
'bool':'number(1)',
'timestamp':'timestamp'
}

sqlitetypemap={
'uint8':'INTEGER',
'uint16':'INTEGER',
'uint32':'INTEGER',
'uint64':'INTEGER',
'int8':'INTEGER',
'int16':'INTEGER',
'int32':'INTEGER',
'int64':'INTEGER',
'float':'REAL',
'double':'REAL',
'string':'TEXT',
'blob':'BLOB',
'bool':'INTEGER',
'timestamp':'DATETIME'
}

#def unpackBlobtoArray(iblob,itemtypecode):
#    '''
#    Inputs:
#    iblob: 
#    itemtypecode: python array type code 
#    '''
#    if itemtypecode not in ['c','b','B','u','h','H','i','I','l','L','f','d']:
#        raise RuntimeError('unsupported typecode '+itemtypecode)
#    result=array.array(itemtypecode)
#    blobstr=iblob.readline()
#    if not blobstr :
#        return None
#    result.fromstring(blobstr)
#    return result

    
####################
##    Selection API
####################

_maxls = 9999
_maxrun = 999999

class brilwsException(Exception):
    pass
        
#class NotSupersetError(brilwsException):
#    def __init__(self, message, runnum,superset,subset):
#        super(brilwsException, self).__init__(message)
#        self.runnum = runnum
#        self.superset = superset
#        self.subset = subset
    
def expandrange(element):
    '''
    expand [x,y] to range[x,y+1]
    output: np array
    '''
    return np.arange(element[0],element[1]+1)

def consecutive(npdata, stepsize=1):
    '''
    split input array into chunks of consecutive numbers
    np.diff(a,n=1,axis=-1)
    Calculate the n-th order discrete difference along given axis.
    output: list of ndarrays
    '''
    return np.split(npdata, np.where(np.diff(npdata) != stepsize )[0]+1)

def checksuperset(iovseries,cmsseries):
    '''
    input:
        iovseries: pd.Series 
        cmsseries: pd.Series from dict {run:[[]],}
    output:
      throw NotSupersetError exception if not superset
    '''
    iovdict = {}
    for data in iovseries:
        runnum = data.index.tolist()[0]
        v = pd.Series(data[runnum]).apply(expandrange)
        v = v.apply(np.unique)
        vi = np.hstack(v.values)
        if not iovdict.has_key(runnum):            
            iovdict[runnum] = []            
        iovdict[runnum] = iovdict[runnum]+vi.tolist()

    #check all requested runs must be covered in normtag
    diffruns = []
    for runnum in cmsseries.index.tolist():
        if not runnum in iovdict.keys():
            diffruns.append(runnum)
    #raise UnNormedRunError('UnNormedRunError',diffruns)
    
    diffls = {}
    #check for each run, normtag ls must be the superset
    for runnum in sorted(iovdict.keys()):
        lsrange = iovdict[runnum]
        if runnum in cmsseries.index:
            cmslsvals = pd.Series(cmsseries[runnum]).apply(expandrange)
            cmslsvals_flat = np.unique(np.hstack(cmslsvals.values))
            if not set(lsrange).issuperset(cmslsvals_flat):
                supersetlist = [[min(x),max(x)] for x in consecutive(np.array(lsrange))]
                subsetlist = cmsseries[runnum]
                if not diffls.has_key(runnum):
                    diffls[runnum] = []
                diffls[runnum] = (supersetlist,subsetlist) 
                #raise NotSupersetError('NotSupersetError',runnum,supersetlist,subsetlist)
    return (diffruns,diffls)
            
def mergerangeseries(x,y):
    '''
    merge two range type series
    x [[x1min,x1max],[x2min,x2max],...]
    y [[y1min,y1max],[y2min,y2max],...]
    into
    z [[z1min,z1max],[z2min,z2max],...]
    '''
    a = pd.Series(x).apply(expandrange)
    ai = np.hstack(a.values)
    b = pd.Series(y).apply(expandrange)
    bi = np.hstack(b.values)    
    i = np.intersect1d(np.unique(ai),np.unique(bi),assume_unique=True)
    scatter = consecutive(i)
    return scatter

def merge_two_dicts(x,y):
    z = x.copy()
    z.update(y)
    return z

def merge_twodicts_onkeys(x,y):
    ds = [x,y]
    z = {}
    for k in x.keys():
        samekeylists = [d[k] for d in ds if d.has_key(k)]
        if samekeylists:
            z[k] = list(itertools.chain.from_iterable(samekeylists))
    return z

def merge_two_dicts_onkeys(x,y):
    if not any(i in x.keys() for i in y.keys()):#no overlap 
        return merge_two_dicts(x,y)
    z = {}
    samekeys = [i for i in x.keys() if i in y.keys()]
    for k in samekeys:
        z[k] = list(itertools.chain.from_iterable([x[k],y[k]]))
        x.pop(k,None)
        y.pop(k,None)
    z = merge_two_dicts(z,x)
    z = merge_two_dicts(z,y)
    return z

def mergeiovrunlsWithDB(dbengine,iovselect,runmin=None,runmax=None,fillmin=None,fillmax=None,tssecmin=None,tssecmax=None,schemaname=''):
    '''
    merge iovselect list and run range selected from DB
    input:
        cmsselect: pd.Series from dict {run:[[]],}
        other paramters are input to DB queries
        select min(runnum),max(runnum) from IDS_DATATAG where ....)
    output:
         [ [x[0],pd.Series(x[1])] for x in final ] 
    '''
    idtablename = 'ids_datatag'
    if schemaname:
         idtablename = '.'.join([schemaname,idtablename])
    q = 'select min(runnum),max(runnum) from %s where '%idtablename
    condition = []
    condition_data = {}
    if runmin==runmax and runmin is not None:
        condition.append('runnum=:runnum')
        condition_data['runnum'] = runmin
    else:
        if runmin:
            condition.append('runnum>=:runmin')
            condition_data['runmin'] = runmin
        if runmax:
             condition.append('runnum<=:runmax' )
             condition_data['runmax'] = runmax
    if fillmin==fillmax and fillmin is not None:
        condition.append('fillnum=:fillnum')
        condition_data['fillnum'] = fillmin
    else:
        if fillmin:
            condition.append('fillnum>=:fillmin')
            condition_data['fillmin'] = fillmin
        if fillmax:
             condition.append('fillnum<=:fillmax' )
             condition_data['fillmax'] = fillmax
    if tssecmin:
        condition.append('timestampsec>=:tssecmin')
        condition_data['tssecmin'] = tssecmin
    if tssecmax:
        condition.append('timestampsec<=:tssecmax')
        condition_data['tssecmax'] = tssecmax
    conditionStr = ' AND '.join(condition)
    q = q+conditionStr
    log.debug('mergeiovrunlsWithDB: '+q+' , '+str(condition_data))
    connection = dbengine.connect()
    r = connection.execution_options(stream_result=True).execute(q,condition_data)
    output = r.fetchall()
    r.close()    

    result = []    
    minrun = output[0][0]
    maxrun = output[0][1]
    if minrun is None or maxrun is None:
        return result

    for [iovtag,iovtagrunls] in iovselect:        
        slim = iovtagrunls[ iovtagrunls.index.isin( range(minrun,maxrun+1) ) ]
        if not slim.empty:
            result.append( [iovtag,slim] )
    return result

def mergeiovrunls(iovselect,cmsselect):
    '''
    merge iovselect list and cms runls select dict
    input:
        cmsselect: pd.Series from dict {run:[[]],}
        iovselect:  [[iovtag,pd.Series],...]  pd.Series from dict {run:[[]],}
        
    '''
    cmsselect_runs = cmsselect.index
    final = []#[[iovtag,{}],[iovtag,{}]]
    previoustag = ''
    coutiovpiece = 0
    #iovselectnew = map(iovselect,mergesametags)
    
    for [iovtag,iovtagrunls] in iovselect:
        iovtagruns = iovtagrunls.index
        runlsdict = {}
        selectedruns = np.intersect1d(cmsselect_runs,iovtagruns)
        if selectedruns.size == 0: continue
        for runnum in selectedruns:
            scatter = mergerangeseries(iovtagrunls[runnum],cmsselect[runnum])
            for c in scatter:
                if len(c)==0: continue
                runlsdict.setdefault(runnum,[]).append([np.min(c),np.max(c)])                
        if iovtag!=previoustag:
            if runlsdict:
                final.append([iovtag,runlsdict])
                previoustag = iovtag
        else:            
            x = final[-1][1]                
            y = runlsdict            
            final[-1][1] = merge_two_dicts_onkeys(x,y)
        coutiovpiece+=1    
    #return final
    return [ [x[0],pd.Series(x[1])] for x in final ] # turn the second element to Series

def parseselectionJSON(filepath_or_buffer):
    d = get_filepath_or_buffer(filepath_or_buffer)
    data = ''
    if os.path.isfile(d):
        with open(d,'r') as f:
            data = f.read().lstrip()        
    else:
        data = filepath_or_buffer.lstrip()
    if data[0]=='[':
        return parseiovtagselectionJSON(data)
    else:
        return parsecmsselectJSON(data)
        
def parseiovtagselectionJSON(filepath_or_buffer):
    """
    parse iov tag selection file
    input:
        if file, parse file
    output:
        normtag string
          or 
        list [iovtag,"{run:[[1,9999]],run:[[1,9999]]}" , [iovtag,"{run:[[lsstart,lsstop]],...}" ]                     
    """
    result = None
    d = get_filepath_or_buffer(filepath_or_buffer)    
    if os.path.isfile(filepath_or_buffer):
        result = pd.read_json(d,orient='index',convert_axes=False,typ='Series')
    elif filepath_or_buffer.find('[') == -1:
        return filepath_or_buffer
    else:
        spacer = re.compile(r'^\s+')
        d = spacer.sub('',d) #remove whitespace
        word = re.compile(r'(\w*[A-Za-z]\w*),')
        d = word.sub(r'"\1",',d) #add quotes to iovtag field
        result = pd.Series( ast.literal_eval(d) ) #Series returns unicode
    final = []
    for r in result:
        if r[0] and isinstance(r[0],unicode):
            iovtag = str(r[0])
        else:
            iovtag = r[0]
        payload = r[1:]
        for piece in payload :
            if isinstance(piece,dict):
                s = pd.Series(piece)
                s.index = [int(k) for k in piece.keys()]
                final.append([iovtag,s])
            else:
                #p = '{"%s":[[1,%s]]}'%(piece,_maxls)
                p = {}
                p[piece] = [[1,_maxls]]
                final.append([iovtag,pd.Series(p)])
    return final

def parsecmsselectJSON(filepath_or_buffer,numpy=False):
    """
    parse cms selection json format
    input: 
        if file, parse file
        if string in dict format, eval as dict. Key is not required to be double quoted in this case
        if single string, convert to [int]
    output:
        pd.Series , index=runnum, value=[[lsmin,lsmax]]
    """
    d = get_filepath_or_buffer(filepath_or_buffer)

    try:
        result = pd.Series([int(d)])
        return result
    except ValueError:
        pass

    if os.path.isfile(d):
        result = pd.read_json(d,orient='index',convert_axes=False,typ='Series',numpy=numpy)
    else:
        d = ast.literal_eval(d)
        result = pd.Series(d)
    result.index = [int(i) for i in result.index]
    return result

@contextlib.contextmanager
def smart_open(filename=None):
    if filename and filename != '-':
        fh = open(filename, 'w')
    else:
        fh = sys.stdout
    try:
        yield fh
    finally:
        if fh is not sys.stdout:
            fh.close()
            
def seqdiff(original,exclude):
    return list(set(original)-set(exclude))

def create_table_stmt(tablename,dbflavor='sqlite'):
    """
    create table statement
    input:
       tablename
       ifnotexists: if true, add IF NOT EXISTS
    """
    if dbflavor=='sqlite':
        result='CREATE TABLE IF NOT EXISTS %s '%(tablename)
    else:
        result='CREATE TABLE %s'%(tablename)
    return result

def drop_table_stmt(tablename, dbflavor='sqlite'):
    if dbflavor=='oracle':
        result='DROP TABLE %s CASCADE CONSTRAINTS;'%(tablename)
    else:
        result='DROP TABLE IF EXISTS %s;'%(tablename)
    return result

def grant_stmt(tablename,writeraccount=None):
    result='GRANT SELECT ON "%s" TO PUBLIC;\n'%(tablename)
    if writeraccount is not None:
        result=result+'GRANT SELECT,INSERT,DELETE,UPDATE ON "%s" TO %s;'%(tablename,writeraccount)
    return result    

def create_index_stmt(tablename,indexdict):
    results=[]
    for idxname,cols in indexdict.items():
        idxcolsStr=','.join(cols)
        results.append('CREATE INDEX %s ON %s(%s) '%(idxname,tablename,idxcolsStr))
    return ';\n'.join(results)
    
def build_column_stmt(columns,typemap,notnull=[]):
    results=[]
    for cdict in columns:
        result=''
        cname,ctype = next(cdict.iteritems())
        ctype=typemap[ctype]
        result=result+'%s %s '%(cname,ctype)
        if notnull and cname in notnull:
          result=result+'NOT NULL '
        results.append(result)
    result=','.join(results)
    return result

def build_unique_stmt(tablename,uniquelist):
    results=[]
    for uniques in uniquelist:
       if type(uniques) is list:
           uniquesStr=','.join(uniques)
       else:
           uniquesStr=uniques 
       results.append('CONSTRAINT %s_UQ UNIQUE (%s)'%(tablename,uniquesStr))
    if results: return ',\n'.join(results)
    return ''

def build_pk_stmt(tablename,pklist):
    pkcolsStr=','.join(pklist)
    pkcolsStr=pkcolsStr
    result='CONSTRAINT %s_PK PRIMARY KEY(%s)'%(tablename,pkcolsStr) 
    if pkcolsStr: 
        return result
    return ''

def build_fk_stmt(tablename,fkdict):
    results=[]
    for fkname,fkcoldict in fkdict.items():
        newdict=dict(chain.from_iterable(map(methodcaller('items'),fkcoldict)))
        columndata=newdict['column']
        colsStr=','.join(columndata)
        parenttablename=newdict['parenttable']
        referencecolumns=newdict['referencecolumn']
        parentcolsStr=','.join(referencecolumns) 
        results.append('ALTER TABLE %s ADD CONSTRAINT %s FOREIGN KEY (%s) REFERENCES %s (%s) ON DELETE CASCADE'%(tablename,fkname,colsStr,parenttablename,parentcolsStr))
    if results: return ';\n'.join(results)
    return ''

def build_sqlfilename(outfilenamebase,operationtype='create',suffix=None,dbflavor='sqlite'):
    result=''
    if suffix:
       result='%s_%s%s_%s.sql'%(outfilenamebase,dbflavor,operationtype,suffix)
    else:
       result='%s_%s%s.sql'%(outfilenamebase,dbflavor,operationtype)
    return result

def drop_tables_sql(outfilebase,schema_def,suffix=None,dbflavor='sqlite'):
    results=[]
    tables=schema_def.keys()
    outfilename=build_sqlfilename(outfilebase,operationtype='drop',suffix=suffix,dbflavor=dbflavor)
    for tname in tables:
        results.append(drop_table_stmt(tname,dbflavor=dbflavor))
    resultStr='\n'.join(results)
    if suffix:
       resultStr=resultStr.replace('&suffix',suffix)
    resultStr=resultStr.upper()

    with open(outfilename,'w') as sqlfile:
        sqlfile.write('/* tablelist: %s */\n'%(','.join([t.upper() for t in tables])))
        sqlfile.write(resultStr)
    
def create_tables_sql(outfilebase,schema_def,suffix=None,dbflavor='sqlite',writeraccount=''):
    '''
    input :
        outfilebase: output file name base
        schema_def: dictionary of dictionaries
    '''
    results=[]
    resultStr=''
    fkresults=[]
    ixresults=[]
    tables=schema_def.keys()
    outfilename=build_sqlfilename(outfilebase,operationtype='create',suffix=suffix,dbflavor=dbflavor)
    columntypemap={}  
    if dbflavor=='oracle':
        columntypemap = oracletypemap
    else:
        columntypemap = sqlitetypemap
    for tname in tables:       
        #if tname.find('NEXTID')!=-1:
        #    stmt=create_sequencetable_stmt(tname,dbflavor)
        #    results.append(create_sequencetable_stmt(tname,dbflavor))       
        #    continue      
        result=create_table_stmt(tname,dbflavor=dbflavor)
        cs=schema_def[tname]['columns']
        nnus=[]
        if schema_def[tname].has_key('notnull'):
           nnus=schema_def[tname]['notnull']
        if schema_def[tname].has_key('index'):
           idxes=schema_def[tname]['index']
           dictidxes={}
           if idxes: 
               dictidxes=dict( (k,v) for d in idxes for (k,v) in d.items() )
               ixresults.append(create_index_stmt(tname,dictidxes))        
        result=result+'('+build_column_stmt(cs,columntypemap,nnus)
        pks=schema_def[tname]['pk']
        fks={}
        for k in schema_def[tname].keys():
           if k.find('fk_')!=-1:
                fks[k]=schema_def[tname][k]
        result=result+','+build_pk_stmt(tname,pks)
        unqs=None
        if schema_def[tname].has_key('unique'):
           unqs=schema_def[tname]['unique']
           result=result+','+build_unique_stmt(tname,unqs)
        
        result=result+')'
        if dbflavor=='oracle' and tname.upper()=='IDS_DATATAG':
            result = result+' partition by range(RUNNUM) (partition r1a values less than (184000), partition r1b values less than (212000), partition r2a values less than (MAXVALUE))'
        result = result+';\n'
        if fks: fkresults.append(fk(tname,fks))
        if dbflavor=='oracle':
            result=result+grant_stmt(tname,writeraccount=writeraccount)
        results.append(result)
    resultStr='\n'.join(results)
    if resultStr.find('&suffix')!=-1:
        if suffix:
            resultStr=resultStr.replace('&suffix',suffix)
        else:
            raise Exception('--suffix is required but not specified')
    resultStr=resultStr.upper()  
    with open(outfilename,'w') as sqlfile: 
        sqlfile.write('/* tablelist: %s */\n'%(','.join([t.upper() for t in tables])))
        sqlfile.write(resultStr)
        if fkresults:
            fkresultStr=';\n'.join([t.replace('&suffix',suffix).upper() for t in fkresults])
            sqlfile.write('\n'+fkresultStr+';')
        if ixresults:
            ixresultStr=';\n'.join([t.replace('&suffix',suffix).upper() for t in ixresults])
            sqlfile.write('\n'+ixresultStr+';')

##### iovschema api
#payloadtableprefix_ ='IOVP'
#iovdict_typecodes_ = ['FLOAT32','UINT32','INT32','UINT64','INT64','UINT16','INT16','UINT8','INT8','STRING']

def nonsequential_key(generator_id):
    '''
    http://ericmittelhammer.com/generating-nonsequential-primary-keys/
    generator_id [1,256]
    '''
    now = int(time.time()*1000) #41 bits
    rmin = 1  
    rmax = 2**15 - 1
    rdm = random.randint(1, rmax)
    yield ((now << 22) + (generator_id << 14) + rdm )

def generate_key(n):
    '''
    generate id based on a unique number
    '''
    now = int(time.time()*1000) #41 bits
    yield ((now <<22) + n )
     
#String Folding
#The rows of result data returned by SQLAlchemy contain many repeated strings
#each one is a different Unicode object
#When these are passed to Pandas, it stores a copy of the data for each string
#on the C heap, which taking up memory.
#We want a single shared string object for any one value
#It's called folding.
#http://www.mobify.com/blog/sqlalchemy-memory-magic/
#
class StringFolder(object):
    """
    Class that will fold strings.
    This object may be safely deleted or go out of scope when strings have been folded.
    """
    def __init__(self):
        self.unicode_map = {}
    def fold_string(self,s):
        """
        Given a string (or unicode) parameter s, return a string object
        that has the same value as s (and may be s). For all objects
        with a given value, the same object will be returned. For unicode
        objects that can be coerced to a string with the same value, a
        string object will be returned.
        If s is not a string or unicode object, it is returned unchanged.
        :param s: a string or unicode object.
        :return: a string or unicode object.
        """
        # If s is not a string or unicode object, return it unchanged
        if not isinstance(s, basestring):
            return s
        
        # If s is already a string, then str() has no effect.
        # If s is Unicode, try and encode as a string and use intern.
        # If s is Unicode and can't be encoded as a string, this try
        # will raise a UnicodeEncodeError.
        try:
            return intern(str(s))
        except UnicodeEncodeError:
            # Fall through and handle s as Unicode
            pass

        # Look up the unicode value in the map and return
        # the object from the map. If there is no matching entry,
        # store this unicode object in the map and return it.
        #t = self.unicode_map.get(s, None)
        #if t is None:
        #    # Put s in the map
        #    t = self.unicode_map[s] = s
        #return t
        return self.unicode_map.setdefault(s,s)
    
def string_folding_wrapper(results):
    """
    This generator yields rows from the results as tuples,
    with all string values folded.
    """
    # Get the list of keys so that we build tuples with all
    # the values in key order.
    keys = results.keys()
    folder = StringFolder()
    for row in results:
        yield tuple( folder.fold_string(row[key]) for key in keys )    

def iov_getpayload(connection,payloadid,payloaddatadict,maxnitems=1):
    """
    input:
        connection:      db handle
        payloadid:       payloadid
        payloaddatadict: payload datadict [{'val':,'key':,'alias':,'maxnpos':}]
    output:
        payload:          [[[]]] or [[{}]] 
        fieldalias:       [alias] 
    sql:
        val : select IITEM,IPOS,VAL from %s where PAYLOADID=:payloadid and IFIELD=:ifield and ISKEY=0;
        key : select k.IITEM, k.IPOS, k.VAL, v.VAL from %s as k, %s as v where k.PAYLOADID=v.PAYLOADID and k.IITEM=v.IITEM and k.IFIELD=v.IFIELD and k.IPOS=v.IPOS and k.PAYLOADID=:payloadid and k.IFIELD=:ifield and k.ISKEY=1 and v.ISKEY=0;
    """

    nfields = len(payloaddatadict)
    payload = [None]*maxnitems            
    q = """select IITEM as iitem, IPOS as ipos, VAL as val from %s where ISKEY=0 and PAYLOADID=:payloadid and IFIELD=:ifield"""
    qq = """select k.IITEM as iitem, k.IPOS as ipos, k.VAL as key, v.VAL as val from %s as k, %s as v where k.ISKEY=1 and v.ISKEY=0 and k.PAYLOADID=v.PAYLOADID and k.IITEM=v.IITEM and k.IFIELD=v.IFIELD and k.IPOS=v.IPOS and k.PAYLOADID=:payloadid and k.IFIELD=:ifield"""
    
    with connection.begin() as trans:
        for field_idx, field_dict in enumerate(payloaddatadict):
            valtable_name = field_dict['val']            
            maxnpos = field_dict['maxnpos']
            if not valtable_name:
                raise ValueError('invalid value table name %s'%valtable_name)
            result = None
            keytable_name = field_dict['key']
            if keytable_name:
                result = connection.execute(qq%(keytable_name,valtable_name),{'payloadid':payloadid,'ifield':field_idx})
            else:
                result = connection.execute(q%(valtable_name),{'payloadid':payloadid,'ifield':field_idx})
            for r in result:
                iitem = r['iitem']
                ipos = r['ipos']                
                val = r['val']
                key = None
                if payload[iitem] is None:
                    payload[iitem] = [None]*nfields
                if payload[iitem][field_idx] is None:
                    payload[iitem][field_idx] = [None]*maxnpos
                if not r.has_key('key'):
                    payload[iitem][field_idx][ipos] = val
                else:
                    key = r['key']
                    payload[iitem][field_idx][ipos] = (key,val)
    payload = [x for x in payload if x is not None]
    
    return payload

def data_gettags(engine,schemaname=''):
    """
    inputs:
        connection: db handle
    outputs:
        result[ datatagname ] = [ datatagnameid,creationutc',comments ]
    sql: select datatagnameid, datatagname, creationutc, comments from DATATAGS
         
    """
    basetablename = tablename = 'DATATAGS'
    if schemaname:
        tablename = '.'.join([schemaname,basetablename])
        
    result = {}
    q =  """select datatagnameid, datatagname, creationutc, comments from %s"""%(tablename)
    log.debug(q)
    connection = engine.connect()
    qresult = connection.execute(q,{})
    for row in qresult:
        creationutc=''
        comments=''
        if row['creationutc']: creationutc=row['creationutc']
        if row['comments']: comments=row['comments']
        result[ row['datatagnameid'] ] = [ row['datatagname'],creationutc,comments ]
    return result

def iov_gettag(engine,tagname,schemaname=''):
    '''
    inputs:
        connection:  db handle
    outputs:
        [tagid,creationutc,datasource,applyto,isdefault,comments]
    '''
    basetablename = tablename = 'iovtags'
    if schemaname:
        tablename = '.'.join([schemaname,basetablename])
    q =  """select tagid, creationutc, datasource, applyto, isdefault, comments from %s where tagname=:tagname"""%(tablename)    
    log.debug(q)
    connection = engine.connect()
    binddict = {'tagname':tagname}
    qresult = connection.execute(q,binddict)
    result = []
    for row in qresult:
        result = [ row['tagid'],row['creationutc'],row['datasource'],row['applyto'],row['isdefault'],row['comments'] ]
    return result

def iov_gettags(engine,datasource=None,applyto=None,isdefault=False,schemaname=''):
    """
    inputs:
        connection:  db handle
        optional query parameters: tagid, tagname,datasource,applyto,isdefault
    outputs:
       {tagname:[tagid,creationutc,datasource,applyto,isdefault,comments]}    
    sql: select tagid, tagname, creationutc, datasource, applyto, isdefault, comments from IOVTAGS where
         
    """
    basetablename = tablename = 'iovtags'
    if schemaname:
        tablename = '.'.join([schemaname,basetablename])
        
    result = {}
    q =  """select tagid, tagname, creationutc, datasource, applyto, isdefault, comments from %s"""%(tablename)
    qCondition = ''
    qPieces = []
    binddict = {}

    if datasource:
        qPieces.append( "datasource=:datasource")
        binddict['datasource'] = datasource
    if applyto:
        qPieces.append( "applyto=:applyto" )
        binddict['applyto'] = applyto
    if isdefault:
        qPieces.append("isdefault=1")
    if qPieces:
        qCondition = ' and '.join(qPieces)
    if qCondition: q = q+' where '+qCondition
    log.debug(q)
    connection = engine.connect()
    qresult = connection.execute(q,binddict)
    for row in qresult:
        result[row['tagname']] = [ row['tagid'],row['creationutc'],row['datasource'],row['applyto'],row['isdefault'],row['comments'] ]
    return result

def _insert_iovtag(connection,tablename,iovtagid,iovtagname,creationutc,datasource,applyto,isdefault,comments,schemaname=None):
    t = Table(tablename, MetaData(), Column('tagid',types.BigInteger), Column('tagname',types.String),Column('creationutc',types.String), Column('applyto',types.String), Column('datasource',types.String), Column('isdefault',types.BOOLEAN), Column('comments',types.String) , schema=schemaname)
    log.debug( str( t.insert() ) )
    log.debug( 'tagid=%ul, tagname=%s, creationutc=%s, applyto=%s, datasource=%s, isdefault=%d, comments=%s'%(iovtagid,iovtagname,creationutc,applyto,datasource,int(isdefault),comments) )
    connection.execute( t.insert(), tagid=iovtagid, tagname=iovtagname, creationutc=creationutc, applyto=applyto, datasource=datasource, isdefault=isdefault, comments=comments)    
    
def _insert_iovdata(connection,tablename,iovtagid,since,payloadstr,func,comments,schemaname=None):
    t = Table(tablename, MetaData(), Column('tagid',types.BigInteger), Column('since',types.Integer),Column('payload',types.String), Column('func',types.String), Column('comments',types.String),schema=schemaname )
    try:
        log.debug( str( t.insert() ) )
        log.debug( 'tagid=%ul, since=%d, payload=%s, func=%s, comments=%s'%(iovtagid,since,payloadstr,func,comments) )
        connection.execute( t.insert(), tagid=int(iovtagid), since=since, payload=payloadstr, func=func, comments=comments)
    except exc.IntegrityError, e:
        if str(e).find('unique constraint')!=-1:
            log.debug( 'Duplicated key iovtagid %ul, since %d, skip insertion, return 0'%(iovtagid,since) )
            return 0
    return iovtagid

def _is_strpattern(istr):
    if not istr: return False
    p = re.compile(r'\?|\*|\[|\]|!')
    return p.findall(istr) # is pattern
    
def iov_insertdata(engine,iovtagname,datasource,iovdata,applyto='lumi',isdefault=False,comments='',schemaname=None ):
    '''
    create a new iov tag or append to an existing one
    iovdata:[{since:{'func':,'payload':,'commments':}},]
    '''
    basetablename = 'iovtags'
    if schemaname:
       tablename = '.'.join([schemaname,basetablename])
    datatablename = 'iovtagdata'
        
    iovtagid = 0
    selectq = '''select tagid from %s where tagname=:iovtagname'''%tablename
    log.debug(selectq)
    connection = engine.connect()
    with connection.begin() as trans: 
        selectqresult = connection.execute(selectq,{'iovtagname':iovtagname})
        for row in selectqresult:
            iovtagid = row['tagid']
            log.debug( 'tag %s exists with id %ul '%(iovtagname,iovtagid) )            
        if not iovtagid:
            log.debug( 'create new tag %s'%(iovtagname) )
            iovtagid = next(nonsequential_key(78))
            utcstr = datetime.now().strftime(params._datetimefm)
            _insert_iovtag(connection,basetablename,iovtagid,iovtagname,utcstr,datasource.upper(),applyto.upper(),isdefault,comments,schemaname=schemaname)

        for sincedict in iovdata:
            sincerunnum = sincedict.keys()[0]
            payloaddata = sincedict.values()[0]
            func = str(sincedict[sincerunnum]['func'])
            sincecomments =  sincedict[sincerunnum]['comments']
            payloadstr = str(sincedict[sincerunnum]['payload'])
            log.debug( 'append to tag %s since %d'%(iovtagname,sincerunnum) )
            inserted = _insert_iovdata(connection,datatablename,iovtagid,sincerunnum,payloadstr,func,sincecomments,schemaname=schemaname)
            print 'inserted ',inserted

def packlistoblob(typecode,data):
    dataarray = array.array(typecode,list(data))
    return buffer(dataarray.tostring())        

def locate_shards(engine,runmin=None,runmax=None,fillmin=None,fillmax=None,tssecmin=None,tssecmax=None,orrunlist=[],schemaname=''):
    '''
    the first 6 input parameters are for _and_ selection
    orrunlist is for _or_ selection
    '''
    shards = []
    s1 = get_shards_run_or(engine,orrunlist,schemaname=schemaname)
    s2 = get_shard_and(engine,runnum=runmin,fillnum=fillmin,tssec=tssecmin,schemaname=schemaname)
    s3 = None
    if (runmax and runmax!=runmin) or (fillmax and fillmax!=fillmin) or (tssecmax and tssecmax!=tssecmin):
        s3 = get_shard_and(engine,runnum=runmax,fillnum=fillmax,tssec=tssecmax,schemaname=schemaname)
    if s1:
        shards = s1
    if s2 and s3:
        shards += range(s2,s3+1)
    elif s2:
        shards.append(s2)
    elif s3:
        shards.append(s3)
    shards = list(np.unique(np.array(shards)))
    return shards

def get_shards_run_or(engine,runlist,schemaname=''):
    '''
    select id from tableshards where (minrun>=:runnum_x and maxrun<=:runnum_x) or (minrun>=:runnum_y and maxrun<=:runnum_y)
    '''
    if not runlist:
        return []
    result = []
    basetablename = tablename = 'tableshards'
    if schemaname:
        tablename = '.'.join([schemaname,basetablename])
    q = "select id from %s where "%(tablename)
    qCondition = ''
    qPieces = []
    binddict = {}
    for i,runnum in enumerate(runlist):
        qPieces.append("(minrun<=:runnum_%d and maxrun>=:runnum_%d)"%(i,i))
        binddict["runnum_%d"%i] = runnum
    qCondition = ' or '.join(qPieces)
    q = q+qCondition
    log.debug('get_shards_run_or: '+q)
    log.debug(str(binddict))
    connection = engine.connect()
    r = connection.execute(q,binddict)
    for row in r:
        result.append(row['id'])
    return result

def get_shard_and(engine,runnum=None,fillnum=None,tssec=None,schemaname=''):
    '''
    result: shardid    
    select id from tableshards where minrun>=:runnum and maxrun<=:runnum and minfill>=:fillnum and maxfill<=:fillnum and mintimestampsec<=:tssec and maxtimestampsec>=tssec ; 
    '''
    if not runnum and not fillnum and not tssec:
        return None
    basetablename = tablename = 'tableshards'
    if schemaname:
        tablename = '.'.join([schemaname,basetablename])
    q = "select id from %s where "%(tablename)
    qCondition = ''
    binddict = {}
    qPieces = []
    if runnum:
        qPieces.append("minrun<=:runnum and maxrun>=:runnum")
        binddict['runnum'] = runnum
    if fillnum:
        qPieces.append("minfill<=:fillnum and maxfill>=:fillnum")
        binddict['fillnum'] = fillnum
    if tssec:
        qPieces.append("mintimestampsec<=:tssec and maxtimestampsec>=:tssec")
        binddict['tssec'] = tssec
    qCondition = ' and '.join(qPieces)
    q = q+qCondition
    log.debug('get_shard_and: '+q)
    log.debug(str(binddict))
    connection = engine.connect()
    row = connection.execute(q,binddict).fetchone()
    if not row:
        return None
    return row['id']
        
def iov_gettags(engine,isdefault=False,datasource='',applyto='',schemaname=''):
    '''
    output: iovtags 
    result: [[tagid,tagname,creationutc,applyto,datasource,isdefault,comments]]
    '''
    basetablename = tablename = 'iovtags'
    if schemaname:
        tablename = '.'.join([schemaname,basetablename])
    q = '''select tagid, tagname, creationutc, applyto, datasource, isdefault, comments from %s'''%(tablename)
    qconditions = []
    qparams = {}    
    if datasource:        
        qconditions.append('datasource=:datasource')
        qparams['datasource'] = datasource.upper()
    if applyto:
        qconditions.append('applyto=:applyto')
        qparams['applyto'] = applyto.upper()
    if isdefault:
        qconditions.append('isdefault=1')
    if qconditions:
        q = q+' where '+' AND '.join(qconditions)
    log.debug(q)
    connection = engine.connect()
    qresult = connection.execute(q,qparams)
    result = {}
    for row in qresult:
        result[row['tagname']] = [ row['tagid'],row['creationutc'],row['applyto'],row['datasource'],row['isdefault'],row['comments'] ] 
    return result

def iov_gettagdata(engine,iovtagname,schemaname=''):
    '''
    result: [[since,func,payload,comments]]
    '''
    basetagstable = tagstable = 'iovtags'
    basetagdatatable = tagdatatable = 'iovtagdata'
    if schemaname:
        tagstable = '.'.join([schemaname,basetagstable])
        tagdatatable = '.'.join([schemaname,basetagdatatable])
        
    q='''select d.since as since, d.payload as payload, d.func as func, d.comments as comments from %s d, %s t where t.tagid=d.tagid and t.tagname=:tagname order by d.since'''%(tagdatatable,tagstable)
    log.debug(q)
    connection = engine.connect()
    qresult = connection.execute(q,{'tagname':iovtagname})
    result = []
    for row in qresult:
        payload = row['payload']        
        result.append( [ row['since'],row['func'],row['payload'],row['comments'] ] )
    return result
    
def iov_updatedefault(connection,tagname,defaultval=1):
    """
    inputs:
        connection: dbhandle
        tagname:    tagname
        defaultval: value(0 or 1) of isdefault column
    sql:
        update IOVTAGS set ISDEFAULT=:defaultval
    """
    if not defaultval in [0,1]:
        raise ValueError('ISDEFAULT value must be 0 or 1')
    log.debug('api.iov_updatedefault %s isdefault %d'%(tagname,defaultval))
    ui = """update IOVTAGS set ISDEFAULT=:isdefault where TAGNAME=:tagname"""
    with connection.begin() as trans:
        log.debug('api.iov_updatedefault query %s %d'%(tagname,defaultval))
        connection.execute(ui, {'isdefault': defaultval,'tagname':tagname})

def get_filepath_or_buffer(filepath_or_buffer):
    """
    Input: 
    filepath_or_buffer: filepath or buffer
    Output:
    a filepath_or_buffer
    """
    if isinstance(filepath_or_buffer, str):
        return os.path.expanduser(filepath_or_buffer)
    return filepath_or_buffer    

import struct,array
#def packArraytoBlob(iarray,typecode):
#    '''
#    Inputs:
#    inputarray: a python array
#    '''
#    t = typecode*len(iarray)
#    buffer = struct.pack(t,*iarray)
#    return result

def unpackBlobtoArray(iblob,itemtypecode):
    '''
    Inputs:
    iblob: blob
    itemtypecode: python array type code 
    '''
    if not isinstance(iblob,buffer) and not isinstance(iblob,str):
        return None
    if itemtypecode not in ['c','b','B','u','h','H','i','I','l','L','f','d']:
        raise RuntimeError('unsupported typecode '+itemtypecode)
    result=array.array(itemtypecode)
    
    #blobstr=iblob.readline()????
    if not iblob :
        return None
    result.fromstring(iblob)
    return result

def packListstrtoCLOB(iListstr,separator=','):
    '''
    pack list of string of comma separated large string CLOB
    '''
    return separator.join(iListstr)

def unpackCLOBtoListstr(iStr,separator=','):
    '''
    unpack a large string to list of string
    '''
    return [i.strip() for i in iStr.strip().split(separator)]

##### Data tag ######    
def data_createtag(engine,datatagname,comments='',schemaname=''):
    '''
    create a new data tag, return the datatag name id
    input:
        insert into schemaname.DATATAGS(datatagname,datatagnameid,creationutc,comments) values(datatagname,datatagnameid,creationutc,comments)
    output:
        datatagnameid  
    '''
    datatagnameid = None
    if datatagname == 'online':
        datatagnameid = 1
    else:
        datatagnameid = next(nonsequential_key(1))
    tablename = 'datatags'    
    utcstr = datetime.utcnow().strftime(params._datetimefm)
    t = Table(tablename, MetaData(), Column('datatagnameid',types.BigInteger), Column('datatagname',types.String),  Column('creationutc',types.String), Column('comments',types.String), schema=schemaname )
    q = str( t.insert() )
    log.debug(q)
    log.debug(utcstr)
    connection = engine.connect()
    connection.execute( t.insert(),datatagnameid=datatagnameid,datatagname=datatagname,creationutc=utcstr,comments=comments)
    return datatagnameid

def getDatatagNameid(engine,datatagname,schemaname=''):
    '''
    select datatagnameid from DATATAGS where datatagname=%datatagname    
    '''
    datatagnameid = 0
    if datatagname=='online': return datatagnameid
    return datatagnameid

def getDatatagName(engine,schemaname='',datatagname=''):
    '''
    output: datatags dataframe
    '''
    basetablename = tablename = 'DATATAGS'
    if schemaname:
        tablename = '.'.join([schemaname,basetablename])
    q = '''select DATATAGNAMEID as id, DATATAGNAME as name, CREATIONUTC as creationutc, COMMENTS as comments from %s'''%(tablename)
    if datatagname:
        q = q+' where datatagname=:datatagname'        
        return pd.read_sql_query(q,engine,index_col='id',params={'datatagname':datatagname})
    return pd.read_sql_query(q,engine,index_col='id',params={})

def insertDataTagEntry(engine,idtablename,datatagnameid,runnum,lsnum,fillnum=0,schemaname=None):
    '''
    insert into IDS_DATATAG_&suffix (datatagnameid,datatagid,fillnum,runnum,lsnum) values(datatagnameid,datatagid,fillnum,runnum,lsnum);
    output:
       datatagid
    '''
    datatagid = 0
    if datatagnameid!=0:
        # generate new id
        pass
    return datatagid

####################
##    Query API
####################

def buildselect_runls(inputSeries,alias=''):
    '''
    output: [conditionstring, var_runs, var_lmins, var_lmaxs]
    '''
    prefix = ''
    if alias:
        prefix = alias+'.'
    result = []
    bind_runindex = 0
    bind_lsindex = 0
    var_runs={}
    var_lmins={}
    var_lmaxs={}
    qstrs = []
    if inputSeries.empty:
        return None
    for run,lsrange in inputSeries.iteritems():
        runvar='r_%d'%(bind_runindex)
        var_runs[runvar] = run
        s = '%srunnum=:%s and '%(prefix,runvar)
        orss = []
        for lsmin,lsmax in lsrange:
            lminvar = 'lmin_%d'%(bind_lsindex)
            lmaxvar = 'lmax_%d'%(bind_lsindex)
            var_lmins[lminvar] = lsmin
            var_lmaxs[lmaxvar] = lsmax
            orss.append( '(%slsnum>=:%s and %slsnum<=:%s)'%(prefix,lminvar,prefix,lmaxvar) )
            bind_lsindex = bind_lsindex + 1
        ss = '('+' or '.join(orss)+')'
        bind_runindex = bind_runindex + 1
        qstrs.append('('+s+ss+')')
    result.append( '('+' or '.join(qstrs)+')' )
    result.append(var_runs)
    result.append(var_lmins)
    result.append(var_lmaxs)
    return result

def max_datatagname(dbengine,schemaname=''):
    '''
    get the most recent datatagname 
    output: (datatagname,datatagid)
    '''
    name = 'datatags'
    result = None    
    if schemaname:
        name = schemaname+'.'+name
    q = "select datatagname,datatagnameid from %s where datatagnameid=(select max(datatagnameid) from %s)"%(name,name)
    log.debug(q)
    connection = dbengine.connect()
    qresult = connection.execute(q,{}).fetchone()
    result = (qresult['datatagname'],qresult['datatagnameid'])
    return result

def datatagnameid(dbengine,datatagname,schemaname=''):
    '''
    get datatagnameid by name
    input: datatagname. 
    output: datatagnameid
    '''
    basetablename = tablename = 'datatags'
    result = None
    if schemaname:
        tablename = '.'.join([schemaname,basetablename])
    result = None
    q = '''select DATATAGNAMEID as datatagnameid from %s where DATATAGNAME=:datatagname'''%tablename
    log.debug(q)
    qresult = pd.read_sql_query(q,dbengine,params={'datatagname':datatagname})
    for idx,row in qresult.iterrows():
        result = row['datatagnameid']
    return result

def max_datatagOfRun(engine,runlist,schemaname=''):
    '''
    get the most recent datatagid of runs
    output: {run:datatagid}
    '''
    result = {}
    basetablename = tablename = 'RUNINFO'
    if schemaname:
        tablename = '.'.join([schemaname,basetablename])
    runliststr = ','.join(runlist)
    q = '''select RUNNUM as runnum, max(DATATAGID) as datatagid from %s where RUNNUM in (%s) limit 1'''%(tablename,runliststr)
    qresult = pd.read_sql_query(q,engine,params={})
    for idx,row in qresult.iterrows():
        run = row['runnum']
        datatagid = row['datatagid']
        result[run] = datatagid
    return result

def table_exists(engine,tablename,schemaname=None):
    return engine.dialect.has_table(engine.connect(),tablename,schema=schemaname)

def build_fillquery_condition(ftabalias,amodetagid=None,targetegev=None):
    qCondition = ''
    qPieces = []
    binddict = {}
    if amodetagid:
        qPieces.append('%s.amodetagid=:amodetagid'%(ftabalias))
        binddict['amodetagid'] = amodetagid
    if targetegev:
        qPieces.append('%s.targetegev=:targetegev'%(ftabalias))
        binddict['targetegev'] = targetegev

    if not qPieces: return ('',{})
    qCondition = ' and '.join(qPieces)
    return (qCondition,binddict)

def build_idquery_condition(alias,runmin=None,runmax=None,fillmin=None,tssecmin=None,tssecmax=None,fillmax=None,beamstatusid=None,runlsselect=None,datatagnameid=None):
    qCondition = ''
    qPieces = []
    binddict = {}
    a = ''
    if alias:
        a = alias+'.'
        
    if fillmin and fillmax:
        if fillmin==fillmax:
            qPieces.append('%sfillnum=:fillnum'%a)
            binddict['fillnum'] = fillmin
        else:
            qPieces.append('%sfillnum>=:fillmin and %sfillnum<=:fillmax'%(a,a))
            binddict['fillmin'] = fillmin
            binddict['fillmax'] = fillmax
    elif fillmin:
        qPieces.append('%sfillnum>=:fillmin'%a)
        binddict['fillmin'] = fillmin
    elif fillmax:
        qPieces.append('%sfillnum<=:fillmax'%a)
        binddict['fillmax'] = fillmax
    if tssecmin:
        qPieces.append('%stimestampsec>=:tssecmin'%a)
        binddict['tssecmin'] = tssecmin
    if tssecmax:
        qPieces.append('%stimestampsec<=:tssecmax'%a)
        binddict['tssecmax'] = tssecmax
    if beamstatusid is not None:
        qPieces.append('%sbeamstatusid=:beamstatusid'%a)
        binddict['beamstatusid'] = beamstatusid        
    if runlsselect is not None and not runlsselect.empty :        
        s_runls = buildselect_runls(runlsselect,alias=alias)
        if s_runls:
            s_runls_str = s_runls[0]
            var_runs = s_runls[1]
            var_lmins = s_runls[2]
            var_lmaxs = s_runls[3]
            qPieces.append(s_runls_str)
            for runvarname,runvalue in var_runs.items():                
                binddict[runvarname] = runvalue
            for lminname,lmin in var_lmins.items():                
                binddict[lminname] = lmin
            for lmaxname,lmax in var_lmaxs.items():                
                binddict[lmaxname] = lmax

    if runmin and runmax :
        if runmin==runmax:
            qPieces.append('%srunnum=:runmin'%a)
            binddict['runmin'] = runmin
        else:
            qPieces.append( '%srunnum>=:runmin and %srunnum<=:runmax'%(a,a) )
            binddict['runmin'] = runmin
            binddict['runmax'] = runmax
    elif runmin:
        qPieces.append('%srunnum>=:runmin'%a)
        binddict['runmin'] = runmin
    elif runmax:
        qPieces.append('%srunnum<=:runmax'%a)
        binddict['runmax'] = runmax

    if datatagnameid:
        qPieces.append('%sdatatagnameid<=:datatagnameid'%s)
        binddict['datatagnameid'] = datatagnameid
        
    #if not qPieces: return ('',{})
    if not qPieces:
        return None
    qCondition = ' and '.join(qPieces)
    return (qCondition,binddict)

def build_or_collection(varname,varnamealias,mycollection):    
    f = []
    binddict = {}
    for i,h in enumerate(mycollection):
        thisalias = '%s%d'%(varnamealias,i)
        f.append( '%s=:%s'%(varname,thisalias) )
        binddict[ thisalias ] = h
    if not f: return ['',{}]
    return ['('+' or '.join(f)+')', binddict]

def online_resultIter(engine,tablename,schemaname='',runmin=None,runmax=None,fillmin=None,tssecmin=None,tssecmax=None,fillmax=None,beamstatusid=None,amodetagid=None,targetegev=None,runlsselect=None,fields=[],sorted=False):
    '''    
    get online bestlumi
    fields choices: [runnum,lsnum,fillnum,timestampsec,cmson,beamstatusid,delivered,recorded,bxdeliveredblob,avgpu,datasource,normtag,normtagid,amodetagid,targetegev,numbxbeamactive,norb,nbperls]
    where amodetagid, targetegev,numbxbeamactive,norb,nbperls are implicitly fields of lhcfill table. 
    '''
    t = tablename
    if schemaname:
        t=schemaname+'.'+t
    ftab = 'lhcfill'
    if schemaname:
        ftab=schemaname+'.'+ftab
    (fCondition,fbinddict) = build_fillquery_condition('f',amodetagid=amodetagid,targetegev=targetegev)
    ifields = []
    ffields = [] 
    for f in fields:
        if f in _lhcfill_fields:
            ffields.append(f)
        else:
            ifields.append(f)
            
    if not ifields:
        ifields = ['runnum','lsnum']
        
    ifieldsStr = ','.join(['i.%s as %s'%(f,f) for f in ifields])
    ffieldsStr = ','.join(['f.%s as %s'%(f,f) for f in ffields])

    if runlsselect is None:
        (qCondition,binddict) = build_idquery_condition('i',runmin=runmin,runmax=runmax,fillmin=fillmin,fillmax=fillmax,tssecmin=tssecmin,tssecmax=tssecmax,beamstatusid=beamstatusid,runlsselect=None)
        if not qCondition:
            raise StopIteration
            #return None #main table must be filtered
        if fCondition:
            for fbk, fbv in fbinddict.items(): #merge binddict
                binddict[fbk] = fbv
        q = "select %s from %s i"%(ifieldsStr,t) + ' where '+qCondition
        if ffields:       
            q = "select %s,%s from %s i, %s f"%(ifieldsStr,ffieldsStr,t,ftab) + ' where '+qCondition
            if ffieldsStr:
                q = q+' and i.fillnum=f.fillnum '
                if fCondition:
                    q = q+' and '+fCondition        
        if sorted:
            q = q+' order by runnum,lsnum'
        
        log.debug('online_resultIter: '+q+' , '+str(binddict))
        connection = engine.connect()
        result = connection.execution_options(stream_result=True).execute(q,binddict)
        output=result.fetchall()
        result.close()
        #return r
        for item in output:
            yield item
            
        #return iter(result)
    else:
        runlssplit_nrows = 1 # the true chunk size
        runlssplit_nchunks = 1 # initial value
        if runlsselect.size>runlssplit_nrows:
            log.debug('runlsselect of size %s should be splitted'%runlsselect.size)
            runlssplit_nchunks =  runlsselect.size//runlssplit_nrows + 1
        runls_array = np.array_split(runlsselect, runlssplit_nchunks)
        #output = itertools.chain()
        connection = engine.connect()
        for runlsselect_i in runls_array:
            if runlsselect_i.empty:
                continue
            (qCondition,binddict) = build_idquery_condition('i',runmin=runmin,runmax=runmax,fillmin=fillmin,fillmax=fillmax,tssecmin=tssecmin,tssecmax=tssecmax,beamstatusid=beamstatusid,runlsselect=runlsselect_i)
            if not qCondition:
                raise StopIteration
                #return None #main table must be filtered
            if fCondition:
                for fbk, fbv in fbinddict.items(): #merge binddict
                    binddict[fbk] = fbv
            q = "select %s from %s i"%(ifieldsStr,t) + ' where '+qCondition
            if ffields:       
                q = "select %s,%s from %s i, %s f"%(ifieldsStr,ffieldsStr,t,ftab) + ' where '+qCondition
                if ffieldsStr:
                    q = q+' and i.fillnum=f.fillnum '
                    if fCondition:
                        q = q+' and '+fCondition        
            if sorted:
                q = q+' order by runnum,lsnum'
        
            log.debug('online_resultIter: '+q+' , '+str(binddict))
            result = connection.execution_options(stream_result=True).execute(q,binddict)
            output = result.fetchall()
            result.close()
            #output = itertools.chain( output, r )
            for item in output:
                yield item
        #return output
    
###############
# trg queries
###############
def translate_fntosql(pattern):
    '''
    translate fnmatch pattern to sql pattern 
    '''    
    sqlresult = pattern
    sqlresult = sqlresult.replace('*','.*')
    sqlresult = sqlresult.replace('?','.?')
    sqlresult = sqlresult.replace('!','^')    
    return sqlresult

def get_hlttrgl1seedmap(engine,hltpath=None,hltconfigids=None,schemaname=''):
    '''
    input :
        hltpath : hltpath name string or pattern
        hltconfigids : number of list of numbers
    output:
       hlttrgl1seedmap : {hltconfigid: [[hltpathid,hltpathname,seedtype,[seedvalues]]]}
    '''
    tablename = name = 'hltpathl1seedmap'
    if schemaname:
        tablename = '.'.join([schemaname,name])
    q = "select hltconfigid, hltpathid, hltpathname, l1seed from %s "%(tablename)
    binddict = {}
    qfields = []    
    result = {}
    if isinstance(hltpath,str):
        if _is_strpattern(hltpath): # is pattern
            hltpath_sqlexpr = translate_fntosql(hltpath)
            qfields.append("regexp_like(hltpathname,'%s')"%(hltpath_sqlexpr))
        else:
            if hltpath:
                qfields.append("hltpathname=:hltpathname")
                binddict['hltpathname'] = hltpath
         
    if isinstance(hltconfigids,int):
        if hltconfigids:
            qfields.append("hltconfigid=:hltconfigid")
            binddict['hltconfigid'] = hltconfigids
    elif isinstance(hltconfigids,collections.Iterable):        
        (qf,s) = build_or_collection('hltconfigid','hltconfigid',hltconfigids)
        if qf:
            qfields.append(qf)
            binddict = merge_two_dicts(binddict,s)
    if qfields:
        q = q+' where '
        if len(qfields)==1:
            q = q+qfields[0]
        else:
            q = q+' and '.join(qfields)
    log.debug(q+','+str(binddict))
    connection = engine.connect()
    resultProxy = connection.execute(q,binddict)
    for row in resultProxy:
        hltconfigid = row['hltconfigid']
        hltpathid = row['hltpathid']
        hltpathname = row['hltpathname']
        l1seedstr = row['l1seed']
        parseresult = parseL1Seed(l1seedstr)
        if not parseresult:
            continue
        l1seedtype = parseresult[0]
        l1seedbits = parseresult[1]
        result.setdefault(hltconfigid,[]).append( [hltpathid,hltpathname,l1seedtype,l1seedbits] )
    #hltpathl1seed['seedtype'],hltpathl1seed['seedvalue'] = zip(*(hltpathl1seed['l1seed'].apply(parseL1Seed)))
    #del hltpathl1seed['l1seed']
    return result

def get_hltmissing(engine,runnum,schemaname=''):
    '''
    input:
        runnum: runnumber
    output:
        [hltmissingls] 
    '''
    result = []
    prescidxchangetable = 'prescidxchange'
    if schemaname:
        prescidxchangetable = '.'.join([schemaname,prescidxchangetable])
    resultstr = ''
    q = "select lsmissing from %s where runnum=:runnum"%(prescidxchangetable)
    binddict = {'runnum':runnum}
    log.debug(q+','+str(binddict))
    connection = engine.connect()
    resultProxy = connection.execute(q,binddict)
    for row in resultProxy:
        missingstr = row['lsmissing']
        if missingstr:
            m = missingstr.split(',')
            result = result + [int(i) for i in m]
    return result
    
def get_prescidx_change(engine,runnums,schemaname=''):
    '''
    input:
        runnums: runnumbers
    output: 
        {runnum:[[lslastscaler,prescidx]]
    '''
    prescidxchangetable = 'prescidxchange'
    if schemaname:
        prescidxchangetable = '.'.join([schemaname,prescidxchangetable])
        
    q = "select runnum,lsnum,prescidx from %s "%(prescidxchangetable)
    binddict = {}
    result = {}#{runnum:[[lslastscaler,prescidx]]
    qfields = []
    if isinstance(runnums,int):
        if runnums:
            qfields.append("runnum=:runnum")
            binddict['runnum'] = runnums
    elif isinstance(runnums,collections.Iterable):
        (qf,s) = build_or_collection('runnum','runnum',runnums)
        if qf:
            qfields.append(qf)
            binddict = merge_two_dicts(binddict,s)
    if qfields:
        q = q+' where '        
        if len(qfields)>1:
            q = q+" and ".join(qfields)
        else:
            q = q+qfields[0]
    q = q+' order by runnum,lsnum'
    log.debug(q+','+str(binddict))
    connection = engine.connect()
    resultProxy = connection.execute(q,binddict)
    for row in resultProxy:
        r = row['runnum']
        lslastscaler = row['lsnum']
        prescidx = row['prescidx']
        result.setdefault(r,[]).append( [lslastscaler,prescidx] )            
    return result
    
def get_hltrunconfig(engine,hltconfigid=None,hltkey=None,runnum=None,schemaname=''):
    '''
    output: [['runnum','hltconfigid','hltkey'],['runnum','hltconfigid','hltkey']]
    '''
    hltrunconftable = 'hltrunconfig'
    if schemaname:
        hltrunconftable = '.'.join([schemaname,hltrunconftable])
    q = "select runnum,hltconfigid,hltkey from %s"%(hltrunconftable)
    binddict = {}
    qfields = []
    result = []
    if isinstance(hltconfigid,int):
        if hltconfigid:
            qfields.append("hltconfigid=:hltconfigid")
            binddict['hltconfigid'] = hltconfigid
    elif isinstance(hltconfigid,collections.Iterable):
        (qf,s) = build_or_collection('hltconfigid','hltconfigid',hltconfigid)
        if qf:
            qfields.append(qf)
            binddict = merge_two_dicts(binddict,s)
            
    if isinstance(hltkey,str):
        if  _is_strpattern(hltkey): # is pattern
            qfields.append("regexp_like(hltkey,'%s')"%hltkey)
        else:
            qfields.append("hltkey=:hltkey")
            binddict['hltkey'] = hltkey
            
    if isinstance(runnum,int):
        if runnum:
            qfields.append("runnum=:runnum")
            binddict['runnum'] = runnum
    elif isinstance(runnum,collections.Iterable):
        (qf,s) = build_or_collection('runnum','runnum',runnum)
        if qf:
            qfields.append(qf)
            binddict = merge_two_dicts(binddict,s)
        
    if qfields:
        q = q+" where "
        if len(qfields)>1:
            q = q+' and '.join(qfields)
        else:
            q = q+qfields[0]
    log.debug(q + ' , ' + str(binddict) )
    connection = engine.connect()    
    resultProxy = connection.execute(q,binddict)
    for row in resultProxy:
        result.append( [ row['runnum'],row['hltconfigid'],row['hltkey'] ])
    return result

def get_hltprescale(engine,runnum,lsnum,hltconfigid,prescidx,hltpathid,schemaname=''):
    '''
    input:
    
    output:
       prescval
    '''
    hltscalertable = 'hltscaler'
    result = 1
    if schemaname:
        hltscalertable = '.'.join([schemaname,hltscalertable])   
    q = "select prescidx,hltpathid,hltprescval from %(hltscalerT)s where hltconfigid=:hltconfigid and runnum=:runnum and lsnum=:lsnum and prescidx=:prescidx and hltpathid=:hltpathid" %{'hltscalerT':hltscalertable}
    binddict = {'runnum':runnum,'lsnum':lsnum,'hltconfigid':hltconfigid,'prescidx':prescidx,'hltpathid':hltpathid}
    log.debug( q+','+str(binddict) )
    connection = engine.connect()
    resultProxy = connection.execute(q,binddict)
    for row in resultProxy:
        result = row['hltprescval']
    return result
    
def get_l1prescale(engine,runnum,lsnum,l1candidates=None,prescidxs=None,ignorel1mask=False,schemaname=''):
    '''
    output:
    { (prescidx,bitname): [trgprescval,bitmask]}
    '''
    trgscalertable = 'trgscaler'
    trgrunconftable = 'trgrunconfig'
    result = {} # { (prescidx,bitname): [trgprescval,bitmask]}
    if schemaname:
        trgscalertable = '.'.join([schemaname,trgscalertable])   #'l'
        trgrunconftable = '.'.join([schemaname,trgrunconftable]) #'r'  
    q = "select l.prescidx as prescidx,r.bitname as bitname,l.trgprescval as trgprescval,r.mask as bitmask from  %(trgscalerT)s l, %(trgrunconfT)s r where r.runnum=l.runnum and r.bitid=l.bitid and l.runnum=:runnum and l.lsnum=:lsnum"%{'trgscalerT':trgscalertable,'trgrunconfT':trgrunconftable}
    if ignorel1mask is False:
        q = q+' and r.mask!=0 '#mask=1, pass; mask=0 masked off
    binddict = {'runnum':runnum,'lsnum':lsnum}
    qfields = []
    if isinstance(l1candidates,str):
        if l1candidates:
            qfields.append('r.bitname=:bitname')
            binddict['bitname']=l1candidates
    elif isinstance(l1candidates,collections.Iterable):
        (qf,s) = build_or_collection('r.bitname','bitname',l1candidates)
        if qf:
            qfields.append(qf)
            binddict = merge_two_dicts(binddict,s)
            
    if isinstance(prescidxs,int):
        qfields.append('l.prescidx=:prescidx')
        binddict['prescidx'] = prescidxs
    elif isinstance(prescidxs,collections.Iterable):
        (qf,s) = build_or_collection('l.prescidx','prescidx',prescidxs)
        if qf:
            qfields.append(qf)
            binddict = merge_two_dicts(binddict,s)
    if qfields:
        q = q+' and '
        if len(qfields)>1:
            q = q+' and '.join(qfields)
        else:
            q = q+qfields[0]
    log.debug( q+','+str(binddict) )
    connection = engine.connect()
    resultProxy = connection.execute(q,binddict)
    for row in resultProxy:
        prescidx = row['prescidx']
        l1bname = row['bitname']
        l1v = row['trgprescval']
        l1ma = row['bitmask']
        result[(prescidx,l1bname)]=[l1v,l1ma]
    return result

def parseL1Seed(l1seed):
    '''
    output: [exptype,[l1seedbits]]
    '''
    sep=re.compile('(\sAND\s|\sOR\s)',re.IGNORECASE)
    result=re.split(sep,l1seed)
    cleanresult=[]
    exptype='ONE'
    notsep=re.compile('NOT\s',re.IGNORECASE)
    andsep=re.compile('\sAND\s',re.IGNORECASE)
    orsep=re.compile('\sOR\s',re.IGNORECASE)
    for r in result:
        if notsep.match(r) : #we don't know what to do with NOT
            return [None,[]]
        if orsep.match(r):
            exptype='OR'
            continue
        if andsep.match(r):
            exptype='AND'
            continue
        #cleanresult.append(string.strip(r).replace('\"',''))
        cleanresult.append(string.strip(r))    
    return [exptype,cleanresult]

def build_joinwithdatatagid_query(datatablename,suffix,datafields,idfields,idcondition,datatagnameid=datatagnameid,ffields=[],fcondition='',schemaname='',sorted=False):
    '''
    if datatagnameid: add datatagnameid to idfield for i and i.datatagnameid<=:datatagnameid
    if ffields, select also lhcfill fields
    if fcondition, add also lhcfill join on fillnum
    
    '''
    idtablename = 'ids_datatag'
    filltablename = 'lhcfill'
    btablename = '_'.join([datatablename,str(suffix)])    
    if schemaname:
        idtablename = '.'.join([schemaname,idtablename])
        btablename = '.'.join([schemaname,btablename])
        filltablename = '.'.join([schemaname,filltablename])        

    data_fieldstr = ','.join([ '%s'%f for f in datafields ])
    id_fieldstr = ','.join([ '%s'%f for f in idfields ])
    f_fieldstr = ','.join([ '%s'%f for f in ffields ])

    if ffields:        
        q = "select datatagid,%s,%s,%s "%(data_fieldstr,id_fieldstr,f_fieldstr)
    else:        
        q = "select datatagid,%s,%s "%(data_fieldstr,id_fieldstr)
   
    id_fieldstr_alias = ','.join([ '%s%s as %s'%('i.',f,f) for f in idfields ])
    data_fieldstr_alias = ','.join([ '%s%s as %s'%('b.',f,f) for f in datafields ])
    f_fieldstr_alias = ','.join([ '%s%s as %s'%('f.',f,f) for f in ffields ])
    rankfield = "rank() over(partition by i.runnum,i.lsnum order by i.datatagid desc) rnk"    

    if ffields:        
        subq = '(select i.datatagid as datatagid,%s,%s,%s,%s from %s i, %s b, %s f where i.fillnum=f.fillnum and i.datatagid=b.datatagid'%(id_fieldstr_alias,data_fieldstr_alias,f_fieldstr_alias,rankfield,idtablename,btablename,filltablename)
    else:
        subq = '(select i.datatagid as datatagid,%s,%s,%s from %s i, %s b where i.datatagid=b.datatagid'%(id_fieldstr_alias,data_fieldstr_alias,rankfield,idtablename,btablename)

    subq = subq+' and '+idcondition
    if fcondition:
        subq = subq+' and '+fcondition
    if datatagnameid:
        subq = subq+' and i.datatagnameid<=:datatagnameid'
    subq = subq+')'
    q = q+ ' from %s where rnk=1'%(subq)
    
    if sorted:
        q = q+' order by runnum,lsnum'
    return q

def dataIter(engine,datasource,datatype,suffix,datafields=[],idfields=[],schemaname='',runmin=None,runmax=None,fillmin=None,tssecmin=None,tssecmax=None,fillmax=None,beamstatusid=None,amodetagid=None,targetegev=None,runlsselect=None,sorted=False,datatagnameid=None):
    '''
    3 table join: id table, lhcfill table, data table
    input:
        datasource: luminometer type
        datatype: result or raw
        suffix: table shard id
        datafields:         
          fields from lumidata table. choices [avglumi,bxlumiblob,fillnum,runnum,lsnum,timestampsec]
          fields from beam table. choices [intenisty1,intensity2,bxidxblob,bxintensity1blob,bxintensity2blob]
        idfields: fields from ids_datatag table and lhcfill table, [runnum,lsnum,fillnum,timestampsec,cmson,beamstatusid,amodetagid,targetegev,numbxbeamactive,norb,nbperls]
        
    output: iterator    
       if datatagnameid: add datatagnameid to idfields and binddict a 

    '''
    if not datafields:
        raise StopIteration
        #return None
    basetablename = datasource
    if datatype:
        basetablename = basetablename+'_'+datatype
    ifields = []
    ffields = []
    for f in idfields:
        if f in _lhcfill_fields:
            ffields.append(f)
        else:
            ifields.append(f)
    idf = ifields
    if datatagnameid:
        idf = ifields+['datatagnameid']
         
    (fCondition,fbinddict) = build_fillquery_condition('f',amodetagid=amodetagid,targetegev=targetegev)

    if runlsselect is not None :
        runlssplit_nrows = 1 # the true chunk size
        runlssplit_nchunks = 1 # initial value
        if runlsselect.size>runlssplit_nrows:
            log.debug('runlsselect of size %s should be splitted'%runlsselect.size)
            runlssplit_nchunks =  runlsselect.size//runlssplit_nrows + 1
        runls_array = np.array_split(runlsselect, runlssplit_nchunks)                    
        #output = itertools.chain()
        connection = engine.connect()
        for runlsselect_i in runls_array:
            if runlsselect_i.empty:
                continue
            (qCondition,binddict) = build_idquery_condition('i',runmin=runmin,runmax=runmax,fillmin=fillmin,fillmax=fillmax,tssecmin=tssecmin,tssecmax=tssecmax,beamstatusid=beamstatusid,runlsselect=runlsselect_i)
            if not qCondition:
                raise StopIteration
                #return None
            if fCondition:
                for fbk, fbv in fbinddict.items(): #merge binddict
                    binddict[fbk] = fbv
            if datatagnameid:
                binddict['datatagnameid'] = datatagnameid        
            q = build_joinwithdatatagid_query(basetablename,suffix,datafields,idf,qCondition,datatagnameid=datatagnameid,ffields=ffields,fcondition=fCondition,schemaname=schemaname,sorted=sorted)    
            log.debug('dataIter %s %s: '%(datasource,datatype)+q)
            log.debug(str(binddict))
        
            result = connection.execution_options(stream_result=True).execute(q,binddict)
            output=result.fetchall()
            result.close()
            for item in output:
                yield item
            #output = itertools.chain( output, iter(result) )
        #return output
    else:
        connection = engine.connect()
        (qCondition,binddict) = build_idquery_condition('i',runmin=runmin,runmax=runmax,fillmin=fillmin,fillmax=fillmax,tssecmin=tssecmin,tssecmax=tssecmax,beamstatusid=beamstatusid,runlsselect=None)
        if not qCondition:
            raise StopIteration
            #return None
        if fCondition:
            for fbk, fbv in fbinddict.items(): #merge binddict
                binddict[fbk] = fbv
        if datatagnameid:
            binddict['datatagnameid'] = datatagnameid        
        q = build_joinwithdatatagid_query(basetablename,suffix,datafields,idf,qCondition,datatagnameid=datatagnameid,ffields=ffields,fcondition=fCondition,schemaname=schemaname,sorted=sorted)
    
        log.debug('dataIter %s %s: '%(datasource,datatype)+q)
        log.debug(str(binddict))        
        result = connection.execution_options(stream_result=True).execute(q,binddict)
        output=result.fetchall()
        result.close()
        for item in output:
            yield item
        #return iter(result) 

