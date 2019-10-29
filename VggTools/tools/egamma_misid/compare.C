void compare(int year, bool isQCD, string filename, string syst, string base, string variation) {

   string sqcd = "";
   if (isQCD) sqcd = "_qcd";

   string variation_title = "../../macros/html/egamma_v5/" + syst + "/sf_egamma_misid_" + filename + "_" + variation + sqcd + "_";
   variation_title += std::to_string(year);
   variation_title = variation_title + ".root";

   string base_title = "../../macros/html/egamma_v5/" + syst + "/sf_egamma_misid_" + filename + "_" + base + sqcd + "_";
   base_title += std::to_string(year);
   base_title = base_title + ".root";

   TFile * f_variation = new TFile((variation_title).c_str());
   TH2D * h_variation = (TH2D*)f_variation->Get("EGamma_SF2D");

   TFile * f_base = new TFile((base_title).c_str());
   TH2D * h_base = (TH2D*)f_base->Get("EGamma_SF2D");

   TH2D* h_ratio = (TH2D*)h_variation->Clone("h_ratio");
   h_ratio->Divide(h_base);

   TH2D* h_ratio_err = (TH2D*)h_variation->Clone("h_ratio_err");

   for(int i = 0; i <= h_ratio_err->GetNbinsX(); i++) {
     for(int j = 0; j <= h_ratio_err->GetNbinsY(); j++) {
       h_ratio_err->SetBinContent(i, j, 0.);
       h_ratio_err->SetBinError(i, j, 0.);
     }
   }

   for(int i = 0; i <= h_ratio_err->GetNbinsX(); i++) {
     for(int j = 0; j <= h_ratio_err->GetNbinsY(); j++) {
       h_ratio_err->SetBinContent(i, j, h_variation->GetBinError(i,j) / h_base->GetBinError(i,j));
     }
   }

   TCanvas * c1 = new TCanvas("c1","c1",0,0,1000,1000);
   c1->cd();
   h_ratio->SetTitle("Ratio variation/base");
   h_ratio->Draw("COLZ TEXT");

   TCanvas * c2 = new TCanvas("c2","c2",0,0,1000,1000);
   c2->cd();
   h_ratio_err->SetTitle("Error ratio variation/base");
   h_ratio_err->Draw("COLZ TEXT");

   string plot_ratio = "../../macros/html/egamma_v5/" + syst + "/ratio_sf_egamma_misid_" + filename + sqcd + "_";
   plot_ratio += std::to_string(year);
   plot_ratio = plot_ratio + ".pdf";

   string plot_ratio_err = "../../macros/html/egamma_v5/" + syst + "/ratio_errors_sf_egamma_misid_" + filename + sqcd + "_";
   plot_ratio_err += std::to_string(year);
   plot_ratio_err = plot_ratio_err + ".pdf";

   c1->SaveAs((plot_ratio).c_str());
   c2->SaveAs((plot_ratio_err).c_str());

   TH2D* h_final = (TH2D*)h_base->Clone("h_final");

   string final_txt_title = "../../macros/html/egamma_v5/" + syst + "/final_" + filename + sqcd + "_";
   final_txt_title += std::to_string(year);
   final_txt_title = final_txt_title + ".txt";

   ofstream final_txt;
   final_txt.open((final_txt_title).c_str());
   final_txt << "SF value" << "\t" << "tot err" << "\t\t" << "  " << "\t\t" << "stat err" << "\t" << "syst err" << endl;

   for(int j = 1; j <= h_final->GetNbinsY(); j++) {
     for(int i = 1; i <= h_final->GetNbinsX(); i++) {
       float bin_err = TMath::Sqrt(TMath::Power(h_final->GetBinError(i,j), 2) + TMath::Power(fabs(h_base->GetBinContent(i,j) - h_variation->GetBinContent(i,j)), 2)); 
       final_txt << std::fixed << std::setprecision(2) << h_final->GetBinContent(i,j) << "\t\t" << bin_err << "\t\t" << std::setprecision(1) << bin_err/h_final->GetBinContent(i,j)*100 << " \%" << std::setprecision(2) << "\t\t" << h_final->GetBinError(i,j) << "\t\t" << fabs(h_base->GetBinContent(i,j) - h_variation->GetBinContent(i,j)) << endl;
       h_final->SetBinError(i, j, bin_err);
     }
       final_txt << " " << endl;
   }   

   final_txt.close();

   string plot_final = "../../macros/html/egamma_v5/" + syst + "/final_" + filename + sqcd + "_";
   plot_final += std::to_string(year);
   plot_final = plot_final + ".pdf";

   TCanvas * c3 = new TCanvas("c3","c3",0,0,1000,1000);
   c3->cd();
   h_final->SetTitle("Final SF");
   h_final->Draw("COLZ TEXT ERROR");

   c3->SaveAs((plot_final).c_str());

   string root_title = "../../macros/html/egamma_v5/" + syst + "/final_" + filename + sqcd + "_";
   root_title += std::to_string(year);
   root_title = root_title + ".root";

   TFile* file = new TFile((root_title).c_str(), "RECREATE");
   h_final->Write("EGamma_SF2D");
   file->Close();
   delete file;


}
