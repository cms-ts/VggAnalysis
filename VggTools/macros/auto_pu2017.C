
#include <fstream>

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include "../scripts/WeightCalculatorFromHistogram.C"

void auto_pu2017(TString input="lists/RunIIFall17NanoAOD_DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8.list", TString output="pileup.root") {

  vector<std::string> files;

  ifstream in(input.Data());
  while (in.good()) {
    TString line;
    line.ReadLine(in);
    if (!line.IsWhitespace() && !line.BeginsWith("#")) {
      files.push_back(line.Data());
    }
  }
  in.close();

  if (files.size()==0) {
    cout << "no files to process" << endl;
    return;
  }

  int nthreads = 30;
  ROOT::EnableImplicitMT(nthreads);

  TChain* chain = new TChain("Events");
  for (uint i=0; i < files.size(); i++) {
    chain->Add(files[i].c_str());
  }

  TH1D* hist = new TH1D("pileup", "pileup", 100, 0., 100.);

  chain->Draw("Pileup_nTrueInt>>h_pu2017", "", "goff");

  TFile* file = new TFile(output.Data(), "RECREATE");
  file->cd();
  hist->Write();
  file->Close();
  delete file;

  if (output.Contains("pileup_ele")) {
    WeightCalculatorFromHistogram(output.Data(), "root/ratio_pileup_Run2017_SingleElectron_31Mar2018.root", true, false, output.Data());
  }
  if (output.Contains("pileup_muo")) {
    WeightCalculatorFromHistogram(output.Data(), "root/ratio_pileup_Run2017_SingleMuon_31Mar2018.root", true, false, output.Data());
  }

}
