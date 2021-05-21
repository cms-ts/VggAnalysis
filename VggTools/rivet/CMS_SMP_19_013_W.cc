#include "Rivet/Analysis.hh"
#include "Rivet/Projections/FinalState.hh"
#include "Rivet/Particle.hh"
#include "Rivet/Particle.fhh"
#include "Rivet/Event.hh"
#include "Rivet/Projections/FastJets.hh"
#include "Rivet/Projections/JetAlg.hh"
#include "Rivet/Projections/ChargedLeptons.hh"
#include "Rivet/Projections/PromptFinalState.hh"
#include "Rivet/Projections/DressedLeptons.hh"
#include "Rivet/Projections/VetoedFinalState.hh"
#include "Rivet/Projections/IdentifiedFinalState.hh"
#include "Rivet/Projections/MissingMomentum.hh"
#include "Rivet/Tools/RivetHepMC.hh"
#include "Rivet/Tools/Cuts.hh"
#include "Rivet/Projections/NeutralFinalState.hh"
#include "Rivet/Projections/ZFinder.hh"
#include "Rivet/Projections/WFinder.hh"
#include "Rivet/Projections/InvMassFinalState.hh"
#include "Rivet/Tools/Logging.hh"
#include <LHAPDF/LHAPDF.h>
#include "LHAPDF/Reweighting.h"
#include <iostream>
#include <string>

using namespace LHAPDF;
using namespace std;

namespace Rivet {

  /// @brief Add a short analysis description here
  class CMS_SMP_19_013_W : public Analysis {
    public:

    /// Constructor
    DEFAULT_RIVET_ANALYSIS_CTOR(CMS_SMP_19_013_W);

    void init() {
      Cut c_any = Cuts::pT >= 15*GeV && Cuts::abseta <= 2.5;
      FinalState fs(-2.5,2.5);

      WFinder weFinder(fs, c_any, PID::ELECTRON, 0.*GeV, 7000.0*GeV, 0*GeV, 0.1, Rivet::WFinder::ClusterPhotons::CLUSTERNODECAY, Rivet::WFinder::PhotonTracking::NOTRACK, Rivet::WFinder::MassWindow::TRANSMASS, 80.4*GeV);
      addProjection(weFinder, "WeFinder");
      WFinder wmuFinder(fs, c_any, PID::MUON, 0.*GeV, 7000.0*GeV, 0*GeV, 0.1, Rivet::WFinder::ClusterPhotons::CLUSTERNODECAY, Rivet::WFinder::PhotonTracking::NOTRACK, Rivet::WFinder::MassWindow::TRANSMASS, 80.4*GeV);
      addProjection(wmuFinder, "WmuFinder");

      Cut c_photons = Cuts::pT >= 15*GeV && Cuts::abseta <= 2.5;
      const FinalState inputfs_pho(c_photons);
      IdentifiedFinalState photons(inputfs_pho);
      photons.acceptId(PID::PHOTON);
      addProjection(photons, "PHOTFS");

      Cut c_leptons = Cuts::pT >= 15*GeV && Cuts::abseta <= 2.5;
      const FinalState inputfs;
      IdentifiedFinalState bareleptons(inputfs);
      bareleptons.acceptIdPair(PID::ELECTRON);
      bareleptons.acceptIdPair(PID::MUON);
      DressedLeptons theLeptons(photons, bareleptons, 0.1, c_leptons);
      addProjection(theLeptons, "DressedLeptons");

      for (int i=0; i< 103; i++) {
        _h_WGG_ele_pho0_pt[i] = bookHisto1D("h_WGG_ele_pho0_pt_set_"+std::to_string(i), 15, 0, 300);
        _h_WGG_muo_pho0_pt[i] = bookHisto1D("h_WGG_muo_pho0_pt_set_"+std::to_string(i), 15, 0, 300);
        _h_WGG_ele_pho1_pt[i] = bookHisto1D("h_WGG_ele_pho1_pt_set_"+std::to_string(i), 15, 0, 300);
        _h_WGG_muo_pho1_pt[i] = bookHisto1D("h_WGG_muo_pho1_pt_set_"+std::to_string(i), 15, 0, 300);
        _h_WGG_ele_pho0_pho1_pt[i] = bookHisto1D("h_WGG_ele_pho0_pho1_pt_set_"+std::to_string(i), 15, 0, 300);
        _h_WGG_muo_pho0_pho1_pt[i] = bookHisto1D("h_WGG_muo_pho0_pho1_pt_set_"+std::to_string(i), 15, 0, 300);
      }
      for (int i=0; i< 9; i++) {
        _h_WGG_ele_pho0_pt_scale[i] = bookHisto1D("h_WGG_ele_pho0_pt_scale_"+std::to_string(i), 15, 0, 300);
        _h_WGG_muo_pho0_pt_scale[i] = bookHisto1D("h_WGG_muo_pho0_pt_scale_"+std::to_string(i), 15, 0, 300);
        _h_WGG_ele_pho1_pt_scale[i] = bookHisto1D("h_WGG_ele_pho1_pt_scale_"+std::to_string(i), 15, 0, 300);
        _h_WGG_muo_pho1_pt_scale[i] = bookHisto1D("h_WGG_muo_pho1_pt_scale_"+std::to_string(i), 15, 0, 300);
        _h_WGG_ele_pho0_pho1_pt_scale[i] = bookHisto1D("h_WGG_ele_pho0_pho1_pt_scale_"+std::to_string(i), 15, 0, 300);
        _h_WGG_muo_pho0_pho1_pt_scale[i] = bookHisto1D("h_WGG_muo_pho0_pho1_pt_scale_"+std::to_string(i), 15, 0, 300);
      }
      _h_WGG_ele_pho0_eta = bookHisto1D("h_WGG_ele_pho0_eta", 15, -2.6, 2.6);
      _h_WGG_ele_pho1_eta = bookHisto1D("h_WGG_ele_pho1_eta", 15, -2.6, 2.6);
      _h_WGG_ele_ele0_eta = bookHisto1D("h_WGG_ele_ele0_eta", 15, -2.6, 2.6);
      _h_WGG_muo_pho0_eta = bookHisto1D("h_WGG_muo_pho0_eta", 15, -2.6, 2.6);
      _h_WGG_muo_pho1_eta = bookHisto1D("h_WGG_muo_pho1_eta", 15, -2.6, 2.6);
      _h_WGG_muo_muo0_eta = bookHisto1D("h_WGG_muo_muo0_eta", 15, -2.6, 2.6);
    }

