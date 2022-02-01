#import pandas as pd
import numpy as np
import prettytable

_floatformatter='{:,.3f}'.format

#pd.set_option('display.max_columns', 4)
#pd.set_option('display.max_colwidth', 200)
#pd.set_option('display.max_rows', 1000)
#pd.set_option('display.width', 200)
#pd.set_option('display.float_format',_floatformatter)



_prettytable_style={
    'withheader':True,
    'align':'l',
    'maxwidth':80
}    


def add_row(row,fh=None,csvwriter=None,ptable=None):
    '''
    input: row=[]
    '''
    if fh and csvwriter:
        csvwriter.writerow(row)
    elif ptable:
        ptable.add_row(row)
    else:
        return
    
def show_table(ptable,style='tab'):
    if not ptable: return
    if style=='tab':
        print(ptable.get_string())
    elif style=='html':
        print(ptable.get_html_string())
    
def create_table(columns,**kwargs):
    '''
    create a prettytable instance
    https://code.google.com/p/prettytable/wiki/Tutorial
    '''
    ptable = prettytable.PrettyTable(columns)
    if kwargs.has_key('border'): ptable.border = kwargs['border']
    if kwargs.has_key('header'): ptable.header = kwargs['header']
    if kwargs.has_key('header_style'): ptable.header_style = kwargs['header_style']
    if kwargs.has_key('hrules'): ptable.hrules = kwargs['hrules']
    if kwargs.has_key('vrules'): ptable.hrules = kwargs['vrules']
    if kwargs.has_key('align'): ptable.align = kwargs['align']
    if kwargs.has_key('valign'): ptable.valign = kwargs['valign']
    if kwargs.has_key('int_format'): ptable.int_format = kwargs['int_format']
    if kwargs.has_key('float_format'): ptable.float_format = kwargs['float_format']
    if kwargs.has_key('padding_width'): ptable.padding_width = kwargs['padding_width']
    if kwargs.has_key('left_padding_width'): ptable.left_padding_width = kwargs['left_padding_width']
    if kwargs.has_key('right_padding_width'): ptable.right_padding_width = kwargs['right_padding_width']
    if kwargs.has_key('vertical_char'): ptable.vertical_char = kwargs['vertical_char']
    if kwargs.has_key('horizontal_char'): ptable.horizontal_char = kwargs['horizontal_char']
    if kwargs.has_key('junction_char'): ptable.junction_char = kwargs['junction_char']
    if kwargs.has_key('maxwidth'): ptable.max_width = kwargs['maxwidth'] 
    return ptable


def formatter_tuple((x,y)):
    if isinstance(x,float):
        x = _floatformatter(x)
    if isinstance(y,float):
        y = _floatformatter(y)
    return '%s:%s'%(x,y)

def listdf(df,npp=100, columns=None, formatters=None, index=False, justify='left', pagination=False):
    '''
    Inputs:
        df:         dataframe
        npp:        number of records per page (default=50)
        formatters: field formatter (default=None)
        index:      display row id (default=False)
    '''
    if not pagination:
        print df.to_string(columns=columns,formatters=formatters,index=index, justify=justify)
    return
    nrows, ncols = df.shape
    total_pages = nrows/npp + 1 
    rec_last_pg = nrows % npp # number of records in last page
    ptr = 0
    for i in xrange(total_pages):
        fromrow = ptr
        if i==(total_pages-1):
           torow = fromrow + rec_last_pg -1
        else:
           torow = fromrow + npp -1
        ptr = torow +1
        print df.ix[fromrow:torow,:].to_string(columns=columns,formatters=formatters,index=index, justify=justify)
        if i!=(total_pages-1):
            try: 
                raw_input("Press a key to continue or '^C' to break...")
            except KeyboardInterrupt:
                break

if __name__=='__main__':
    chunksize = 200
    #rowdef = np.dtype([('tagid',np.uint64),('tagname',object),('value',np.float32)])
    rowdef = np.dtype([('tagid','u8'),('tagname','O'),('value','f4')]) 
    mydf = np.empty( (chunksize,), dtype=rowdef )
    myformatter = {'value':_floatformatter}
    for i in xrange(chunksize):
        mydf['tagname'][i]='ab'
        mydf['tagid'][i]=i
        mydf['value'][i]=0.5*i
    #df = pd.DataFrame.from_records(mydf,index=None,columns=rowdef.names)
    #print rowdef.names
    #listdf(df,npp=30,formatters=myformatter,columns=['tagid','tagname'])

    
    create_table(['a','b'],border = True,align='l')

       
