#!/bin/env python

import sys
import ROOT

from SimGeneral.MixingModule.mix_2018_25ns_JuneProjectionFull18_PoissonOOTPU_cfi import *

# print mix.input.nbPileupEvents.probFunctionVariable
# print mix.input.nbPileupEvents.probValue

binMin = 0
binMax = 100

hist = ROOT.TH1D("pileup", "pileup", binMax-binMin, binMin, binMax)

for bin in mix.input.nbPileupEvents.probFunctionVariable:
    hist.SetBinContent(bin+1, mix.input.nbPileupEvents.probValue[bin])

file = ROOT.TFile.Open("pileup/pileup_mc_2018.root", "recreate")

hist.Write()
file.Write()
file.Close()
