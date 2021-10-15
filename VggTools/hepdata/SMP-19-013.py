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
submission.add_record_id(1865855, "inspire")

#FIGURE 2 UPPER LEFT
fig2_ul = Table("Figure 2 (upper left)")
fig2_ul.description = "Distribution of the transverse momentum of the diphoton system for the $\mathrm{W}\gamma\gamma$ electron channel. The predicted yields are shown with their pre-fit normalisations. The observed data, the expected signal contribution and the background estimates are presented with error bars showing the corresponding statistical uncertainties."
fig2_ul.location = "Data from Figure 2 on Page 6 of the preprint"
fig2_ul.keywords["observables"] = ["Diphoton pT"]
fig2_ul.keywords["reactions"] = ["P P --> W GAMMA GAMMA --> ELECTRON NU GAMMA GAMMA"]

fig2_ul_in = np.loadtxt("input/fig2_ul.txt", skiprows = 1)

#diphoton pT
fig2_ul_pt = Variable("$p_T^{\gamma\gamma}$", is_independent = True, is_binned = False, units = "GeV")
fig2_ul_pt.values = fig2_ul_in[:,0]

#Data
fig2_ul_Data = Variable("Data", is_independent = False, is_binned = False, units = "Events per bin")
fig2_ul_Data.values = fig2_ul_in[:,1]
fig2_ul_Data_stat = Uncertainty("stat", is_symmetric = True)
fig2_ul_Data_stat.values = fig2_ul_in[:,2]
fig2_ul_Data.add_uncertainty(fig2_ul_Data_stat)

#Wgg
fig2_ul_Wgg = Variable("$\mathrm{W}\gamma\gamma$", is_independent = False, is_binned = False, units = "Events per bin")
fig2_ul_Wgg.values = fig2_ul_in[:,3]
fig2_ul_Wgg_stat = Uncertainty("stat", is_symmetric = True)
fig2_ul_Wgg_stat.values = fig2_ul_in[:,4]
fig2_ul_Wgg.add_uncertainty(fig2_ul_Wgg_stat)

#Misid. electrons
fig2_ul_Mele = Variable("Misid. electrons", is_independent = False, is_binned = False, units = "Events per bin")
fig2_ul_Mele.values = fig2_ul_in[:,5]
fig2_ul_Mele_stat = Uncertainty("stat", is_symmetric = True)
fig2_ul_Mele_stat.values = fig2_ul_in[:,6]
fig2_ul_Mele.add_uncertainty(fig2_ul_Mele_stat)

#Others
fig2_ul_Others = Variable("Others", is_independent = False, is_binned = False, units = "Events per bin")
fig2_ul_Others.values = fig2_ul_in[:,7]
fig2_ul_Others_stat = Uncertainty("stat", is_symmetric = True)
fig2_ul_Others_stat.values = fig2_ul_in[:,8]
fig2_ul_Others.add_uncertainty(fig2_ul_Others_stat)

#Misid. jets
fig2_ul_Mjets = Variable("Misid. jets", is_independent = False, is_binned = False, units = "Events per bin")
fig2_ul_Mjets.values = fig2_ul_in[:,9]
fig2_ul_Mjets_stat = Uncertainty("stat", is_symmetric = True)
fig2_ul_Mjets_stat.values = fig2_ul_in[:,10]
fig2_ul_Mjets.add_uncertainty(fig2_ul_Mjets_stat)

fig2_ul.add_variable(fig2_ul_pt)
fig2_ul.add_variable(fig2_ul_Data)
fig2_ul.add_variable(fig2_ul_Wgg)
fig2_ul.add_variable(fig2_ul_Mele)
fig2_ul.add_variable(fig2_ul_Others)
fig2_ul.add_variable(fig2_ul_Mjets)
fig2_ul.add_image("input/Figure_002-a.pdf")

submission.add_table(fig2_ul)

