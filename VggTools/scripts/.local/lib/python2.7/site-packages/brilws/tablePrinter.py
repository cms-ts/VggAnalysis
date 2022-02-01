#
# pretty table printer
# written by George Sakkis
# http://code.activestate.com/recipes/267662
#
import cStringIO,operator
def indent(rows,hasHeader=False,headerChar='-',delim=' | ',justify='center',
           separateRows=False,prefix='',postfix='',wrapfunc=lambda x:x):
    """
    Indents a table by column.
    - rows: A sequence of sequences of items, one sequence per row.
    - hadHeader: True if the first row consists of the column's names.
    - headerChar: Character to be used for the row separator line
    (if hasHeader==True or separateRows==True).
    - delim: The column delimiter.
    - justify: Determines how are data justified in their column.
    Valid values are 'left','right','center'.
    - separateRows: True if rows are to be separated by a line of 'headerChar's.
    - prefix: A string prepended to each printed row.
    - postfix: A string appended to each printed row.
    - wrapfunc: A function f(text) for wrapping text; each element in the table is first wrapped by this function.
    """
    #nested function
    #closure for breaking logical rows to physical, using wrapfunc
    def rowWrapper(row):
        newRows=[wrapfunc(item).split('\n') for item in row]
        #print 'newRows: ',newRows
        #print 'map result:  ',map(None,*newRows)
        #print 'rowwrapped: ',[[substr or '' for substr in item] for item in map(None,*newRows)]
        return [[substr or '' for substr in item] for item in map(None,*newRows)]
    # break each logical row into one or more physical ones
#    logicalRows = [rowWrapper(row) for row in rows]
    logicalRows = [(row,) for row in rows]#http://code.activestate.com/recipes/577615-table-indentation/
    # columns of physical rows
    columns = map(None,*reduce(operator.add,logicalRows))
    # get the maximum of each column by the string length of its items
    maxWidths = [max([len(str(item)) for item in column]) for column in columns]
    rowSeparator = headerChar * (len(prefix) + len(postfix) + sum(maxWidths) + len(delim)*(len(maxWidths)-1))
    # select the appropriate justify method
    justify = {'center':str.center,'right':str.rjust,'left':str.ljust}[justify.lower()]
    output=cStringIO.StringIO()
    if separateRows: print >> output,rowSeparator
    for physicalRows in logicalRows:
        for row in physicalRows:
            print >> output, prefix+delim.join([justify(str(item),width) for (item,width) in zip(row,maxWidths)])+postfix
        if separateRows or hasHeader: print >> output, rowSeparator; hasHeader=False
    return output.getvalue()

# word-wrap functions
# written by Mike Brown
# http://aspn.activestate.com/ASPN/Cookbook/Python/Recipe/148061
import math,re
def wrap_always(text, width):
    """
    A simple word-wrap function that wraps text on exactly width characters.
    It doesn't split the text in words.
    """
    return '\n'.join([ text[width*i:width*(i+1)] \
                       for i in xrange(int(math.ceil(1.*len(text)/width))) ])

def wrap_onspace(text,width):
    """
    A word-wrap function that preserves existing line breaks
    and most spaces in the text. Expects that existing line
    breaks are posix newlines (\n).
    """
    return reduce(lambda line, word, width=width: '%s%s%s' %
                  (line,
                   ' \n'[(len(line[line.rfind('\n')+1:])
                          + len(word.split('\n',1)[0]
                                ) >= width)],
                   word),
                  text.split(' ')
                  )
def wrap_onspace_strict(text, width):
    """
    Similar to wrap_onspace, but enforces the width constraint:
    words longer than width are split.
    """
    wordRegex = re.compile(r'\S{'+str(width)+r',}')
    return wrap_onspace(wordRegex.sub(lambda m: wrap_always(m.group(),width),text),width)

if __name__ == '__main__':
    labels=('First Name','Last Name','Age','Position')
    data="""John,Smith,24,Software Engineer
    Mary,Brohowski,23,Sales Manager
    Aristidis,Papageorgopoulos,28,Senior Reseacher"""
    rows=[row.strip().split(',') for row in data.splitlines()]
    print rows
    print 'without wrapping function\n'
    print 'raw input: ',[labels]+rows
    print indent([labels]+rows,hasHeader=True)
    width=10
    for wrapper in (wrap_always,wrap_onspace,wrap_onspace_strict):
        print 'Wrapping function: %s(x,width=%d)\n'%(wrapper.__name__,width)
        print indent([labels]+rows,hasHeader=True,separateRows=True,prefix='| ',postfix=' |',wrapfunc=lambda x: wrapper(x,width))

    lumidata=[\
        ('%-*s'%(8,'run'),'%-*s'%(8,'first'),'%-*s'%(8,'last'),'%-*s'%(10,'delivered'),'%-*s'%(10,'recorded'),'%-*s'%(20,'recorded\nmypathdfdafddafd')),\
        ['%d'%(132440),'%d'%(23),'%d'%(99),'%.2f'%(2.345),'%.2f'%(1.23),'%.2f'%(0.5678)],\
        ['%d'%(132442),'%d'%(1),'%d'%(20),'%.2f'%(2.345),'%.2f'%(1.23),'%.2f'%(0.5678)],\
        ['','%d'%(27),'%d'%(43),'%.2f'%(2.345),'%.2f'%(1.23),'%.2f'%(0.5678)]\
        ]
    lumiheader=[('%-*s'%(30,'Lumi Sections'),'%-*s'%(46,'Luminosity'))]
    headerwidth=46
    print indent(lumiheader,hasHeader=True,separateRows=False,prefix='| ',postfix='',wrapfunc=lambda x: wrap_always(x,headerwidth))
    lumifooter=[('%-*s'%(24,'189'),'%-*s'%(10,'17.89'),'%-*s'%(10,'16.1'),'%-*s'%(20,'3.47'))]
    width=20
    print indent(lumidata,hasHeader=True,separateRows=False,prefix='| ',postfix='',wrapfunc=lambda x: wrap_onspace_strict(x,width))
    print
    print indent(lumifooter,hasHeader=False,separateRows=True,prefix=' total: ',postfix='',delim=' | ',wrapfunc=lambda x: wrap_always(x,25))
