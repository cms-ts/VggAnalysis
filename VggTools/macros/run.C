#pragma cling load("libTreePlayer.so")

void run(TString input="lists/Run2017B_DoubleEG_31Mar2018.list", TString output="selector.root") {

  TDatime now;
  Info("run", "%s", now.AsSQLString());

  TString option = "";
  if (input.Contains("Run2016H")) option="DT16H";
  if (input.Contains("Run2016") && !input.Contains("Run2016H")) option="DT16";
  if (input.Contains("Run2017B")) option="DT17B";
  if (input.Contains("Run2017") && !input.Contains("Run2017B")) option="DT17";
  if (input.Contains("Run2018")) option="DT18";
  if (input.Contains("RunIISummer16NanoAOD")) option="MC16";
  if (input.Contains("RunIIFall17NanoAOD")) option="MC17";
  if (input.Contains("RunIIFall18NanoAOD")) option="MC18";
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

  int nWorkers = 10;
  if (gROOT->IsBatch()) nWorkers = 2;

  ROOT::EnableThreadSafety();
  ROOT::TTreeProcessorMP workers(nWorkers);

  int nevt = -1;

  TSelector* selector;

  if (option.Contains("DT")) {
#if defined(__APPLE__)
    if (option.Contains("DT16H"))                             selector = TSelector::GetSelector("mainSelectorDT16H.C");
    if (option.Contains("DT16") && !option.Contains("DT16H")) selector = TSelector::GetSelector("mainSelectorDT16.C");
    if (option.Contains("DT17B"))                             selector = TSelector::GetSelector("mainSelectorDT17B.C");
    if (option.Contains("DT17") && !option.Contains("DT17B")) selector = TSelector::GetSelector("mainSelectorDT17.C");
    if (option.Contains("DT18"))                              selector = TSelector::GetSelector("mainSelectorDT18.C");
#else
    if (option.Contains("DT16H"))                             selector = TSelector::GetSelector("mainSelectorDT16H.C+");
    if (option.Contains("DT16") && !option.Contains("DT16H")) selector = TSelector::GetSelector("mainSelectorDT16.C+");
    if (option.Contains("DT17B"))                             selector = TSelector::GetSelector("mainSelectorDT17B.C+");
    if (option.Contains("DT17") && !option.Contains("DT17B")) selector = TSelector::GetSelector("mainSelectorDT17.C+");
    if (option.Contains("DT18"))                              selector = TSelector::GetSelector("mainSelectorDT18.C+");
#endif
    selector->SetOption("DT");
    workers.Process(files, *selector, "Events", nevt);
  }
  if (option.Contains("MC")) {
#if defined(__APPLE__)
    if (option.Contains("MC16")) selector = TSelector::GetSelector("mainSelectorMC16.C");
    if (option.Contains("MC17")) selector = TSelector::GetSelector("mainSelectorMC17.C");
    if (option.Contains("MC18")) selector = TSelector::GetSelector("mainSelectorMC18.C");
#else
    if (option.Contains("MC16")) selector = TSelector::GetSelector("mainSelectorMC16.C+");
    if (option.Contains("MC17")) selector = TSelector::GetSelector("mainSelectorMC17.C+");
    if (option.Contains("MC18")) selector = TSelector::GetSelector("mainSelectorMC18.C+");
#endif
    selector->SetOption("MC");
    if (input.Contains("WJetsToLNu"))                   selector->SetOption("MC,WJetsToLNu");
    if (input.Contains("WG") && !input.Contains("WGG")) selector->SetOption("MC,WG");
    if (input.Contains("WGG"))                          selector->SetOption("MC,WGG");
    if (input.Contains("WTauNu"))                       selector->SetOption("MC,WTauNu");
    if (input.Contains("DYJetsToLL"))                   selector->SetOption("MC,DYJetsToLL");
    if (input.Contains("ZG") && !input.Contains("ZGG")) selector->SetOption("MC,ZG");
    if (input.Contains("ZGG"))                          selector->SetOption("MC,ZGG");
    if (input.Contains("ZTauTau"))                      selector->SetOption("MC,ZTauTau");
    workers.Process(files, *selector, "Events", nevt);
  }

  now = TDatime();
  Info("run", "%s", now.AsSQLString());

  Info("run", "output file: %s", output.Data());
  TFile f(output.Data(), "RECREATE");
  f.cd();
  TList* fOutput = selector->GetOutputList();
  TIter next(fOutput);
  TObject* obj = 0;
  while ((obj = next())) {
    if (!TString(obj->ClassName()).Contains("TH")) continue;
    if (!TString(obj->GetName()).Contains("h_")) continue;
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

  now = TDatime();
  Info("run", "%s", now.AsSQLString());

}
