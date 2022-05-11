/*
 root -l -b -q 'examples/MyHiggs4l.C("../delphes_h4lep/Events/run_01/tag_1_delphes_events.root","signal.root")' 
*/




#ifdef __CLING__
R__LOAD_LIBRARY(libDelphes)
#include "classes/DelphesClasses.h"
#include "external/ExRootAnalysis/ExRootTreeReader.h"
#endif




void MyHiggs4l(const char *fileName,const char *saveName){
  
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
  // ...

  // Book histograms
  TH1 *histHiggsMass = new TH1F("HiggsMass", "m_{4l}", 60, 0.0, 300.0);
  //TH1 *histHiggsMass = new TH1F("HiggsMass", "m_{4l}", 60, 0.0, 0.0, 10.0, 200.0);

  TLorentzVector higgs(0,0,0,0);
  
  // Loop over all events
  for(Int_t entry = 0; entry < numberOfEntries; ++entry)
  {
    // print event number in the file
    if(entry%100==0) cout << "Reading Event " << entry << endl;
    
    // Load selected branches with data from specified event
    treeReader->ReadEntry(entry);
    
    // If event contains exactly 4 leptons
    if(branchElectron->GetEntries() + branchMuon->GetEntries()  == 4)
    {


      // case 1: all electrons
      if(branchElectron->GetEntries()==4){
        higgs = ((Electron*) branchElectron->At(0))->P4();
        higgs += ((Electron*) branchElectron->At(1))->P4();
        higgs += ((Electron*) branchElectron->At(2))->P4();
        higgs += ((Electron*) branchElectron->At(3))->P4();
      }



      
      // case 2: all muons
      else if(branchMuon->GetEntries()==4){
        higgs = ((Muon*) branchMuon->At(0))->P4();
        higgs += ((Muon*) branchMuon->At(1))->P4();
        higgs += ((Muon*) branchMuon->At(2))->P4();
        higgs += ((Muon*) branchMuon->At(3))->P4();
      }
      // case 3: 2 muons + 2 electrons
      else if(branchMuon->GetEntries()==2 && branchElectron->GetEntries()==2){
        higgs = ((Electron*) branchElectron->At(0))->P4();
        higgs += ((Electron*) branchElectron->At(1))->P4();
        higgs += ((Muon*) branchMuon->At(0))->P4();
        higgs += ((Muon*) branchMuon->At(1))->P4();
      }
      else{
        continue;
      }
      
      histHiggsMass->Fill(higgs.M());
    }

  }

  TCanvas *c = new TCanvas();
  histHiggsMass->Draw("E");
    
  // Save 4l mass hist
  TFile *f = new TFile(saveName,"RECREATE");
  histHiggsMass->Write("",TObject::kOverwrite);  
}
 