#FIGURE 2 UPPER RIGHT
fig2_ur = Table("Figure 2 (upper right)")
fig2_ur.description = "Distribution of the transverse momentum of the diphoton system for the $\mathrm{W}\gamma\gamma$ muon channel. The predicted yields are shown with their pre-fit normalisations. The observed data, the expected signal contribution and the background estimates are presented with error bars showing the corresponding statistical uncertainties."
fig2_ur.location = "Data from Figure 2 on Page 6 of the preprint"
fig2_ur.keywords["observables"] = ["Diphoton pT"]
fig2_ur.keywords["reactions"] = ["P P --> W GAMMA GAMMA --> MUON NU GAMMA GAMMA"]

fig2_ur_in = np.loadtxt("input/fig2_ur.txt", skiprows = 1)

#diphoton pT
fig2_ur_pt = Variable("$p_T^{\gamma\gamma}$", is_independent = True, is_binned = False, units = "GeV")
fig2_ur_pt.values = fig2_ur_in[:,0]

#Data
fig2_ur_Data = Variable("Data", is_independent = False, is_binned = False, units = "Events per bin")
fig2_ur_Data.values = fig2_ur_in[:,1]
fig2_ur_Data_stat = Uncertainty("stat", is_symmetric = True)
fig2_ur_Data_stat.values = fig2_ur_in[:,2]
fig2_ur_Data.add_uncertainty(fig2_ur_Data_stat)

#Wgg
fig2_ur_Wgg = Variable("$\mathrm{W}\gamma\gamma$", is_independent = False, is_binned = False, units = "Events per bin")
fig2_ur_Wgg.values = fig2_ur_in[:,3]
fig2_ur_Wgg_stat = Uncertainty("stat", is_symmetric = True)
fig2_ur_Wgg_stat.values = fig2_ur_in[:,4]
fig2_ur_Wgg.add_uncertainty(fig2_ur_Wgg_stat)

#Misid. electrons
fig2_ur_Mele = Variable("Misid. electrons", is_independent = False, is_binned = False, units = "Events per bin")
fig2_ur_Mele.values = fig2_ur_in[:,5]
fig2_ur_Mele_stat = Uncertainty("stat", is_symmetric = True)
fig2_ur_Mele_stat.values = fig2_ur_in[:,6]
fig2_ur_Mele.add_uncertainty(fig2_ur_Mele_stat)

#Others
fig2_ur_Others = Variable("Others", is_independent = False, is_binned = False, units = "Events per bin")
fig2_ur_Others.values = fig2_ur_in[:,7]
fig2_ur_Others_stat = Uncertainty("stat", is_symmetric = True)
fig2_ur_Others_stat.values = fig2_ur_in[:,8]
fig2_ur_Others.add_uncertainty(fig2_ur_Others_stat)

#Misid. jets
fig2_ur_Mjets = Variable("Misid. jets", is_independent = False, is_binned = False, units = "Events per bin")
fig2_ur_Mjets.values = fig2_ur_in[:,9]
fig2_ur_Mjets_stat = Uncertainty("stat", is_symmetric = True)
fig2_ur_Mjets_stat.values = fig2_ur_in[:,10]
fig2_ur_Mjets.add_uncertainty(fig2_ur_Mjets_stat)

fig2_ur.add_variable(fig2_ur_pt)
fig2_ur.add_variable(fig2_ur_Data)
fig2_ur.add_variable(fig2_ur_Wgg)
fig2_ur.add_variable(fig2_ur_Mele)
fig2_ur.add_variable(fig2_ur_Others)
fig2_ur.add_variable(fig2_ur_Mjets)
fig2_ur.add_image("input/Figure_002-b.pdf")

submission.add_table(fig2_ur)

#FIGURE 2 BOTTOM LEFT
fig2_bl = Table("Figure 2 (bottom left)")
fig2_bl.description = "Distribution of the transverse momentum of the diphoton system for the $\mathrm{Z}\gamma\gamma$ electron channel. The predicted yields are shown with their pre-fit normalisations. The observed data, the expected signal contribution and the background estimates are presented with error bars showing the corresponding statistical uncertainties."
fig2_bl.location = "Data from Figure 2 on Page 6 of the preprint"
fig2_bl.keywords["observables"] = ["Diphoton pT"]
fig2_bl.keywords["reactions"] = ["P P --> Z0 GAMMA GAMMA --> ELECTRON+ ELECTRON- GAMMA GAMMA"]

