/*
Simple macro showing how to access branches from the delphes output root file,
loop over events, and plot simple quantities such as the jet pt and the di-electron invariant
mass.

root -l examples/Example1.C'("delphes_output.root")'
*/

#ifdef __CLING__
R__LOAD_LIBRARY(libDelphes)
#include "classes/DelphesClasses.h"
#include "external/ExRootAnalysis/ExRootTreeReader.h"
#endif

//------------------------------------------------------------------------------

void Analyzer1(const char *inputFile)
{
  TCanvas * canvas1 = new TCanvas("canvas1");
  TCanvas * canvas2 = new TCanvas("canvas2");
  TCanvas * canvas3 = new TCanvas("canvas3");
  TCanvas * canvas4 = new TCanvas("canvas4");


  gSystem->Load("libDelphes");

  // Create chain of root trees
  TChain chain("Delphes");
  chain.Add(inputFile);

  // Create object of class ExRootTreeReader
  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
  Long64_t numberOfEntries = treeReader->GetEntries();

  // Get pointers to branches used in this analysis
  TClonesArray *branchJet = treeReader->UseBranch("Jet");
  TClonesArray *branchElectron = treeReader->UseBranch("Electron");
  TClonesArray *branchEvent = treeReader->UseBranch("Event");
  TClonesArray *branchPhoton = treeReader->UseBranch("Photon");
  TClonesArray *branchMET  = treeReader->UseBranch("MissingET");



  // Book histograms
  //TH1 *histJetPT = new TH1F("jet_pt", "jet P_{T}", 100, 0.0, 100.0);
  TH1 *histJetPT = new TH1F("jet_pt", "jet P_{T}", 500, 0.0, 2500);
  //  histJetPT->GetYaxis()->SetRange(0,22000);
  //  histJetPT->GetXaxis()->SetRange(0,2200);
  TH1 *histMass = new TH1F("mass", "M_{inv}(e_{1}, e_{2})", 100, -40.0, 240.0);
  TH1 *histDiPhotMass = new TH1F("DiPhotMass", "M_{inv}(a_{1}, a_{2})", 100, 40.0, 140.0);
  TH1 *histMET = new TH1F("MET", "MET", 100, 0.0, 300.0);




  /*  let's normalize these distributions to a benchmark scenario of 300 fb^-1 of integrated luminosity at 13 TeV 
      so that we can determine the event yield. The event weight factor is cross section * branching ratio * integrated 
      luminosity / number of generated events. Let's use our theoretical cross section * branching ratio = 0.0004 pb 
      that we found earlier. Before your event loop, calculated the weight factor and create your yield variable:        */
  Double_t weight = 0.0004 * 300 * 1E3 / numberOfEntries;
  Double_t yield = 0;
  Double_t y2 = 0;




  // Loop over all events
  for(Int_t entry = 0; entry < numberOfEntries; ++entry)
  {
    // Load selected branches with data from specified event
    treeReader->ReadEntry(entry);

    
    //HepMCEvent *event = (HepMCEvent*) branchEvent -> At(0);
    //LHEFEvent *event = (LHEFEvent*) branchEvent -> At(0);
    //Float_t weight = event->Weight;



    // If event contains at least 1 jet
    if(branchJet->GetEntries() > 0)
    {
      // Take first jet
      Jet *jet = (Jet*) branchJet->At(0);

      // Plot jet transverse momentum
      histJetPT->Fill(jet->PT);
    
      // Print jet transverse momentum
      cout << "Jet pt: "<<jet->PT << endl;
    }



    Electron *elec1, *elec2;

    // If event contains at least 2 electrons
    if(branchElectron->GetEntries() > 1)
    {
      // Take first two electrons
      elec1 = (Electron *) branchElectron->At(0);
      elec2 = (Electron *) branchElectron->At(1);

      // Plot their invariant mass
      histMass->Fill(( (elec1->P4()) + (elec2->P4()) ).M());
    }


    
    if(branchMET->GetEntries() > 0)
    {   
      MissingET *Met = (MissingET *) branchMET->At(0);
      //histMET->Fill(Met->MET);
      histMET->Fill(Met->MET, weight);
    }   
    
    
    
    Photon *phot1, *phot2;    
    if(branchPhoton->GetEntries() > 1)
    {   
      phot1 = (Photon *) branchPhoton->At(0);
      phot2 = (Photon *) branchPhoton->At(1);
      if(phot1->PT < 20 | phot2->PT < 20 | abs(phot1->Eta) > 2.5 | abs(phot2->Eta) > 2.5) continue;
      //histDiPhotMass->Fill(((phot1->P4()) + (phot2->P4())).M());
      histDiPhotMass->Fill(((phot1->P4()) + (phot2->P4())).M(), weight);
    } 


    yield += weight;
    y2 += weight*weight;
  }

  cout << "Event yield:   " << yield << " +/- " << sqrt(y2) << endl;
  cout << "Selection Eff: " << yield / (weight*numberOfEntries) << endl;




  
  // Show resulting histograms
  /*histJetPT->Draw();
  histMass->Draw();
  */
  canvas1->cd();
  histJetPT->Draw();
  canvas2->cd();
  histMass->Draw();
  canvas3->cd();
  histMET->Draw();
  canvas4->cd();
  histDiPhotMass->Draw();

  
  TFile *file1 = new TFile("histos.root", "UPDATE");
  histJetPT->Write();
  histMass->Write();
  histMET->Write();
  histDiPhotMass->Write();
  file1->Close();  
}

