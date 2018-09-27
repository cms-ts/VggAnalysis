#pragma cling load("libTreePlayer.so")

void run(TString input="lists/Run2017B_DoubleEG.list", TString output="selector.root") {

  TString option = "";
  if (input.Contains("Run2016")) option="DT";
  if (input.Contains("Run2017")) option="DT";
  if (input.Contains("Run2018")) option="DT";
  if (input.Contains("RunIISummer16NanoAOD")) option="MC";
  if (input.Contains("RunIIFall17NanoAOD")) option="MC";
  if (input.Contains("RunIIFall18NanoAOD")) option="MC";
  if (option.Length()==0) {
    cout << "unknown input list: " << input << endl;
    return;
  }

  cout << "input list: " << input << endl;

  vector<std::string> files;

  ifstream file(input.Data());
  while (file.good()) {
    TString line;
    line.ReadLine(file);
    if (!line.IsWhitespace() && !line.BeginsWith("#")) {
      files.push_back(line.Data());
    }
  }
  file.close();

  if (files.size()==0) {
    cout << "no files to process" << endl;
    return;
  }

  int nWorkers = 4;

  ROOT::EnableThreadSafety();
  ROOT::TTreeProcessorMP workers(nWorkers);

  int nevt = -1;

  TSelector* selector;

  if (option.Contains("DT")) {
#if defined(__APPLE__)
    selector = TSelector::GetSelector("mainSelectorDT.C");
#else
    selector = TSelector::GetSelector("mainSelectorDT.C+");
#endif
    selector->SetOption("DT");
    workers.Process(files, *selector, "Events", nevt);
  }
  if (option.Contains("MC")) {
#if defined(__APPLE__)
    selector = TSelector::GetSelector("mainSelectorMC.C");
#else
    selector = TSelector::GetSelector("mainSelectorMC.C+");
#endif
    selector->SetOption("MC");
    workers.Process(files, *selector, "Events", nevt);
  }

  Info("run", "output file: %s", output.Data());
  TFile f(output.Data(), "RECREATE");
  f.cd();
  TList* fOutput = selector->GetOutputList();
  TIter next(fOutput);
  TObject* obj = 0;
  while ((obj = next())) {
    if (!TString(obj->ClassName()).Contains("TH")) continue;
    Info("run", "writing %s", obj->GetName());
    obj->Write();
  }
  f.Close();

  TH1D* h_nevt = dynamic_cast<TH1D*>(fOutput->FindObject("h_nevt"));
  int nevt0 = 0;
  if (h_nevt) nevt0 = h_nevt->GetBinContent(1);

  Info("run", "processed events: %d", nevt0);

  TChain* chain = new TChain("Events");
  for (int i=0; i < files.size(); i++) {
    chain->Add(files[i].c_str());
  }
  int nevt1 = chain->GetEntries();
  delete chain;

  if (nevt0 != nevt1) {
    Error("run", "expected events: %d", nevt1);
  }

}
