#include <TFile.h>
#include <TTree.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <TH1.h>
#include <TCanvas.h>

float getWeight(float x, float y, TH1 *histogram_) {
  if (histogram_==NULL) {
    std::cout << "ERROR! The weights input histogram is not loaded. Returning weight 0!" << std::endl;
    return 0.;
  }
  if (!histogram_->InheritsFrom("TH2")) {
    int bin = std::max(1, std::min(histogram_->GetNbinsX(), histogram_->GetXaxis()->FindBin(x)));
    return histogram_->GetBinContent(bin);
  } else {
    int binx = std::max(1, std::min(histogram_->GetNbinsX(), histogram_->GetXaxis()->FindBin(x)));
    int biny = std::max(1, std::min(histogram_->GetNbinsY(), histogram_->GetYaxis()->FindBin(y)));
    return histogram_->GetBinContent(binx,biny);
  }
}

float getWeightErr(float x, float y, TH1 *histogram_) {
  if (histogram_==NULL) {
    std::cout << "ERROR! The weights input histogram is not loaded. Returning weight error 1!" << std::endl;
    return 1.;
  }
  if (!histogram_->InheritsFrom("TH2")) {
    int bin = std::max(1, std::min(histogram_->GetNbinsX(), histogram_->GetXaxis()->FindBin(x)));
    return histogram_->GetBinError(bin);
  } else {
    int binx = std::max(1, std::min(histogram_->GetNbinsX(), histogram_->GetXaxis()->FindBin(x)));
    int biny = std::max(1, std::min(histogram_->GetNbinsX(), histogram_->GetXaxis()->FindBin(y)));
    return histogram_->GetBinError(binx,biny);
  }
}

std::vector<float> loadVals(TH1 *hist, bool norm) {
  int nbins=hist->GetNcells();
  std::vector<float> vals;
  for (int i=0; i<nbins; ++i) {
    double bc=hist->GetBinContent(i);
    double val = (i>0 && bc==0 && hist->GetBinContent(i-1)>0 && hist->GetBinContent(i+1)>0) ? 0.5*(hist->GetBinContent(i-1)+hist->GetBinContent(i+1)) : bc;
    vals.push_back(std::max(bc,0.));
  }
  if (norm) {
    float scale = 1.0/hist->Integral();
    for (int i=0; i<nbins; ++i) vals[i] *= scale;
  }
  return vals;
}

float checkIntegral(std::vector<float> wgt1, std::vector<float> wgt2, std::vector<float> refvals_) {
  float myint=0;
  float refint=0;
  for (int i=0; i<(int)wgt1.size(); ++i) {
    myint += wgt1[i]*refvals_[i];
    refint += wgt2[i]*refvals_[i];
  }
  return (myint-refint)/refint;
}

void fixLargeWeights(std::vector<float> &weights, std::vector<float> refvals_) {
  float maxshift = 0.0025; 
  float hardmax = 3; 
  float maxw = std::min(*(std::max_element(weights.begin(),weights.end())),float(5.)); //why 5?
  std::vector<float> cropped;
  while (maxw > hardmax) {
    for (int i=0; i<(int)weights.size(); ++i) cropped.push_back(std::min(maxw,weights[i]));
    float shift = checkIntegral(cropped, weights, refvals_ );
    if (fabs(shift) > maxshift) break;
    maxw *= 0.95;
  }
  maxw /= 0.95;
  if (cropped.size()>0) {
      for (int i=0; i<(int)weights.size(); ++i) cropped[i] = std::min(maxw,weights[i]);
      float normshift = checkIntegral(cropped, weights, refvals_);
      for (int i=0; i<(int)weights.size(); ++i) weights[i] = cropped[i]*(1-normshift);
  }
}

TH1* my_ratio(TH1 *h_mc, TH1 *h_data, bool fixLargeWgts, std::vector<float> refvals_, bool norm_) {
  TH1 *ret = (TH1*)h_mc->Clone("h_weights");
  ret->SetDirectory(0);

  std::vector<float> vals = loadVals(h_mc,norm_);
  std::vector<float> targetvals = loadVals(h_data,norm_);
  std::vector<float> weights;
  int nbins = vals.size();
  for (int i=0; i<nbins; ++i) {
    float weight = vals[i] !=0 ? targetvals[i]/vals[i] : 1.;
    weights.push_back(weight);
  }
  if (fixLargeWgts) fixLargeWeights(weights, refvals_);
  for (int i=0; i<(int)weights.size(); ++i) {
    ret->SetBinContent(i,weights[i]);
  }
  return ret;
}

void WeightCalculatorFromHistogram(string root_mc, string root_data, bool norm_, bool fixLargeWgts, string root_output) {
  TFile *f_mc = new TFile(root_mc.c_str(),"OPEN");
  TH1 *h_mc = (TH1*)f_mc->Get("pileup");
  TFile *f_data = new TFile(root_data.c_str(),"OPEN");
  TH1 *h_data = (TH1*)f_data->Get("pileup");

  TH1* histogram_;
  std::vector<float> refvals_,targetvals_;  
  if (h_mc->GetNcells()!=h_data->GetNcells()) {
    std::cout << "ERROR! Numerator and denominator histograms have different number of bins!" << std::endl;
    histogram_=0;
  } else {
    for (int i=0; i<(int)h_mc->GetNcells(); ++i) {
      refvals_.push_back(h_mc->GetBinContent(i));
      targetvals_.push_back(h_data->GetBinContent(i));
    }
    histogram_ = my_ratio(h_mc, h_data, fixLargeWgts, refvals_, norm_);
  }
 
  TFile *f_output = new TFile(root_output.c_str(),"RECREATE");
  f_output->cd();
  histogram_->Write("h_puWeights");
  f_output->Close();
}
