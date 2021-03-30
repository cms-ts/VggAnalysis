#include "TROOT.h"

#include "ROOT/TProcessExecutor.hxx"

#include "plot0.C"
#include "plot1.C"
#include "plot2.C"
#include "plot3.C"
#include "plot4.C"
#include "plot5.C"

void wrapper(string main, string plot, string title, string version, string options, string flag) {

  cout << "Processing " << main << ".C(\"" << plot << "\",\""
                                           << title << "\",\""
                                           << version << "\",\""
                                           << options << "\",\""
                                           << flag << "\")..." << endl;

  int status = 0;

  if (main == "plot0") status = plot0(plot, title, version, options, flag);
  if (main == "plot1") status = plot1(plot, title, version, options, flag);
  if (main == "plot2") status = plot2(plot, title, version, options, flag);
  if (main == "plot3") status = plot3(plot, title, version, options, flag);
  if (main == "plot4") status = plot4(plot, title, version, options, flag);
  if (main == "plot5") status = plot5(plot, title, version, options, flag);

  cout << endl;

  if (status) {
    cout << "ERROR in " << main << " !!" << endl;
    gSystem->Exit(1);
  }

}

void plot0_wrapper(string year, string version, string options, string flag) {

  vector<string> titles;

  bool SKIP1 = kTRUE;
  bool SKIP2 = kTRUE;
  bool SKIP3 = kTRUE;

  if (options.find("qcd") != string::npos) SKIP1 = kFALSE;

  if (flag != "reference") SKIP2 = kFALSE;

  if (year == "Run2") SKIP3 = kFALSE;

                               titles.push_back("h_W_ele");
                               titles.push_back("h_W_muo");

  if (         SKIP2 && SKIP3) titles.push_back("h_W_ele_npvs");
  if (                  SKIP3) titles.push_back("h_W_ele_npvs_w");
  if (         SKIP2 && SKIP3) titles.push_back("h_W_muo_npvs");
  if (                  SKIP3) titles.push_back("h_W_muo_npvs_w");

                               titles.push_back("h_W_ele0_pt");
                               titles.push_back("h_W_ele0_eta");
  if (         SKIP2 && SKIP3) titles.push_back("h_W_ele0_phi");
  if (         SKIP2 && SKIP3) titles.push_back("h_W_ele0_r9");
  if (         SKIP2 && SKIP3) titles.push_back("h_W_ele0_sieie");
                               titles.push_back("h_W_ele_met_pt");
  if (         SKIP2 && SKIP3) titles.push_back("h_W_ele_met_phi");

                               titles.push_back("h_W_muo0_pt");
                               titles.push_back("h_W_muo0_eta");
  if (         SKIP2 && SKIP3) titles.push_back("h_W_muo0_phi");
                               titles.push_back("h_W_muo_met_pt");
  if (         SKIP2 && SKIP3) titles.push_back("h_W_muo_met_phi");

  if (         SKIP2 && SKIP3) titles.push_back("h_W_ele0_mva");

  if (         SKIP2 && SKIP3) titles.push_back("h_W_ele0_pf_iso_all");
  if (         SKIP2 && SKIP3) titles.push_back("h_W_ele0_pf_iso_chg");
  if (         SKIP2 && SKIP3) titles.push_back("h_W_muo0_pf_iso_all");
  if (         SKIP2 && SKIP3) titles.push_back("h_W_muo0_pf_iso_chg");

  if (SKIP1                  ) titles.push_back("h_Z_ele");
  if (SKIP1                  ) titles.push_back("h_Z_muo");

  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_Z_ele_npvs");
  if (SKIP1 &&          SKIP3) titles.push_back("h_Z_ele_npvs_w");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_Z_muo_npvs");
  if (SKIP1 &&          SKIP3) titles.push_back("h_Z_muo_npvs_w");

  if (SKIP1 &&          SKIP3) titles.push_back("h_Z_ele0_pt");
  if (SKIP1                  ) titles.push_back("h_Z_ele0_eta");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_Z_ele0_phi");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_Z_ele0_r9");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_Z_ele0_sieie");
  if (SKIP1 &&          SKIP3) titles.push_back("h_Z_ele1_pt");
  if (SKIP1 &&          SKIP3) titles.push_back("h_Z_ele1_eta");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_Z_ele1_phi");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_Z_ele1_r9");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_Z_ele1_sieie");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_Z_ele_met_pt");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_Z_ele_met_phi");

  if (SKIP1 &&          SKIP3) titles.push_back("h_Z_muo0_pt");
  if (SKIP1                  ) titles.push_back("h_Z_muo0_eta");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_Z_muo0_phi");
  if (SKIP1 &&          SKIP3) titles.push_back("h_Z_muo1_pt");
  if (SKIP1 &&          SKIP3) titles.push_back("h_Z_muo1_eta");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_Z_muo1_phi");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_Z_muo_met_pt");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_Z_muo_met_phi");

  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_Z_ele0_mva");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_Z_ele1_mva");

  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_Z_ele0_pf_iso_all");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_Z_ele0_pf_iso_chg");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_Z_ele1_pf_iso_all");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_Z_ele1_pf_iso_chg");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_Z_muo0_pf_iso_all");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_Z_muo0_pf_iso_chg");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_Z_muo1_pf_iso_all");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_Z_muo1_pf_iso_chg");

  if (         SKIP2 && SKIP3) titles.push_back("h_W_ele_njets");
  if (         SKIP2 && SKIP3) titles.push_back("h_W_ele_jet0_pt");
  if (         SKIP2 && SKIP3) titles.push_back("h_W_ele_jet0_eta");
  if (         SKIP2 && SKIP3) titles.push_back("h_W_ele_jet0_phi");
  if (         SKIP2 && SKIP3) titles.push_back("h_W_muo_njets");
  if (         SKIP2 && SKIP3) titles.push_back("h_W_muo_jet0_pt");
  if (         SKIP2 && SKIP3) titles.push_back("h_W_muo_jet0_eta");
  if (         SKIP2 && SKIP3) titles.push_back("h_W_muo_jet0_phi");

  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_Z_ele_njets");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_Z_ele_jet0_pt");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_Z_ele_jet0_eta");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_Z_ele_jet0_phi");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_Z_muo_njets");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_Z_muo_jet0_pt");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_Z_muo_jet0_eta");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_Z_muo_jet0_phi");

                               titles.push_back("h_W_ele_nphotons");
  if (                  SKIP3) titles.push_back("h_WG_ele_ele0_pt");
  if (                  SKIP3) titles.push_back("h_WG_ele_ele0_eta");
  if (                  SKIP3) titles.push_back("h_WG_ele_ele0_phi");
                               titles.push_back("h_WG_ele_pho0_pt");
                               titles.push_back("h_WG_ele_pho0_eta");
                               titles.push_back("h_WG_ele_pho0_phi");
  if (         SKIP2 && SKIP3) titles.push_back("h_WG_ele_pho0_r9");
  if (         SKIP2 && SKIP3) titles.push_back("h_WG_ele_pho0_sieie");
  if (         SKIP2 && SKIP3) titles.push_back("h_WG_ele_pho0_jet0_dR");
  if (         SKIP2 && SKIP3) titles.push_back("h_WG_ele_pho0_mva");
  if (         SKIP2 && SKIP3) titles.push_back("h_WG_ele_pho0_pf_iso_all");
  if (         SKIP2 && SKIP3) titles.push_back("h_WG_ele_pho0_pf_iso_chg");
  if (         SKIP2         ) titles.push_back("h_WG_ele_pho0_dR");

  if (         SKIP2 && SKIP3) titles.push_back("h_WG_ele_pho0_pf_iso_all_nocut_eb");
  if (         SKIP2 && SKIP3) titles.push_back("h_WG_ele_pho0_pf_iso_all_nocut_ee");
  if (         SKIP2 && SKIP3) titles.push_back("h_WG_ele_pho0_sieie_nocut_eb");
  if (         SKIP2 && SKIP3) titles.push_back("h_WG_ele_pho0_sieie_nocut_ee");

                               titles.push_back("h_WGG_ele_ele0_pt");
                               titles.push_back("h_WGG_ele_ele0_eta");
                               titles.push_back("h_WGG_ele_ele0_phi");
                               titles.push_back("h_WGG_ele_pho0_pt");
                               titles.push_back("h_WGG_ele_pho0_eta");
                               titles.push_back("h_WGG_ele_pho0_phi");
  if (         SKIP2 && SKIP3) titles.push_back("h_WGG_ele_pho0_sieie");
  if (         SKIP2 && SKIP3) titles.push_back("h_WGG_ele_pho0_mva");
                               titles.push_back("h_WGG_ele_pho1_pt");
                               titles.push_back("h_WGG_ele_pho1_eta");
                               titles.push_back("h_WGG_ele_pho1_phi");
  if (         SKIP2 && SKIP3) titles.push_back("h_WGG_ele_pho1_r9");
  if (         SKIP2 && SKIP3) titles.push_back("h_WGG_ele_pho1_sieie");
  if (         SKIP2 && SKIP3) titles.push_back("h_WGG_ele_pho1_jet0_dR");
  if (         SKIP2 && SKIP3) titles.push_back("h_WGG_ele_pho1_mva");
  if (         SKIP2 && SKIP3) titles.push_back("h_WGG_ele_pho1_pf_iso_all");
  if (         SKIP2 && SKIP3) titles.push_back("h_WGG_ele_pho1_pf_iso_chg");
  if (         SKIP2 && SKIP3) titles.push_back("h_WGG_ele_pho1_dR");
  if (         SKIP2 && SKIP3) titles.push_back("h_WGG_ele_pho0_pho1_dR");

                               titles.push_back("h_W_muo_nphotons");
  if (                  SKIP3) titles.push_back("h_WG_muo_muo0_pt");
  if (                  SKIP3) titles.push_back("h_WG_muo_muo0_eta");
  if (                  SKIP3) titles.push_back("h_WG_muo_muo0_phi");
                               titles.push_back("h_WG_muo_pho0_pt");
                               titles.push_back("h_WG_muo_pho0_eta");
                               titles.push_back("h_WG_muo_pho0_phi");
  if (         SKIP2 && SKIP3) titles.push_back("h_WG_muo_pho0_r9");
  if (         SKIP2 && SKIP3) titles.push_back("h_WG_muo_pho0_sieie");
  if (         SKIP2 && SKIP3) titles.push_back("h_WG_muo_pho0_jet0_dR");
  if (         SKIP2 && SKIP3) titles.push_back("h_WG_muo_pho0_mva");
  if (         SKIP2 && SKIP3) titles.push_back("h_WG_muo_pho0_pf_iso_all");
  if (         SKIP2 && SKIP3) titles.push_back("h_WG_muo_pho0_pf_iso_chg");
  if (         SKIP2         ) titles.push_back("h_WG_muo_pho0_dR");

  if (         SKIP2 && SKIP3) titles.push_back("h_WG_muo_pho0_pf_iso_all_nocut_eb");
  if (         SKIP2 && SKIP3) titles.push_back("h_WG_muo_pho0_pf_iso_all_nocut_ee");
  if (         SKIP2 && SKIP3) titles.push_back("h_WG_muo_pho0_sieie_nocut_eb");
  if (         SKIP2 && SKIP3) titles.push_back("h_WG_muo_pho0_sieie_nocut_ee");

                               titles.push_back("h_WGG_muo_muo0_pt");
                               titles.push_back("h_WGG_muo_muo0_eta");
                               titles.push_back("h_WGG_muo_muo0_phi");
                               titles.push_back("h_WGG_muo_pho0_pt");
                               titles.push_back("h_WGG_muo_pho0_eta");
                               titles.push_back("h_WGG_muo_pho0_phi");
  if (         SKIP2 && SKIP3) titles.push_back("h_WGG_muo_pho0_sieie");
  if (         SKIP2 && SKIP3) titles.push_back("h_WGG_muo_pho0_mva");
                               titles.push_back("h_WGG_muo_pho1_pt");
                               titles.push_back("h_WGG_muo_pho1_eta");
                               titles.push_back("h_WGG_muo_pho1_phi");
  if (         SKIP2 && SKIP3) titles.push_back("h_WGG_muo_pho1_r9");
  if (         SKIP2 && SKIP3) titles.push_back("h_WGG_muo_pho1_sieie");
  if (         SKIP2 && SKIP3) titles.push_back("h_WGG_muo_pho1_jet0_dR");
  if (         SKIP2 && SKIP3) titles.push_back("h_WGG_muo_pho1_mva");
  if (         SKIP2 && SKIP3) titles.push_back("h_WGG_muo_pho1_pf_iso_all");
  if (         SKIP2 && SKIP3) titles.push_back("h_WGG_muo_pho1_pf_iso_chg");
  if (         SKIP2 && SKIP3) titles.push_back("h_WGG_muo_pho1_dR");
  if (         SKIP2 && SKIP3) titles.push_back("h_WGG_muo_pho0_pho1_dR");

  if (SKIP1                  ) titles.push_back("h_Z_ele_nphotons");
  if (SKIP1 &&          SKIP3) titles.push_back("h_ZG_ele_ele0_pt");
  if (SKIP1 &&          SKIP3) titles.push_back("h_ZG_ele_ele0_eta");
  if (SKIP1 &&          SKIP3) titles.push_back("h_ZG_ele_ele0_phi");
  if (SKIP1 &&          SKIP3) titles.push_back("h_ZG_ele_ele1_pt");
  if (SKIP1 &&          SKIP3) titles.push_back("h_ZG_ele_ele1_eta");
  if (SKIP1 &&          SKIP3) titles.push_back("h_ZG_ele_ele1_phi");
  if (SKIP1                  ) titles.push_back("h_ZG_ele_pho0_pt");
  if (SKIP1                  ) titles.push_back("h_ZG_ele_pho0_eta");
  if (SKIP1                  ) titles.push_back("h_ZG_ele_pho0_phi");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZG_ele_pho0_r9");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZG_ele_pho0_sieie");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZG_ele_pho0_jet0_dR");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZG_ele_pho0_mva");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZG_ele_pho0_pf_iso_all");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZG_ele_pho0_pf_iso_chg");
  if (SKIP1 && SKIP2         ) titles.push_back("h_ZG_ele_pho0_dR");

  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZG_ele_pho0_pt_fsr_iso");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZG_ele_pho0_pt_fsr_noiso");

  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZG_ele_pho0_pf_iso_all_nocut_eb");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZG_ele_pho0_pf_iso_all_nocut_ee");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZG_ele_pho0_sieie_nocut_eb");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZG_ele_pho0_sieie_nocut_ee");

  if (SKIP1                  ) titles.push_back("h_ZGG_ele_ele0_pt");
  if (SKIP1                  ) titles.push_back("h_ZGG_ele_ele0_eta");
  if (SKIP1                  ) titles.push_back("h_ZGG_ele_ele0_phi");
  if (SKIP1                  ) titles.push_back("h_ZGG_ele_ele1_pt");
  if (SKIP1                  ) titles.push_back("h_ZGG_ele_ele1_eta");
  if (SKIP1                  ) titles.push_back("h_ZGG_ele_ele1_phi");
  if (SKIP1                  ) titles.push_back("h_ZGG_ele_pho0_pt");
  if (SKIP1                  ) titles.push_back("h_ZGG_ele_pho0_eta");
  if (SKIP1                  ) titles.push_back("h_ZGG_ele_pho0_phi");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZGG_ele_pho0_sieie");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZGG_ele_pho0_mva");
  if (SKIP1                  ) titles.push_back("h_ZGG_ele_pho1_pt");
  if (SKIP1                  ) titles.push_back("h_ZGG_ele_pho1_eta");
  if (SKIP1                  ) titles.push_back("h_ZGG_ele_pho1_phi");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZGG_ele_pho1_r9");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZGG_ele_pho1_sieie");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZGG_ele_pho1_jet0_dR");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZGG_ele_pho1_mva");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZGG_ele_pho1_pf_iso_all");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZGG_ele_pho1_pf_iso_chg");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZGG_ele_pho1_dR");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZGG_ele_pho0_pho1_dR");

  if (SKIP1                  ) titles.push_back("h_Z_muo_nphotons");
  if (SKIP1 &&          SKIP3) titles.push_back("h_ZG_muo_muo0_pt");
  if (SKIP1 &&          SKIP3) titles.push_back("h_ZG_muo_muo0_eta");
  if (SKIP1 &&          SKIP3) titles.push_back("h_ZG_muo_muo0_phi");
  if (SKIP1 &&          SKIP3) titles.push_back("h_ZG_muo_muo1_pt");
  if (SKIP1 &&          SKIP3) titles.push_back("h_ZG_muo_muo1_eta");
  if (SKIP1 &&          SKIP3) titles.push_back("h_ZG_muo_muo1_phi");
  if (SKIP1                  ) titles.push_back("h_ZG_muo_pho0_pt");
  if (SKIP1                  ) titles.push_back("h_ZG_muo_pho0_eta");
  if (SKIP1                  ) titles.push_back("h_ZG_muo_pho0_phi");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZG_muo_pho0_r9");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZG_muo_pho0_sieie");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZG_muo_pho0_jet0_dR");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZG_muo_pho0_mva");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZG_muo_pho0_pf_iso_all");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZG_muo_pho0_pf_iso_chg");
  if (SKIP1 && SKIP2         ) titles.push_back("h_ZG_muo_pho0_dR");

  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZG_muo_pho0_pt_fsr_iso");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZG_muo_pho0_pt_fsr_noiso");

  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZG_muo_pho0_pf_iso_all_nocut_eb");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZG_muo_pho0_pf_iso_all_nocut_ee");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZG_muo_pho0_sieie_nocut_eb");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZG_muo_pho0_sieie_nocut_ee");

  if (SKIP1                  ) titles.push_back("h_ZGG_muo_muo0_pt");
  if (SKIP1                  ) titles.push_back("h_ZGG_muo_muo0_eta");
  if (SKIP1                  ) titles.push_back("h_ZGG_muo_muo0_phi");
  if (SKIP1                  ) titles.push_back("h_ZGG_muo_muo1_pt");
  if (SKIP1                  ) titles.push_back("h_ZGG_muo_muo1_eta");
  if (SKIP1                  ) titles.push_back("h_ZGG_muo_muo1_phi");
  if (SKIP1                  ) titles.push_back("h_ZGG_muo_pho0_pt");
  if (SKIP1                  ) titles.push_back("h_ZGG_muo_pho0_eta");
  if (SKIP1                  ) titles.push_back("h_ZGG_muo_pho0_phi");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZGG_muo_pho0_sieie");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZGG_muo_pho0_mva");
  if (SKIP1                  ) titles.push_back("h_ZGG_muo_pho1_pt");
  if (SKIP1                  ) titles.push_back("h_ZGG_muo_pho1_eta");
  if (SKIP1                  ) titles.push_back("h_ZGG_muo_pho1_phi");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZGG_muo_pho1_r9");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZGG_muo_pho1_sieie");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZGG_muo_pho1_jet0_dR");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZGG_muo_pho1_mva");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZGG_muo_pho1_pf_iso_all");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZGG_muo_pho1_pf_iso_chg");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZGG_muo_pho1_dR");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZGG_muo_pho0_pho1_dR");

                               titles.push_back("h_WG_ele");
                               titles.push_back("h_WG_muo");
  if (SKIP1                  ) titles.push_back("h_ZG_ele");
  if (SKIP1                  ) titles.push_back("h_ZG_muo");

                               titles.push_back("h_WGG_ele");
                               titles.push_back("h_WGG_muo");
  if (SKIP1                  ) titles.push_back("h_ZGG_ele");
  if (SKIP1                  ) titles.push_back("h_ZGG_muo");

  if (         SKIP2 && SKIP3) titles.push_back("h_WG_ele_ele0_pho0");
                               titles.push_back("h_WGG_ele_pho0_pho1_pt");
                               titles.push_back("h_WGG_ele_pho0_pho1");
  if (         SKIP2 && SKIP3) titles.push_back("h_WGG_ele_ele0_pho0");
  if (         SKIP2 && SKIP3) titles.push_back("h_WGG_ele_ele0_pho1");
                               titles.push_back("h_WGG_ele_ele0_pho0_pho1");

  if (                  SKIP3) titles.push_back("h_WG_ele_ele0_pho0_fake");

  if (         SKIP2 && SKIP3) titles.push_back("h_WG_muo_muo0_pho0");
                               titles.push_back("h_WGG_muo_pho0_pho1_pt");
                               titles.push_back("h_WGG_muo_pho0_pho1");
  if (         SKIP2 && SKIP3) titles.push_back("h_WGG_muo_muo0_pho0");
  if (         SKIP2 && SKIP3) titles.push_back("h_WGG_muo_muo0_pho1");
                               titles.push_back("h_WGG_muo_muo0_pho0_pho1");

  if (                  SKIP3) titles.push_back("h_WG_muo_muo0_pho0_fake");

  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZG_ele_ele0_pho0");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZG_ele_ele1_pho0");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZG_ele_ele0_ele1_pho0");
  if (SKIP1                  ) titles.push_back("h_ZGG_ele_pho0_pho1_pt");
  if (SKIP1                  ) titles.push_back("h_ZGG_ele_pho0_pho1");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZGG_ele_ele0_pho1");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZGG_ele_ele1_pho1");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZGG_ele_ele0_pho0_pho1");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZGG_ele_ele1_pho0_pho1");
  if (SKIP1                  ) titles.push_back("h_ZGG_ele_ele0_ele1_pho0_pho1");

  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZG_muo_muo0_pho0");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZG_muo_muo0_muo1_pho0");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZG_muo_muo1_pho0");
  if (SKIP1                  ) titles.push_back("h_ZGG_muo_pho0_pho1_pt");
  if (SKIP1                  ) titles.push_back("h_ZGG_muo_pho0_pho1");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZGG_muo_muo0_pho1");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZGG_muo_muo1_pho1");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZGG_muo_muo0_pho0_pho1");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_ZGG_muo_muo1_pho0_pho1");
  if (SKIP1                  ) titles.push_back("h_ZGG_muo_muo0_muo1_pho0_pho1");

  if (         SKIP2 && SKIP3) titles.push_back("h_W_ele0_trig");

  if (         SKIP2 && SKIP3) titles.push_back("h_W_muo0_trig");

  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_Z_ele0_trig");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_Z_ele1_trig");

  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_Z_muo0_trig");
  if (SKIP1 && SKIP2 && SKIP3) titles.push_back("h_Z_muo1_trig");

  if (         SKIP2         ) titles.push_back("h_WGG_ele_pho0_pho1_pt_tl");
  if (         SKIP2         ) titles.push_back("h_WGG_muo_pho0_pho1_pt_tl");
  if (SKIP1 && SKIP2         ) titles.push_back("h_ZGG_ele_pho0_pho1_pt_tl");
  if (SKIP1 && SKIP2         ) titles.push_back("h_ZGG_muo_pho0_pho1_pt_tl");

  if (         SKIP2         ) titles.push_back("h_WGG_ele_pho0_pho1_pt_lt");
  if (         SKIP2         ) titles.push_back("h_WGG_muo_pho0_pho1_pt_lt");
  if (SKIP1 && SKIP2         ) titles.push_back("h_ZGG_ele_pho0_pho1_pt_lt");
  if (SKIP1 && SKIP2         ) titles.push_back("h_ZGG_muo_pho0_pho1_pt_lt");

  if (         SKIP2         ) titles.push_back("h_WGG_ele_pho0_pho1_pt_ll");
  if (         SKIP2         ) titles.push_back("h_WGG_muo_pho0_pho1_pt_ll");
  if (SKIP1 && SKIP2         ) titles.push_back("h_ZGG_ele_pho0_pho1_pt_ll");
  if (SKIP1 && SKIP2         ) titles.push_back("h_ZGG_muo_pho0_pho1_pt_ll");

  if (         SKIP2         ) titles.push_back("h_WGG_ele_pho0_pho1_pt_tl_genmatch");
  if (         SKIP2         ) titles.push_back("h_WGG_muo_pho0_pho1_pt_tl_genmatch");
  if (SKIP1 && SKIP2         ) titles.push_back("h_ZGG_ele_pho0_pho1_pt_tl_genmatch");
  if (SKIP1 && SKIP2         ) titles.push_back("h_ZGG_muo_pho0_pho1_pt_tl_genmatch");

  if (         SKIP2         ) titles.push_back("h_WGG_ele_pho0_pho1_pt_lt_genmatch");
  if (         SKIP2         ) titles.push_back("h_WGG_muo_pho0_pho1_pt_lt_genmatch");
  if (SKIP1 && SKIP2         ) titles.push_back("h_ZGG_ele_pho0_pho1_pt_lt_genmatch");
  if (SKIP1 && SKIP2         ) titles.push_back("h_ZGG_muo_pho0_pho1_pt_lt_genmatch");

  if (         SKIP2         ) titles.push_back("h_WGG_ele_pho0_pho1_pt_ll_genmatch");
  if (         SKIP2         ) titles.push_back("h_WGG_muo_pho0_pho1_pt_ll_genmatch");
  if (SKIP1 && SKIP2         ) titles.push_back("h_ZGG_ele_pho0_pho1_pt_ll_genmatch");
  if (SKIP1 && SKIP2         ) titles.push_back("h_ZGG_muo_pho0_pho1_pt_ll_genmatch");

  if (         SKIP2         ) titles.push_back("h_WGG_ele_pho0_pho1_pt_tl_genmatch2");
  if (         SKIP2         ) titles.push_back("h_WGG_muo_pho0_pho1_pt_tl_genmatch2");
  if (SKIP1 && SKIP2         ) titles.push_back("h_ZGG_ele_pho0_pho1_pt_tl_genmatch2");
  if (SKIP1 && SKIP2         ) titles.push_back("h_ZGG_muo_pho0_pho1_pt_tl_genmatch2");

  if (         SKIP2         ) titles.push_back("h_WGG_ele_pho0_pho1_pt_lt_genmatch2");
  if (         SKIP2         ) titles.push_back("h_WGG_muo_pho0_pho1_pt_lt_genmatch2");
  if (SKIP1 && SKIP2         ) titles.push_back("h_ZGG_ele_pho0_pho1_pt_lt_genmatch2");
  if (SKIP1 && SKIP2         ) titles.push_back("h_ZGG_muo_pho0_pho1_pt_lt_genmatch2");

  if (         SKIP2         ) titles.push_back("h_WGG_ele_pho0_pho1_pt_ll_genmatch2");
  if (         SKIP2         ) titles.push_back("h_WGG_muo_pho0_pho1_pt_ll_genmatch2");
  if (SKIP1 && SKIP2         ) titles.push_back("h_ZGG_ele_pho0_pho1_pt_ll_genmatch2");
  if (SKIP1 && SKIP2         ) titles.push_back("h_ZGG_muo_pho0_pho1_pt_ll_genmatch2");

  for (uint i = 0; i < titles.size(); i++) {

    string title = titles[i];

    string plot = "";
    if (title.find("h_W") != string::npos && title.find("ele") != string::npos) plot = "Wgg" + year + "_ele";
    if (title.find("h_W") != string::npos && title.find("muo") != string::npos) plot = "Wgg" + year + "_muo";
    if (title.find("h_Z") != string::npos && title.find("ele") != string::npos) plot = "Zgg" + year + "_ele";
    if (title.find("h_Z") != string::npos && title.find("muo") != string::npos) plot = "Zgg" + year + "_muo";

    wrapper("plot0", plot, title, version, options, flag);

  }

}

