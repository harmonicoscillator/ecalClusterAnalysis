// Author: Alex Barbieri
#ifndef alexEcalSkim_h
#define alexEcalSkim_h

#include "TTree.h"
#include "TFile.h"

enum sampleType {
  kHIDATA, //0
  kHIMC,   //1
  kPPDATA, //2
  kPPMC,   //3
  kPADATA, //4
  kPAMC    //5
};

TString getSampleName ( sampleType colli) {
  if (colli == kHIDATA) return "pbpbDATA";
  if (colli == kHIMC) return "pbpbMC";
  if (colli == kPPDATA) return "ppDATA";
  if (colli == kPPMC) return "ppMC";
  if (colli == kPADATA) return "ppbDATA";
  if (colli == kPAMC) return "ppbMC";
  return "NULL";
}
TString getSampleName ( int colli) {
  if (colli == kHIDATA) return "pbpbDATA";
  if (colli == kHIMC) return "pbpbMC";
  if (colli == kPPDATA) return "ppDATA";
  if (colli == kPPMC) return "ppMC";
  if (colli == kPADATA) return "ppbDATA";
  if (colli == kPAMC) return "ppbMC";
  return "NULL";
}

const UInt_t MAXCLUSTERS = 500;

TTree *ecalTree_;
// ecal tree
Int_t run_;
Int_t event_;
Int_t lumi_;
Float_t HF_;
Float_t HFplusEta4_;
Float_t HFminusEta4_;
Int_t nClust_;
Int_t hiBin_;

Float_t pt_[MAXCLUSTERS];
//Float_t corrGPt_;
Float_t eta_[MAXCLUSTERS];
Float_t phi_[MAXCLUSTERS];
Float_t cc4_[MAXCLUSTERS];
Float_t cr4_[MAXCLUSTERS];
Float_t ct4PtCut20_[MAXCLUSTERS];
Float_t hadronicOverEm_[MAXCLUSTERS];
Float_t sigmaIetaIeta_[MAXCLUSTERS];
Float_t r9_[MAXCLUSTERS];
Float_t ecalRecHitSumEtConeDR04_[MAXCLUSTERS];
Float_t hcalTowerSumEtConeDR04_[MAXCLUSTERS];
Float_t trkSumPtHollowConeDR04_[MAXCLUSTERS];

// MC elements
Float_t ptHat_;
Float_t mcweight_;
Int_t genMomId_[MAXCLUSTERS];
Float_t genCalIsoDR04_[MAXCLUSTERS];
Float_t genTrkIsoDR04_[MAXCLUSTERS];
Float_t genGPt_[MAXCLUSTERS];
Float_t genGEta_[MAXCLUSTERS];
Float_t genGPhi_[MAXCLUSTERS];

void setBranches_(bool montecarlo)
{
  ecalTree_->Branch("run",&run_,"run/I");
  ecalTree_->Branch("event",&event_,"event/I");
  ecalTree_->Branch("lumi",&lumi_,"lumi/I");
  ecalTree_->Branch("HF",&HF_,"HF/F");
  ecalTree_->Branch("HFplusEta4",&HFplusEta4_,"HFplusEta4/F");
  ecalTree_->Branch("HFminusEta4",&HFminusEta4_,"HFminusEta4/F");
  ecalTree_->Branch("hiBin",&hiBin_,"hiBin/I");
  ecalTree_->Branch("nClust",&nClust_,"nClust/I");
  ecalTree_->Branch("pt",pt_,"pt[nClust]/F");
  //ecalTree_->Branch("corrPt",corrGPt_,"corrPt/F");
  ecalTree_->Branch("eta",eta_,"eta[nClust]/F");
  ecalTree_->Branch("phi",phi_,"phi[nClust]/F");
  ecalTree_->Branch("cc4",cc4_,"cc4[nClust]/F");
  ecalTree_->Branch("cr4",cr4_,"cr4[nClust]/F");
  ecalTree_->Branch("ct4PtCut20",ct4PtCut20_,"ct4PtCut20[nClust]/F");
  ecalTree_->Branch("hadronicOverEm",hadronicOverEm_,"hadronicOverEm[nClust]/F");
  ecalTree_->Branch("sigmaIetaIeta",sigmaIetaIeta_,"sigmaIetaIeta[nClust]/F");
  ecalTree_->Branch("r9",r9_,"r9[nClust]/F");
  ecalTree_->Branch("ecalRecHitSumEtConeDR04",ecalRecHitSumEtConeDR04_,"ecalRecHitSumEtConeDR04[nClust]/F");
  ecalTree_->Branch("hcalTowerSumEtConeDR04",hcalTowerSumEtConeDR04_,"hcalTowerSumEtConeDR04[nClust]/F");
  ecalTree_->Branch("trkSumPtHollowConeDR04",trkSumPtHollowConeDR04_,"trkSumPtHollowConeDR04[nClust]/F");

  if(montecarlo)
  {
    ecalTree_->Branch("ptHat",&ptHat_,"ptHat/F");
    ecalTree_->Branch("mcweight",&mcweight_,"mcweight/F");
    ecalTree_->Branch("genMomId",genMomId_,"genMomId[nClust]/I");
    ecalTree_->Branch("genCalIsoDR04",genCalIsoDR04_,"genCalIsoDR04[nClust]/F");
    ecalTree_->Branch("genTrkIsoDR04",genTrkIsoDR04_,"genTrkIsoDR04[nClust]/F");
    ecalTree_->Branch("genPt",genGPt_,"genPt[nClust]/F");
    ecalTree_->Branch("genEta",genGEta_,"genEta[nClust]/F");
    ecalTree_->Branch("genPhi",genGPhi_,"genPhi[nClust]/F");
  }
}

