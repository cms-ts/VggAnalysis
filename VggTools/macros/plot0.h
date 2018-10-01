
#include "TROOT.h"
#include "TSystem.h"
#include "TObject.h"
#include "TColor.h"
#include "TFile.h"
#include "TLine.h"
#include "TMarker.h"
#include "TStyle.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH1D.h"
#include "TProfile.h"
#include "THStack.h"
#include "TMath.h"
#include "TVectorD.h"
#include "TMatrix.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TPad.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TVirtualFitter.h"

#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>

void readMap(string myFile, map<string, float> &myMap) {
  ifstream input(myFile.data());
  string line;
  while (getline(input, line)) {
    if (line.length() > 0 && line[0] != '#') {
      istringstream stream(line);
      string key;
      float val;
      stream >> key >> val;
      myMap.insert(pair<string, float>(key, val));
//      cout << key << " " << val << endl;
    }
  }
  input.close();
}

void readMultiMap(string myFile, multimap<string, float> &myMap) {
  ifstream input(myFile.data());
  string line;
  while (getline(input, line)) {
    if (line.length() > 0 && line[0] != '#') {
      istringstream stream(line);
      string key;
      float val;
      stream >> key >> val;
      myMap.insert(pair<string, float>(key, val));
//      cout << key << " " << val << endl;
    }
  }
  input.close();
}

