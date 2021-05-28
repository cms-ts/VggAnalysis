from __future__ import print_function
import os
import numpy as np
from hepdata_lib import Submission, Table, Variable, Uncertainty

#INITIALIZE
submission = Submission()

#ABSTRACT
submission.read_abstract("input/abstract.txt")
submission.add_link("Webpage with all figures and tables", "https://cms-results.web.cern.ch/cms-results/public-results/publications/SMP-19-013/")
submission.add_link("arXiv", "http://arxiv.org/abs/arXiv:2105.12780")
submission.add_record_id(123456, "inspire") #FIXME

#XSECS
table_xsecs = Table("Table 1")
table_xsecs.description = "The measured $\mathrm{W}\gamma\gamma$ and $\mathrm{Z}\gamma\gamma$ fiducial cross sections and corresponding theoretical predictions from MadGraph5_aMC@NLO. The measured yields in the electron and muon channels are extrapolated to a common fiducial phase space determined from simulated signal events at the generated particle level. Generated particles are considered stable if their mean decay length is larger than $1\,\mathrm{cm}$. Generated leptons are required to have a $\mathrm{p}_\mathrm{t}>15\,\mathrm{GeV}$ and $|\eta|<2.5$. The momenta of photons in a cone of $\Delta R=0.1$, the same cone size as the one applied to reconstructed data, are added to the charged lepton momentum to correct for final-state radiation. Generated photons are required to have $\mathrm{p}_\mathrm{t}>15\,\mathrm{GeV}$ and $|\eta|<2.5$. Additionally, the candidate photons are required to have no selected leptons or photons in a cone of radius $\Delta R=0.4$ and no other stable particles, apart from photons and neutrinos, in a cone of radius $\Delta R=0.1$. Events are then selected in the $\mathrm{W}\gamma\gamma$ channel by requiring exactly one electron (muon) with $\mathrm{p}_\mathrm{t}>30\,\mathrm{GeV}$ and at least two photons with $\mathrm{p}_\mathrm{t}>20\,\mathrm{GeV}$. Events are selected in the $\mathrm{Z}\gamma\gamma$ channel by requiring two electrons (muons), at least one of them with $\mathrm{p}_\mathrm{t}>30\,\mathrm{GeV}$, and not less than two photons, each of them with $\mathrm{p}_\mathrm{t}>20\,\mathrm{GeV}$. Additionally, the invariant mass of the dilepton system is required to be $m_{\ell\ell}>55\,\mathrm{GeV}$."
table_xsecs.location = "Data from Page 10 of preprint"
table_xsecs.keywords["reactions"] = ["P P --> W GAMMA GAMMA --> LEPTON NU GAMMA GAMMA", "P P --> Z0 GAMMA GAMMA --> LEPTON+ LEPTON- GAMMA GAMMA"]

data_xsecs_meas = np.loadtxt("input/xsecs_meas.txt")
data_xsecs_theo = np.loadtxt("input/xsecs_theo.txt")

channel = Variable("Channel", is_independent = True, is_binned = False, units = "")
channel.values = ["$\ell\\nu\gamma\gamma$", "$\ell\ell\gamma\gamma$"]

xsecs_meas = Variable("SIG (fiducial)", is_independent = False, is_binned = False, units = "FB")
xsecs_meas.values = data_xsecs_meas[:,0]

xsecs_meas_stat = Uncertainty("stat", is_symmetric = False)
xsecs_meas_stat.values = zip(data_xsecs_meas[:,1], data_xsecs_meas[:,2])
xsecs_meas.add_uncertainty(xsecs_meas_stat)

xsecs_meas_syst = Uncertainty("syst", is_symmetric = False)
xsecs_meas_syst.values = zip(data_xsecs_meas[:,3], data_xsecs_meas[:,4])
xsecs_meas.add_uncertainty(xsecs_meas_syst)

xsecs_meas_pdf = Uncertainty("PDF + scale")
xsecs_meas_pdf.values = [float(x) for x in data_xsecs_meas[:,5]]
xsecs_meas.add_uncertainty(xsecs_meas_pdf)

xsecs_meas.add_qualifier("SQRT(S)", 13, "TeV")

xsecs_theo = Variable("SIG (theory)", is_independent = False, is_binned = False, units = "FB")
xsecs_theo.values = data_xsecs_theo[:,0]

xsecs_theo_stat = Uncertainty("stat", is_symmetric = True)
xsecs_theo_stat.values = [float(x) for x in data_xsecs_theo[:,1]]
xsecs_theo.add_uncertainty(xsecs_theo_stat)

xsecs_theo_pdf = Uncertainty("PDF + scale", is_symmetric = True)
xsecs_theo_pdf.values = [float(x) for x in data_xsecs_theo[:,2]] 
xsecs_theo.add_uncertainty(xsecs_theo_pdf)

xsecs_theo.add_qualifier("SQRT(S)", 13, "TeV")

table_xsecs.add_variable(channel)
table_xsecs.add_variable(xsecs_meas)
table_xsecs.add_variable(xsecs_theo)

submission.add_table(table_xsecs)