void plot1_wrapper(string year, string version, string options, string flag) {

  vector<string> titles;

  titles.push_back("h_W_ele");
  titles.push_back("h_W_muo");
  titles.push_back("h_WG_ele");
  titles.push_back("h_WG_muo");

  for (uint i = 0; i < titles.size(); i++) {

    string title = titles[i];

    string plot = "";
    if (title.find("h_W") != string::npos && title.find("ele") != string::npos) plot = "Wgg" + year + "_ele";
    if (title.find("h_W") != string::npos && title.find("muo") != string::npos) plot = "Wgg" + year + "_muo";
    if (title.find("h_Z") != string::npos && title.find("ele") != string::npos) plot = "Zgg" + year + "_ele";
    if (title.find("h_Z") != string::npos && title.find("muo") != string::npos) plot = "Zgg" + year + "_muo";

    wrapper("plot0", plot, title, version, options + ",nofit", flag);

    wrapper("plot0", plot, title, version, options + ",qcd,nofit", flag);

    wrapper("plot1", plot, title, version, options, flag);

  }

}

void plot2_wrapper(string year, string version, string options, string flag) {

  vector<string> titles;

  titles.push_back("h_WGG_ele_pho0_pt");
  titles.push_back("h_WGG_ele_pho1_pt");
  titles.push_back("h_WGG_ele_pho0_pho1_pt");
  titles.push_back("h_WGG_muo_pho0_pt");
  titles.push_back("h_WGG_muo_pho1_pt");
  titles.push_back("h_WGG_muo_pho0_pho1_pt");

  titles.push_back("h_ZGG_ele_pho0_pt");
  titles.push_back("h_ZGG_ele_pho1_pt");
  titles.push_back("h_ZGG_ele_pho0_pho1_pt");
  titles.push_back("h_ZGG_muo_pho0_pt");
  titles.push_back("h_ZGG_muo_pho1_pt");
  titles.push_back("h_ZGG_muo_pho0_pho1_pt");

  for (uint i = 0; i < titles.size(); i++) {

    string title = titles[i];

    string plot = "";
    if (title.find("h_W") != string::npos && title.find("ele") != string::npos) plot = "Wgg" + year + "_ele";
    if (title.find("h_W") != string::npos && title.find("muo") != string::npos) plot = "Wgg" + year + "_muo";
    if (title.find("h_Z") != string::npos && title.find("ele") != string::npos) plot = "Zgg" + year + "_ele";
    if (title.find("h_Z") != string::npos && title.find("muo") != string::npos) plot = "Zgg" + year + "_muo";

    wrapper("plot2", plot, title, version, options, flag);

  }

}