    void analyze(const Event& event) {
      double w = event.weight();
      const HepMC::WeightContainer w_vector = event.genEvent()->weights();

      const Particles photons = apply<IdentifiedFinalState>(event, "PHOTFS").particlesByPt();
      const DressedLeptons& theLeptons = applyProjection<DressedLeptons>(event, "DressedLeptons");

      const WFinder& weFS = applyProjection<WFinder>(event, "WeFinder");
      const WFinder& wmuFS = applyProjection<WFinder>(event, "WmuFinder");
      const Particles& wmu = wmuFS.bosons();
      const Particles& we = weFS.bosons();

      if (we.size() + wmu.size() != 1) vetoEvent;
      const Particles& theConstituents = we.size() ? weFS.constituentLeptons() : wmuFS.constituentLeptons();

      int ipho0 = -1;
      int ipho1 = -1;
      FourMomentum pho0, pho1;

      int p_size = 0;
      int n_pho = (int) photons.size();

      for (int i=0; i<n_pho; i++) {
        if (photons[i].isPrompt() != 1) continue;
        if (photons[i].genParticle()->status() != 1) continue;
        if (photons[i].pT() < 15*GeV) continue;
        if (fabs(photons[i].eta()) > 2.5) continue;

        bool skip=false;

        FourMomentum tmp_pho = photons[i].momentum();

        foreach (const DressedLepton& l, theLeptons.dressedLeptons()) {
          if (skip) continue;
          if (l.pT() < 15*GeV) continue;
          FourMomentum tmp_lep = l.momentum();
          if (fabs(tmp_lep.eta()) > 2.5) continue;
          if (deltaR(tmp_pho, tmp_lep) < 0.4) skip = true;
        }
        if (skip) continue;

        foreach (const GenParticle* p, Rivet::particles(event.genEvent()))  {
          if (skip) continue;
          if (p->status() != 1) continue;
          if (fabs(p->pdg_id()) == 22) continue;
          if (fabs(p->pdg_id()) == 12) continue;
          if (fabs(p->pdg_id()) == 14) continue;
          if (fabs(p->pdg_id()) == 16) continue;
          FourMomentum tmp_q = p->momentum();
          if (tmp_q.pT() < 15*GeV) continue;
          if (fabs(tmp_q.eta()) > 2.5) continue;
          if (deltaR(tmp_pho, tmp_q) < 0.1) skip = true;
        }

        if (skip) continue;

        if (ipho0 != -1) {
          FourMomentum tmp_pho0 = photons[ipho0].momentum();
          if (deltaR(tmp_pho, tmp_pho0) < 0.4) continue;
        }
        if (ipho1 != -1) {
          FourMomentum tmp_pho1 = photons[ipho1].momentum();
          if (deltaR(tmp_pho, tmp_pho1) < 0.4) continue;
        }
        if (ipho0 != -1) {
          if (photons[i].pT() > photons[ipho0].pT()) {
            ipho1 = ipho0;
            ipho0 = i;
          } else {
            if (ipho1 == -1) {
              ipho1 = i;
            } else {
              if(photons[i].pT() > photons[ipho1].pT()) {
                ipho1 = i;
              }
            }
          }
        }
        if (ipho0 == -1) ipho0 = i;
        p_size++;
      }

      if (ipho0 != -1) {
        pho0 = photons[ipho0].momentum();
      }
      if (ipho1 != -1) {
        pho1 = photons[ipho1].momentum();
      }

      if (ipho0 != -1) {
        if (photons[ipho0].pT() < 20*GeV) {
          ipho0 = -1;
          p_size = p_size - 1;
        }
      }
      if (ipho1 != -1) {
        if (photons[ipho1].pT() < 20*GeV) {
          ipho1 = -1;
          p_size = p_size - 1;
        }
      }

      if (we.size() == 1) {
        if (theConstituents[0].pT()<30) vetoEvent;
      }
      if (wmu.size() == 1) {
        if (theConstituents[0].pT()<30) vetoEvent;
      }

      if (p_size < 2) vetoEvent;

      LHAPDF::setVerbosity(0);
      if (event.genEvent()->pdf_info() == 0) vetoEvent;
      HepMC::PdfInfo pdfi = *event.genEvent()->pdf_info();

      const string setname = "NNPDF31_nnlo_hessian_pdfas"; // pdfset to test (2018)
      //const string setname = "NNPDF30_nlo_nf_5_pdfas"; // pdfset to test (2016)
      const int nmem = 102; // 101 and 102 -> alpha_s

      double x1 = pdfi.x1();
      double x2 = pdfi.x2();
      double id1 = pdfi.id1();
      double id2 = pdfi.id2();
      double Q = pdfi.scalePDF(); // factorisation scale in GeV

      LHAPDF::PDF* pdfs[nmem];
      LHAPDF::PDF* pdfs0 = mkPDF(setname, 0);
      double reweight[nmem];

      //-----------------------------------------------------------------------------------
      // Code to decouple pdf weight from global event weight
      const string refpdf_setname = "NNPDF31_nnlo_hessian_pdfas"; // pdfset of the 2018 mini
      //const string refpdf_setname = "NNPDF30_nlo_nf_5_pdfas"; // pdfset of the 2016 mini
      LHAPDF::PDF* refpdf_pdfs0 = mkPDF(refpdf_setname, 0);
      double refpdf_weight_0 = LHAPDF::weightxxQ(id1,id2,x1,x2,Q,refpdf_pdfs0,pdfs0);

      w = w * refpdf_weight_0;
      //-----------------------------------------------------------------------------------

      if (we.size() == 1) {
        _h_WGG_ele_pho0_pt[0]->fill(pho0.pt(), w);
        _h_WGG_ele_pho1_pt[0]->fill(pho1.pt(), w);
        _h_WGG_ele_pho0_pho1_pt[0]->fill((pho0+pho1).pt(), w);
        _h_WGG_ele_pho0_eta->fill(pho0.eta(), w);
        _h_WGG_ele_pho1_eta->fill(pho1.eta(), w);
        _h_WGG_ele_ele0_eta->fill(theConstituents[0].eta(), w);
      }
      if (wmu.size() == 1) {
        _h_WGG_muo_pho0_pt[0]->fill(pho0.pt(), w);
        _h_WGG_muo_pho1_pt[0]->fill(pho1.pt(), w);
        _h_WGG_muo_pho0_pho1_pt[0]->fill((pho0+pho1).pt(), w);
        _h_WGG_muo_pho0_eta->fill(pho0.eta(), w);
        _h_WGG_muo_pho1_eta->fill(pho1.eta(), w);
        _h_WGG_muo_muo0_eta->fill(theConstituents[0].eta(), w);
      }

      for (int imem = 0; imem < nmem ; imem++) {
        pdfs[imem] = mkPDF(setname, imem+1);
        const bool b1 = pdfs[imem]->inPhysicalRangeXQ(x1,Q);
        const bool b2 = pdfs[imem]->inPhysicalRangeX(x2);
        if ((b1 == 0 ) || (b2 == 0 ) ) vetoEvent;
        reweight[imem] = LHAPDF::weightxxQ(id1,id2,x1,x2,Q,pdfs0,pdfs[imem]);
        if (we.size() == 1) {
          _h_WGG_ele_pho0_pt[imem+1]->fill(pho0.pt(), w*reweight[imem]);
          _h_WGG_ele_pho1_pt[imem+1]->fill(pho1.pt(), w*reweight[imem]);
          _h_WGG_ele_pho0_pho1_pt[imem+1]->fill((pho0+pho1).pt(), w*reweight[imem]);
        }
        if (wmu.size() == 1) {
          _h_WGG_muo_pho0_pt[imem+1]->fill(pho0.pt(), w*reweight[imem]);
          _h_WGG_muo_pho1_pt[imem+1]->fill(pho1.pt(), w*reweight[imem]);
          _h_WGG_muo_pho0_pho1_pt[imem+1]->fill((pho0+pho1).pt(), w*reweight[imem]);
        }
        delete pdfs[imem];
      }
      for (int i=0; i< 9; i++) {
        if (we.size() == 1) {
          _h_WGG_ele_pho0_pt_scale[i]->fill(pho0.pt(), w_vector[i]);
          _h_WGG_ele_pho1_pt_scale[i]->fill(pho1.pt(), w_vector[i]);
          _h_WGG_ele_pho0_pho1_pt_scale[i]->fill((pho0+pho1).pt(), w_vector[i]);
        }
        if (wmu.size() == 1) {
          _h_WGG_muo_pho0_pt_scale[i]->fill(pho0.pt(), w_vector[i]);
          _h_WGG_muo_pho1_pt_scale[i]->fill(pho1.pt(), w_vector[i]);
          _h_WGG_muo_pho0_pho1_pt_scale[i]->fill((pho0+pho1).pt(), w_vector[i]);
        }
      }
    }

