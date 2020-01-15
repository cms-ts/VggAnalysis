#include "plot3.h"
#include "rebin.h"

void plot3(string plot="", string title="", string version="v00", string options="", string flag="reference") {

  string year = "";

  if (plot.find("2016") != string::npos) year = "2016";
  if (plot.find("2017") != string::npos) year = "2017";
  if (plot.find("2018") != string::npos) year = "2018";
  if (plot.find("Run2") != string::npos) year = "Run2";

  if (options.find("test") != string::npos) version = version + ".test";
  if (options.find("new") != string::npos) version = version + ".new";
  if (options.find("jet") != string::npos) version = version + ".jet";

  if (options.find("amcatnlo") != string::npos) version = version + ".amcatnlo";
  if (options.find("madgraph") != string::npos) version = version + ".madgraph";
  if (options.find("default") != string::npos) version = version + ".default";

  TFile* file_iso = new TFile(("html/" + version + "/" + flag + "/" + year + "/root/" + title + ".root").c_str());
  TH1D* h_iso_data = (TH1D*)file_iso->Get("h_data_cat");
  TH1D* h_iso_mc = (TH1D*)file_iso->Get("h_mc_cat");

  TFile* file_noiso = new TFile(("html/" + version + "/" + flag + "/" + year + "/root/" + title + "_noiso.root").c_str());
  TH1D* h_noiso_data = (TH1D*)file_noiso->Get("h_data_cat");
  TH1D* h_noiso_mc = (TH1D*)file_noiso->Get("h_mc_cat");

  TH1D* ratio_data = (TH1D*) h_iso_data->Clone("ratio_data");
  ratio_data->Divide(h_noiso_data);

  TH1D* ratio_mc = (TH1D*) h_iso_mc->Clone("ratio_mc");
  ratio_mc->Divide(h_noiso_mc);

  for (int i = 0; i < ratio_data->GetNbinsX()+2; i++) {
    if (ratio_data->GetBinContent(i) < 0) {
      ratio_data->SetBinContent(i, 0);
      ratio_data->SetBinError(i, 0);
    }
    if (ratio_mc->GetBinContent(i) < 0) {
      ratio_mc->SetBinContent(i, 0);
      ratio_mc->SetBinError(i, 0);
    }
  } 

  while (gSystem->AccessPathName(("html/" + version + "/" + flag + "/" + year + ".matrix/root/").c_str())) {
    gSystem->mkdir(("html/" + version + "/" + flag + "/" + year + ".matrix/root/").c_str(), kTRUE);
  }
  TFile* file = new TFile(("html/" + version + "/" + flag + "/" + year + ".matrix/root/" + title + "_matrix_weight.root").c_str(), "RECREATE");
  Info("TFile::Open", "root file %s has been created", ("html/" + version + "/" + flag + "/" + year + ".matrix/root/" + title + "_matrix_weight.root").c_str());
  ratio_data->Write((title.substr(0, 8) + "_weight").c_str());
  ratio_mc->Write((title.substr(0, 8) + "_weight_mc").c_str());
  file->Close();
  delete file;

}

int main(int argc, char *argv[]) {

#pragma unused (argc)

cout << "Processing plot3.C(\"" << argv[1] << "\",\""
                                << argv[2] << "\",\""
                                << argv[3] << "\",\""
                                << argv[4] << "\",\""
                                << argv[5] << "\")..." << endl;

plot3(argv[1], argv[2], argv[3], argv[4], argv[5]);

}