void plot3_wrapper(string year, string version, string options, string flag) {

  vector<string> titles;

  titles.push_back("h_WG_ele_pho0_pt");
  titles.push_back("h_WG_muo_pho0_pt");
  titles.push_back("h_ZG_ele_pho0_pt");
  titles.push_back("h_ZG_muo_pho0_pt");

  for (uint i = 0; i < titles.size(); i++) {

    string title = titles[i];

    string plot = "";
    if (title.find("h_W") != string::npos && title.find("ele") != string::npos) plot = "Wgg" + year + "_ele";
    if (title.find("h_W") != string::npos && title.find("muo") != string::npos) plot = "Wgg" + year + "_muo";
    if (title.find("h_Z") != string::npos && title.find("ele") != string::npos) plot = "Zgg" + year + "_ele";
    if (title.find("h_Z") != string::npos && title.find("muo") != string::npos) plot = "Zgg" + year + "_muo";

    wrapper("plot3", plot, title, version, options, flag);

  }

}

void plot4_wrapper(string year, string version, string options, string flag) {

  vector<string> titles;

  titles.push_back("h_WGG_ele_pho0_pt");
  titles.push_back("h_WGG_ele_pho1_pt");
  titles.push_back("h_WGG_ele_pho0_pho1_pt");
  titles.push_back("h_WGG_muo_pho0_pt");
  titles.push_back("h_WGG_muo_pho1_pt");
  titles.push_back("h_WGG_muo_pho0_pho1_pt");

  titles.push_back("h_ZGG_ele_pho0_pt");
  titles.push_back("h_ZGG_ele_pho1_pt");
  titles.push_back("h_ZGG_ele_pho0_pho1_pt");
  titles.push_back("h_ZGG_muo_pho0_pt");
  titles.push_back("h_ZGG_muo_pho1_pt");
  titles.push_back("h_ZGG_muo_pho0_pho1_pt");

  for (uint i = 0; i < titles.size(); i++) {

    string title = titles[i];

    string plot = "";
    if (title.find("h_W") != string::npos && title.find("ele") != string::npos) plot = "Wgg" + year + "_ele";
    if (title.find("h_W") != string::npos && title.find("muo") != string::npos) plot = "Wgg" + year + "_muo";
    if (title.find("h_Z") != string::npos && title.find("ele") != string::npos) plot = "Zgg" + year + "_ele";
    if (title.find("h_Z") != string::npos && title.find("muo") != string::npos) plot = "Zgg" + year + "_muo";

    wrapper("plot4", plot, title, version, options, flag);

  }

}

