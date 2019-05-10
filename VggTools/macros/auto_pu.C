#pragma cling load("libTreePlayer.so")

using namespace std;

#include <fstream>

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TSystem.h>

#include <ROOT/TTreeProcessorMP.hxx>

#include "../scripts/WeightCalculatorFromHistogram.C"

void auto_pu(TString input="lists/RunIIFall17NanoAOD_DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8.list", TString output="pileup.root") {

  TDatime now;
  Info("auto_pu", "%s", now.AsSQLString());

  Info("auto_pu", "input list = %s", input.Data());

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

  if (files.size() == 0) {
    cout << "no files to process" << endl;
    return;
  }

  int nWorkers = 10;
  if (gROOT->IsBatch()) nWorkers = 4;

  ROOT::EnableThreadSafety();
  ROOT::TTreeProcessorMP workers(nWorkers);

  int nevt = -1;

  auto work = [](TTreeReader& fReader) {
    TTreeReaderValue<Float_t> Pileup_nTrueInt = {fReader, "Pileup_nTrueInt"};
    TH1D* h = new TH1D("pileup", "pileup", 100, 0., 100.);
    while (fReader.Next()) {
      h->Fill(*Pileup_nTrueInt);
    }
    return h;
  };

  TH1D* hist = workers.Process(files, work, "Events", nevt);

  now = TDatime();
  Info("auto_pu", "%s", now.AsSQLString());

  TChain* chain = new TChain("Events");
  for (uint i=0; i < files.size(); i++) {
    chain->Add(files[i].c_str());
  }
  int nevt0 = chain->GetEntries();
  delete chain;

  int nevt1 = hist->GetEntries();

  Info("auto_pu", "processed events: %d", nevt1);

  if (nevt1 != nevt0) {
    Error("auto_pu", "expected events: %d", nevt0);
  }

  TFile* file = new TFile(output.Data(), "RECREATE");
  file->cd();
  hist->Write();
  file->Close();
  delete file;

  if (output.Contains("pileup_ele_RunIIFall17")) {
      WeightCalculatorFromHistogram(output.Data(), "root/ratio_pileup_Run2017_SingleElectron_14Dec2018.root", true, false, output.Data());
  }
  if (output.Contains("pileup_ele_up_RunIIFall17")) {
      WeightCalculatorFromHistogram(output.Data(), "root/ratio_pileup_up_Run2017_SingleElectron_14Dec2018.root", true, false, output.Data());
  }
  if (output.Contains("pileup_ele_down_RunIIFall17")) {
      WeightCalculatorFromHistogram(output.Data(), "root/ratio_pileup_down_Run2017_SingleElectron_14Dec2018.root", true, false, output.Data());
  }
  if (output.Contains("pileup_muo_RunIIFall17")) {
      WeightCalculatorFromHistogram(output.Data(), "root/ratio_pileup_Run2017_SingleMuon_14Dec2018.root", true, false, output.Data());
  }
  if (output.Contains("pileup_muo_up_RunIIFall17")) {
      WeightCalculatorFromHistogram(output.Data(), "root/ratio_pileup_up_Run2017_SingleMuon_14Dec2018.root", true, false, output.Data());
  }
  if (output.Contains("pileup_muo_down_RunIIFall17")) {
      WeightCalculatorFromHistogram(output.Data(), "root/ratio_pileup_down_Run2017_SingleMuon_14Dec2018.root", true, false, output.Data());
  }

  now = TDatime();
  Info("auto_pu", "%s", now.AsSQLString());

}

int main(int argc, char *argv[]) {

auto_pu(argv[1], argv[2]);

}
