// ----------------------------- *************************** -----------------------------
// 
// execute with:
// root -l -q triple_top_14TeV_LHC.C+\(\"_inputfile_name_\",_file_cross_section_,\"_outputfile_name\"\)
// Or run it as:  .L triple_top_14TeV_LHC.C++
// ----------------------------- *************************** -----------------------------

#if !defined(__CINT__) || defined(__MAKECINT__)

// Stdlib header file for input and output.
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

// include statements for all needed dependencies
#include <TROOT.h>
#include <TSystem.h>
#include <TFile.h>
#include <TTree.h>
#include <TClonesArray.h>
#include <TVector2.h>
#include <TMath.h>
#include <TChain.h>
#include <TH1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TLegend.h"
#include "TImage.h"
#include <vector>
#include "TLorentzVector.h"
#include "TH1D.h"
#include <TStopwatch.h>
#include <TDatime.h>
#include <TPaveText.h>
#include <iomanip>
#include "Math/LorentzVector.h"


// include statements for Delphes
 #include "classes/DelphesModule.h"
#include "modules/Delphes.h"                    // delphes
#include "ExRootAnalysis/ExRootTreeReader.h"    // delphes
#include "classes/DelphesClasses.h"             // delphes
#include "ExRootAnalysis/ExRootResult.h"        // delphes

#endif

// ----------------------------- *************************** -----------------------------

// Declare variables
const bool Signal=true, Background=false;

TString BackgroundSample;

// Declare functions8*,
void Analysis_triple_top( TTree*, TString, Double_t, bool);

void prn(int n, int N, string f, int d = 1);       //    Dr. Etesami

Float_t deltaR( const Float_t eta1, const Float_t eta2, const Float_t phi1, const Float_t phi2 );
Float_t deltaPhi( const Float_t phi1, const Float_t phi2 );
Float_t deltaEta( const Float_t eta1, const Float_t eta2 );


// ----------------------------- *************************** -----------------------------

// pt/eta cut parameters
   Float_t muonMinPt = 10.0;
   Float_t muonMaxEta = 2.5;

   Float_t electronMinPt = 10.0;
   Float_t electronMaxEta = 2.5;

   Float_t photonMinPt = 40.0;
   Float_t photonMaxEta = 2.5;

   Float_t missingETMinPt = 30;

   Float_t jetMinPt = 20.0;
   Float_t jetMaxEta = 2.5;

   Float_t deltaRCutphotonbjets = 0.4;
   Float_t deltaRCutJetiJetj = 0.4;

// -------------------------------------------------
// good electrons, muons, and jets are electrons, muons, and jets which pass the pt/eta cut
  vector<Electron> goodElectrons;
  vector<Muon> goodMuons;
  vector<Photon> goodPhotons;
  vector<MissingET> goodmissingET;

  vector<Electron>  goodElectronsP;
  vector<Muon> goodMuonsP;

  vector<Electron> goodElectronsM;
  vector<Muon> goodMuonsM; 

// -------------------------------------------------
// good b-jets are jets which pass the pt/eta cut and are b-tagged
  vector<Jet> goodJets;
  vector<Jet> goodlightJets;
  vector<Jet> goodBJets;
// -------------------------------------------------

  TLorentzVector MyGoodLeptonPlus;
  TLorentzVector MyGoodLeptonMinus;

  vector<TLorentzVector> MyFinalLeptonPlus;
  vector<TLorentzVector> MyFinalLeptonMinus;

  TLorentzVector MyJeti;
  TLorentzVector MyJetj;

// Main Function for pp to ttt~ (tt~t~) at 14 TeV analysis. Please run it as:  .L triple_top_14TeV_LHC.C++

// ----------------------------- *************************** -----------------------------
// ----------------------------- *************************** -----------------------------

Float_t weight = 1;  Float_t eventweight;
Float_t mll;         Float_t dphill;
Float_t ht;          Float_t met;
Float_t jetsmulti;   Float_t bjetsmulti;

Float_t coslb;       Float_t cosll;          Float_t deltaetall;
Float_t deltarlb;