void plot5_wrapper(string year, string version, string options, string flag) {

  vector<string> titles;

  titles.push_back("h_WGG_ele_pho0_pt");
  titles.push_back("h_WGG_ele_pho1_pt");
  titles.push_back("h_WGG_ele_pho0_pho1_pt");
  titles.push_back("h_WGG_muo_pho0_pt");
  titles.push_back("h_WGG_muo_pho1_pt");
  titles.push_back("h_WGG_muo_pho0_pho1_pt");

  titles.push_back("h_ZGG_ele_pho0_pt");
  titles.push_back("h_ZGG_ele_pho1_pt");
  titles.push_back("h_ZGG_ele_pho0_pho1_pt");
  titles.push_back("h_ZGG_muo_pho0_pt");
  titles.push_back("h_ZGG_muo_pho1_pt");
  titles.push_back("h_ZGG_muo_pho0_pho1_pt");

  for (uint i = 0; i < titles.size(); i++) {

    string title = titles[i];

    string plot = "";
    if (title.find("h_W") != string::npos && title.find("ele") != string::npos) plot = "Wgg" + year + "_ele";
    if (title.find("h_W") != string::npos && title.find("muo") != string::npos) plot = "Wgg" + year + "_muo";
    if (title.find("h_Z") != string::npos && title.find("ele") != string::npos) plot = "Zgg" + year + "_ele";
    if (title.find("h_Z") != string::npos && title.find("muo") != string::npos) plot = "Zgg" + year + "_muo";

    wrapper("plot5", plot, title, version, options, flag);

  }

}

