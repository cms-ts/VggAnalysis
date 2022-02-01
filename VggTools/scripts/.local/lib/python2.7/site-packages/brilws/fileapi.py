import tables as tb
import numpy as np
import pandas as pd
import os,sys
import logging
import params

from time import time

log = logging.getLogger('brilws')

def _is_element_tuple(me):
    '''
    Check if element of me is tuple 
    Input: collection
    '''
    return np.all([isinstance(x,tuple) for x in me])

def _is_subset(me,target):
    '''
    Check me collection is a subset of the target collection
    '''
    return np.in1d(me,target).all()

def _open_validfile(filename, tables):
    '''
    Check if the file has all the required table    
    Input: f: filename, tables: required table names
    Output: filehandle if input is valid, None if input is invalid 
    '''    

    f = None
    try:
        f = tb.open_file(filename)
    except tb.exceptions.HDF5ExtError:
        log.debug('failed to open %s, skip'%filename)
        return None
    nodes = f.root._v_children.keys()
    if not len(nodes):
        f.close()
        return None
    if not _is_subset(tables,nodes):
        f.close()
        return None
    tablelist = map(lambda x: f.get_node('/'+x),tables) #get selected tables by name
    filledtables = filter(lambda x: x.nrows>0, tablelist)  #filledtables
    if len(tablelist) != len(filledtables):
        return None
    return f

def open_validfiles(filenames,lumitype):
    '''
    Input: [filename], lumitype
    Output: [filehandle]
    '''    
    mytype = lumitype.upper()
    requiredtables = ['tcds','beam']
    if mytype in params._lumitypeToh5tablename.keys():
        requiredtables.append(params._lumitypeToh5tablename[mytype])

    return filter(lambda x: x is not None,[_open_validfile(f,requiredtables) for f in filenames])

def _build_preselectcondition( runmin=None,runmax=None,fillmin=None,tssecmin=None,tssecmax=None,fillmax=None, runlsselect=None ):
        if runlsselect is not None:        
            if runmin==runmax==fillmin==tssecmin==tssecmax==fillmax==None:
                runmin = min(runlsselect.index.tolist())
                runmax = max(runlsselect.index.tolist())       
        conditions = []
        if runmin and runmax and runmin==runmax:
            conditions.append('(runnum == %d)'%runmin)   
        elif runmin: 
            conditions.append('(runnum >= %d)'%runmin)
        elif runmax: 
            conditions.append('(runnum <= %d)'%runmax)
        if fillmin and fillmax and fillmin==fillmax:
            conditions.append('(fillnum == %d)'%fillmin)
        elif fillmin:
            conditions.append('(fillnum >= %d)'%fillmin)
        elif fillmax: 
            conditions.append('(fillnum <= %d)'%fillmax)
        if tssecmin and tssecmax and tssecmin==tssecmax:
            conditions.append('(tssec == %d)'%tssecmin)
        elif tssecmin: 
            conditions.append('(tssec >= %d)'%tssecmin)
        elif tssecmax: 
            conditions.append('(tssec <= %d)'%tssecmax)
        conditionStr = '&'.join(conditions) 
        return conditionStr

class dataRangeIterator:    
    def __init__(self,filehandles,tablenames,conditionStr):
        self._filehandles = filehandles
        self._tablenames = tablenames
        self._conditionStr = conditionStr

    def _get_range_in_file(self,filehandle):
        '''
        Selected range of all tables in file
        Output: {tablename:coordinates}
        '''
        result = {}
        if not self._conditionStr:
            return result
        for tablename in self._tablenames:
            n = filehandle.get_node('/'+tablename)
            coordinates = n.get_where_list(self._conditionStr,sort=False)
            if coordinates.size == 0: 
                result[tablename] = None
            else:
                result[tablename] = coordinates.tolist()
        return result
 
    def next(self):
        '''
        Output: (filehandle, {tablename: coordinates})
        '''
        for f in self._filehandles: #loop over files
            log.debug('Processing file '+f.filename)
            alltables = f.root._v_children.keys()
            if not _is_subset(self._tablenames,alltables):
                log.debug('file %s does not contain all the tables, skip '%f.filename)
                continue
            results = self._get_range_in_file(f)
            if not results:
                continue
            yield (f,results) 

    
