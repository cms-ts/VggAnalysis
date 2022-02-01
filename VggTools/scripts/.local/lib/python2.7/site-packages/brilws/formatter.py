import numpy as np

#dec_prec = 9
#dec_prec_value = 10 ** (-1 * dec_prec)

def bxintensity(x):    
    return '{:d} {:.4e} {:.4e}'.format(int(x[0]),x[1],x[2])

def bitprescFormatter(x):
    bitname = x[0]
    prescval = x[1]
    return '%s/%d'%(bitname,prescval)

class Formatter:
    def __init__(self, formatstr, prec):
        self.formatstr = formatstr
        self.prec = prec
        self.dec_prec_value = None
        if self.formatstr=='f':
            self.dec_prec_value = 10 ** (-1 * self.prec)

    def lumi(self,x):
        if self.formatstr=='e':
            return self.lumiE(x)
        if abs(x)<self.dec_prec_value:
            return '0'    
        return '{:.{}f}'.format(float(x),self.prec)

    def bxlumi(self,x):
        if self.formatstr=='e':
            return self.bxlumiE(x)
        bxid = int(x[0])
        bxid_str = '{:d}'.format(bxid)
        vd = x[1]
        if abs(vd)<self.dec_prec_value:    
            return ' '.join([bxid_str,'0','0'])
        vd_str = '{:.{}f}'.format(vd,self.prec)
        vr = x[2]
        if abs(vr)<self.dec_prec_value:
            return ' '.join([bxid_str,vd_str,'0'])
        vr_str = '{:.{}f}'.format(vr,self.prec)
        return ' '.join([bxid_str,vd_str,vr_str])

    def lumiE(self,x):
        v_str = '{:.{}}e'.format(float(x),self.prec)
        return v_str

    def bxlumiE(self,x):
        bxid = int(x[0])
        vd = x[1]
        vr = x[2]
        bxid_str = '{:d}'.format(bxid)
        vd_str = '{:.{}}e'.format(vd,self.prec)
        vr_str = '{:.{}}e'.format(vr,self.prec)
        return ' '.join([bxid_str,vd_str,vr_str])
    
    @property
    def lumiunit_to_scalefactor(self):
        return {    
        '/kb':1.0e-09,
        '1e21/cm2':1.0e-09,
        'hz/kb':23.31*1.0e-09,
        '1e21/cm2s':23.31*1.0e-09,        

        '/b':1.0e-06,
        '1e24/cm2':1.0e-06,
        'hz/b':23.31*1.0e-06,
        '1e24/cm2s':23.31*1.0e-06,
    
        '/mb':1.0e-03,
        '1e27/cm2':1.0e-03,
        'hz/mb':23.31*1.0e-03,
        '1e27/cm2s':23.31*1.0e-03,
        
        '/ub':1.0,
        '1e30/cm2':1.0,
        'hz/ub':23.31,
        '1e30/cm2s':23.31,
        
        '/nb':1.0e3,
        '1e33/cm2':1.0e3,
        'hz/nb':23.31*1.0e3,
        '1e33/cm2s':23.31*1.0e3,
        
        '/pb':1.0e6,
        '1e36/cm2':1.0e6,
        'hz/nb':23.31*1.0e6,
        '1e36/cm2s':23.31*1.0e6,
        
        '/fb':1.0e9,
        '1e39/cm2':1.0e9,
        'hz/fb':23.31*1.0e9,
        '1e39/cm2s':23.31*1.0e9,
        
        '/ab':1.0e12,
        '1e42/cm2':1.0e12,
        'hz/ab':23.31*1.0e12,
        '1e42/cm2s':23.31*1.0e12,
         }

    def lumiunit(self,x,unitstr):
        if x.find('(/ub)')==-1: 
            return x
        return x.replace('(/ub)','(%s)'%unitstr)
    
#def lumiunit(x,scalefactor):
#    '''
#    return lumiunit according to scalefactor 
#    if x does not contain string /ub, do nothing
#    special if scalefactor is about 23, return hz/ub
#    else:
#        if scalefactor>=1.0e-03 and scalefactor<1, replace /ub with /mb
#        if scalefactor>=1 and scalefactor<1e3, keep /ub
#        if scalefactor>=1e3 and scalefactor<1e6, replace /ub with /nb
#        if scalefactor>=1e6 and scalefactor<1e9, replace /ub with /pb
#        if scalefactor>=1e9 and scalefactor<1e12, replace /ub with /fb
#        if scalefactor>=1e12 and scalefactor<1e15, replace /ub with /ab
#    '''
    
#    if x.find('(/ub)')==-1: return x    
#    if int(scalefactor) == 23: return x.replace('(/ub)','(hz/ub)')
#    if (scalefactor>=1.0e-09) and (scalefactor<1.0e-06): return x.replace('(/ub)','(/kb)')
#    if (scalefactor>=1.0e-06) and (scalefactor<1.0e-03): return x.replace('(/ub)','(/b)')
#    if (scalefactor>=1.0e-03) and (scalefactor<1.0): return x.replace('(/ub)','(/mb)')
#    if (scalefactor>=1.0) and (scalefactor<1.0e3): return x
#    if (scalefactor>=1.0e3) and (scalefactor<1.0e6): return x.replace('(/ub)','(/nb)')
#    if (scalefactor>=1.0e6) and (scalefactor<1.0e9): return x.replace('(/ub)','(/pb)')
#    if (scalefactor>=1.0e9) and (scalefactor<1.0e12): return x.replace('(/ub)','(/fb)')
#    if (scalefactor>=1.0e12) and (scalefactor<1.0e15): return x.replace('(/ub)','(/ab)')
#    return x

    def guesslumiUnit(self,inverseubval):
        '''
        input:
        float value in 1/ub
        output:
        printable value (value(float),unit(str)) unit in [1/kb,1/b,1/mb,1/ub,1/nb,1/pb,1/fb]
        '''
        denomitor = 1.0
        if inverseubval>=1.0e-09 and inverseubval<1.0e-06:
            denomitor=1.0e-09
            unitstring='/kb'
            return (float(inverseubval)/float(denomitor),unitstring)
        if inverseubval>=1.0e-06 and inverseubval<1.0e-03:
            denomitor=1.0e-06
            unitstring='/b'
            return (float(inverseubval)/float(denomitor),unitstring)
        if inverseubval>=1.0e-03 and inverseubval<1.0:
            denomitor=1.0e-03
            unitstring='/mb'
            return (float(inverseubval)/float(denomitor),unitstring)
        if inverseubval>=1.0 and inverseubval<1.0e3:
            unitstring='/ub'
            return (inverseubval,unitstring)
        if inverseubval>=1.0e3 and inverseubval<1.0e06:
            denomitor=1.0e3
            unitstring='/nb'
            return (float(inverseubval)/float(denomitor),unitstring)
        if inverseubval>=1.0e6 and inverseubval<1.0e9:
            denomitor=1.0e6
            unitstring='/pb'
            return (float(inverseubval)/float(denomitor),unitstring)
        if inverseubval>=1.0e9 and inverseubval<1.0e12:
            denomitor=1.0e9
            unitstring='/fb'
            return (float(inverseubval)/float(denomitor),unitstring)
        if inverseubval>=1.0e12 and inverseubval<1.0e15:
            denomitor=1.0e12
            unitstring='/ab'
            return (float(inverseubval)/float(denomitor),unitstring)
        return (float(inverseubval),denomitor,'/ub')



