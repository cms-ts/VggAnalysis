#include "plot0.h"

void plot0(string title="") {

  map<string, float> lumiData;

  ifstream input0("lumi.dat");
  string line0;
  while (getline(input0, line0)) {
    if (line0.length() > 0 && line0[0] != '#') {
      istringstream stream(line0);
      string key;
      float val;
      stream >> key >> val;
      lumiData[key] = val;
//      cout << key << " " << val << endl;
    }
  }
  input0.close();
  cout << "Read lumi data for " << lumiData.size() << " datasets" << endl;

  map<string, float> xsecData;

  ifstream input1("xsec.dat");
  string line1;
  while (getline(input0, line0)) {
    if (line0.length() > 0 && line0[0] != '#') {
      istringstream stream(line0);
      string key;
      float val;
      stream >> key >> val;
      xsecData[key] = val;
//      cout << key << " " << val << endl;
    }
  }
  input1.close();
  cout << "Read xsec data for " << xsecData.size() << " datasets" << endl;

}
