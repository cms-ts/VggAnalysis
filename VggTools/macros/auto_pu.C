#include <fstream>
#include <functional>

using namespace std;

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <TSystem.h>

#include <TH1D.h>

#include <ROOT/TTreeProcessorMP.hxx>

#include "../scripts/WeightCalculatorFromHistogram.C"

#define NANOAODv7

void auto_pu(TString input="lists/RunIIFall17NanoAODv7_DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8.list", TString output="pileup.root") {

  TDatime now;
  Info("auto_pu", "%s", now.AsSQLString());

  Info("auto_pu", "input list = %s", input.Data());

  vector<string> files;

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

  int nWorkers = 16;
  if (TString(gSystem->HostName()).Contains("farmui")) nWorkers = 32;
  if (gROOT->IsBatch()) nWorkers = 4;

  ROOT::TTreeProcessorMP workers(nWorkers);

  int nevt = -1;

  function<TH1D*(TTreeReader &)> work = [](TTreeReader& fReader) {
    TH1D* h = new TH1D("pileup", "pileup", 100, 0., 100.);
    TTreeReaderValue<Float_t> Pileup_nTrueInt = {fReader, "Pileup_nTrueInt"};
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
  delete file;

  if (output.Contains("pileup_ele_RunIIFall17")) {
#if defined(NANOAODv7)
      WeightCalculatorFromHistogram(output.Data(), "root/ratio_pileup_Run2017_SingleElectron_02Apr2020.root", true, false, output.Data());
#endif // defined(NANOAODv7)
  }
  if (output.Contains("pileup_ele_up_RunIIFall17")) {
#if defined(NANOAODv7)
      WeightCalculatorFromHistogram(output.Data(), "root/ratio_pileup_up_Run2017_SingleElectron_02Apr2020.root", true, false, output.Data());
#endif // defined(NANOAODv7)
  }
  if (output.Contains("pileup_ele_down_RunIIFall17")) {
#if defined(NANOAODv7)
      WeightCalculatorFromHistogram(output.Data(), "root/ratio_pileup_down_Run2017_SingleElectron_02Apr2020.root", true, false, output.Data());
#endif // defined(NANOAODv7)
  }
  if (output.Contains("pileup_muo_RunIIFall17")) {
#if defined(NANOAODv7)
      WeightCalculatorFromHistogram(output.Data(), "root/ratio_pileup_Run2017_SingleMuon_02Apr2020.root", true, false, output.Data());
#endif // defined(NANOAODv7)
  }
  if (output.Contains("pileup_muo_up_RunIIFall17")) {
#if defined(NANOAODv7)
      WeightCalculatorFromHistogram(output.Data(), "root/ratio_pileup_up_Run2017_SingleMuon_02Apr2020.root", true, false, output.Data());
#endif // defined(NANOAODv7)
  }
  if (output.Contains("pileup_muo_down_RunIIFall17")) {
#if defined(NANOAODv7)
      WeightCalculatorFromHistogram(output.Data(), "root/ratio_pileup_down_Run2017_SingleMuon_02Apr2020.root", true, false, output.Data());
#endif // defined(NANOAODv7)
  }

  now = TDatime();
  Info("auto_pu", "%s", now.AsSQLString());

}

#ifndef __ACLIC__
int main(int argc, char *argv[]) {

  vector<string> args = {"auto_pu.exe", "", ""};

  for (uint i = 0; i < argc; i++) args[i] = argv[i];

  cout << "Processing auto_pu.C(\"" << args[1] << "\",\""
                                    << args[2] << "\")..." << endl;

  auto_pu(args[1], args[2]);

  return 0;

}
#endif