fig2_bl_in = np.loadtxt("input/fig2_bl.txt", skiprows = 1)

#diphoton pT
fig2_bl_pt = Variable("$p_T^{\gamma\gamma}$", is_independent = True, is_binned = False, units = "GeV")
fig2_bl_pt.values = fig2_bl_in[:,0]

#Data
fig2_bl_Data = Variable("Data", is_independent = False, is_binned = False, units = "Events per bin")
fig2_bl_Data.values = fig2_bl_in[:,1]
fig2_bl_Data_stat = Uncertainty("stat", is_symmetric = True)
fig2_bl_Data_stat.values = fig2_bl_in[:,2]
fig2_bl_Data.add_uncertainty(fig2_bl_Data_stat)

#Zgg
fig2_bl_Zgg = Variable("$\mathrm{Z}\gamma\gamma$", is_independent = False, is_binned = False, units = "Events per bin")
fig2_bl_Zgg.values = fig2_bl_in[:,3]
fig2_bl_Zgg_stat = Uncertainty("stat", is_symmetric = True)
fig2_bl_Zgg_stat.values = fig2_bl_in[:,4]
fig2_bl_Zgg.add_uncertainty(fig2_bl_Zgg_stat)

#Others
fig2_bl_Others = Variable("Others", is_independent = False, is_binned = False, units = "Events per bin")
fig2_bl_Others.values = fig2_bl_in[:,5]
fig2_bl_Others_stat = Uncertainty("stat", is_symmetric = True)
fig2_bl_Others_stat.values = fig2_bl_in[:,6]
fig2_bl_Others.add_uncertainty(fig2_bl_Others_stat)

#Misid. jets
fig2_bl_Mjets = Variable("Misid. jets", is_independent = False, is_binned = False, units = "Events per bin")
fig2_bl_Mjets.values = fig2_bl_in[:,7]
fig2_bl_Mjets_stat = Uncertainty("stat", is_symmetric = True)
fig2_bl_Mjets_stat.values = fig2_bl_in[:,8]
fig2_bl_Mjets.add_uncertainty(fig2_bl_Mjets_stat)

fig2_bl.add_variable(fig2_bl_pt)
fig2_bl.add_variable(fig2_bl_Data)
fig2_bl.add_variable(fig2_bl_Zgg)
fig2_bl.add_variable(fig2_bl_Others)
fig2_bl.add_variable(fig2_bl_Mjets)
fig2_bl.add_image("input/Figure_002-c.pdf")

submission.add_table(fig2_bl)

#FIGURE 2 BOTTOM RIGHT
fig2_br = Table("Figure 2 (bottom right)")
fig2_br.description = "Distribution of the transverse momentum of the diphoton system for the $\mathrm{Z}\gamma\gamma$ muon channel. The predicted yields are shown with their pre-fit normalisations. The observed data, the expected signal contribution and the background estimates are presented with error bars showing the corresponding statistical uncertainties."
fig2_br.location = "Data from Figure 2 on Page 6 of the preprint"
fig2_br.keywords["observables"] = ["Diphoton pT"]
fig2_br.keywords["reactions"] = ["P P --> Z0 GAMMA GAMMA --> MUON+ MUON- GAMMA GAMMA"]

fig2_br_in = np.loadtxt("input/fig2_br.txt", skiprows = 1)

#diphoton pT
fig2_br_pt = Variable("$p_T^{\gamma\gamma}$", is_independent = True, is_binned = False, units = "GeV")
fig2_br_pt.values = fig2_br_in[:,0]

#Data
fig2_br_Data = Variable("Data", is_independent = False, is_binned = False, units = "Events per bin")
fig2_br_Data.values = fig2_br_in[:,1]
fig2_br_Data_stat = Uncertainty("stat", is_symmetric = True)
fig2_br_Data_stat.values = fig2_br_in[:,2]
fig2_br_Data.add_uncertainty(fig2_br_Data_stat)

