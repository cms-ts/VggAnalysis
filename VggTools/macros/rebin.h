#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TMath.h"

TH1D* rebin(TH1D* old) {

  string name = old->GetName();

  int nb = 0;
  float nbins[100];

  if (name.find("pho0_pho1_pt") != string::npos ||
      name.find("WGG_ele_pho0_pt") != string::npos || name.find("WGG_ele_pho1_pt") != string::npos ||
      name.find("WGG_muo_pho0_pt") != string::npos || name.find("WGG_muo_pho1_pt") != string::npos ||
      name.find("ZGG_ele_pho0_pt") != string::npos || name.find("ZGG_ele_pho1_pt") != string::npos ||
      name.find("ZGG_muo_pho0_pt") != string::npos || name.find("ZGG_muo_pho1_pt") != string::npos) {
    nb = 6;
    nbins[0] = 1;
    nbins[1] = 1;
    nbins[2] = 1;
    nbins[3] = 1;
    nbins[4] = 5;
    nbins[5] = 6;
  } else if (name.find("WG_ele_pho0_pt") != string::npos ||
             name.find("WG_muo_pho0_pt") != string::npos ||
             name.find("ZG_ele_pho0_pt") != string::npos ||
             name.find("ZG_muo_pho0_pt") != string::npos) {
    nb = 19;
    for (int i = 0; i < 15; i++) {
      nbins[i] = 2;
    }
    nbins[15] = 6;
    nbins[16] = 6;
    nbins[17] = 6;
    nbins[18] = 12;
  } else {
    return old;
  }

  if (old->GetNbinsX() == nb) {
    cout << "ERROR: " << name << " already binned" << endl;
    return old;
  }

  int n = 0;
  for (int i = 0; i < nb; i++) {
    n = n + nbins[i];
  }
  if (n != old->GetNbinsX()) {
    cout << "ERROR: " << name << " - " << n << " " << old->GetNbinsX() << endl;
    return old;
  }

  int s = 0;
  const int nbs = nb + 1;
  double xbins[nbs];
  for (int i = 0; i < nb + 1; i++) {
    if (i > 0) s = s + nbins[i - 1];
    xbins[i] = old->GetXaxis()->GetBinUpEdge(s);
  }

  TH1D* tmp = new TH1D("tmp", old->GetTitle(), nb, xbins);

  for (int i = 0; i < old->GetXaxis()->GetNbins()+2; i++) {
    float c1 = old->GetBinContent(i);
    float e1 = old->GetBinError(i);
    float c1b = tmp->GetBinContent(tmp->GetXaxis()->FindBin(old->GetXaxis()->GetBinCenter(i)));
    float e1b = tmp->GetBinError(tmp->GetXaxis()->FindBin(old->GetXaxis()->GetBinCenter(i)));
    tmp->SetBinContent(tmp->GetXaxis()->FindBin(old->GetXaxis()->GetBinCenter(i)), c1+c1b);
    tmp->SetBinError(tmp->GetXaxis()->FindBin(old->GetXaxis()->GetBinCenter(i)), TMath::Sqrt(e1*e1+e1b*e1b));
  }

  old->Delete();
  tmp->SetName(name.c_str());

  return tmp;
}

TH2D* rebin(TH2D* old) {

  string name = old->GetName();

  int nxb = 0;
  float nxbins[100];
  int nyb = 0;
  float nybins[100];

  if (name.find("misid") != string::npos) {
    nxb = 8;
    for (int i = 0; i < 8; i++) {
      nxbins[i] = 1;
    }

    nyb = 19;
    for (int i = 0; i < 15; i++) {
      nybins[i] = 2;
    }
    nybins[15] = 6;
    nybins[16] = 6;
    nybins[17] = 6;
    nybins[18] = 12;
  } else {
    return old;
  }

  if (old->GetNbinsX() == nxb || old->GetNbinsY() == nyb) {
    cout << "ERROR: " << name << " already binned" << endl;
    return old;
  }

  int nx = 0;
  for (int i = 0; i < nxb; i++) {
    nx = nx + nxbins[i];
  }
  if (nx != old->GetNbinsX()) {
    cout << "ERROR: " << name << " - " << nx << " " << old->GetNbinsX() << endl;
    return old;
  }
  int ny = 0;
  for (int i = 0; i < nyb; i++) {
    ny = ny + nybins[i];
  }
  if (ny != old->GetNbinsY()) {
    cout << "ERROR: " << name << " - " << ny << " " << old->GetNbinsY() << endl;
    return old;
  }

  int sx = 0;
  const int nxbs = nxb + 1;
  double xbins[nxbs];
  for (int i = 0; i < nxb + 1; i++) {
    if (i > 0) sx = sx + nxbins[i-1];
    xbins[i] = old->GetXaxis()->GetBinUpEdge(sx);
  }
  int sy = 0;
  const int nybs = nyb + 1;
  double ybins[nybs];
  for (int i = 0; i < nyb + 1; i++) {
    if (i > 0) sy = sy + nybins[i-1];
    ybins[i] = old->GetYaxis()->GetBinUpEdge(sy);
  }

  TH2D* tmp = new TH2D("tmp", old->GetTitle(), nxb, xbins, nyb, ybins);

  for (int i = 0; i < old->GetXaxis()->GetNbins()+2; i++) {
    for (int j = 0; j < old->GetYaxis()->GetNbins()+2; j++) {
      float c2 = old->GetBinContent(i, j);
      float e2 = old->GetBinError(i, j);
      float c2b = tmp->GetBinContent(tmp->GetXaxis()->FindBin(old->GetXaxis()->GetBinCenter(i)), tmp->GetYaxis()->FindBin(old->GetYaxis()->GetBinCenter(j)));
      float e2b = tmp->GetBinError(tmp->GetXaxis()->FindBin(old->GetXaxis()->GetBinCenter(i)), tmp->GetYaxis()->FindBin(old->GetYaxis()->GetBinCenter(j)));
      tmp->SetBinContent(tmp->GetXaxis()->FindBin(old->GetXaxis()->GetBinCenter(i)), tmp->GetYaxis()->FindBin(old->GetYaxis()->GetBinCenter(j)), c2+c2b);
      tmp->SetBinError(tmp->GetXaxis()->FindBin(old->GetXaxis()->GetBinCenter(i)), tmp->GetYaxis()->FindBin(old->GetYaxis()->GetBinCenter(j)), TMath::Sqrt(e2*e2+e2b*e2b));
    }
  }

  old->Delete();
  tmp->SetName(name.c_str());

  return tmp;
}

