void run6(TString input="lists/Run2017B_DoubleEG.list", TString output="selector.root") {

#if defined(__APPLE__)
  gInterpreter->AddIncludePath("/Users/dellaric/Unix/lib/xrootd-4.8/include/xrootd");
#else
  gInterpreter->AddIncludePath("/cvmfs/cms.cern.ch/slc6_amd64_gcc700/external/xrootd/4.8.3/include/xrootd");
#endif

  gSystem->Setenv("ROOT_INCLUDE_PATH", "$HOME/work/cms/proof/ALT1");

  TProof* proof = 0;

  //proof = TProof::Open("");
  //proof = TProof::Open("workers=4");
  //proof = TProof::Open("proof://dellaric@farmui01.ts.infn.it:21001");
  //proof = TProof::Open("pod://");

  //if (proof) proof->ClearCache();
  //if (proof) proof->Print();
  //if (proof) proof->SetProgressDialog(0);

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

  TChain* chain = new TChain("Events");

  ifstream file(input.Data());
  while (file.good()) {
    TString line;
    line.ReadLine(file);
    if (!line.IsWhitespace() && !line.BeginsWith("#")) {
      chain->Add(line.Data());
    }
  }
  file.close();

  if (chain->GetListOfFiles()->GetEntries()==0) {
    cout << "no files to process" << endl;
    return;
  }

  if (proof) proof->AddInput(new TNamed("OUTPUTFILE", "selector.root"));

  if (proof) chain->SetProof();

  if (proof) proof->SetParameter("PROOF_StatsHist", "");
//  if (proof) proof->SetParameter("PROOF_StatsTrace", "");
//  if (proof) proof->SetParameter("PROOF_SlaveStatsTrace", "");

  TSelector* selector;

  if (option.Contains("DT")) {
    if (proof) {
#if defined(__APPLE__)
      chain->Process("mainSelectorDT.C", "DT");
#else
      chain->Process("mainSelectorDT.C+", "DT");
#endif
    } else {
#if defined(__APPLE__)
      selector = TSelector::GetSelector("mainSelectorDT.C");
#else
      selector = TSelector::GetSelector("mainSelectorDT.C+");
#endif
      chain->Process(selector, "DT");
    }
  }
  if (option.Contains("MC")) {
    if (proof) {
#if defined(__APPLE__)
      chain->Process("mainSelectorMC.C", "MC");
#else
      chain->Process("mainSelectorMC.C+", "MC");
#endif
    } else {
#if defined(__APPLE__)
      selector = TSelector::GetSelector("mainSelectorMC.C");
#else
      selector = TSelector::GetSelector("mainSelectorMC.C+");
#endif
      chain->Process(selector, "MC");
    }
  }

  if (proof) chain->SetProof(0);

  Info("run6", "output file: %s", output.Data());
  TFile f(output.Data(), "RECREATE");
  f.cd();
  TList* fOutput;
  if (proof) {
    fOutput = proof->GetOutputList();
  } else {
    fOutput = selector->GetOutputList();
  }
  TIter next(fOutput);
  TObject* obj = 0;
  while ((obj = next())) {
    if (!TString(obj->ClassName()).Contains("TH")) continue;
    Info("run6", "writing %s", obj->GetName());
    obj->Write();
  }
  f.Close();

  TH1D* h_nevt = dynamic_cast<TH1D*>(fOutput->FindObject("h_nevt"));
  int nevt0 = 0;
  if (h_nevt) nevt0 = h_nevt->GetBinContent(1);

  Info("run6", "processed events: %d", nevt0);

  int nevt1 = chain->GetEntries();
  delete chain;

  if (nevt0 != nevt1) {
    Error("run6", "expected events: %d", nevt1);
  }

  if (proof) proof->GetQueryResult()->Print("F");
  if (proof) proof->ShowMissingFiles();

  if (proof) proof->GetManager()->Close();
  if (proof) proof->Close();

  if (proof) delete proof;

}