#Zgg
fig2_br_Zgg = Variable("$\mathrm{Z}\gamma\gamma$", is_independent = False, is_binned = False, units = "Events per bin")
fig2_br_Zgg.values = fig2_br_in[:,3]
fig2_br_Zgg_stat = Uncertainty("stat", is_symmetric = True)
fig2_br_Zgg_stat.values = fig2_br_in[:,4]
fig2_br_Zgg.add_uncertainty(fig2_br_Zgg_stat)

#Others
fig2_br_Others = Variable("Others", is_independent = False, is_binned = False, units = "Events per bin")
fig2_br_Others.values = fig2_br_in[:,5]
fig2_br_Others_stat = Uncertainty("stat", is_symmetric = True)
fig2_br_Others_stat.values = fig2_br_in[:,6]
fig2_br_Others.add_uncertainty(fig2_br_Others_stat)

#Misid. jets
fig2_br_Mjets = Variable("Misid. jets", is_independent = False, is_binned = False, units = "Events per bin")
fig2_br_Mjets.values = fig2_br_in[:,7]
fig2_br_Mjets_stat = Uncertainty("stat", is_symmetric = True)
fig2_br_Mjets_stat.values = fig2_br_in[:,8]
fig2_br_Mjets.add_uncertainty(fig2_br_Mjets_stat)

fig2_br.add_variable(fig2_br_pt)
fig2_br.add_variable(fig2_br_Data)
fig2_br.add_variable(fig2_br_Zgg)
fig2_br.add_variable(fig2_br_Others)
fig2_br.add_variable(fig2_br_Mjets)
fig2_br.add_image("input/Figure_002-d.pdf")

submission.add_table(fig2_br)

#FIGURE 3 LEFT
fig3_l = Table("Figure 3 (left)")
fig3_l.description = "Distribution of the transverse momentum of the diphoton system, obtained in the control region enriched in misidentified photons for the $\mathrm{W}\gamma\gamma$ electron channel. The predicted yields are shown with their pre-fit normalisations. The observed data, the expected signal contribution and the background estimates are presented with error bars showing the corresponding statistical uncertainties."
fig3_l.location = "Data from Figure 3 on Page 7 of the preprint"
fig3_l.keywords["observables"] = ["Diphoton pT"]
fig3_l.keywords["reactions"] = ["P P --> W GAMMA GAMMA --> ELECTRON NU GAMMA GAMMA"]

fig3_l_in = np.loadtxt("input/fig3_l.txt", skiprows = 1)

#diphoton pT
fig3_l_pt = Variable("$p_T^{\gamma\gamma}$", is_independent = True, is_binned = False, units = "GeV")
fig3_l_pt.values = fig3_l_in[:,0]

#Data
fig3_l_Data = Variable("Data", is_independent = False, is_binned = False, units = "Events per bin")
fig3_l_Data.values = fig3_l_in[:,1]
fig3_l_Data_stat = Uncertainty("stat", is_symmetric = True)
fig3_l_Data_stat.values = fig3_l_in[:,2]
fig3_l_Data.add_uncertainty(fig3_l_Data_stat)

#Wgg
fig3_l_Wgg = Variable("$\mathrm{W}\gamma\gamma$", is_independent = False, is_binned = False, units = "Events per bin")
fig3_l_Wgg.values = fig3_l_in[:,3]
fig3_l_Wgg_stat = Uncertainty("stat", is_symmetric = True)
fig3_l_Wgg_stat.values = fig3_l_in[:,4]
fig3_l_Wgg.add_uncertainty(fig3_l_Wgg_stat)

#Misid. electrons
fig3_l_Mele = Variable("Misid. electrons", is_independent = False, is_binned = False, units = "Events per bin")
fig3_l_Mele.values = fig3_l_in[:,5]
fig3_l_Mele_stat = Uncertainty("stat", is_symmetric = True)
fig3_l_Mele_stat.values = fig3_l_in[:,6]
fig3_l_Mele.add_uncertainty(fig3_l_Mele_stat)

