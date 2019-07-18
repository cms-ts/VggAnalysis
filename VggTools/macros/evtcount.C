void evtcount(TString list="lists/Run2017B_SingleElectron.txt") {

  cout << "list: " << list << endl;

  TChain* chain = new TChain("Events");

  ifstream file(list.Data());
  while (file.good()) {
    TString line;
    line.ReadLine(file);
    if (!line.IsWhitespace() && !line.BeginsWith("#")) {
      chain->Add(line.Data());
    }
  }
  file.close();

  TString dataset = TString(gSystem->BaseName(list)).ReplaceAll(".list", "");

  cout << "dataset: " << dataset << " ";
  cout << "files: " << chain->GetListOfFiles()->GetEntries() << " ";
  cout << "events: " << chain->GetEntries() << endl;

  delete chain;

}
