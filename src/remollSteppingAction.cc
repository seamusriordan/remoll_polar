#include "remollSteppingAction.hh"
//#include "remollSteppingActionMessenger.hh"

#include "G4VVisManager.hh"
#include "G4Polyline.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4SteppingManager.hh"

remollSteppingAction::remollSteppingAction()
:drawFlag(false)
{
///  new remollSteppingActionMessenger(this);

    fEnableKryptonite = true;

    fKryptoniteThresh = 5.0*g/cm3;
}

void remollSteppingAction::UserSteppingAction(const G4Step *aStep) {
    G4Track* fTrack = aStep->GetTrack();
    G4Material* material = fTrack->GetMaterial();

    // Don't continue in thick materials  FIXME:  GEMCopper is a bad way to do this
    if(  material->GetDensity() > fKryptoniteThresh && fEnableKryptonite && material->GetName()!="GEMCopper"  ){
	fTrack->SetTrackStatus(fStopAndKill);
    }
    if(   material->GetName()=="Kryptonite" ){
	fTrack->SetTrackStatus(fStopAndKill);
    }


}


