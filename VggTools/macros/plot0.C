#include "plot0.h"

void plot0(string title="") {

  string version = "v00";

  map<string, float> lumiMap;
  readMap("lumi.dat", lumiMap);
  cout << "Read lumi map for " << lumiMap.size() << " datasets" << endl;

  map<string, float> xsecMap;
  readMap("xsec.dat", xsecMap);
  cout << "Read xsec map for " << xsecMap.size() << " datasets" << endl;

  map<string, float> plotMap;
  readMap("plotMap_Zgg.dat", plotMap);
  cout << "Read plot map for " << plotMap.size() << " datasets" << endl;

  TH1D* histo[999] = {0};

  int ngen = 0;
  float lumi = 0.0;

  for (map<string, float>::iterator it = plotMap.begin(); it != plotMap.end(); it++) {
    TFile file(("data/" + version + "/" + it->first + ".root").c_str()); 
    int index = int(it->second);
    if (index == 0) {
      lumi = lumiMap[it->first];
      histo[index] = (TH1D*)gDirectory->Get(title.c_str());
      histo[index]->SetDirectory(0);
    }
    if (index != 0) {
      ngen = ((TH1D*)gDirectory->Get("h_nevt"))->GetBinContent(1);
      float norm = lumi/ngen;
      if (histo[index]) {
        histo[index]->Add((TH1D*)gDirectory->Get(title.c_str()), norm);
      } else {
        histo[index] = (TH1D*)gDirectory->Get(title.c_str());
        histo[index]->SetDirectory(0);
        histo[index]->Scale(norm);
      }
    }
    file.Close();
  }

  for (uint i = 0; i < sizeof(histo)/sizeof(histo[0]); i++) {
    if (histo[i]) {
      cout << i << " " << histo[i]->Integral() << endl;
    }
  }

}
