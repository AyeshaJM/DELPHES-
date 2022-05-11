#ifdef __CLING__
R__LOAD_LIBRARY(libDelphes)
#include "classes/DelphesClasses.h"
#include "external/ExRootAnalysis/ExRootTreeReader.h"
#endif


void MyHistMerger(){
  gStyle->SetOptStat(0);  

  TFile *f_sig = new TFile("signal.root");
  TFile *f_bkg = new TFile("background.root");
  TFile *f_data = new TFile("data.root");
  
  TH1F *h_sig = (TH1F*)f_sig->Get("HiggsMass")->Clone("h_sig");
  TH1F *h_bkg = (TH1F*)f_bkg->Get("HiggsMass")->Clone("h_bkg");
  TH1F *h_data = (TH1F*)f_data->Get("HiggsMass")->Clone("h_data");
  
  float lumi = 25000;

  // scale according to x-sec
  float xsec_sig = 0.0001847 * 10;
  float xsec_bkg = 0.01509;
  float ntot_sig = 10000;
  float ntot_bkg = 10000;
  
  h_sig->Scale(lumi*xsec_sig/ntot_sig);
    cout << "Signal scaled by " << lumi*xsec_sig/ntot_sig << endl;
  h_bkg->Scale(lumi*xsec_bkg/ntot_bkg);
    cout << "Bkg scaled by " << lumi*xsec_bkg/ntot_bkg << endl;
  
  TCanvas *c = new TCanvas("c","c");
  
  h_sig->SetFillColor(kRed);
  h_bkg->SetFillColor(kWhite);
  
  THStack *h_stack = new THStack();
  h_stack->Add(h_bkg);
  h_stack->Add(h_sig);
  
  h_data->SetMarkerSize(1);
  h_data->SetMarkerStyle(kFullCircle);
  
  h_stack->Draw("HIST");
  h_data->Draw("E same");
  
  h_stack->SetMaximum(h_bkg->GetMaximum()*2);
  
  c->SaveAs("HiggsMass.png");
}
