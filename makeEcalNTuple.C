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
#include "stdio.h"
#include "TRandom3.h"
#include "../HiForestAnalysis/hiForest.h"
#include "alexEcalSkim.h"

const Double_t etaCut = 3.0;
const Double_t vzCut = 15;

collisionType getCType(sampleType sType);

int makeEcalNTuple(const char *inFile, sampleType sType, const char *outName, Float_t mcweight=1)
{
  bool montecarlo = false;
  if(sType == kPPMC || sType == kPAMC || sType == kHIMC)
    montecarlo = true;

  collisionType cType = getCType(sType);

  TFile *outfile = new TFile(outName,"RECREATE");

  initEcalSkim(montecarlo); //see alexEcalSkim.h

  HiForest *c = new HiForest(inFile, "Forest", cType, montecarlo);
  c->InitTree(); //could be redundant, but doesn't hurt
  // if( cType == cPbPb )
  //   c->GetEnergyScaleTable((char*)"photonEnergyScaleTable_lowPt_v6.root");

  c->LoadNoTrees(); // turns off trees I'm not using: loops faster
  c->hasPhotonTree = true;
  c->hasSkimTree = true; // required for selectEvent()
  c->hasEvtTree = true;
  c->hasHltTree = true;

  //loop over events in each file
  Long64_t nentries = c->GetEntries();
  for(Long64_t jentry = 0; jentry<nentries; ++jentry)
  {
    if (jentry % 1000 == 0)  {
      printf("%lld / %lld\n",jentry,nentries);
    }

    c->GetEntry(jentry);

    //event selection
    if( !c->selectEvent() )
      continue;

    if( TMath::Abs(c->evt.vz) > vzCut )
      continue;

    if(c->photon.nPhotons == 0)
      continue;

    //loop over photons in the event
    //////////////////////////////////////////
    nClust_ = 0;
    for(Int_t i = 0; i < c->photon.nPhotons; ++i)
    {
      if(
	(TMath::Abs(c->photon.eta[i]) > etaCut) ||
	(c->isSpike(i)) //||
	//(!(c->isLoosePhoton(i)))
	)
	continue;

      pt_[nClust_] = c->photon.pt[i];
      //corrGPt_ = leadingCorrectedPt;
      eta_[nClust_] = c->photon.eta[i];
      phi_[nClust_] = c->photon.phi[i];
      cc4_[nClust_] = c->photon.cc4[i];
      cr4_[nClust_] = c->photon.cr4[i];
      ct4PtCut20_[nClust_] = c->photon.ct4PtCut20[i];
      hadronicOverEm_[nClust_] = c->photon.hadronicOverEm[i];
      sigmaIetaIeta_[nClust_] = c->photon.sigmaIetaIeta[i];
      r9_[nClust_] = c->photon.r9[i];
      ecalRecHitSumEtConeDR04_[nClust_] = c->photon.ecalRecHitSumEtConeDR04[i];
      hcalTowerSumEtConeDR04_[nClust_] = c->photon.hcalTowerSumEtConeDR04[i];
      trkSumPtHollowConeDR04_[nClust_] = c->photon.trkSumPtHollowConeDR04[i];

      if(montecarlo)
      {
	genMomId_[nClust_] = c->photon.genMomId[i];
	genCalIsoDR04_[nClust_] = c->photon.genCalIsoDR04[i];
	genTrkIsoDR04_[nClust_] = c->photon.genTrkIsoDR04[i];
	genGPt_[nClust_] = c->photon.genMatchedPt[i];
	genGEta_[nClust_] = c->photon.genMatchedEta[i];
	genGPhi_[nClust_] = c->photon.genMatchedPhi[i];
      }

      nClust_++;
      if((unsigned)nClust_ > MAXCLUSTERS)
      {
	printf("ERROR: Number of clusters exceeds 500\n");
	printf("Total: %i\n",c->photon.nPhotons);
	exit(1);
      }
    }
    run_ = c->evt.run;
    event_ = c->photon.event;
    lumi_ = c->evt.lumi;
    HF_ = c->evt.hiHF;
    HFplusEta4_ = c->evt.hiHFplusEta4;
    HFminusEta4_ = c->evt.hiHFminusEta4;
    hiBin_ = c->evt.hiBin;

    L1_SingleEG5_BptxAND = c->hlt.L1_SingleEG5_BptxAND;
    L1_SingleEG5_BptxAND_Prescl = c->hlt.L1_SingleEG5_BptxAND_Prescl;
    L1_SingleEG12 = c->hlt.L1_SingleEG12;
    L1_SingleEG12_Prescl = c->hlt.L1_SingleEG12_Prescl;
    HLT_PAPhoton10_NoCaloIdVL_v1 = c->hlt.HLT_PAPhoton10_NoCaloIdVL_v1;
    HLT_PAPhoton10_NoCaloIdVL_v1_Prescl = c->hlt.HLT_PAPhoton10_NoCaloIdVL_v1_Prescl;
    HLT_PAPhoton15_NoCaloIdVL_v1 = c->hlt.HLT_PAPhoton15_NoCaloIdVL_v1;
    HLT_PAPhoton15_NoCaloIdVL_v1_Prescl = c->hlt.HLT_PAPhoton15_NoCaloIdVL_v1_Prescl;
    HLT_PAPhoton20_NoCaloIdVL_v1 = c->hlt.HLT_PAPhoton20_NoCaloIdVL_v1;
    HLT_PAPhoton20_NoCaloIdVL_v1_Prescl = c->hlt.HLT_PAPhoton20_NoCaloIdVL_v1_Prescl;
    HLT_PAPhoton30_NoCaloIdVL_v1 = c->hlt.HLT_PAPhoton30_NoCaloIdVL_v1;
    HLT_PAPhoton30_NoCaloIdVL_v1_Prescl = c->hlt.HLT_PAPhoton30_NoCaloIdVL_v1_Prescl;
    HLT_PAPhoton40_NoCaloIdVL_v1 = c->hlt.HLT_PAPhoton40_NoCaloIdVL_v1;
    HLT_PAPhoton40_NoCaloIdVL_v1_Prescl = c->hlt.HLT_PAPhoton40_NoCaloIdVL_v1_Prescl;
    HLT_PAPhoton60_NoCaloIdVL_v1 = c->hlt.HLT_PAPhoton60_NoCaloIdVL_v1;
    HLT_PAPhoton60_NoCaloIdVL_v1_Prescl = c->hlt.HLT_PAPhoton60_NoCaloIdVL_v1_Prescl;

    if(montecarlo)
    {
      ptHat_ = c->photon.ptHat;
      mcweight_ = mcweight;
    }

    ecalTree_->Fill();
  }

  outfile->cd();
  ecalTree_->Write();
  outfile->Close();

  printf("Done.\n");
  return(0);
}

collisionType getCType(sampleType sType)
{
  switch (sType)
  {
  case kPPDATA:
  case kPPMC:
    return cPP;
  case kPADATA:
  case kPAMC:
    return cPPb;
  case kHIDATA:
  case kHIMC:
    return cPbPb;
  }
  return cPbPb; //probably a bad guess
}

int main(int argc, char *argv[])
{
  if(argc != 4 && argc != 5)
  {
    printf("Usage: makeEcalNTuple.exe \"inForest\" sampleType \"outname\" mcweight");
    return(1);
  }
  if(argc == 4)
    return(makeEcalNTuple(argv[1], (sampleType)atoi(argv[2]), argv[3]));
  else
    return(makeEcalNTuple(argv[1], (sampleType)atoi(argv[2]), argv[3], atof(argv[4])));
}