void triple_top_14TeV_LHC ( TString backgroundSample = "All" ) {

  BackgroundSample = backgroundSample;

  TFile F("triple_top_FCNC_14TeV_LHC.root","recreate");

  TTree * tree_signal_tug =new TTree("Signal_tug","Signal_tug");

          tree_signal_tug->Branch("weight", &weight);

          tree_signal_tug->Branch("mll",    &mll);
          tree_signal_tug->Branch("dphill", &dphill);
          tree_signal_tug->Branch("ht",     &ht);
          tree_signal_tug->Branch("met",    &met);
          tree_signal_tug->Branch("jetsmulti",        &jetsmulti);
          tree_signal_tug->Branch("bjetsmulti",       &bjetsmulti);

          tree_signal_tug->Branch("coslb",     &coslb);
          tree_signal_tug->Branch("cosll",     &cosll);
          tree_signal_tug->Branch("deltaetall",   &deltaetall);
          tree_signal_tug->Branch("deltarlb",     &deltarlb);


          tree_signal_tug->Branch("eventweight", &eventweight);

 // -------------------------------------------------

  TTree * tree_signal_tcg =new TTree("Signal_tcg","Signal_tcg");

          tree_signal_tcg->Branch("weight", &weight);

          tree_signal_tcg->Branch("mll",    &mll);
          tree_signal_tcg->Branch("dphill", &dphill);
          tree_signal_tcg->Branch("ht",     &ht);
          tree_signal_tcg->Branch("met",   &met);
          tree_signal_tcg->Branch("jetsmulti",        &jetsmulti);
          tree_signal_tcg->Branch("bjetsmulti",       &bjetsmulti);

          tree_signal_tcg->Branch("coslb",     &coslb);
          tree_signal_tcg->Branch("cosll",     &cosll);
          tree_signal_tcg->Branch("deltaetall",   &deltaetall);
          tree_signal_tcg->Branch("deltarlb",     &deltarlb);

          tree_signal_tcg->Branch("eventweight", &eventweight);

 // -------------------------------------------------

  TTree * tree_signal_tuH =new TTree("Signal_tuH","Signal_tuH");

          tree_signal_tuH->Branch("weight", &weight);

          tree_signal_tuH->Branch("mll",    &mll);
          tree_signal_tuH->Branch("dphill", &dphill);
          tree_signal_tuH->Branch("ht",     &ht);
          tree_signal_tuH->Branch("met",   &met);
          tree_signal_tuH->Branch("jetsmulti",        &jetsmulti);
          tree_signal_tuH->Branch("bjetsmulti",       &bjetsmulti);

          tree_signal_tuH->Branch("coslb",     &coslb);
          tree_signal_tuH->Branch("cosll",     &cosll);
          tree_signal_tuH->Branch("deltaetall",   &deltaetall);
          tree_signal_tuH->Branch("deltarlb",     &deltarlb);
          
          tree_signal_tuH->Branch("eventweight", &eventweight);

 // -------------------------------------------------

  TTree * tree_signal_tcH =new TTree("Signal_tcH","Signal_tcH");

          tree_signal_tcH->Branch("weight", &weight);

          tree_signal_tcH->Branch("mll",    &mll);
          tree_signal_tcH->Branch("dphill", &dphill);
          tree_signal_tcH->Branch("ht",     &ht);
          tree_signal_tcH->Branch("met",   &met);
          tree_signal_tcH->Branch("jetsmulti",        &jetsmulti);
          tree_signal_tcH->Branch("bjetsmulti",       &bjetsmulti);

          tree_signal_tcH->Branch("coslb",     &coslb);
          tree_signal_tcH->Branch("cosll",     &cosll);
          tree_signal_tcH->Branch("deltaetall",   &deltaetall);
          tree_signal_tcH->Branch("deltarlb",     &deltarlb);

          tree_signal_tcH->Branch("eventweight", &eventweight);

 // -------------------------------------------------

  TTree * tree_signal_tuz_Gammamu =new TTree("Signal_tuz_Gammamu","Signal_tuz_Gammamu");

          tree_signal_tuz_Gammamu->Branch("weight", &weight);

          tree_signal_tuz_Gammamu->Branch("mll",    &mll);
          tree_signal_tuz_Gammamu->Branch("dphill", &dphill);
          tree_signal_tuz_Gammamu->Branch("ht",     &ht);
          tree_signal_tuz_Gammamu->Branch("met",   &met);
          tree_signal_tuz_Gammamu->Branch("jetsmulti",        &jetsmulti);
          tree_signal_tuz_Gammamu->Branch("bjetsmulti",       &bjetsmulti);

          tree_signal_tuz_Gammamu->Branch("coslb",     &coslb);
          tree_signal_tuz_Gammamu->Branch("cosll",     &cosll);
          tree_signal_tuz_Gammamu->Branch("deltaetall",   &deltaetall);
          tree_signal_tuz_Gammamu->Branch("deltarlb",     &deltarlb);

          tree_signal_tuz_Gammamu->Branch("eventweight", &eventweight);

 // -------------------------------------------------

  TTree * tree_signal_tcz_Gammamu =new TTree("Signal_tcz_Gammamu","Signal_tcz_Gammamu");

          tree_signal_tcz_Gammamu->Branch("weight", &weight);

          tree_signal_tcz_Gammamu->Branch("mll",    &mll);
          tree_signal_tcz_Gammamu->Branch("dphill", &dphill);
          tree_signal_tcz_Gammamu->Branch("ht",     &ht);
          tree_signal_tcz_Gammamu->Branch("met",   &met);
          tree_signal_tcz_Gammamu->Branch("jetsmulti",        &jetsmulti);
          tree_signal_tcz_Gammamu->Branch("bjetsmulti",       &bjetsmulti);

          tree_signal_tcz_Gammamu->Branch("coslb",     &coslb);
          tree_signal_tcz_Gammamu->Branch("cosll",     &cosll);
          tree_signal_tcz_Gammamu->Branch("deltaetall",   &deltaetall);
          tree_signal_tcz_Gammamu->Branch("deltarlb",     &deltarlb);

          tree_signal_tcz_Gammamu->Branch("eventweight", &eventweight);


 // -------------------------------------------------

  TTree * tree_signal_tuz_Sigmamunu =new TTree("Signal_tuz_Sigmamunu","Signal_tuz_Sigmamunu");

          tree_signal_tuz_Sigmamunu->Branch("weight", &weight);

          tree_signal_tuz_Sigmamunu->Branch("mll",    &mll);
          tree_signal_tuz_Sigmamunu->Branch("dphill", &dphill);
          tree_signal_tuz_Sigmamunu->Branch("ht",     &ht);
          tree_signal_tuz_Sigmamunu->Branch("met",   &met);
          tree_signal_tuz_Sigmamunu->Branch("jetsmulti",        &jetsmulti);
          tree_signal_tuz_Sigmamunu->Branch("bjetsmulti",       &bjetsmulti);

          tree_signal_tuz_Sigmamunu->Branch("coslb",     &coslb);
          tree_signal_tuz_Sigmamunu->Branch("cosll",     &cosll);
          tree_signal_tuz_Sigmamunu->Branch("deltaetall",   &deltaetall);
          tree_signal_tuz_Sigmamunu->Branch("deltarlb",     &deltarlb);

          tree_signal_tuz_Sigmamunu->Branch("eventweight", &eventweight);

 // -------------------------------------------------

  TTree * tree_signal_tcz_Sigmamunu =new TTree("Signal_tcz_Sigmamunu","Signal_tcz_Sigmamunu");

          tree_signal_tcz_Sigmamunu->Branch("weight", &weight);

          tree_signal_tcz_Sigmamunu->Branch("mll",    &mll);
          tree_signal_tcz_Sigmamunu->Branch("dphill", &dphill);
          tree_signal_tcz_Sigmamunu->Branch("ht",     &ht);
          tree_signal_tcz_Sigmamunu->Branch("met",   &met);
          tree_signal_tcz_Sigmamunu->Branch("jetsmulti",        &jetsmulti);
          tree_signal_tcz_Sigmamunu->Branch("bjetsmulti",       &bjetsmulti);

          tree_signal_tcz_Sigmamunu->Branch("coslb",     &coslb);
          tree_signal_tcz_Sigmamunu->Branch("cosll",     &cosll);
          tree_signal_tcz_Sigmamunu->Branch("deltaetall",   &deltaetall);
          tree_signal_tcz_Sigmamunu->Branch("deltarlb",     &deltarlb);

          tree_signal_tcz_Sigmamunu->Branch("eventweight", &eventweight);

 // -------------------------------------------------

  TTree * tree_signal_tua =new TTree("Signal_tua","Signal_tua");

          tree_signal_tua->Branch("weight", &weight);

          tree_signal_tua->Branch("mll",    &mll);
          tree_signal_tua->Branch("dphill", &dphill);
          tree_signal_tua->Branch("ht",     &ht);
          tree_signal_tua->Branch("met",   &met);
          tree_signal_tua->Branch("jetsmulti",        &jetsmulti);
          tree_signal_tua->Branch("bjetsmulti",       &bjetsmulti);

          tree_signal_tua->Branch("coslb",     &coslb);
          tree_signal_tua->Branch("cosll",     &cosll);
          tree_signal_tua->Branch("deltaetall",   &deltaetall);
          tree_signal_tua->Branch("deltarlb",     &deltarlb);
          
          tree_signal_tua->Branch("eventweight", &eventweight);

 // -------------------------------------------------

  TTree * tree_signal_tca =new TTree("Signal_tca","Signal_tca");

          tree_signal_tca->Branch("weight", &weight);

          tree_signal_tca->Branch("mll",    &mll);
          tree_signal_tca->Branch("dphill", &dphill);
          tree_signal_tca->Branch("ht",     &ht);
          tree_signal_tca->Branch("met",   &met);
          tree_signal_tca->Branch("jetsmulti",        &jetsmulti);
          tree_signal_tca->Branch("bjetsmulti",       &bjetsmulti);

          tree_signal_tca->Branch("coslb",     &coslb);
          tree_signal_tca->Branch("cosll",     &cosll);
          tree_signal_tca->Branch("deltaetall",   &deltaetall);
          tree_signal_tca->Branch("deltarlb",     &deltarlb);
          
          tree_signal_tca->Branch("eventweight", &eventweight);

  // -------------------------------------------------

  TTree * tree_ttbarz =new TTree("ttbarz", "ttbarz");

          tree_ttbarz->Branch("weight", &weight);

          tree_ttbarz->Branch("mll",    &mll);
          tree_ttbarz->Branch("dphill", &dphill);
          tree_ttbarz->Branch("ht",     &ht);
          tree_ttbarz->Branch("met",   &met);
          tree_ttbarz->Branch("jetsmulti",        &jetsmulti);
          tree_ttbarz->Branch("bjetsmulti",       &bjetsmulti);

          tree_ttbarz->Branch("coslb",     &coslb);
          tree_ttbarz->Branch("cosll",     &cosll);
          tree_ttbarz->Branch("deltaetall",   &deltaetall);
          tree_ttbarz->Branch("deltarlb",     &deltarlb);

          tree_ttbarz->Branch("eventweight", &eventweight);

 // -------------------------------------------------

  TTree * tree_ttbarw =new TTree("ttbarw", "ttbarw");

          tree_ttbarw->Branch("weight", &weight);

          tree_ttbarw->Branch("mll",    &mll);
          tree_ttbarw->Branch("dphill", &dphill);
          tree_ttbarw->Branch("ht",     &ht);
          tree_ttbarw->Branch("met",   &met);
          tree_ttbarw->Branch("jetsmulti",        &jetsmulti);
          tree_ttbarw->Branch("bjetsmulti",       &bjetsmulti);

          tree_ttbarw->Branch("coslb",     &coslb);
          tree_ttbarw->Branch("cosll",     &cosll);
          tree_ttbarw->Branch("deltaetall",   &deltaetall);
          tree_ttbarw->Branch("deltarlb",     &deltarlb);

          tree_ttbarw->Branch("eventweight", &eventweight);

 // -------------------------------------------------

  TTree * tree_wwz =new TTree("wwz", "wwz");

          tree_wwz->Branch("weight", &weight);

          tree_wwz->Branch("mll",    &mll);
          tree_wwz->Branch("dphill", &dphill);
          tree_wwz->Branch("ht",     &ht);
          tree_wwz->Branch("met",   &met);
          tree_wwz->Branch("jetsmulti",        &jetsmulti);
          tree_wwz->Branch("bjetsmulti",       &bjetsmulti);

          tree_wwz->Branch("coslb",     &coslb);
          tree_wwz->Branch("cosll",     &cosll);
          tree_wwz->Branch("deltaetall",   &deltaetall);
          tree_wwz->Branch("deltarlb",     &deltarlb);

          tree_wwz->Branch("eventweight", &eventweight);

// -------------------------------------------------
// -------------------------------------------------

// Analysis Signal higgs photon

Analysis_triple_top(tree_signal_tug,"ttt.root", 704.586862122, Signal);
Analysis_triple_top(tree_signal_tcg,"ttt.root", 49.5813467819, Signal);


Analysis_triple_top(tree_signal_tuH,"ttt.root", 0.579821713,  Signal);
Analysis_triple_top(tree_signal_tcH,"ttt.root", 0.0659849173, Signal);


Analysis_triple_top(tree_signal_tuz_Gammamu,"ttt.root", 2.02279247,  Signal);
Analysis_triple_top(tree_signal_tcz_Gammamu,"ttt.root", 0.220207743, Signal);


Analysis_triple_top(tree_signal_tuz_Sigmamunu,"ttt.root", 3.259934648, Signal);
Analysis_triple_top(tree_signal_tcz_Sigmamunu,"ttt.root", 0.286182721, Signal);


Analysis_triple_top(tree_signal_tua,"ttt.root", 0.477193768,  Signal);
Analysis_triple_top(tree_signal_tca,"ttt.root", 0.0422159907, Signal);



// Analysis Back_14TeV_ttbarz
if(BackgroundSample == "ttbarz"){
Analysis_triple_top(tree_ttbarz, "ttt.root", 8.3310664,    Background);
}

// Analysis Back_14TeV_ttbarw+_ttbarw-
else if(BackgroundSample == "ttbarw"){
Analysis_triple_top(tree_ttbarw, "ttt.root", 7.2044,   Background);
}

// Analysis Back_14TeV_w+w-z
else if(BackgroundSample == "wwz"){
Analysis_triple_top(tree_wwz, "ttt.root", 1.31716243759,   Background);
}


    else if ( BackgroundSample == "Signal" ) {
    cout << "Processing only signal events" << endl;
	}


else if(BackgroundSample == "All"){

cout << "Processing all Background events" << endl;


// Analysis Back_14TeV_ttbarz
Analysis_triple_top(tree_ttbarz, "ttt.root", 8.3310664,    Background);


// Analysis Back_14TeV_ttbarw+_ttbarw-
Analysis_triple_top(tree_ttbarw, "ttt.root", 7.2044,   Background);


// Analysis Back_14TeV_w+w-z
Analysis_triple_top(tree_wwz, "ttt.root", 1.31716243759,   Background);

}

    else {
    cout << " Sorry, I can not find the corresponding background sample !!! " << endl;
    return;
	}

  // save file
  F.Write();

  // close file
  F.Close();
}


