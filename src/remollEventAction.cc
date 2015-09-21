#include "remollEventAction.hh"
#include "remollGenericDetectorHit.hh"
#include "remollGenericDetectorSum.hh"
#include "remollCalDetectorSum.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4SDManager.hh"
#include "G4UImanager.hh"
#include "G4ios.hh"
#include "remollglobs.hh"
#include "remollIO.hh"


remollEventAction::remollEventAction() {
}

remollEventAction::~remollEventAction(){
}


void remollEventAction::BeginOfEventAction(const G4Event*ev) {
    // Pretty ongoing status with flush
    if( (ev->GetEventID() % 100) == 0 ){
	printf("Event %8d\r", ev->GetEventID() );
	fflush(stdout);
    }

    return;
}

void remollEventAction::EndOfEventAction(const G4Event* evt ) {
  //G4SDManager   *SDman = G4SDManager::GetSDMpointer();
  G4HCofThisEvent *HCE = evt->GetHCofThisEvent();

  G4VHitsCollection *thiscol;
  Bool_t hitBore = false;


  // Traverse all hit collections, sort by output type
  for( int hcidx = 0; hcidx < HCE->GetCapacity(); hcidx++ ){
      thiscol = HCE->GetHC(hcidx);
      if(thiscol){ // This is NULL if nothing is stored
	  // Dyanmic cast to test types, process however see fit and feed to IO
	  
	  ////  Generic Detector Hits ///////////////////////////////////
	  if( remollGenericDetectorHitsCollection *thiscast = 
		  dynamic_cast<remollGenericDetectorHitsCollection *>(thiscol)){
	      for( unsigned int hidx = 0; hidx < thiscast->GetSize(); hidx++ ){
		  fIO->AddGenericDetectorHit(
			  (remollGenericDetectorHit *) thiscast->GetHit(hidx) );
                  if (((remollGenericDetectorHit *) thiscast->GetHit(hidx))->fDetID == gBoreDetNum 
				  && ((remollGenericDetectorHit *) thiscast->GetHit(hidx))->fmTrID == 0) {
			  // This is an exclusive cut, if either particle hits the magnet bore then this boolean is turned to true in reference to the event, rather than the individual particles (one may not hit the magnet bore but it still gets the boolean switched due to the other particle's bad path).
	                  hitBore=true;
	          }	  
	      }
	  }
	  
	  ////  Generic Detector Sum ////////////////////////////////////
	  if( remollGenericDetectorSumCollection *thiscast = 
		  dynamic_cast<remollGenericDetectorSumCollection *>(thiscol)){
	      for( unsigned int hidx = 0; hidx < thiscast->GetSize(); hidx++ ){
		  fIO->AddGenericDetectorSum(
			  (remollGenericDetectorSum *) thiscast->GetHit(hidx) );
	      }
	  }
	  
	  ////  CalDetector Sum ////////////////////////////////////
	  if( remollCalDetectorSumCollection *thiscast = 
		  dynamic_cast<remollCalDetectorSumCollection *>(thiscol)){
	    for( unsigned int hidx = 0; hidx < thiscast->GetSize(); hidx++ ){
	      fIO->AddCalDetectorSum(
				     (remollCalDetectorSum *) thiscast->GetHit(hidx) );
	    }
	  }


      }
  }

  fIO->SetHitBore(hitBore);

  // Fill tree and reset buffers
  fIO->FillTree();
  fIO->Flush();

  return;
}