    void finalize() {
      const double xsec = 2.001 * 0.79839723; //taucorrection = 0.79839723
      const double normal = xsec / femtobarn / sumOfWeights();
      for (int imem = 0; imem < 103; imem++) {
        scale(_h_WGG_ele_pho0_pt[imem], normal);
        scale(_h_WGG_ele_pho1_pt[imem], normal);
        scale(_h_WGG_ele_pho0_pho1_pt[imem], normal);
        scale(_h_WGG_muo_pho0_pt[imem], normal);
        scale(_h_WGG_muo_pho1_pt[imem], normal);
        scale(_h_WGG_muo_pho0_pho1_pt[imem], normal);
      }
      for (int i = 0; i < 9 ; i++) {
        scale(_h_WGG_ele_pho0_pt_scale[i], normal);
        scale(_h_WGG_ele_pho1_pt_scale[i], normal);
        scale(_h_WGG_ele_pho0_pho1_pt_scale[i], normal);
        scale(_h_WGG_muo_pho0_pt_scale[i], normal);
        scale(_h_WGG_muo_pho1_pt_scale[i], normal);
        scale(_h_WGG_muo_pho0_pho1_pt_scale[i], normal);
      }
      scale(_h_WGG_ele_pho0_eta, normal);
      scale(_h_WGG_ele_pho1_eta, normal);
      scale(_h_WGG_ele_ele0_eta, normal);
      scale(_h_WGG_muo_pho0_eta, normal);
      scale(_h_WGG_muo_pho1_eta, normal);
      scale(_h_WGG_muo_muo0_eta, normal);
    }

