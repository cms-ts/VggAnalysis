void run5(TString input="lists/Run2017B_DoubleEG.list", TString output="selector.root") {

#if defined(__APPLE__)
  gInterpreter->AddIncludePath("/Users/dellaric/Unix/lib/xrootd-4.8/include/xrootd");
#else
  gInterpreter->AddIncludePath("/cvmfs/cms.cern.ch/slc6_amd64_gcc700/external/xrootd/4.8.3/include/xrootd");
#endif

  gSystem->Setenv("ROOT_INCLUDE_PATH", "$HOME/work/cms/proof/ALT1");

  TProof* proof = 0;

  //proof = TProof::Open("");
  proof = TProof::Open("workers=4");
  //proof = TProof::Open("proof://dellaric@farmui01.ts.infn.it:21001");
  //proof = TProof::Open("pod://");

  //proof->ClearCache();
  //proof->Print();
  //proof->SetProgressDialog(0);

  TString option = "";
  if (input.Contains("Run2016")) option="DT";
  if (input.Contains("Run2017")) option="DT";
  if (input.Contains("RunIISummer16NanoAOD")) option="MC";
  if (input.Contains("RunIIFall17NanoAOD")) option="MC";
  if (option.Length()==0) {
    cout << "unknown input list: " << input << endl;
    return;
  }

  cout << "input list: " << input << endl;

  vector<std::string> files;
  TDSet* dset = new TDSet("TTree", "Events", "");

  ifstream file(input.Data());
  while (file.good()) {
    TString line;
    line.ReadLine(file);
    if (!line.IsWhitespace() && !line.BeginsWith("#")) {
      files.push_back(line.Data());
      dset->Add(line.Data());
    }
  }
  file.close();

  if (dset->GetNumOfFiles()==0) {
    cout << "no files to process" << endl;
    return;
  }

  proof->SetParameter("PROOF_StatsHist", "");
//  proof->SetParameter("PROOF_StatsTrace", "");
//  proof->SetParameter("PROOF_SlaveStatsTrace", "");

  int nevt = -1;

  if (option.Contains("DT")) {
#if defined(__APPLE__)
    dset->Process("mainSelectorDT.C", "DT", nevt);
#else
    dset->Process("mainSelectorDT.C+", "DT", nevt);
#endif
  }
  if (option.Contains("MC")) {
#if defined(__APPLE__)
    dset->Process("mainSelectorMC.C", "MC", nevt);
#else
    dset->Process("mainSelectorMC.C+", "MC", nevt);
#endif
  }

  Info("run5", "output file: %s", output.Data());
  TFile f(output.Data(), "RECREATE");
  f.cd();
  TList* fOutput = proof->GetOutputList();
  TIter next(fOutput);
  TObject* obj = 0;
  while ((obj = next())) {
    if (!TString(obj->ClassName()).Contains("TH")) continue;
    Info("run5", "writing %s", obj->GetName());
    obj->Write();
  }
  f.Close();

  TH1D* h_nevt = dynamic_cast<TH1D*>(fOutput->FindObject("h_nevt"));
  int nevt0 = 0;
  if (h_nevt) nevt0 = h_nevt->GetBinContent(1);

  Info("run5", "processed events: %d", nevt0);

  TChain* chain = new TChain("Events");
  for (int i=0; i < files.size(); i++) {
    chain->Add(files[i].c_str());
  }
  int nevt1 = chain->GetEntries();
  delete chain;

  if (nevt0 != nevt1) {
    Error("run5", "expected events: %d", nevt1);
  }

  delete dset;

  proof->GetQueryResult()->Print("F");
  proof->ShowMissingFiles();

  proof->GetManager()->Close();
  proof->Close();

  delete proof;

}