void getBranches_(bool montecarlo)
{
  ecalTree_->SetBranchAddress("run",&run_);
  ecalTree_->SetBranchAddress("event",&event_);
  ecalTree_->SetBranchAddress("lumi",&lumi_);
  ecalTree_->SetBranchAddress("HF",&HF_);
  ecalTree_->SetBranchAddress("HFplusEta4",&HFplusEta4_);
  ecalTree_->SetBranchAddress("HFminusEta4",&HFminusEta4_);
  ecalTree_->SetBranchAddress("hiBin",&hiBin_);
  ecalTree_->SetBranchAddress("nClust",&nClust_);
  ecalTree_->SetBranchAddress("pt",pt_);
  //ecalTree_->SetBranchAddress("corrPt",corrGPt_);
  ecalTree_->SetBranchAddress("eta",eta_);
  ecalTree_->SetBranchAddress("phi",phi_);
  ecalTree_->SetBranchAddress("cc4",cc4_);
  ecalTree_->SetBranchAddress("cr4",cr4_);
  ecalTree_->SetBranchAddress("ct4PtCut20",ct4PtCut20_);
  ecalTree_->SetBranchAddress("hadronicOverEm",hadronicOverEm_);
  ecalTree_->SetBranchAddress("sigmaIetaIeta",sigmaIetaIeta_);
  ecalTree_->SetBranchAddress("r9",r9_);
  ecalTree_->SetBranchAddress("ecalRecHitSumEtConeDR04",ecalRecHitSumEtConeDR04_);
  ecalTree_->SetBranchAddress("hcalTowerSumEtConeDR04",hcalTowerSumEtConeDR04_);
  ecalTree_->SetBranchAddress("trkSumPtHollowConeDR04",trkSumPtHollowConeDR04_);

  if(montecarlo)
  {
    ecalTree_->SetBranchAddress("ptHat",&ptHat_);
    ecalTree_->SetBranchAddress("mcweight",&mcweight_);
    ecalTree_->SetBranchAddress("genMomId",genMomId_);
    ecalTree_->SetBranchAddress("genCalIsoDR04",genCalIsoDR04_);
    ecalTree_->SetBranchAddress("genTrkIsoDR04",genTrkIsoDR04_);
    ecalTree_->SetBranchAddress("genPt",genGPt_);
    ecalTree_->SetBranchAddress("genEta",genGEta_);
    ecalTree_->SetBranchAddress("genPhi",genGPhi_);
  }
}

void readEcalSkim(TFile *filename, bool montecarlo = false)
{
  ecalTree_ = (TTree*)filename->Get("ecalTree");

  getBranches_(montecarlo);
}

void initEcalSkim(bool montecarlo = false)
{
  ecalTree_ = new TTree("ecalTree","ecalTree");

  setBranches_(montecarlo);
}



#endif
