/*
Simple macro showing how to access branches from the delphes output root file,
loop over events, and plot the elecron pt.

root -l 'examples/MyReader.C("../delphes_1stRUN_ttbar/Events/run_02/tag_1_delphes_events.root")'
*/


#ifdef __CLING__
R__LOAD_LIBRARY(libDelphes)
#include "classes/DelphesClasses.h"
#include "external/ExRootAnalysis/ExRootTreeReader.h"
#endif



void MyReader(const char *fileName){
  
  gSystem->Load("libDelphes");

  // Create chain of root trees
  TChain chain("Delphes");
  chain.Add(fileName);
  
  // Create object of class ExRootTreeReader
  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
  Long64_t numberOfEntries = treeReader->GetEntries();
  
  // Get pointers to branches used in this analysis
  TClonesArray *branchElectron = treeReader->UseBranch("Electron");
  TClonesArray *branchMuon = treeReader->UseBranch("Muon");
  TClonesArray *branchJet = treeReader->UseBranch("Jet");
  // ...

  // Book histograms
   TH1 *histElectronPT = new TH1F("electron pt", "electron P_{T}", 50, 0.0, 360.0);

  // Loop over all events
  for(Int_t entry = 0; entry < numberOfEntries; ++entry)
  {
    // print event number in the file
    if(entry%100==0) cout << "Reading Event " << entry << endl;
    
    // Load selected branches with data from specified event
    treeReader->ReadEntry(entry);



    Electron *electron;
    // If event contains at least 1 electron
    if(branchElectron->GetEntries() > 0)
    {
      // Take first electron
      // Electron *electron = (Electron*) branchElectron->At(0);
      electron = (Electron*) branchElectron->At(0);


      // Plot electron transverse momentum
       histElectronPT->Fill(electron->PT);
      
      // Print electron transverse momentum
      cout << electron->PT << endl;
    }

  }

  // Show resulting histograms
  TCanvas *c = new TCanvas("c","c");
  histElectronPT->Draw();

  // Save the result as image
  //c->SaveAs("ElectronPT.png");

  // Save the histogram in a ROOT file
  TFile *f = new TFile("ElectronPT.root","RECREATE");
  histElectronPT->Write("",TObject::kOverwrite);
}
 