// -----------------------------
// set up output variables and file
  Int_t   nEvents;
  Float_t Mll;           Float_t  dPhill;
  Float_t Ht;            Float_t  MET;
  Float_t JetsMulti;     Float_t  BJetsMulti;
  Float_t HtgoodJets;    Float_t HtLeptonPlus;   Float_t HtLeptonMinus;
  Float_t Coslb;         Float_t Cosll;          Float_t deltaEtall;
  Float_t deltaRlb; 

// -----------------------------
  // counters for b-quark, light Jet and lepton in the events
   Float_t n_lepton  = 0.0;
   Float_t n_MET     = 0.0;
   Float_t n_Jets    = 0.0;
   Float_t n_btagged = 0.0;
   
    Float_t N_P = 0.0;
    Float_t N_M = 0.0;
// -----------------------------


void Analysis_triple_top (TTree* MyTree, TString inputfile, Double_t crossSection, bool SigBkg) {

//      const TString outputfile = "/home/Hamzeh_Khanpour/Delphes-3.3.2/triple_top_14TeV_LHC/" + inputfile + ".root";

        cout << endl;
cout << "****" << endl;
cout << "--------------------------- *************************** ---------------------------" << endl;
cout << "      A sample program to analysis triple_top_14TeV_LHC  - March 2020              " << endl;
cout << "           Nazima Bibi & Dr. Ijaz Ahmed                  " << endl;
cout << "--------------------------- *************************** ---------------------------" << endl;
cout << "****" << endl;

	cout << endl;
	cout << " inputfile == " << inputfile << endl;
	cout << endl;

  TStopwatch Watch;
  Watch.Start();

//    Load shared library
//    gSystem->Load("/root/ExRootAnalysis/libExRootAnalysis.so");

    gSystem->Load("libPhysics");
    gSystem->Load("libDelphes");

  // read input input file
  TChain chain("Delphes");
  chain.Add(inputfile);
  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
  Long64_t numberOfEntries = treeReader->GetEntries();

  // set up branches to read in from file
  TClonesArray *branchMuon = treeReader->UseBranch("Muon");
  TClonesArray *branchElectron = treeReader->UseBranch("Electron");
  TClonesArray *branchPhoton = treeReader->UseBranch("Photon");
  TClonesArray *branchMissingET = treeReader -> UseBranch("MissingET");
  TClonesArray *branchJet = treeReader->UseBranch("Jet");

  if (!(branchJet)) {
    cout << "File broken" << endl;
    return;
  }

  TClonesArray *branchParticle = treeReader->UseBranch("Particle");
  TClonesArray *branchGenJet = treeReader->UseBranch("GenJet");
  TClonesArray *branchEvent = treeReader->UseBranch("Event");

 
   Int_t nEvents;
   nEvents = numberOfEntries;

   Float_t n_lepton  = -1.0;
   Float_t n_MET     = -1.0;
   Float_t n_Jets    = -1.0;
   Float_t n_btagged = -1.0;
   
    Float_t N_P = -1.0;
    Float_t N_M = -1.0;


  cout << "numberOfEntries == "  <<  numberOfEntries  << endl;

  for (Int_t iEntry = 0; iEntry < numberOfEntries; iEntry++) {  // number Of Entries start event loop

    treeReader->ReadEntry(iEntry);
    if ( iEntry % 100000 == 0 )
    std::cout << " --- iEntry =  " << iEntry << std::endl;

    prn(iEntry, numberOfEntries, treeReader->GetName(), 1);


    goodElectronsP.clear();
    goodMuonsP.clear();

    goodElectronsM.clear();
    goodMuonsM.clear();

    goodElectrons.clear();
    goodMuons.clear();
    goodPhotons.clear();
    goodmissingET.clear();
    goodJets.clear();
    goodlightJets.clear();
    goodBJets.clear();

    MyFinalLeptonPlus.clear();
    MyFinalLeptonMinus.clear();

 Float_t  luminosity = 300.0;
 Float_t  EventWeight = crossSection * luminosity / nEvents;

          eventweight = EventWeight;

// To check both positive and negative leptons (including electron and muon) pass the Pt and Eta cuts
   bool hasMuonP = false;        bool hasMuonM = false;
   bool hasElectronP = false;    bool hasElectronM = false;

// ==================================================================================

		for (Int_t i = 0; i < branchElectron->GetEntries(); i++)
		{
			Electron * electron = (Electron*) branchElectron->At(i);

			if ( electron->PT > electronMinPt && fabs(electron->Eta) < electronMaxEta ) {
			
                                goodElectrons.push_back(*electron);

				if (electron->Charge == 1)
				{
					hasElectronP = true;
                                 goodElectronsP.push_back(*electron);

  MyGoodLeptonPlus.SetPtEtaPhiE( (goodElectrons[i].P4()).Pt(), (goodElectrons[i].P4()).Eta(), (goodElectrons[i].P4()).Phi(), (goodElectrons[i].P4()).E() );
  MyFinalLeptonPlus.push_back(MyGoodLeptonPlus);
				}
				else if (electron->Charge == -1)
				{
					hasElectronM = true;
                                 goodElectronsM.push_back(*electron);

  MyGoodLeptonMinus.SetPtEtaPhiE( (goodElectrons[i].P4()).Pt(), (goodElectrons[i].P4()).Eta(), (goodElectrons[i].P4()).Phi(), (goodElectrons[i].P4()).E() );
  MyFinalLeptonMinus.push_back(MyGoodLeptonMinus);
  
				}
                        }
		}

// ==================================================================================

		// apply the pt/eta cut to muons
		for (Int_t i = 0; i < branchMuon->GetEntries(); i++)
		{
			Muon * muon = (Muon*) branchMuon->At(i);

			if ( muon->PT > muonMinPt && fabs(muon->Eta) < muonMaxEta ) {
			
                                goodMuons.push_back(*muon);

                                if (muon->Charge == 1)
				{
					hasMuonP = true;

                                        goodMuonsP.push_back(*muon);

  MyGoodLeptonPlus.SetPtEtaPhiE( (goodMuons[i].P4()).Pt(), (goodMuons[i].P4()).Eta(), (goodMuons[i].P4()).Phi(), (goodMuons[i].P4()).E() );
  MyFinalLeptonPlus.push_back(MyGoodLeptonPlus);
				}
				else if (muon->Charge == -1)
				{
					hasMuonM = true;

                                         goodMuonsM.push_back(*muon);

  MyGoodLeptonMinus.SetPtEtaPhiE( (goodMuons[i].P4()).Pt(), (goodMuons[i].P4()).Eta(), (goodMuons[i].P4()).Phi(), (goodMuons[i].P4()).E() );
  MyFinalLeptonMinus.push_back(MyGoodLeptonMinus);
				}
                        }
		}

// ==================================================================================

  if ( MyFinalLeptonPlus.size()    == 0 && MyFinalLeptonMinus.size() == 0 ) continue;
  if ( MyFinalLeptonPlus.size()    == 0 && MyFinalLeptonMinus.size() == 1 ) continue;
  if ( MyFinalLeptonPlus.size()    == 1 && MyFinalLeptonMinus.size() == 0 ) continue;
  if ( MyFinalLeptonPlus.size()    == 1 && MyFinalLeptonMinus.size() == 1 ) continue;
  if ( MyFinalLeptonPlus.size()    == 1 && MyFinalLeptonMinus.size() == 3 ) continue;
  if ( MyFinalLeptonPlus.size()    == 3 && MyFinalLeptonMinus.size() == 1 ) continue;
  if ( MyFinalLeptonPlus.size()    == 0 && MyFinalLeptonMinus.size() == 3 ) continue;
  if ( MyFinalLeptonPlus.size()    == 3 && MyFinalLeptonMinus.size() == 0 ) continue;

  if ( MyFinalLeptonPlus.size()    == 1 && MyFinalLeptonMinus.size() == 2 ) continue;
  if ( MyFinalLeptonPlus.size()    == 2 && MyFinalLeptonMinus.size() == 1 ) continue;

// ==================================================================================

// cout << "MyFinalLeptonPlus.size() =="   <<  MyFinalLeptonPlus.size() << endl;
// cout << "MyFinalLeptonMinus.size() =="  <<  MyFinalLeptonMinus.size() << endl; 

 n_lepton++;  //  lepton veto (counters for lepton veto)

// ==================================================================================

                    // reco MissingET loop
		for ( Int_t i = 0; i < branchMissingET->GetEntries(); i++ )
		{
			MissingET * missingET = (MissingET*) branchMissingET->At(i);

                    //   if ( missingET->MET > missingETMinPt ) {

                                goodmissingET.push_back(*missingET);
		    //	}
                }

MET = (goodmissingET[0].P4()).Pt();

if ( (goodmissingET[0].P4()).Pt() < missingETMinPt ) { continue; }

n_MET++; //  MET veto (counters for MET veto)

// ==================================================================================

                // Apply the pt/eta cut to jets
                //  Set up storage variables
		for ( Int_t i = 0; i < branchJet->GetEntries(); i++ )
		{
			Jet * jet = (Jet*) branchJet->At(i);

			if (jet->PT > jetMinPt && fabs(jet->Eta) < jetMaxEta) {

				goodJets.push_back(*jet);
                        //       AllJetsIndex = i;
			}
                }
//-----------------------------------------------------------------------------------
		//  Find b-tagged jets
		for ( Size_t j = 0; j < goodJets.size(); j++ )
		{

			if ( goodJets[j].BTag == 1 )
			{
                                goodBJets.push_back(goodJets[j]);
                        //        bJetIndex = i;

			}
			else     goodlightJets.push_back(goodJets[j]);
                        //        lightJetIndex = i;
                }


//-----------------------------------
   JetsMulti      =  goodJets.size();
   BJetsMulti     =  goodBJets.size();
//-----------------------------------
   jetsmulti      = JetsMulti;
   bjetsmulti     = BJetsMulti;
//-----------------------------------

// ==================================================================================

 if ( goodJets.size() < 5 ) { continue; }   // atleat 5 jets !

// ==================================================================================

//  dR l j

for (Size_t i = 0; i < goodMuons.size(); i++)  {
   for ( Size_t j = 0; j < goodJets.size(); j++ ) {
 if ( deltaR ( (goodMuons[i].P4()).Eta(), (goodJets[j].P4()).Eta(), (goodMuons[i].P4()).Phi(), (goodJets[j].P4()).Phi() )  < deltaRCutphotonbjets ) { continue; }
} }

for (Size_t i = 0; i < goodElectrons.size(); i++)  {
   for (Size_t j = 0; j < goodJets.size(); j++)  {
 if ( deltaR ( (goodElectrons[i].P4()).Eta(), (goodJets[j].P4()).Eta(), (goodElectrons[i].P4()).Phi(), (goodJets[j].P4()).Phi() )  < deltaRCutphotonbjets ) { continue; }
} }

//-----------------------------------------------------------------------------------

//  dR j j

for ( Size_t i = 0; i < goodJets.size(); i++ ) {
   for ( Size_t j = 0; j < goodJets.size(); j++ ) {

            // Do not include the same jet
              if ( i == j )  continue;

MyJeti.SetPtEtaPhiE( (goodJets[i].P4()).Pt(), (goodJets[i].P4()).Eta(), (goodJets[i].P4()).Phi(), (goodJets[i].P4()).E()  );
MyJetj.SetPtEtaPhiE( (goodJets[j].P4()).Pt(), (goodJets[j].P4()).Eta(), (goodJets[j].P4()).Phi(), (goodJets[j].P4()).E()  );

if ( deltaR ( MyJeti.Eta(), MyJetj.Eta(), MyJeti.Phi(), MyJetj.Phi() )  < deltaRCutJetiJetj ) { continue; }

           }
             }

  n_Jets++;      // Jets selection (counters for Jets candidate)

// ==================================================================================

 if ( goodBJets.size() < 3 ) { continue; }   // At least 3 b_jets !

  n_btagged++;  // b-jet selection (counters for b-quark candidate)

// ==================================================================================


for ( Size_t i = 0; i < goodJets.size(); ++i ) {


  HtgoodJets = goodJets[i].P4().Pt();

             }

for ( Size_t j = 0; j < MyFinalLeptonPlus.size(); ++j ) {

  HtLeptonPlus = MyFinalLeptonPlus.at(j).Pt();

             } 

for ( Size_t k = 0; k < MyFinalLeptonMinus.size(); ++k ) {

  HtLeptonMinus = MyFinalLeptonMinus.at(k).Pt();

             }

Ht = HtgoodJets;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

for ( Size_t i = 0; i < MyFinalLeptonPlus.size(); i++ ) {
   for ( Size_t j = 0; j < MyFinalLeptonPlus.size(); j++ ) {

            // Do not include the same lepton
              if ( i == j )  continue;

  Mll    =  ( MyFinalLeptonPlus.at(i) + MyFinalLeptonPlus.at(j) ).M();

  Coslb = TMath::Cos((MyFinalLeptonPlus.at(i).Vect()).Angle(goodBJets[0].P4().Vect())); 
  Cosll = TMath::Cos((MyFinalLeptonPlus.at(i).Vect()).Angle(MyFinalLeptonPlus.at(j).Vect())); 
  deltaEtall = MyFinalLeptonPlus.at(i).Eta() - MyFinalLeptonPlus.at(j).Eta();

  deltaRlb = deltaR ( (MyFinalLeptonPlus.at(i)).Eta(), (goodBJets[0].P4()).Eta(), (MyFinalLeptonPlus.at(i)).Phi(), (goodBJets[0].P4()).Phi() );

  dPhill = deltaPhi( MyFinalLeptonPlus.at(i).Phi(), MyFinalLeptonPlus.at(j).Phi() );

  } }

// -----------------------------------

for ( Size_t i = 0; i < MyFinalLeptonMinus.size(); i++ ) {
   for ( Size_t j = 0; j < MyFinalLeptonMinus.size(); j++ ) {

            // Do not include the same lepton
              if ( i == j )  continue;

  Mll    =  ( MyFinalLeptonMinus.at(i) + MyFinalLeptonMinus.at(j) ).M();

  Coslb = TMath::Cos((MyFinalLeptonMinus.at(i).Vect()).Angle(goodBJets[0].P4().Vect())); 
  Cosll = TMath::Cos((MyFinalLeptonMinus.at(i).Vect()).Angle(MyFinalLeptonMinus.at(j).Vect())); 
  deltaEtall = MyFinalLeptonMinus.at(i).Eta() - MyFinalLeptonMinus.at(j).Eta();

  deltaRlb = deltaR ( (MyFinalLeptonMinus.at(i)).Eta(), (goodBJets[0].P4()).Eta(), (MyFinalLeptonMinus.at(i)).Phi(), (goodBJets[0].P4()).Phi() );

  dPhill = deltaPhi( MyFinalLeptonMinus.at(i).Phi(), MyFinalLeptonMinus.at(j).Phi() );

  } }



// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

   ht = Ht;
   mll  =  Mll;

   coslb = Coslb;
   cosll = Cosll;

   deltaetall = deltaEtall;

   dphill = dPhill;

   deltarlb = deltaRlb;

   met = MET;

   if(cosll > 0) {N_P++;}
   else
   if(cosll < 0) {N_M++;}

   MyTree -> Fill();


  } // end event loop


// ==================================================================================


cout << " ****************************************************" << endl;

cout << " [ Pre_selection Cuts ]" << endl;

    cout << " Number of event after lepton veto = " <<  n_lepton << endl;
        cout << " lepton veto efficiency = " <<  n_lepton/numberOfEntries << endl;

    cout << " Number of event after MET veto = " <<  n_MET << endl;
        cout << " MET veto efficiency = " <<  n_MET/numberOfEntries << endl;

    cout << " Number of Jets candidate (Jets selection)  = "  << n_Jets << endl;
        cout << " Jets selection efficiency  = "  << n_Jets/numberOfEntries << endl;

    cout << " Number of b-tagged Jets (b-quark candidate) = " <<  n_btagged << endl;
        cout << " b-quark selection efficiency = " <<  n_btagged/numberOfEntries << endl;

cout << " ****************************************************" << endl;

cout << "N_P ="  << N_P << endl;
cout << "N_M ="  << N_M << endl;

cout << " ****************************************************" << endl;

  cout << endl;
cout << "****" << endl;
  cout << " ---- This is the END of the analysis !! ---- " << endl;
cout << "****" << endl;
  cout << endl;

  cout << " The end of the triple_top_FCNC_14TeV_LHC analysis based on Delphes " << endl;

   	Int_t Min = Watch.RealTime()/60.0;

   	Float_t Sec = Watch.RealTime() - 60.0*Min;

   	std::cout << " The Running Time Was: " << Min << "--- Minute and " << Sec << "--- Second" << std::endl;
  cout << endl;

}

