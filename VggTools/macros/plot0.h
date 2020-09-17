#ifndef plot0_h
#define plot0_h

#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>

#include <vector>
#include <map>

using namespace std;

#include "TROOT.h"
#include "TSystem.h"
#include "TObject.h"
#include "TColor.h"
#include "TFile.h"
#include "TLine.h"
#include "TMarker.h"
#include "TStyle.h"
#include "TGaxis.h"
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
#include "TFrame.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TVirtualFitter.h"

void readMap(string myFile, map<string, double> &myMap) {
  ifstream input(myFile.data());
  string line;
  while (getline(input, line)) {
    if (line.length() > 0 && line[0] != '#') {
      istringstream stream(line);
      string key;
      double val;
      stream >> key >> val;
      myMap[key] = val;
    }
  }
  input.close();
}

void readMultiMap(string myFile, multimap<string, double> &myMap) {
  ifstream input(myFile.data());
  string line;
  while (getline(input, line)) {
    if (line.length() > 0 && line[0] != '#') {
      istringstream stream(line);
      string key;
      double val;
      stream >> key >> val;
      myMap.insert(pair<string, double>(key, val));
    }
  }
  input.close();
}

#endif