#Others
fig3_l_Others = Variable("Others", is_independent = False, is_binned = False, units = "Events per bin")
fig3_l_Others.values = fig3_l_in[:,7]
fig3_l_Others_stat = Uncertainty("stat", is_symmetric = True)
fig3_l_Others_stat.values = fig3_l_in[:,8]
fig3_l_Others.add_uncertainty(fig3_l_Others_stat)

#Misid. jets
fig3_l_Mjets = Variable("Misid. jets", is_independent = False, is_binned = False, units = "Events per bin")
fig3_l_Mjets.values = fig3_l_in[:,9]
fig3_l_Mjets_stat = Uncertainty("stat", is_symmetric = True)
fig3_l_Mjets_stat.values = fig3_l_in[:,10]
fig3_l_Mjets.add_uncertainty(fig3_l_Mjets_stat)

fig3_l.add_variable(fig3_l_pt)
fig3_l.add_variable(fig3_l_Data)
fig3_l.add_variable(fig3_l_Wgg)
fig3_l.add_variable(fig3_l_Mele)
fig3_l.add_variable(fig3_l_Others)
fig3_l.add_variable(fig3_l_Mjets)
fig3_l.add_image("input/Figure_003-a.pdf")

submission.add_table(fig3_l)

#FIGURE 3 RIGHT
fig3_r = Table("Figure 3 (right)")
fig3_r.description = "Distribution of the transverse momentum of the diphoton system, obtained in the control region enriched in misidentified photons for the $\mathrm{Z}\gamma\gamma$ electron channel. The predicted yields are shown with their pre-fit normalisations. The observed data, the expected signal contribution and the background estimates are presented with error bars showing the corresponding statistical uncertainties."
fig3_r.location = "Data from Figure 3 on Page 7 of the preprint"
fig3_r.keywords["observables"] = ["Diphoton pT"]
fig3_r.keywords["reactions"] = ["P P --> Z0 GAMMA GAMMA --> ELECTRON+ ELECTRON- GAMMA GAMMA"]

fig3_r_in = np.loadtxt("input/fig3_r.txt", skiprows = 1)

#diphoton pT
fig3_r_pt = Variable("$p_T^{\gamma\gamma}$", is_independent = True, is_binned = False, units = "GeV")
fig3_r_pt.values = fig3_r_in[:,0]

#Data
fig3_r_Data = Variable("Data", is_independent = False, is_binned = False, units = "Events per bin")
fig3_r_Data.values = fig3_r_in[:,1]
fig3_r_Data_stat = Uncertainty("stat", is_symmetric = True)
fig3_r_Data_stat.values = fig3_r_in[:,2]
fig3_r_Data.add_uncertainty(fig3_r_Data_stat)

#Zgg
fig3_r_Zgg = Variable("$\mathrm{Z}\gamma\gamma$", is_independent = False, is_binned = False, units = "Events per bin")
fig3_r_Zgg.values = fig3_r_in[:,3]
fig3_r_Zgg_stat = Uncertainty("stat", is_symmetric = True)
fig3_r_Zgg_stat.values = fig3_r_in[:,4]
fig3_r_Zgg.add_uncertainty(fig3_r_Zgg_stat)

#Others
fig3_r_Others = Variable("Others", is_independent = False, is_binned = False, units = "Events per bin")
fig3_r_Others.values = fig3_r_in[:,5]
fig3_r_Others_stat = Uncertainty("stat", is_symmetric = True)
fig3_r_Others_stat.values = fig3_r_in[:,6]
fig3_r_Others.add_uncertainty(fig3_r_Others_stat)

#Misid. jets
fig3_r_Mjets = Variable("Misid. jets", is_independent = False, is_binned = False, units = "Events per bin")
fig3_r_Mjets.values = fig3_r_in[:,7]
fig3_r_Mjets_stat = Uncertainty("stat", is_symmetric = True)
fig3_r_Mjets_stat.values = fig3_r_in[:,8]
fig3_r_Mjets.add_uncertainty(fig3_r_Mjets_stat)

