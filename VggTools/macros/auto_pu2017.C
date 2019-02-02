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

  if (files.size() == 0) {
    cout << "no files to process" << endl;
    return;
  }

  auto work = [](TTreeReader& fReader) {
    TTreeReaderValue<Float_t> Pileup_nTrueInt(fReader, "Pileup_nTrueInt");
    auto h = new TH1D("pileup", "pileup", 100, 0., 100.);
    while (fReader.Next()) {
      h->Fill(*Pileup_nTrueInt);
    }
    return h;
  };

  ROOT::TTreeProcessorMP workers(4);
  auto hist = workers.Process(files, work, "Events");

  TChain* chain = new TChain("Events");
  for (uint i=0; i < files.size(); i++) {
    chain->Add(files[i].c_str());
  }
  int nevt0 = chain->GetEntries();
  delete chain;

  int nevt1 = hist->GetEntries();

  Info("auto_pu2017", "processed events: %d", nevt1);

  if (nevt1 != nevt0) {
    Error("auto_pu2017", "expected events: %d", nevt0);
  }

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

int main(int argc, char *argv[]) {

auto_pu2017(argv[1], argv[2]);

}
