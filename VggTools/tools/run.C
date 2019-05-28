#pragma cling load("libTreePlayer.so")

using namespace std;

#include <fstream>

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TSystem.h>

#include <ROOT/TTreeProcessorMP.hxx>

void run(TString input="../macros/lists/Run2017B_DoubleEG_14Dec2018.list", TString output="selector.root") {

  TDatime now;
  Info("run", "%s", now.AsSQLString());

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

  long nevt = TTree::kMaxEntries;

  TSelector* selector = 0;

  if (input.Contains("Run2016H"))                               selector = TSelector::GetSelector("treeMakerDT16H.C+");
  if (input.Contains("Run2016") && !input.Contains("Run2016H")) selector = TSelector::GetSelector("treeMakerDT16.C+");
  if (input.Contains("Run2017B"))                               selector = TSelector::GetSelector("treeMakerDT17B.C+");
  if (input.Contains("Run2017") && !input.Contains("Run2017B")) selector = TSelector::GetSelector("treeMakerDT17.C+");
  if (input.Contains("Run2018"))                                selector = TSelector::GetSelector("treeMakerDT18.C+");

  if (input.Contains("RunIISummer16NanoAOD")) selector = TSelector::GetSelector("treeMakerMC16.C+");
  if (input.Contains("RunIIFall17NanoAOD"))   selector = TSelector::GetSelector("treeMakerMC17.C+");
  if (input.Contains("RunIIAutumn18NanoAOD")) selector = TSelector::GetSelector("treeMakerMC18.C+");

  TList* fInput = new TList();

  if (input.Contains("RunIIFall17NanoAOD")) {
    TString output_ele = "../macros/data/auto_pu/" + TString(gSystem->BaseName(input));
    TString output_muo = "../macros/data/auto_pu/" + TString(gSystem->BaseName(input));
    output_ele.ReplaceAll("RunIIFall17", "pileup_ele_RunIIFall17");
    output_muo.ReplaceAll("RunIIFall17", "pileup_muo_RunIIFall17");
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

  TChain* chain = new TChain("Events");
  for (uint i=0; i < files.size(); i++) {
    chain->Add(files[i].c_str());
  }
  int nevt0 = chain->GetEntries();

  now = TDatime();
  Info("run", "%s", now.AsSQLString());

  Info("run", "output file = %s", output.Data());
  TFile* file = new TFile(output.Data(), "RECREATE");
  fInput->Add(new TNamed("output", output.Data()));
  fInput->Add(file);

  chain->Process(selector, "", nevt);

  delete chain;

  TList* fOutput = selector->GetOutputList();

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