def dataFilter(tablehandle,coordinates,field_dtypes,runlsRangeSelectSeries=None,runlsnbPointFilterSeries=None):
    '''
    Filter input table nodes on fields based on runls range selection and runlsnb point selection conditions
    Input:  
            tablehandle: table handle
            coordinates: row coordinates
            fields: output fields dtype
            runlsRangeSelectSeries: run,ls range selection matrix. Note: if None, select all
            runlsnbPointSelectSeries: [run,(ls,nb)]. Note: if None, select all
    Output: 
            numpy record array of type field_dtypes
    Note: this filter does not produce None. Empty result means reject all
    '''   
    myrows = tablehandle.read_coordinates(coordinates)
    thisrun = np.array(myrows['runnum'])[0]
    lsnums = np.array(myrows['lsnum'])
    masks = np.full(lsnums.shape, True, dtype=bool) #default to select all

    if runlsRangeSelectSeries is not None:
        selectedruns = runlsRangeSelectSeries.index
        if thisrun not in selectedruns: #run is not selected
            masks = np.full(lsnums.shape, False, dtype=bool) #mask out all ls
        else: 
            thisselectedls = runlsRangeSelectSeries[thisrun]
            masks = np.logical_or.reduce([np.logical_and(lsnums>=xmin, lsnums<=xmax) for [xmin,xmax] in thisselectedls]) #find masks   

    if runlsnbPointFilterSeries is not None:
        if thisrun not in runlsnbPointFilterSeries.index: #run is not selected
            masks = np.full(lsnums[masks].shape, False, dtype=bool) #mask out all the rest ls                
        else:
            lsnbselect = runlsnbPointFilterSeries[thisrun].values.tolist() #this run values : [(lsnum,nbnum)] 
            mylsnbs = [tuple(x) for x in np.column_stack((myrows['lsnum'][masks],myrows['nbnum'][masks]))]
            for i,lsnb in enumerate(mylsnbs):
                if lsnb not in lsnbselect:
                    masks[i] = False
    all_fields = []
    for fieldname in field_dtypes.names:
        value = myrows[fieldname][masks]
        all_fields.append(value)
    nrows = masks[np.nonzero(masks)].size
    log.debug('selected rows %d'%nrows)
    result = np.core.records.fromarrays(all_fields,names=field_dtypes.names,dtype=field_dtypes)    
    return result

def andFilter(irecordsSize,conditions):
    masks = np.full(irecordsSize, True, dtype=bool) #default to select all      
    for co in conditions:
        #print 'passed n masks:', masks[np.nonzero(masks)].size
        masks = np.logical_and(masks,co)
    return masks


class typebuilder:   
    def __init__(self,datatablename,datatype,withBX): 
        '''
        Build np.dtype for input tables and output data
        Input: 
            datatablename: table name in hdf5 file
            withBX: if output is with per bx data       
        '''
        self._basetypelist = [('runnum','uint32'),('lsnum','uint32'),('nbnum','uint32'),('timestampsec','uint32')]
        self._tcdstypelist = self._basetypelist + [('cmson','bool8'),('deadfrac','float32'),('ncollidingbx','uint32')]
        self._beam_typelist = self._basetypelist + [('status','U28'),('machinemode','U20'),('targetegev','uint32')] 
        self._withBX = withBX  
        self._datatablename = datatablename
        self._datatype = datatype

    def datatablename(self):
        return self._datatablename

    def datatype(self):
        return self._datatype 

    def tcds_typelist(self):
        '''
            tcds table input fields 
        '''
        return np.dtype(self._tcdstypelist)

    def beam_typelist(self):
        '''
             beam table input fields 
        '''
        return np.dtype(self._beam_typelist)

    def lumidata_typelist(self):
        '''
            lumi data table input fields            
        '''
        if self._datatablename == 'bestlumi':
            datafieldtypelist = self._basetypelist + [('fillnum','uint32'),('delivered','float32'),('recorded','float32'),('avgpu','float32'),('provider','U8')]
            if self._withBX:
                datafieldtypelist.append(('bxdelivered','float32',(3564,)))
        else:
            if self._datatype == 'raw':
                datafieldtypelist = self._basetypelist + [('fillnum','uint32'),('avgraw','float32')]
                if self._withBX:
                    datafieldtypelist.append(('bxraw','float32',(3564,)))
            else:
                datafieldtypelist = self._basetypelist + [('fillnum','uint32'),('avg','float32')]
                if self._withBX:
                    datafieldtypelist.append(('bx','float32',(3564,)))
        return np.dtype(datafieldtypelist)
    
