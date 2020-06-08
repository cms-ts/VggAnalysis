void draw(int year, bool isQCD, string filename, string fitfunc, string syst) {

   string sqcd = "";
   if (isQCD) sqcd = "_qcd";

   string txt_title = syst + "/sf_" + filename + "_" + fitfunc + sqcd + "_";
   txt_title += std::to_string(year);
   txt_title = txt_title + ".txt";

cout << txt_title << endl;

   int index[20];
   double sf[20];
   double sf_e[20];

   int npt = 0;

   ifstream in;
   in.open((txt_title).c_str());

   while ( kTRUE ) {

      in >> index[npt] >> sf[npt] >> sf_e[npt];

      if ( ! in.good() ) break;

      npt++;

   }

   in.close();

   for (int i = 0; i < 20; i++) {
   cout << index[i] << "  " << sf[i] << "  " << sf_e[i] << endl;
   }

   double xbins[7] = {0., 0.5, 1., 1.4442, 1.566, 2., 2.5};
   double ybins[5] = {20., 30., 40., 50., 200.};

   TH2D * h2 = new TH2D("elepho_sf","elepho_sf", 6, xbins, 4, ybins);

   h2->SetBinContent(1, 1, sf[0]);
   h2->SetBinContent(2, 1, sf[1]);
   h2->SetBinContent(3, 1, sf[2]);
   h2->SetBinContent(4, 1, 1.);
   h2->SetBinContent(5, 1, sf[3]);
   h2->SetBinContent(6, 1, sf[4]);

   h2->SetBinContent(1, 2, sf[5]);
   h2->SetBinContent(2, 2, sf[6]);
   h2->SetBinContent(3, 2, sf[7]);
   h2->SetBinContent(4, 2, 1.);
   h2->SetBinContent(5, 2, sf[8]);
   h2->SetBinContent(6, 2, sf[9]);

   h2->SetBinContent(1, 3, sf[10]);
   h2->SetBinContent(2, 3, sf[11]);
   h2->SetBinContent(3, 3, sf[12]);
   h2->SetBinContent(4, 3, 1.);
   h2->SetBinContent(5, 3, sf[13]);
   h2->SetBinContent(6, 3, sf[14]);

   h2->SetBinContent(1, 4, sf[15]);
   h2->SetBinContent(2, 4, sf[16]);
   h2->SetBinContent(3, 4, sf[17]);
   h2->SetBinContent(4, 4, 1.);
   h2->SetBinContent(5, 4, sf[18]);
   h2->SetBinContent(6, 4, sf[19]);


   h2->SetBinError(1, 1, sf_e[0]);
   h2->SetBinError(2, 1, sf_e[1]);
   h2->SetBinError(3, 1, sf_e[2]);
   h2->SetBinError(4, 1, 1.);
   h2->SetBinError(5, 1, sf_e[3]);
   h2->SetBinError(6, 1, sf_e[4]);

   h2->SetBinError(1, 2, sf_e[5]);
   h2->SetBinError(2, 2, sf_e[6]);
   h2->SetBinError(3, 2, sf_e[7]);
   h2->SetBinError(4, 2, 1.);
   h2->SetBinError(5, 2, sf_e[8]);
   h2->SetBinError(6, 2, sf_e[9]);

   h2->SetBinError(1, 3, sf_e[10]);
   h2->SetBinError(2, 3, sf_e[11]);
   h2->SetBinError(3, 3, sf_e[12]);
   h2->SetBinError(4, 3, 1.);
   h2->SetBinError(5, 3, sf_e[13]);
   h2->SetBinError(6, 3, sf_e[14]);

   h2->SetBinError(1, 4, sf_e[15]);
   h2->SetBinError(2, 4, sf_e[16]);
   h2->SetBinError(3, 4, sf_e[17]);
   h2->SetBinError(4, 4, 1.);
   h2->SetBinError(5, 4, sf_e[18]);
   h2->SetBinError(6, 4, sf_e[19]);

   gStyle->SetOptStat(0);

   string c_title = "Scale factors - " + fitfunc + " fit - " + std::to_string(year);

   TCanvas * c = new TCanvas("c","c",0,0,800,800);
   c->cd();
   h2->SetTitle((c_title).c_str());
   h2->Draw("COLZ TEXT ERROR");

   string plot_title = "../../macros/html/egamma_v6/" + syst + "/sf_egamma_misid_" + filename + "_" + fitfunc + sqcd + "_";
   plot_title += std::to_string(year);
   plot_title = plot_title + ".pdf";

   c->SaveAs((plot_title).c_str());

   string root_title = "../../macros/html/egamma_v6/" + syst + "/sf_egamma_misid_" + filename + "_" + fitfunc + sqcd + "_";
   root_title += std::to_string(year);
   root_title = root_title + ".root";

   TFile* file = new TFile((root_title).c_str(), "RECREATE");
   h2->Write("EGamma_SF2D");
   file->Close();
   delete file;

}
