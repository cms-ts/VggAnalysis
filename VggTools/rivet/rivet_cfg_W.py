import FWCore.ParameterSet.Config as cms

process = cms.Process('RIVET')

# import standard configurations
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load("GeneratorInterface.RivetInterface.genParticles2HepMC_cff")
process.load("GeneratorInterface.RivetInterface.rivetAnalyzer_cfi")
process.load("GeneratorInterface.GenFilters.LHEGenericFilter_cfi")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.MessageLogger.cerr.threshold = 'INFO'
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

# input source
process.source = cms.Source("PoolSource",
    # test run over WGG MiniAOD signal sample               
    fileNames = cms.untracked.vstring('/store/mc/RunIIAutumn18MiniAOD/WGG_5f_TuneCP5_13TeV-amcatnlo-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/20000/93432D3D-2FE6-294F-9B04-83CBF5B7BFAE.root')
)

# convert CMS generator info into HepMC format
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load("GeneratorInterface.RivetInterface.genParticles2HepMC_cfi")
#process.genParticles2HepMC.genParticles = cms.InputTag("genParticles")
process.genParticles2HepMC.genParticles = cms.InputTag("finalGenParticles")

# NanoAOD pruner
process.finalGenParticles = cms.EDProducer("GenParticlePruner",
  src = cms.InputTag("genParticles"),
  select = cms.vstring(
    "drop *",
    "keep++ abs(pdgId) == 15 & (pt > 15 ||  isPromptDecayed() )",#  keep full tau decay chain for some taus
    #"drop status==1 & pt < 1", #drop soft stable particle in tau decay
    "keep+ abs(pdgId) == 15 ",  #  keep first gen decay product for all tau
    "+keep pdgId == 22 && status == 1 && (pt > 10 || isPromptFinalState())", # keep gamma above 10 GeV (or all prompt) and its first parent
    "+keep abs(pdgId) == 11 || abs(pdgId) == 13 || abs(pdgId) == 15", #keep leptons, with at most one mother back in the history
#
#    "drop abs(pdgId)= 2212 && abs(pz) > 1000", #drop LHC protons accidentally added by previous keeps
    "keep abs(pdgId)= 2212 && abs(pz) > 1000", #drop LHC protons accidentally added by previous keeps
#
    "keep (400 < abs(pdgId) < 600) || (4000 < abs(pdgId) < 6000)", #keep all B and C hadrons
    "keep abs(pdgId) == 12 || abs(pdgId) == 14 || abs(pdgId) == 16",   # keep neutrinos
    "keep status == 3 || (status > 20 && status < 30)", #keep matrix element summary
    "keep isHardProcess() ||  fromHardProcessDecayed()  || fromHardProcessFinalState() || (statusFlags().fromHardProcess() && statusFlags().isLastCopy())",  #keep event summary based on status flags
    "keep  (status > 70 && status < 80 && pt > 15) ", # keep high pt partons right before hadronization
    "keep abs(pdgId) == 23 || abs(pdgId) == 24 || abs(pdgId) == 25 || abs(pdgId) == 37 ",   # keep VIP(articles)s
    #"keep abs(pdgId) == 310 && abs(eta) < 2.5 && pt > 1 ",                                                     # keep K0
    "keep (1000001 <= abs(pdgId) <= 1000039 ) || ( 2000001 <= abs(pdgId) <= 2000015)", #keep SUSY fiction particles
  )
)

# Rivet analysis
process.rivetAnalyzer.HepMCCollection = cms.InputTag("genParticles2HepMC:unsmeared")
process.rivetAnalyzer.AnalysisNames = cms.vstring('CMS_SMP_19_068')
#process.rivetAnalyzer.AnalysisNames = cms.vstring('CMS_SMP_19_013_W')
process.rivetAnalyzer.OutputFile = cms.string('outWGGanalysis.yoda')

process.lheGenericFilter.src = cms.InputTag("externalLHEProducer")
process.lheGenericFilter.NumRequired = cms.int32(0)
process.lheGenericFilter.ParticleID = cms.vint32(15)
process.lheGenericFilter.AcceptLogic = cms.string("GT")

# drop tau decays
process.newFilter = cms.EDFilter("PythiaFilter",
  moduleLabel = cms.untracked.string("genParticles2HepMC"),
  ParticleID = cms.untracked.int32(15),
  MotherID = cms.untracked.int32(24)
)

# required for MiniAOD samples
#process.load("GeneratorInterface.RivetInterface.mergedGenParticles_cfi")
#process.finalGenParticles.src = cms.InputTag("mergedGenParticles")

process.rivet_step = cms.Path(
#  process.mergedGenParticles*
  process.finalGenParticles*
  process.genParticles2HepMC*
  ~process.newFilter*
  process.rivetAnalyzer
)

process.schedule = cms.Schedule(process.rivet_step)