TH3D* rebin(TH3D* old) {

  string name = old->GetName();

  int nxb = 0;
  float nxbins[100];
  int nyb = 0;
  float nybins[100];
  int nzb = 0;
  float nzbins[100];

  if (name.find("map") != string::npos) {
    nxb = 19;
    for (int i = 0; i < 15; i++) {
      nxbins[i] = 2;
    }
    nxbins[15] = 6;
    nxbins[16] = 6;
    nxbins[17] = 6;
    nxbins[18] = 12;

    nyb = 19;
    for (int i = 0; i < 15; i++) {
      nybins[i] = 2;
    }
    nybins[15] = 6;
    nybins[16] = 6;
    nybins[17] = 6;
    nybins[18] = 12;

    nzb = 6;
    nzbins[0] = 1;
    nzbins[1] = 1;
    nzbins[2] = 1;
    nzbins[3] = 1;
    nzbins[4] = 5;
    nzbins[5] = 6;
  } else {
    return old;
  }

  if (old->GetNbinsX() == nxb || old->GetNbinsY() == nyb || old->GetNbinsZ() == nzb) {
    cout << "ERROR: " << name << " already binned" << endl;
    return old;
  }

  int nx = 0;
  for (int i = 0; i < nxb; i++) {
    nx = nx + nxbins[i];
  }
  if (nx != old->GetNbinsX()) {
    cout << "ERROR: " << name << " - " << nx << " " << old->GetNbinsX() << endl;
    return old;
  }
  int ny = 0;
  for (int i = 0; i < nyb; i++) {
    ny = ny + nybins[i];
  }
  if (ny != old->GetNbinsY()) {
    cout << "ERROR: " << name << " - "  << ny << " " << old->GetNbinsY() << endl;
    return old;
  }
  int nz = 0;
  for (int i = 0; i < nzb; i++) {
    nz = nz + nzbins[i];
  }
  if (nz != old->GetNbinsZ()) {
    cout << "ERROR: " << name << " - " << nz << " " << old->GetNbinsZ() << endl;
    return old;
  }

  int sx = 0;
  const int nxbs = nxb + 1;
  double xbins[nxbs];
  for (int i = 0; i < nxb + 1; i++) {
    if (i > 0) sx = sx + nxbins[i-1];
    xbins[i] = old->GetXaxis()->GetBinUpEdge(sx);
  }
  int sy = 0;
  const int nybs = nyb + 1;
  double ybins[nybs];
  for (int i = 0; i < nyb + 1; i++) {
    if (i > 0) sy = sy + nybins[i-1];
    ybins[i] = old->GetYaxis()->GetBinUpEdge(sy);
  }
  int sz = 0;
  const int nzbs = nzb + 1;
  double zbins[nzbs];
  for (int i = 0; i < nzb + 1; i++) {
    if (i > 0) sz = sz + nzbins[i-1];
    zbins[i] = old->GetZaxis()->GetBinUpEdge(sz);
  }

  TH3D* tmp = new TH3D("tmp", old->GetTitle(), nxb, xbins, nyb, ybins, nzb, zbins);

  for (int i = 0; i < old->GetXaxis()->GetNbins()+2; i++) {
    for (int j = 0; j < old->GetYaxis()->GetNbins()+2; j++) {
      for (int k = 0; k < old->GetZaxis()->GetNbins()+2; k++) {
        float c2 = old->GetBinContent(i, j, k);
        float e2 = old->GetBinError(i, j, k);
        float c2b = tmp->GetBinContent(tmp->GetXaxis()->FindBin(old->GetXaxis()->GetBinCenter(i)), tmp->GetYaxis()->FindBin(old->GetYaxis()->GetBinCenter(j)), tmp->GetZaxis()->FindBin(old->GetZaxis()->GetBinCenter(k)));
        float e2b = tmp->GetBinError(tmp->GetXaxis()->FindBin(old->GetXaxis()->GetBinCenter(i)), tmp->GetYaxis()->FindBin(old->GetYaxis()->GetBinCenter(j)), tmp->GetZaxis()->FindBin(old->GetZaxis()->GetBinCenter(k)));
        tmp->SetBinContent(tmp->GetXaxis()->FindBin(old->GetXaxis()->GetBinCenter(i)), tmp->GetYaxis()->FindBin(old->GetYaxis()->GetBinCenter(j)), tmp->GetZaxis()->FindBin(old->GetZaxis()->GetBinCenter(k)), c2+c2b);
        tmp->SetBinError(tmp->GetXaxis()->FindBin(old->GetXaxis()->GetBinCenter(i)), tmp->GetYaxis()->FindBin(old->GetYaxis()->GetBinCenter(j)), tmp->GetZaxis()->FindBin(old->GetZaxis()->GetBinCenter(k)), TMath::Sqrt(e2*e2+e2b*e2b));
      }
    }
  }

  old->Delete();
  tmp->SetName(name.c_str());

  return tmp;
}

