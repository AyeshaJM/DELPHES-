/*
root -l 'examples/MyReader_1.C("../delphes_h4lep///Events/run_01/tag_1_delphes_events.root")'
*/


#ifdef __CLING__
R__LOAD_LIBRARY(libDelphes)
#include "classes/DelphesClasses.h"
#include "external/ExRootAnalysis/ExRootTreeReader.h"
#include "external/ExRootAnalysis/ExRootResult.h"
#include "external/ExRootAnalysis/ExRootTreeBranch.h"
#include "external/ExRootAnalysis/ExRootTreeWriter.h"
#include "external/ExRootAnalysis/ExRootFilter.h"
#else
class ExRootTreeReader;
class ExRootResult;
class ExRootTreeBranch;
class ExRootTreeWriter;
class ExRootFilter;
#endif

#include <iostream>
#include <cmath>
#include <array>
#include <vector>
#include <TArrayC.h>
#include <string>
#include "TH1.h"                                 // for histrograming
#include "TVirtualPad.h"
#include "TApplication.h"
#include "TBranch.h"
#include "TBranchElement.h"
#include "TFile.h"    // ROOT, for saving file.
#include  <map>
#include "TTree.h"  //for Tree file 
#include "TROOT.h"

void MyReader_1(const char *fileName){
  
  gSystem->Load("libDelphes");

  // Create chain of root trees
  TChain chain("Delphes");
  chain.Add(fileName);

   // Creating the output file and tree
//   TFile *outfile = new TFile(outputFile,"RECREATE");
   TTree *outtree=new TTree("eventtree","Test");

  // Create object of class ExRootTreeReader
  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
  Long64_t numberOfEntries = treeReader->GetEntries();
  
  // Get pointers to branches used in this analysis
  TClonesArray *branchElectron = treeReader->UseBranch("Electron");
  TClonesArray *branchMuon = treeReader->UseBranch("Muon");
  TClonesArray *branchJet = treeReader->UseBranch("Jet");
  // ...

  // Book histograms
  TH1 *histElectronPT = new TH1F("electron pt", "electron P_{T}", 100, 0.0, 500.0);
  TH1 *histMuonsPT    = new TH1F("Muons pt", "Muons P_{T}", 100, 0.0, 500.0);
  TH1 *histJetsPT    = new TH1F("Jets pt", "Jets P_{T}", 100, 0.0, 500.0);


   Double_t elecPt, MuonPt;

   std::vector<Double_t> ELECPT;
   std::vector<Double_t> MuPT;

   //double ELECTPT;
/*------------------ Creates the Branches ------------------------*/
   outtree->Branch("ELECPT", "vector<Double_t>",&ELECPT);
   //outtree->Branch("ELECPT",&ELECPT,ELECPT/I);
   outtree->Branch("MuPT", "vector<Double_t>",&MuPT);
/*-----------------------------------------------------------------*/

  // Loop over all events
  for(Int_t entry = 0; entry < numberOfEntries; ++entry)
  {
    // print event number in the file
    if(entry%100==0) cout << "Reading Event " << entry << endl;
    
    // Load selected branches with data from specified event
    treeReader->ReadEntry(entry);
  
    // If event contains at least 1 electron
    if(branchElectron->GetEntries() > 2)
    {
      // Take first electron
       Electron *electron = (Electron*) branchElectron->At(0);
      
      // Plot electron transverse momentum
      elecPt = electron->PT;
       histElectronPT->Fill(elecPt);
       ELECPT.push_back(elecPt);

      
      // Print electron transverse momentum
       cout << electron->PT << endl;
    }

    if(branchMuon->GetEntries() > 2)
    {
      // Take first electron
       Muon *muon = (Muon*) branchMuon->At(0);

      // Plot electron transverse momentum
       histMuonsPT->Fill(muon->PT);
       MuPT.push_back(muon->PT);

      // Print electron transverse momentum
       cout << muon->PT << endl;
    }

  outtree->Fill();
  }// end of events for-loop
  outtree->Print();
  //outtree->Write();


//outfile->Write();
//   delete outfile;

  // Show resulting histograms
   TCanvas *c = new TCanvas("c","c");
   c->Divide(2,1);
   c->cd(1);         histElectronPT->Draw();
   c->cd(2);         histMuonsPT->Draw();
   //TCanvas *c1 = new TCanvas("c1","c1");
   

  // Save the result as image
   c->SaveAs("ElectronMuonsPT.png");
   //c->SaveAs("ElectronPT.png");
   //c1->SaveAs("MuonPT.png");

  // Save the histogram in a ROOT file
   TFile *f = new TFile("ElectronPT.root","RECREATE");
   //histElectronPT->Write("",TObject::kOverwrite);
   //histMuonsPT->Write("",TObject::kOverwrite);
   outtree->Write("",TObject::kOverwrite);
}
 
