#include "plot0.h"

void plot0(string title="") {

  map<string, float> lumiMap;
  readMap("lumi.dat", lumiMap);
  cout << "Read lumi map for " << lumiMap.size() << " datasets" << endl;

  map<string, float> xsecMap;
  readMap("xsec.dat", xsecMap);
  cout << "Read xsec map for " << xsecMap.size() << " datasets" << endl;

  map<string, float> plotMap;
  readMap("plotMap_Zgg.dat", plotMap);
  cout << "Read plot map for " << plotMap.size() << " datasets" << endl;

  map<string, float>::iterator it;
  for (it=plotMap.begin(); it!=plotMap.end(); it++) {
    cout << it->first << " " << it->second << endl;
  }

}