def resultIter(filehandles,lumitype,datatype='best',runmin=None,runmax=None,fillmin=None,tssecmin=None,tssecmax=None,fillmax=None,beamstatusid=None,amodetagid=None,targetegev=None,runlsselect=None,withBX=False):
    '''
    get online bestlumi
    field choices: [runnum,lsnum,fillnum,timestampsec,cmson,beamstatus,delivered,recorded,bx,avgpu,datasource,normtag,normtagid,amodetagid,targetegev,numbxbeamactive,norb,nbperls]
    
    '''
    datatablename = params._lumitypeToh5tablename[lumitype.upper()]
    tbuilder = typebuilder(datatablename,datatype,withBX)
    preconditionStr = _build_preselectcondition(runmin=runmin,runmax=runmax,fillmin=fillmin,tssecmin=tssecmin,tssecmax=tssecmax,fillmax=fillmax,runlsselect=runlsselect)
    rangeIter = dataRangeIterator(filehandles,['tcds','beam',datatablename],preconditionStr)
        
    for co in rangeIter.next():
        filehandle = co[0]
        all_coordinates = co[1].values()
        if None in all_coordinates:
            log.debug('not all tables passed preselection, skip file ',filehandle.filename)
            continue

        #tcds selection

        tcds_coordinates = co[1]['tcds']
        tcds_table_handle = filehandle.get_node('/tcds')
        tcds_result = dataFilter(tcds_table_handle,tcds_coordinates,field_dtypes=tbuilder.tcds_typelist(),runlsRangeSelectSeries=runlsselect,runlsnbPointFilterSeries=None)

        if not tcds_result.size:
            log.debug('tcds failed data selection, continue ',filehandle.filename)
            continue
     
        selected_time = np.column_stack((tcds_result['runnum'],tcds_result['lsnum'],tcds_result['nbnum']))       
        runlsnbSeries = _make_runlsnb_Series( selected_time )
        #beam selection

        beam_coordinates = co[1]['beam']
        beam_table_handle = filehandle.get_node('/beam')
        beam_result = dataFilter(beam_table_handle,beam_coordinates,field_dtypes=tbuilder.beam_typelist(),runlsRangeSelectSeries=None,runlsnbPointFilterSeries=runlsnbSeries)
        beamconditions = []
        if beamstatusid is not None:
            req_beamstatus = params._idtobeamstatus[beamstatusid]
            beamconditions.append( beam_result['status']==req_beamstatus )
        if amodetagid is not None:
            req_amodetag = params._idtoamodetag[amodetagid]
            if params._amodetagtofull.has_key(req_amodetag):
                req_amodetag = params._amodetagtofull[req_amodetag]
            beamconditions.append( beam_result['machinemode']==req_amodetag )
        if targetegev is not None:
            beamconditions.append( beam_result['targetegev']==targetegev )
        beam_masks = andFilter(beam_result.size,beamconditions)        
        beam_result = beam_result[beam_masks]

        if not beam_result.size:
            log.debug('beam failed data selection, continue ',filehandle.filename)
            continue

        beam_time = np.column_stack((beam_result['runnum'],beam_result['lsnum'],beam_result['nbnum']))  
        if not np.array_equal(beam_time,selected_time):
            log.debug('beam time differs from tcds time, remake a narrower selection')
            runlsnbSeries = _make_runlsnb_Series( beam_time)

        #data selection

        data_coordinates = co[1][datatablename]
        data_table_handle = filehandle.get_node('/'+datatablename)

        data_result = dataFilter(data_table_handle,data_coordinates,field_dtypes=tbuilder.lumidata_typelist(),runlsRangeSelectSeries=None,runlsnbPointFilterSeries=runlsnbSeries)      

        for record in data_result:
            r = {}
            r['fillnum'] = record['fillnum']
            r['runnum'] = record['runnum']
            r['lsnum'] = lsnum = record['lsnum']
            nbnum = record['nbnum']
            r['timestampsec'] = record['timestampsec']
            tcds_masks = andFilter(tcds_result.size,[tcds_result['lsnum']==lsnum , tcds_result['nbnum']==nbnum])
            tcds_data = tcds_result[tcds_masks]
            r['deadtimefrac'] = tcds_data['deadfrac'][0]
            r['cmson'] = tcds_data['cmson'][0]
            r['numbxbeamactive'] = tcds_data['ncollidingbx'][0]
            beam_data = beam_result[ np.logical_and(beam_result['lsnum']==lsnum , beam_result['nbnum']==nbnum) ]            
            r['beamstatusid'] = params._beamstatustoid[beam_data['status'][0]]
            machinemode = beam_data['machinemode'][0]
            r['amodetag'] = params._fulltoamodetag[machinemode]
            r['targetegev'] = beam_data['targetegev']

            if datatype == 'best':
                r['delivered'] = record['delivered']
                r['recorded'] = record['recorded']
                r['avgpu'] = record['avgpu']
                r['datasource'] = record['provider']
                if withBX:
                    r['bxdeliveredblob'] = record['bxdelivered']
            elif datatype == 'raw':        
                r['avglumi'] = record['avgraw']             
                if withBX:
                    r['bxlumiblob'] = record['bxraw']
            else:
                r['avglumi'] = record['avg']
                if withBX:
                    r['bxlumiblob'] = record['bx']            
            yield r 
