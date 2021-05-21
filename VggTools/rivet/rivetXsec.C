void _rivetXsec(string flag) {

cout << ">>> flag = " << flag << " <<<" << endl;

TFile* fileW = 0;
TFile* fileZ = 0;

if (flag == "OLD-01") {
  fileW = TFile::Open("rivet/wgg-2018.nlo.mini/WGGtotal.root");
  fileZ = TFile::Open("rivet/zgg-2018.nlo.mini/ZGGtotal.root");
}
if (flag == "OLD-02") {
  fileW = TFile::Open("rivet/wgg-2018.nlo.eta24/WGGtotal.root");
  fileZ = TFile::Open("rivet/zgg-2018.nlo.eta24/ZGGtotal.root");
}
if (flag == "OLD-03") {
  fileW = TFile::Open("rivet/wgg-2018.nlo.eta25/WGGtotal.root");
  fileZ = TFile::Open("rivet/zgg-2018.nlo.eta25/ZGGtotal.root");
}
if (flag == "OLD-04") {
  fileW = TFile::Open("rivet/wgg-2018.nlo/WGGtotal.root");
  fileZ = TFile::Open("rivet/zgg-2018.nlo/ZGGtotal.root");
}
if (flag == "OLD-05") {
  fileW = TFile::Open("rivet/wgg-2018.nlo.PART/WGGtotal.root");
  fileZ = TFile::Open("rivet/zgg-2018.nlo.PART/ZGGtotal.root");
}

if (flag == "NEW-00") {
  fileW = TFile::Open("/gpfs/cms/users/fvazzole/work/RIVET_TO_COMMIT/CMSSW_10_2_7/src/output/v15.wideSF.default/WGGToLLGG_5f_TuneCP5_13TeV-amcatnlo-pythia8/outWGGanalysis.root");
  fileZ = TFile::Open("/gpfs/cms/users/fvazzole/work/RIVET_TO_COMMIT/CMSSW_10_2_7/src/output/v15.wideSF.default/ZGGToLLGG_5f_TuneCP5_13TeV-amcatnlo-pythia8/outZGGanalysis.root");
}
if (flag == "NEW-01") {
  fileW = TFile::Open("rivet/wgg-2018.nlo.mini.pdf/WGGtotal.root");
  fileZ = TFile::Open("rivet/zgg-2018.nlo.mini.pdf/ZGGtotal.root");
}

if (fileW == 0 || fileZ == 0) return;

TH1D* h_nevtW = (TH1D*) fileW->Get("CMS_SMP_19_068/h_nevt");

TH1D* h_WGG_ele_pho0_pho1_pt = 0;
TH1D* h_WGG_muo_pho0_pho1_pt = 0;

if (h_nevtW != 0) {
  h_WGG_ele_pho0_pho1_pt = (TH1D*) fileW->Get("CMS_SMP_19_068/h_WGG_ele_pho0_pho1_pt");
  h_WGG_muo_pho0_pho1_pt = (TH1D*) fileW->Get("CMS_SMP_19_068/h_WGG_muo_pho0_pho1_pt");
}

if (h_nevtW == 0) {
  h_WGG_ele_pho0_pho1_pt = (TH1D*) fileW->Get("CMS_SMP_19_013_W/h_WGG_ele_pho0_pho1_pt_set_0");
  h_WGG_muo_pho0_pho1_pt = (TH1D*) fileW->Get("CMS_SMP_19_013_W/h_WGG_muo_pho0_pho1_pt_set_0");
}

TH1D* h_nevtZ = (TH1D*) fileZ->Get("CMS_SMP_19_067/h_nevt");

TH1D* h_ZGG_ele_pho0_pho1_pt = 0;
TH1D* h_ZGG_muo_pho0_pho1_pt = 0;

if (h_nevtZ != 0) {
  h_ZGG_ele_pho0_pho1_pt = (TH1D*) fileZ->Get("CMS_SMP_19_067/h_ZGG_ele_pho0_pho1_pt");
  h_ZGG_muo_pho0_pho1_pt = (TH1D*) fileZ->Get("CMS_SMP_19_067/h_ZGG_muo_pho0_pho1_pt");
}

if (h_nevtW == 0) {
  h_ZGG_ele_pho0_pho1_pt = (TH1D*) fileZ->Get("CMS_SMP_19_013_Z/h_ZGG_ele_pho0_pho1_pt_set_0");
  h_ZGG_muo_pho0_pho1_pt = (TH1D*) fileZ->Get("CMS_SMP_19_013_Z/h_ZGG_muo_pho0_pho1_pt_set_0");
}

TH1D* h_WGG_pho0_pho1_pt = (TH1D*) h_WGG_ele_pho0_pho1_pt->Clone("h_WGG_pho0_pho1_pt");
h_WGG_pho0_pho1_pt->Add(h_WGG_muo_pho0_pho1_pt);

TH1D* h_ZGG_pho0_pho1_pt = (TH1D*) h_ZGG_ele_pho0_pho1_pt->Clone("h_ZGG_pho0_pho1_pt");
h_ZGG_pho0_pho1_pt->Add(h_ZGG_muo_pho0_pho1_pt);

double xsec_stat_mc_genW = 0.;
double xsec_mc_genW = h_WGG_pho0_pho1_pt->IntegralAndError(0, h_WGG_pho0_pho1_pt->GetNbinsX()+1, xsec_stat_mc_genW);

if (h_nevtW) {
  double xsec_mc_total_genW = 2.001 * 0.79839723 * 1000.;
  xsec_mc_genW = xsec_mc_genW * xsec_mc_total_genW / h_nevtW->GetBinContent(2);
  xsec_stat_mc_genW = xsec_stat_mc_genW * xsec_mc_total_genW / h_nevtW->GetBinContent(2);
}

xsec_mc_genW = xsec_mc_genW * 0.5;
xsec_stat_mc_genW = xsec_stat_mc_genW * 0.5;

//
xsec_mc_genW = xsec_mc_genW * 0.80753600 / 0.79839723;
xsec_stat_mc_genW = xsec_stat_mc_genW * 0.80753600 / 0.79839723;
//

double xsec_stat_mc_genZ = 0.;
double xsec_mc_genZ = h_ZGG_pho0_pho1_pt->IntegralAndError(0, h_ZGG_pho0_pho1_pt->GetNbinsX()+1, xsec_stat_mc_genZ);

if (h_nevtZ) {
  double xsec_mc_total_genZ = 0.6832 * 0.76588448 * 1000.;
  xsec_mc_genZ = xsec_mc_genZ * xsec_mc_total_genZ / h_nevtZ->GetBinContent(2);
  xsec_stat_mc_genZ = xsec_stat_mc_genZ * xsec_mc_total_genZ / h_nevtZ->GetBinContent(2);
}

xsec_mc_genZ = xsec_mc_genZ * 0.5;
xsec_stat_mc_genZ = xsec_stat_mc_genZ * 0.5;

//
xsec_mc_genZ = xsec_mc_genZ * 0.76900024 / 0.76588448;
xsec_stat_mc_genZ = xsec_stat_mc_genZ * 0.76900024 / 0.76588448;
//

cout << endl;
cout << "fileW = " << fileW->GetName() << endl;
cout << "fileZ = " << fileZ->GetName() << endl;
cout << endl;
cout << "WGG xsec = " << xsec_mc_genW << " +- " << xsec_stat_mc_genW << " fb - (" << 100.*xsec_stat_mc_genW/xsec_mc_genW << " %)" << endl;
cout << "ZGG xsec = " << xsec_mc_genZ << " +- " << xsec_stat_mc_genZ << " fb - (" << 100.*xsec_stat_mc_genZ/xsec_mc_genZ << " %)" << endl;
cout << endl;

delete fileW;
delete fileZ;

}

void rivetXsec() {

cout << endl;

//_rivetXsec("NEW-00");
_rivetXsec("NEW-01");

_rivetXsec("OLD-01");
//_rivetXsec("OLD-02");
//_rivetXsec("OLD-03");
_rivetXsec("OLD-04");
//_rivetXsec("OLD-05");

}