// ------------------------------------------------------

Float_t deltaR( const Float_t eta1, const Float_t eta2, const Float_t phi1, const Float_t phi2 ) {

  const Float_t pi = 3.14159265358979;

  Float_t etaDiff = (eta1 - eta2);
  Float_t phiDiff = fabs(phi1 - phi2);
  while ( phiDiff > pi ) phiDiff = fabs(phiDiff - 2.0*pi);

  Float_t deltaRSquared = etaDiff * etaDiff + phiDiff * phiDiff;

  return TMath::Sqrt(deltaRSquared);
}

// ------------------------------------------------------

Float_t deltaPhi( const Float_t phi1, const Float_t phi2 ) {
  const Float_t Pi = 3.14159265358979;
  Float_t phiDiff = fabs( phi1 - phi2 );
  while ( phiDiff > Pi ) phiDiff = fabs(phiDiff - 2.0 * Pi);
  return phiDiff;
}

// ------------------------------------------------------

Float_t deltaEta( const Float_t eta1, const Float_t eta2 ) {
 Float_t etaDiff = ( eta1 - eta2 );
  return etaDiff;
}

// ------------------------------------------------------

void prn(int n, int N, string f, int d ) {
  d = 100000;
                if (n % d == 0) {
                        fprintf(stdout, "\rEvents: \033[1;36;40m%6d of %6d\033[0m File %s", n, N, f.c_str());
                        fflush(stdout);
                }
                if (n == (N - 1)) {
                        fprintf(stdout, "\n");
                        fflush(stdout);
                }
        }
// ------------------------------------------------------
