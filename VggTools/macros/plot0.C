#include "plot0.h"

#include "utils.C"

void plot0(string title="") {

  map<string, float> lumiMap;
  readMap("lumi.dat", lumiMap);
  cout << "Read lumi map for " << lumiMap.size() << " datasets" << endl;

  map<string, float> xsecMap;
  readMap("xsec.dat", xsecMap);
  cout << "Read xsec map for " << xsecMap.size() << " datasets" << endl;

}