def _make_runlsnb_Series(runlsnbarray):
    '''
    Make pandas Series from [[run,ls,nb]] structure
    Input: 2-D structure [[run,ls,nb]]
    Output: pandas Series [(ls,nb), index=runs]
    '''
    runs = runlsnbarray[:,:1]
    lsnb = [tuple(x) for x in runlsnbarray[:,1:3]]
    return pd.Series(lsnb,index=runs.T[0])

if __name__=='__main__':
    tables = ['beam','tcds','hfetlumi']
    #runlsselect = pd.Series([[1340,1345],[1400,1500]], index=[327554,327554]) #pd.Series , index=runnum, value=[[lsmin,lsmax]]
    #runlsselect = pd.Series([[1,10],[14,15]], index=[327560,327560]) #pd.Series , index=runnum, value=[[lsmin,lsmax]]
    runlsselect = None

    #filenames = ['/home/zhen/data/7491/7491_327554_1812020507_1812020558.hd5','/home/zhen/data/7491/7491_327559_1812020558_1812020731.hd5','/home/zhen/data/7491/7491_327560_1812020731_1812021237.hd5']
    
    filenames =  ['/home/zhen/data/7491/7491_327560_1812020731_1812021237.hd5']
    lumitype = 'BEST'
    filehandles = open_validfiles(filenames,lumitype)    
    for result in resultIter(filehandles,lumitype,'best',fillmin=7491,fillmax=7491,runlsselect=runlsselect,beamstatusid=11,withBX=True):
        print result['fillnum'],result['runnum'],result['lsnum'],result['timestampsec'],result['beamstatusid'],result['cmson'],result['delivered'],result['recorded']
    lumitype = 'HFOC'
    for result in resultIter(filehandles,lumitype,'raw',fillmin=7491,fillmax=7491,runlsselect=runlsselect,beamstatusid=11,withBX=False):
        print result['fillnum'],result['runnum'],result['lsnum'],result['timestampsec'],result['beamstatusid'],result['cmson'],result['avglumi']

    [f.close() for f in filehandles] 
    