#LIMITS
table_limits = Table("Table 2") 
table_limits.description = "Expected and observed 95% confidence level intervals for the different anomalous couplings parameters in both the $\ell\\nu\gamma\gamma$ and $\ell\ell\gamma\gamma$ channels. All parameters are fixed to their SM values except the one that is fitted. No unitarity regularisation scheme is applied."
table_limits.location = "Data from Table 3 of preprint"
table_limits.keywords["reactions"] = ["P P --> W GAMMA GAMMA --> LEPTON NU GAMMA GAMMA", "P P --> Z0 GAMMA GAMMA --> LEPTON+ LEPTON- GAMMA GAMMA"]

data_limits = np.loadtxt("input/limits.txt")

operator = Variable("Operator", is_independent = True, is_binned = False, units = "")
operator.values = ["$f_{\mathrm{M}2}/\Lambda^4$", "$f_{\mathrm{M}3}/\Lambda^4$", "$f_{\mathrm{T}0}/\Lambda^4$", "$f_{\mathrm{T}1}/\Lambda^4$", "$f_{\mathrm{T}2}/\Lambda^4$", "$f_{\mathrm{T}5}/\Lambda^4$", "$f_{\mathrm{T}6}/\Lambda^4$", "$f_{\mathrm{T}7}/\Lambda^4$", "$f_{\mathrm{T}8}/\Lambda^4$", "$f_{\mathrm{T}9}/\Lambda^4$"]

exp_Wgg_neg = Variable("Limits (TeV$^{-4}$)", is_independent = False, is_binned = False, units = "")
exp_Wgg_neg.values = data_limits[:,0]
exp_Wgg_neg.add_qualifier("Limits", "Expected $\ell\\nu\gamma\gamma$ negative")
exp_Wgg_neg.add_qualifier("SQRT(S)", 13, "TeV")

exp_Wgg_pos = Variable("Limits (TeV$^{-4}$)", is_independent = False, is_binned = False, units = "")
exp_Wgg_pos.values = data_limits[:,1]
exp_Wgg_pos.add_qualifier("Limits", "Expected $\ell\\nu\gamma\gamma$ positive")
exp_Wgg_pos.add_qualifier("SQRT(S)", 13, "TeV")

obs_Wgg_neg = Variable("Limits (TeV$^{-4}$)", is_independent = False, is_binned = False, units = "")
obs_Wgg_neg.values = data_limits[:,2]
obs_Wgg_neg.add_qualifier("Limits", "Observed $\ell\\nu\gamma\gamma$ negative")
obs_Wgg_neg.add_qualifier("SQRT(S)", 13, "TeV")

obs_Wgg_pos = Variable("Limits (TeV$^{-4}$)", is_independent = False, is_binned = False, units = "")
obs_Wgg_pos.values = data_limits[:,3]
obs_Wgg_pos.add_qualifier("Limits", "Observed $\ell\\nu\gamma\gamma$ positive")
obs_Wgg_pos.add_qualifier("SQRT(S)", 13, "TeV")

exp_Zgg_neg = Variable("Limits (TeV$^{-4}$)", is_independent = False, is_binned = False, units = "")
exp_Zgg_neg.values = data_limits[:,4]
exp_Zgg_neg.add_qualifier("Limits", "Expected $\ell\ell\gamma\gamma$ negative")
exp_Zgg_neg.add_qualifier("SQRT(S)", 13, "TeV")

exp_Zgg_pos = Variable("Limits (TeV$^{-4}$)", is_independent = False, is_binned = False, units = "")
exp_Zgg_pos.values = data_limits[:,5]
exp_Zgg_pos.add_qualifier("Limits", "Expected $\ell\ell\gamma\gamma$ positive")
exp_Zgg_pos.add_qualifier("SQRT(S)", 13, "TeV")

obs_Zgg_neg = Variable("Limits (TeV$^{-4}$)", is_independent = False, is_binned = False, units = "")
obs_Zgg_neg.values = data_limits[:,6]
obs_Zgg_neg.add_qualifier("Limits", "Observed $\ell\ell\gamma\gamma$ negative")
obs_Zgg_neg.add_qualifier("SQRT(S)", 13, "TeV")

obs_Zgg_pos = Variable("Limits (TeV$^{-4}$)", is_independent = False, is_binned = False, units = "")
obs_Zgg_pos.values = data_limits[:,7]
obs_Zgg_pos.add_qualifier("Limits", "Observed $\ell\ell\gamma\gamma$ positive")
obs_Zgg_pos.add_qualifier("SQRT(S)", 13, "TeV")

table_limits.add_variable(operator)
table_limits.add_variable(exp_Wgg_neg)
table_limits.add_variable(exp_Wgg_pos)
table_limits.add_variable(obs_Wgg_neg)
table_limits.add_variable(obs_Wgg_pos)
table_limits.add_variable(exp_Zgg_neg)
table_limits.add_variable(exp_Zgg_pos)
table_limits.add_variable(obs_Zgg_neg)
table_limits.add_variable(obs_Zgg_pos)

submission.add_table(table_limits)

#FINALIZE
for table in submission.tables:
  table.keywords["cmenergies"] = [13000]

outdir = "HEPData-SMP-19-013"
os.system("rm -r {0}/*".format(outdir))
submission.create_files(outdir)

print ("Done")
print ("HEPData sandbox: https://www.hepdata.net/record/sandbox/1617909075")
