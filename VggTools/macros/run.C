#pragma cling load("libTreePlayer.so")

#include <fstream>

using namespace std;

#include <TROOT.h>
#include <TSystem.h>
#include <TFile.h>
#include <TChain.h>
#include <TSelector.h>

#include <TH1D.h>

#include <ROOT/TTreeProcessorMP.hxx>

void run(TString input="lists/Run2017B_SingleElectron.list", TString output="selector.root", TString flag="reference") {

  TDatime now;
  Info("run", "%s", now.AsSQLString());

  TString option = "";
  if (input.Contains("Run2016")) option="DT16";
  if (input.Contains("Run2017")) option="DT17";
  if (input.Contains("Run2018")) option="DT18";
  if (input.Contains("RunIISummer16NanoAOD")) option="MC16";
  if (input.Contains("RunIIFall17NanoAOD")) option="MC17";
  if (input.Contains("RunIIAutumn18NanoAOD")) option="MC18";
  if (option.Length() == 0) {
    cout << "unknown input list: " << input << endl;
    return;
  }

  Info("run", "input list = %s", input.Data());

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

  TSelector* selector = 0;

  if (option.Contains("DT")) {
    if (option.Contains("DT16")) selector = TSelector::GetSelector("mainSelectorDT16.C+");
    if (option.Contains("DT17")) selector = TSelector::GetSelector("mainSelectorDT17.C+");
    if (option.Contains("DT18")) selector = TSelector::GetSelector("mainSelectorDT18.C+");
    selector->SetOption("DT");
  }

  if (option.Contains("MC")) {
    if (option.Contains("MC16")) selector = TSelector::GetSelector("mainSelectorMC16.C+");
    if (option.Contains("MC17")) selector = TSelector::GetSelector("mainSelectorMC17.C+");
    if (option.Contains("MC18")) selector = TSelector::GetSelector("mainSelectorMC18.C+");
    selector->SetOption("MC");
  }

  if (option.Contains("DT")) {
    if (input.Contains("Run2016B")) selector->SetOption("DT,2016B");
    if (input.Contains("Run2016C")) selector->SetOption("DT,2016C");
    if (input.Contains("Run2016D")) selector->SetOption("DT,2016D");
    if (input.Contains("Run2016E")) selector->SetOption("DT,2016E");
    if (input.Contains("Run2016F")) selector->SetOption("DT,2016F");
    if (input.Contains("Run2016G")) selector->SetOption("DT,2016G");
    if (input.Contains("Run2016H")) selector->SetOption("DT,2016H");

    if (input.Contains("Run2017B")) selector->SetOption("DT,2017B");
    if (input.Contains("Run2017C")) selector->SetOption("DT,2017C");
    if (input.Contains("Run2017D")) selector->SetOption("DT,2017D");
    if (input.Contains("Run2017E")) selector->SetOption("DT,2017E");
    if (input.Contains("Run2017F")) selector->SetOption("DT,2017F");

    if (input.Contains("Run2018A")) selector->SetOption("DT,2018A");
    if (input.Contains("Run2018B")) selector->SetOption("DT,2018B");
    if (input.Contains("Run2018C")) selector->SetOption("DT,2018C");
    if (input.Contains("Run2018D")) selector->SetOption("DT,2018D");
  }

  if (option.Contains("MC")) {
    if (input.Contains("WJetsToLNu") || input.Contains("WToLNu"))                 selector->SetOption("MC,WJetsToLNu");
    if (input.Contains("WG") && !input.Contains("WGG") && !input.Contains("WWG")) selector->SetOption("MC,WG");
    if (input.Contains("WGG"))                                                    selector->SetOption("MC,WGG");
    if (input.Contains("WTauNu"))                                                 selector->SetOption("MC,WTauNu");
    if (input.Contains("DYJetsToLL") || input.Contains("DYToLL"))                 selector->SetOption("MC,DYJetsToLL");
    if (input.Contains("ZG") && !input.Contains("ZGG") && !input.Contains("WZG")) selector->SetOption("MC,ZG");
    if (input.Contains("ZGG"))                                                    selector->SetOption("MC,ZGG");
    if (input.Contains("ZTauTau"))                                                selector->SetOption("MC,ZTauTau");
    if (input.Contains("ST_t-channel") && !input.Contains("ST_tW"))               selector->SetOption("MC,ST_t-channel");
    if (input.Contains("TGJets") && !input.Contains("TTGJets"))                   selector->SetOption("MC,TGJets");
    if (input.Contains("TTJets"))                                                 selector->SetOption("MC,TTJets");
    if (input.Contains("TTGJets"))                                                selector->SetOption("MC,TTGJets");
    if (input.Contains("TTGG"))                                                   selector->SetOption("MC,TTGG");
    if (input.Contains("WW") && !input.Contains("WWG"))                           selector->SetOption("MC,WW");
    if (input.Contains("WWG"))                                                    selector->SetOption("MC,WWG");
    if (input.Contains("WZ") && !input.Contains("WZG"))                           selector->SetOption("MC,WZ");
    if (input.Contains("WZG"))                                                    selector->SetOption("MC,WZG");
  }

  Info("run", "flag = %s", flag.Data());

  TList* fInput = new TList();

  fInput->Add(new TNamed("flag", flag.Data()));

  if (option.Contains("MC17")) {
    TString output_ele = "data/auto_pu/" + TString(gSystem->BaseName(input));
    TString output_muo = "data/auto_pu/" + TString(gSystem->BaseName(input));
    output_ele.ReplaceAll("RunIIFall17", "pileup_ele_RunIIFall17");
    output_muo.ReplaceAll("RunIIFall17", "pileup_muo_RunIIFall17");
    if (flag.Contains("pileup_up")) {
      output_ele.ReplaceAll("pileup_ele", "pileup_ele_up");
      output_muo.ReplaceAll("pileup_muo", "pileup_muo_up");
    }
    if (flag.Contains("pileup_down")) {
      output_ele.ReplaceAll("pileup_ele", "pileup_ele_down");
      output_muo.ReplaceAll("pileup_muo", "pileup_muo_down");
    }
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
      fInput->Add(new TNamed("auto_pu", ""));
      fInput->Add(pu_ele_weights);
      fInput->Add(pu_muo_weights);
    }
  }

  selector->SetInputList(fInput);

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

  delete selector;

  now = TDatime();
  Info("run", "%s", now.AsSQLString());

}

#ifndef __ACLIC__
int main(int argc, char *argv[]) {

  vector<string> args = {"run.exe", "", "", "reference"};

  for (uint i = 0; i < argc; i++) args[i] = argv[i];

  cout << "Processing run.C(\"" << args[1] << "\",\""
                                << args[2] << "\",\""
                                << args[3] << "\")..." << endl;

  run(args[1], args[2], args[3]);

  return 0;

}
#endif
