class ParametersObject (object):
    '''
    collection of constants used in lumi related calculation
    '''
    def __init__ (self):
        self._NBX            = 3564  # number beam crossings
        self._numorbit       = 2**18 # 262144
        self._minBiasXsec    = 80000.0 # default minBiasXsec unit: microbarn
        self._rotationRate    = 11245.613 # for 3.5 TeV Beam energy
        self._rotationTime    = 1 / self._rotationRate
        self._lumiSectionLen  = self._numorbit * self._rotationTime
        
    @property
    def minbias(self):
        return self._minBiasXsec

    @property
    def NBX(self):
        return self._NBX

    @property
    def numorbit(self):
        return self._numorbit

    @property
    def lslengthsec(self):
        '''
        Calculate lslength in sec from number of orbit and BX
        '''
        return self._lumiSectionLen 

    def setRotationRate(self,rate):
        '''
        update the default LHC orbit frequency
        Single beam energy of 450GeV:  11245.589
        Single beam energy of 3.5TeV: 11245.613
        '''
        self._rotationRate =rate
        
    def setNumOrbit(self,numorbit):
        self._numorbit=numorbit
        
    def setNumBx(self,numbx):
        '''
        update the default number of BX
        '''
        self._NBX = numbx
        
    def calculateTimeParameters(self):
        '''Given the rotation rate, calculate lumi section length and
        rotation time.  This should be called if rotationRate is
        updated.
        '''
        self._rotationTime    = 1 / self._rotationRate
        self._lumiSectionLen  = self._numorbit * self._rotationTime

    def avgpu(self,avglumi,ncollidingbx,minbias):
        '''
        avglumi hz/ub
        minbias ub
        '''
        if not ncollidingbx or not avglumi:
            return 0
        return avglumi/float(ncollidingbx)*float(minbias)/self._rotationRate
    
#=======================================================
#   Unit Test
#=======================================================
if __name__ == "__main__":
    p=ParametersObject()
    print p.lslengthsec
    print p.minBiasXsec
    print p.NBX
    print p.numorbit