    private:
      Histo1DPtr _h_WGG_ele_pho0_pho1_pt_scale[9];
      Histo1DPtr _h_WGG_muo_pho0_pho1_pt_scale[9];
      Histo1DPtr _h_WGG_ele_pho0_pt_scale[9];
      Histo1DPtr _h_WGG_ele_pho1_pt_scale[9];
      Histo1DPtr _h_WGG_muo_pho0_pt_scale[9];
      Histo1DPtr _h_WGG_muo_pho1_pt_scale[9];
      Histo1DPtr _h_WGG_ele_pho0_pho1_pt[103];
      Histo1DPtr _h_WGG_muo_pho0_pho1_pt[103];
      Histo1DPtr _h_WGG_ele_pho0_pt[103];
      Histo1DPtr _h_WGG_ele_pho1_pt[103];
      Histo1DPtr _h_WGG_muo_pho0_pt[103];
      Histo1DPtr _h_WGG_muo_pho1_pt[103];
      Histo1DPtr _h_WGG_ele_pho0_eta;
      Histo1DPtr _h_WGG_ele_pho1_eta;
      Histo1DPtr _h_WGG_ele_ele0_eta;
      Histo1DPtr _h_WGG_muo_pho0_eta;
      Histo1DPtr _h_WGG_muo_pho1_eta;
      Histo1DPtr _h_WGG_muo_muo0_eta;
  };

  DECLARE_RIVET_PLUGIN(CMS_SMP_19_013_W);
}
