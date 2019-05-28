from libPython.tnpClassUtils import tnpSample

### qll stat
base_path = 'data/'

TnP2016 = {
    ### MiniAOD TnP for IDs scale factors
    'DY_madgraph'          : tnpSample('DY_madgraph',
                                       base_path + 'RunIISummer16NanoAODv4_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root',
                                       isMC = True, nEvts =  -1 ),
    'DY_amcatnlo' : tnpSample('DY_amcatnlo', 
                                       base_path + 'RunIISummer16NanoAODv4_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8.root',
                                       isMC = True, nEvts =  -1 ),

    'data_Run2016B' : tnpSample('data_Run2016B' , base_path + 'Run2016B_SingleElectron_14Dec2018.root' , lumi = 5.75 ),
    'data_Run2016C' : tnpSample('data_Run2016C' , base_path + 'Run2016C_SingleElectron_14Dec2018.root' , lumi = 2.573 ),
    'data_Run2016D' : tnpSample('data_Run2016D' , base_path + 'Run2016D_SingleElectron_14Dec2018.root' , lumi = 4.242 ),
    'data_Run2016E' : tnpSample('data_Run2016E' , base_path + 'Run2016E_SingleElectron_14Dec2018.root' , lumi = 4.025 ),
    'data_Run2016F' : tnpSample('data_Run2016F' , base_path + 'Run2016F_SingleElectron_14Dec2018.root' , lumi = 3.105 ),
    'data_Run2016G' : tnpSample('data_Run2016G' , base_path + 'Run2016G_SingleElectron_14Dec2018.root' , lumi = 7.576 ),
    'data_Run2016H' : tnpSample('data_Run2016H' , base_path + 'Run2016H_SingleElectron_14Dec2018.root' , lumi = 8.651 ),

    }

TnP2017 = {
    ### MiniAOD TnP for IDs scale factors
    'DY_madgraph'          : tnpSample('DY_madgraph',
                                       base_path + 'RunIIFall17NanoAODv4_DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8.root',
                                       isMC = True, nEvts =  -1 ),
    'DY_amcatnlo' : tnpSample('DY_amcatnlo', 
                                       base_path + 'RunIIFall17NanoAODv4_DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8.root',
                                       isMC = True, nEvts =  -1 ),

    'data_Run2017B' : tnpSample('data_Run2017B' , base_path + 'Run2017B_SingleElectron_14Dec2018.root' , lumi = 4.794 ),
    'data_Run2017C' : tnpSample('data_Run2017C' , base_path + 'Run2017C_SingleElectron_14Dec2018.root' , lumi = 9.631 ),
    'data_Run2017D' : tnpSample('data_Run2017D' , base_path + 'Run2017D_SingleElectron_14Dec2018.root' , lumi = 4.248 ),
    'data_Run2017E' : tnpSample('data_Run2017E' , base_path + 'Run2017E_SingleElectron_14Dec2018.root' , lumi = 9.314 ),
    'data_Run2017F' : tnpSample('data_Run2017F' , base_path + 'Run2017F_SingleElectron_14Dec2018.root' , lumi = 13.539 ),

    }

TnP2018 = {
    ### MiniAOD TnP for IDs scale factors
    'DY_madgraph'          : tnpSample('DY_madgraph',
                                       base_path + 'RunIIAutumn18NanoAODv4_DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8.root',
                                       isMC = True, nEvts =  -1 ),
    'DY_amcatnlo' : tnpSample('DY_amcatnlo', 
                                       base_path + 'RunIIAutumn18NanoAODv4_DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8.root',
                                       isMC = True, nEvts =  -1 ),

    'data_Run2018A' : tnpSample('data_Run2018A' , base_path + 'Run2018A_EGamma_14Dec2018.root' , lumi = 13.705 ),
    'data_Run2018B' : tnpSample('data_Run2018B' , base_path + 'Run2018B_EGamma_14Dec2018.root' , lumi = 7.061 ),
    'data_Run2018C' : tnpSample('data_Run2018C' , base_path + 'Run2018C_EGamma_14Dec2018.root' , lumi = 6.891 ),
    'data_Run2018D' : tnpSample('data_Run2018D' , base_path + 'Run2018D_EGamma_14Dec2018.root' , lumi = 31.067 ),

    }
