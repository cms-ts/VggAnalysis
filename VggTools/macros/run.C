#pragma cling load("libTreePlayer.so")

using namespace std;

#include <fstream>

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TSystem.h>

#include <ROOT/TTreeProcessorMP.hxx>

void run(TString input="lists/Run2017B_DoubleEG_31Mar2018.list", TString output="selector.root") {

  TDatime now;
  Info("run", "%s", now.AsSQLString());

  TString option = "";
  if (input.Contains("Run2016H")) option="DT16H";
  if (input.Contains("Run2016") && !input.Contains("Run2016H")) option="DT16";
  if (input.Contains("Run2017B")) option="DT17B";
  if (input.Contains("Run2017") && !input.Contains("Run2017B")) option="DT17";
  if (input.Contains("Run2018")) option="DT18";
  if (input.Contains("RunIISummer16NanoAOD")) option="MC16";
  if (input.Contains("RunIIFall17NanoAOD")) option="MC17";
  if (input.Contains("RunIIFall18NanoAOD")) option="MC18";
  if (input.Contains("RunIIAutumn18NanoAOD")) option="MC18";
  if (option.Length()==0) {
    cout << "unknown input list: " << input << endl;
    return;
  }

  Info("run", "input list = %s", input.Data());

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
  if (gROOT->IsBatch()) nWorkers = 2;

  ROOT::EnableThreadSafety();
  ROOT::TTreeProcessorMP workers(nWorkers);

  int nevt = -1;

  TSelector* selector = 0;

  if (option.Contains("DT")) {
#if defined(__APPLE__)
    if (option.Contains("DT16H"))                             selector = TSelector::GetSelector("mainSelectorDT16H.C");
    if (option.Contains("DT16") && !option.Contains("DT16H")) selector = TSelector::GetSelector("mainSelectorDT16.C");
    if (option.Contains("DT17B"))                             selector = TSelector::GetSelector("mainSelectorDT17B.C");
    if (option.Contains("DT17") && !option.Contains("DT17B")) selector = TSelector::GetSelector("mainSelectorDT17.C");
    if (option.Contains("DT18"))                              selector = TSelector::GetSelector("mainSelectorDT18.C");
#else
    if (option.Contains("DT16H"))                             selector = TSelector::GetSelector("mainSelectorDT16H.C+");
    if (option.Contains("DT16") && !option.Contains("DT16H")) selector = TSelector::GetSelector("mainSelectorDT16.C+");
    if (option.Contains("DT17B"))                             selector = TSelector::GetSelector("mainSelectorDT17B.C+");
    if (option.Contains("DT17") && !option.Contains("DT17B")) selector = TSelector::GetSelector("mainSelectorDT17.C+");
    if (option.Contains("DT18"))                              selector = TSelector::GetSelector("mainSelectorDT18.C+");
#endif
    selector->SetOption("DT");
  }
  if (option.Contains("MC")) {
#if defined(__APPLE__)
    if (option.Contains("MC16")) selector = TSelector::GetSelector("mainSelectorMC16.C");
    if (option.Contains("MC17")) selector = TSelector::GetSelector("mainSelectorMC17.C");
    if (option.Contains("MC18")) selector = TSelector::GetSelector("mainSelectorMC18.C");
#else
    if (option.Contains("MC16")) selector = TSelector::GetSelector("mainSelectorMC16.C+");
    if (option.Contains("MC17")) selector = TSelector::GetSelector("mainSelectorMC17.C+");
    if (option.Contains("MC18")) selector = TSelector::GetSelector("mainSelectorMC18.C+");
#endif
    selector->SetOption("MC");
  }

  if (option.Contains("MC")) {
    if (input.Contains("WJetsToLNu"))                   selector->SetOption("MC,WJetsToLNu");
    if (input.Contains("WG") && !input.Contains("WGG")) selector->SetOption("MC,WG");
    if (input.Contains("WGG"))                          selector->SetOption("MC,WGG");
    if (input.Contains("WTauNu"))                       selector->SetOption("MC,WTauNu");
    if (input.Contains("DYJetsToLL"))                   selector->SetOption("MC,DYJetsToLL");
    if (input.Contains("ZG") && !input.Contains("ZGG")) selector->SetOption("MC,ZG");
    if (input.Contains("ZGG"))                          selector->SetOption("MC,ZGG");
    if (input.Contains("ZTauTau"))                      selector->SetOption("MC,ZTauTau");
  }

  if (option.Contains("MC17")) {
    TString output_ele = "data/auto_pu2017/" + TString(gSystem->BaseName(input));
    TString output_muo = "data/auto_pu2017/" + TString(gSystem->BaseName(input));
    output_ele.ReplaceAll("RunIIFall17NanoAOD", "pileup_ele_RunIIFall17NanoAOD");
    output_muo.ReplaceAll("RunIIFall17NanoAOD", "pileup_muo_RunIIFall17NanoAOD");
    output_ele.ReplaceAll(".list", ".root");
    output_muo.ReplaceAll(".list", ".root");
    if (!gSystem->AccessPathName(output_ele.Data()) && !gSystem->AccessPathName(output_muo.Data())) {
      TFile* file_ele_pu = new TFile(output_ele.Data());
      TFile* file_muo_pu = new TFile(output_muo.Data());
      TH1D* pu_ele_weights = (TH1D*)file_ele_pu->Get("pu_weights");
      TH1D* pu_muo_weights = (TH1D*)file_muo_pu->Get("pu_weights");
      pu_ele_weights->SetDirectory(0);
      pu_muo_weights->SetDirectory(0);
      pu_ele_weights->SetName("pu_ele_weights");
      pu_muo_weights->SetName("pu_muo_weights");
      file_ele_pu->Close();
      file_muo_pu->Close();
      delete file_ele_pu;
      delete file_muo_pu;
      TList* fInput = new TList();
      fInput->Add(new TNamed("auto_pu2017", ""));
      fInput->Add(pu_ele_weights);
      fInput->Add(pu_muo_weights);
      selector->SetInputList(fInput);
    }
  }

  workers.Process(files, *selector, "Events", nevt);

  now = TDatime();
  Info("run", "%s", now.AsSQLString());

  Info("run", "output file = %s", output.Data());
  TFile* file = new TFile(output.Data(), "RECREATE");
  file->cd();
  TList* fOutput = selector->GetOutputList();
  TIter next(fOutput);
  TObject* obj = 0;
  while ((obj = next())) {
    if (!TString(obj->ClassName()).Contains("TH")) continue;
    if (!TString(obj->GetName()).Contains("h_")) continue;
    Info("run", "writing %s", obj->GetName());
    obj->Write();
  }
  file->Close();
  delete file;

  TChain* chain = new TChain("Events");
  for (uint i=0; i < files.size(); i++) {
    chain->Add(files[i].c_str());
  }
  int nevt0 = chain->GetEntries();
  delete chain;

  TH1D* h_nevt = dynamic_cast<TH1D*>(fOutput->FindObject("h_nevt"));
  int nevt1 = 0;
  if (h_nevt) nevt1 = h_nevt->GetBinContent(1);

  Info("run", "processed events: %d", nevt1);

  if (nevt1 != nevt0) {
    Error("run", "expected events: %d", nevt0);
  }

  now = TDatime();
  Info("run", "%s", now.AsSQLString());

}

int main(int argc, char *argv[]) {

run(argv[1], argv[2]);

}
