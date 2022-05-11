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
##include "TVirtualPad.h"
#include "TApplication.h"
#include "TBranch.h"
#include "TBranchElement.h"
#include "TFile.h"                     // ROOT, for saving file.
#include  <map>
#include "TTree.h"                     //for Tree file 
#include "TROOT.h"


//------------------------------------------------------------------------------

void DelphesAnalysis(const char *inputFile)
{
  gSystem->Load("libDelphes");

  // Create chain of root trees
  TChain chain("Delphes");
  chain.Add(inputFile);
 
  // Creating the output file and tree
  TFile *outfile = new TFile("DelphesExtracted.root","RECREATE");
  TTree *outtree=new TTree("event_tree","Test");


  // Create object of class ExRootTreeReader
  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
  
  Long64_t numberOfEntries = treeReader->GetEntries();

  cout << "** Chain contains " << numberOfEntries << " events" << endl; //To see the total number of events
  ExRootResult *result = new ExRootResult();


  // Get pointers to branches used in this analysis
  TClonesArray *branchPhoton = treeReader->UseBranch("Photon");
  TClonesArray *branchMissingET = treeReader->UseBranch("MissingET");

  
   Photon *photon;
   MissingET *misset;

   Double_t MET, ETAmiss, PHImiss, PTph, Eph, ETAph, PHIph;


  /* --------- Creating the DATA file ---------------*/

  ofstream myfile;  
  myfile.open ("ExtractedData.dat");


  /*-------------------------------------------------*/

  /*--------------------------------------------------------*/
  outtree->Branch("MET",&MET);
  outtree->Branch("ETAmiss",&ETAmiss);
  outtree->Branch("PHImiss",&PHImiss);
  outtree->Branch("PTph",&PTph);
  outtree->Branch("Eph",&Eph);
  outtree->Branch("ETAph",&ETAph);
  outtree->Branch("PHIph",&PHIph);
 /*--------------------------------------------------------*/

  // Loop over all events
  for(Int_t entry = 0; entry < numberOfEntries; ++entry)
  {
    // Load selected branches with data from specified event
    treeReader->ReadEntry(entry);
   
   // if(entry>10) break;

   // cout<<"--------- New Event ("<< entry << ") ---------" <<endl;

    // loop over all input particles in the event

   for(Int_t ii=0; ii < branchMissingET->GetEntriesFast(); ii++)
    {
     misset = (MissingET*) branchMissingET->At(ii);
     MET = misset->MET;
     ETAmiss = misset->Eta;
     PHImiss = misset->Phi;
    // cout<<"| MET: "<<misset->MET<<" | Eta: "<<misset->Eta<<" | Phi: "<<misset->Phi<<" | "<<endl;
     myfile << misset->MET << "\t" << misset->Eta << "\t" << misset->Phi <<"\t";
	}

 for(Int_t i=0; i < branchPhoton->GetEntriesFast(); i++)
    {
     photon = (Photon*) branchPhoton->At(i);
     PTph = photon->PT;
     Eph = photon->E;
     ETAph = photon->Eta;
     PHIph = photon->Phi;
    // cout<<"| E: "<<photon->E<<" | PT: "<<photon->PT<<" | Eta: "<<photon->Eta<<" | Phi: "<<photon->Phi<<" | "<<endl;
     myfile << photon->E <<"\t"<< photon->PT <<"\t"<< photon->Eta <<"\t"<<photon->Phi<<"\n";
        }

  }
outtree->Fill();
outfile->Write();
delete outfile;
}