fig3_r.add_variable(fig3_r_pt)
fig3_r.add_variable(fig3_r_Data)
fig3_r.add_variable(fig3_r_Zgg)
fig3_r.add_variable(fig3_r_Others)
fig3_r.add_variable(fig3_r_Mjets)
fig3_r.add_image("input/Figure_003-b.pdf")

submission.add_table(fig3_r)

#XSECS
table_xsecs = Table("Table 1")
table_xsecs.description = "The measured $\mathrm{W}\gamma\gamma$ and $\mathrm{Z}\gamma\gamma$ fiducial cross sections and corresponding theoretical predictions from MadGraph5_aMC@NLO. The measured yields in the electron and muon channels are extrapolated to a common fiducial phase space determined from simulated signal events at the generated particle level. Generated particles are considered stable if their mean decay length is larger than $1\,\mathrm{cm}$. Generated leptons are required to have a $\mathrm{p}_\mathrm{t}>15\,\mathrm{GeV}$ and $|\eta|<2.5$. The momenta of photons in a cone of $\Delta R=0.1$, the same cone size as the one applied to reconstructed data, are added to the charged lepton momentum to correct for final-state radiation. Generated photons are required to have $\mathrm{p}_\mathrm{t}>15\,\mathrm{GeV}$ and $|\eta|<2.5$. Additionally, the candidate photons are required to have no selected leptons or photons in a cone of radius $\Delta R=0.4$ and no other stable particles, apart from photons and neutrinos, in a cone of radius $\Delta R=0.1$. Events are then selected in the $\mathrm{W}\gamma\gamma$ channel by requiring exactly one electron (muon) with $\mathrm{p}_\mathrm{t}>30\,\mathrm{GeV}$ and at least two photons with $\mathrm{p}_\mathrm{t}>20\,\mathrm{GeV}$. Events are selected in the $\mathrm{Z}\gamma\gamma$ channel by requiring two electrons (muons), at least one of them with $\mathrm{p}_\mathrm{t}>30\,\mathrm{GeV}$, and not less than two photons, each of them with $\mathrm{p}_\mathrm{t}>20\,\mathrm{GeV}$. Additionally, the invariant mass of the dilepton system is required to be $m_{\ell\ell}>55\,\mathrm{GeV}$."
table_xsecs.location = "Data from Page 10 of preprint"
table_xsecs.keywords["reactions"] = ["P P --> W GAMMA GAMMA --> ELECTRON NU GAMMA GAMMA","P P --> W GAMMA GAMMA --> MUON NU GAMMA GAMMA", "P P --> W GAMMA GAMMA --> LEPTON NU GAMMA GAMMA","P P --> Z0 GAMMA GAMMA --> ELECTRON+ ELECTRON- GAMMA GAMMA", "P P --> Z0 GAMMA GAMMA --> MUON+ MUON- GAMMA GAMMA", "P P --> Z0 GAMMA GAMMA --> LEPTON+ LEPTON- GAMMA GAMMA"]

data_xsecs_meas = np.loadtxt("input/xsecs_meas.txt")
data_xsecs_theo = np.loadtxt("input/xsecs_theo.txt")

channel = Variable("Channel", is_independent = True, is_binned = False, units = "")
channel.values = ["$\mathrm{e}\\nu\gamma\gamma$", "$\\mu\\nu\gamma\gamma$", "$\ell\\nu\gamma\gamma$", "$\mathrm{e}\mathrm{e}\gamma\gamma$", "$\\mu\\mu\gamma\gamma$","$\ell\ell\gamma\gamma$"]

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
table_limits.description = "Expected and observed 95% confidence level intervals for the different anomalous couplings parameters in both the $\ell\\nu\gamma\gamma$ and $\ell\ell\gamma\gamma$ channels. All parameters are fixed to their SM values except the one that is fitted. No unitarity regularisation scheme is applied. Intervals with a NAN value are not measured in the corresponding channels."
table_limits.location = "Data from Table 3 on Page 12 of the preprint"
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