void process(string version="v00", string options="default", string flag="reference") {

  gROOT->SetBatch();

  vector <string> flags;

  if (flag == "all") {
    flags.push_back("reference");
    flags.push_back("bkg_stat");
    flags.push_back("jet_misid_stat");
    flags.push_back("pileup_up");
    flags.push_back("pileup_down");
//    flags.push_back("jec_up_2016");
//    flags.push_back("jec_up_2017");
//    flags.push_back("jec_up_2018");
//    flags.push_back("jec_down_2016");
//    flags.push_back("jec_down_2017");
//    flags.push_back("jec_down_2018");
//    flags.push_back("jer_up_2016");
//    flags.push_back("jer_up_2017");
//    flags.push_back("jer_up_2018");
//    flags.push_back("jer_down_2016");
//    flags.push_back("jer_down_2017");
//    flags.push_back("jer_down_2018");
    flags.push_back("sf_ele_eff_up");
    flags.push_back("sf_ele_eff_down");
    flags.push_back("sf_ele_reco_up");
    flags.push_back("sf_ele_reco_down");
    flags.push_back("sf_ele_trig_up");
    flags.push_back("sf_ele_trig_down");
    flags.push_back("sf_muo_id_up");
    flags.push_back("sf_muo_id_down");
    flags.push_back("sf_muo_iso_up");
    flags.push_back("sf_muo_iso_down");
    flags.push_back("sf_muo_trig_up");
    flags.push_back("sf_muo_trig_down");
    flags.push_back("sf_pho_eff_up");
    flags.push_back("sf_pho_eff_down");
    flags.push_back("sf_pho_veto_up_2016");
    flags.push_back("sf_pho_veto_up_2017");
    flags.push_back("sf_pho_veto_up_2018");
    flags.push_back("sf_pho_veto_down_2016");
    flags.push_back("sf_pho_veto_down_2017");
    flags.push_back("sf_pho_veto_down_2018");
    flags.push_back("l1prefiring_up");
    flags.push_back("l1prefiring_down");
    flags.push_back("eg_misid_up");
    flags.push_back("eg_misid_down");
//    flags.push_back("bkg_syst");
    flags.push_back("xsec_syst_wg");
    flags.push_back("xsec_syst_zg");
    flags.push_back("xsec_syst_others");
    flags.push_back("jet_misid_syst");
    flags.push_back("jet_misid_test");
    flags.push_back("jet_misid_qcd");
    flags.push_back("jet_misid_sherpa");
//    flags.push_back("jet_misid_mc");
    flags.push_back("jet_bkg_mc");
    flags.push_back("qcd_fit");
    flags.push_back("veto_ele_medium");
    flags.push_back("veto_muo_medium");
    flags.push_back("lumi_up");
    flags.push_back("lumi_down");
  } else {
    flags.push_back(flag);
  }

#if 1
  ROOT::TProcessExecutor workers(3);

  for (uint i = 0; i < flags.size(); i++) {

    string flag = flags[i];

    function<int(string)> process_work = [&](string year) {
      plot1_wrapper(year, version, options, flag);

      plot0_wrapper(year, version, options + ",qcd,nofit", flag);
      plot0_wrapper(year, version, options, flag);

      plot2_wrapper(year, version, options, flag);

      plot3_wrapper(year, version, options + ",qcd", flag);

      plot3_wrapper(year, version, options, flag);
      plot4_wrapper(year, version, options, flag);

      plot3_wrapper(year, version, options + ",identity0", flag);
      plot4_wrapper(year, version, options + ",identity0", flag);

      plot3_wrapper(year, version, options + ",identity1", flag);
      plot4_wrapper(year, version, options + ",identity1", flag);

      plot3_wrapper(year, version, options + ",closure0", flag);
      plot4_wrapper(year, version, options + ",closure0", flag);

      plot3_wrapper(year, version, options + ",closure1", flag);
      plot4_wrapper(year, version, options + ",closure1", flag);

      plot3_wrapper(year, version, options + ",closure2", flag);

      plot4_wrapper(year, version, options + ",paper", flag);

      plot4_wrapper(year, version, options + ",control1", flag);
      plot4_wrapper(year, version, options + ",control2", flag);
      plot4_wrapper(year, version, options + ",control3", flag);
      plot4_wrapper(year, version, options + ",control3,paper", flag);

      plot5_wrapper(year, version, options, flag);

      return 0;
    };

    workers.Map(process_work, {"2016", "2017", "2018"});

    process_work("Run2");

  }
#endif

#if 0
  vector<string> years;

  years.push_back("2016");
  years.push_back("2017");
  years.push_back("2018");

  years.push_back("Run2");

  ROOT::TProcessExecutor workers(flags.size());

  function<int(string)> process_work = [&](string flag) {
    for (uint i = 0; i < years.size(); i++) {

      string year = years[i];

      plot1_wrapper(year, version, options, flag);

      plot0_wrapper(year, version, options + ",qcd,nofit", flag);
      plot0_wrapper(year, version, options, flag);

      plot2_wrapper(year, version, options, flag);

      plot3_wrapper(year, version, options + ",qcd", flag);

      plot3_wrapper(year, version, options, flag);
      plot4_wrapper(year, version, options, flag);

      plot3_wrapper(year, version, options + ",identity0", flag);
      plot4_wrapper(year, version, options + ",identity0", flag);

      plot3_wrapper(year, version, options + ",identity1", flag);
      plot4_wrapper(year, version, options + ",identity1", flag);

      plot3_wrapper(year, version, options + ",closure0", flag);
      plot4_wrapper(year, version, options + ",closure0", flag);

      plot3_wrapper(year, version, options + ",closure1", flag);
      plot4_wrapper(year, version, options + ",closure1", flag);

      plot3_wrapper(year, version, options + ",closure2", flag);

      plot4_wrapper(year, version, options + ",paper", flag);

      plot5_wrapper(year, version, options, flag);
    }
    return 0;
  };

  workers.Map(process_work, flags);
#endif

#if 0
  vector<string> years;

  years.push_back("2016");
  years.push_back("2017");
  years.push_back("2018");

  //ROOT::TProcessExecutor workers(years.size()*flags.size());
  ROOT::TProcessExecutor workers(0);

  function<int(string)> process_work = [&](string arg) {

    string year = arg.substr(0, arg.find(":"));
    string flag = arg.substr(arg.find(":")+1, arg.length());

    plot1_wrapper(year, version, options, flag);

    plot0_wrapper(year, version, options + ",qcd,nofit", flag);
    plot0_wrapper(year, version, options, flag);

    plot2_wrapper(year, version, options, flag);

    plot3_wrapper(year, version, options + ",qcd", flag);

    plot3_wrapper(year, version, options, flag);
    plot4_wrapper(year, version, options, flag);

    plot3_wrapper(year, version, options + ",identity0", flag);
    plot4_wrapper(year, version, options + ",identity0", flag);

    plot3_wrapper(year, version, options + ",identity1", flag);
    plot4_wrapper(year, version, options + ",identity1", flag);

    plot3_wrapper(year, version, options + ",closure0", flag);
    plot4_wrapper(year, version, options + ",closure0", flag);

    plot3_wrapper(year, version, options + ",closure1", flag);
    plot4_wrapper(year, version, options + ",closure1", flag);

    plot3_wrapper(year, version, options + ",closure2", flag);

    plot4_wrapper(year, version, options + ",paper", flag);

    plot5_wrapper(year, version, options, flag);

    return 0;
  };

  vector<string> args;

  for (uint i = 0; i < flags.size(); i++) {
    for (uint j = 0; j < years.size(); j++) {
      args.push_back(years[j] + ":" + flags[i]);
    }
  }

  workers.Map(process_work, args);

  args.clear();

  for (uint i = 0; i < flags.size(); i++) {
    args.push_back("Run2:" + flags[i]);
  }

  workers.Map(process_work, args);
#endif

}

#ifndef __ACLIC__
int main(int argc, char *argv[]) {

  vector<string> args = {"process.exe", "v00", "default,nolog", "reference"};

  for (uint i = 0; i < argc; i++) args[i] = argv[i];

  process(args[1], args[2], args[3]);

  return 0;

}
#endif
