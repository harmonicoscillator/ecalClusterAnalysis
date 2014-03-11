// Author Alex Barbieri
#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TString.h"
#include "TChain.h"
#include "TCut.h"
#include "stdio.h"
//#include "fitResult.h"

void ecalSpectra()
{
  TH1::SetDefaultSumw2();

  //const Double_t PTBINS[] = {0,2.5,5,7.5,10,12.5,15,17.5, 20,25, 30,35, 40, 50, 60, 80, 120, 300};
  //const Int_t nPTBINS = 5;
  //const Int_t nPTBINS = sizeof(PTBINS)/sizeof(Double_t) -1;

  TChain *ecalTree = new TChain("ecalTree");
  ecalTree->Add("pA_promptRECO/*.root");
  //ecalTree->Add("pA_promptRECO/89.root");
  //TH1D *ecalSpectra = new TH1D("ecalSpectra","ecalSpectra", nPTBINS, PTBINS);
  TH1D *ecalSpectra = new TH1D("ecalSpectra","ecalSpectra",300,0,300);

  // const TCut ecalEtaCut = "abs(ecalTree.eta) < 1.44";
  // const TCut isoCut = "ecalRecHitSumEtConeDR04 < 4.2  &&  hcalTowerSumEtConeDR04 < 2.2  &&  trkSumPtHollowConeDR04 < 2 && hadronicOverEm<0.1";
  // const TCut genCut = "genCalIsoDR04<5 && abs(genMomId)<=22";
  // const TCut sbCut = "(cc4+cr4+ct4PtCut20>10) && (cc4+cr4+ct4PtCut20<20) && hadronicOverEm<0.1";
  // const TCut candidateCut = "sigmaIetaIeta<0.01";
  // const TCut decayCut = "(sigmaIetaIeta>0.011) && (sigmaIetaIeta<0.017)";

  //TCut ecalPtCut = "ecalTree.corrPt>40 && ecalTree.corrPt<300";

  //const TCut triggerCut = "HLT_PAPhoton10_NoCaloIdVL_v1 && HLT_PAPhoton10_NoCaloIdVL_v1_Prescl==1 && L1_SingleEG5_BptxAND_Prescl==1";
  const TCut triggerCut = "HLT_PAPhoton10_NoCaloIdVL_v1";
  const TCut showerCut = "sigmaIetaIeta > 0.011";
  const TCut etaCut = "abs(eta) < 1.44";
  //const TCut trackerIso = "trkSumPtHollowConeDR04 > 2";
  const TCut ecalIso = "ecalRecHitSumEtConeDR04 > 4.2";
  //const TCut hcalIso
  Int_t count = ecalTree->Project(ecalSpectra->GetName(),"pt", triggerCut && showerCut && etaCut && ecalIso);
  printf("Num events: %i\n", count);

  TCanvas *c1 = new TCanvas();
  ecalSpectra->Draw();
  // correctedEcalSpectra->Draw("same");
  c1->SetLogy();

  // TFile *outFile = new TFile("ecalSpectra.root", "RECREATE");
  // outFile->cd();
  // ecalSpectra->Write();
  // correctedEcalSpectra->Write();
  // outFile->Close();
}

int main()
{
  ecalSpectra();
  return 0;
}
