#include "remollGenPion.hh"

#include "G4String.hh"
#include "CLHEP/Random/RandFlat.h"

#include "wiser_pion.h"
#include "remollEvent.hh"
#include "remollVertex.hh"
#include "G4Material.hh"

#include "remolltypes.hh"

remollGenPion::remollGenPion(){
    fApplyMultScatt = false;

    fTh_min = 20*deg;
    fTh_max = 70*deg;

    fPionType = kPiMinus;
}

remollGenPion::~remollGenPion(){
}

void remollGenPion::SamplePhysics(remollVertex *vert, remollEvent *evt){
    // Generate Pion event

    double beamE   = vert->GetBeamE();
    double rad_len = vert->GetRadLen();

    double th = acos(CLHEP::RandFlat::shoot(cos(fTh_max), cos(fTh_min)));
    double ph = CLHEP::RandFlat::shoot(fPh_min, fPh_max);
    double pf = CLHEP::RandFlat::shoot(0.0, beamE);

    //solid angle in steradians : rakitha Tue Sep 24 14:11:36 EDT 2013
    double V = (fPh_max-fPh_min)*(cos(fTh_min) - cos(fTh_max));
    double E_int = beamE; //The integral of pion energies from 0 to beamE -> int dE from 0 to beamE : rakitha Tue Sep 24 14:11:36 EDT 2013
    //checking the radiation length: a comment in wiser_pion.h says, *effective* *total* radiator = rad_len*4/3 + 0.05
    /*
    double sigpip = wiser_sigma(beamE/GeV, pf/GeV, th, rad_len + 0.05, 0)*nanobarn/GeV;
    double sigpim = wiser_sigma(beamE/GeV, pf/GeV, th, rad_len + 0.05, 1)*nanobarn/GeV;
    */

    double sigpip = wiser_sigma(beamE/GeV, pf/GeV, th, rad_len*4.0/3.0 + 0.05, 0)*nanobarn/GeV;
    double sigpim = wiser_sigma(beamE/GeV, pf/GeV, th, rad_len*4.0/3.0 + 0.05, 1)*nanobarn/GeV;

    G4String piontypestr;

    double thisxs = 0.0;

    switch(fPionType){
	case kPiMinus:
	    piontypestr = G4String("pi-");
	    thisxs = vert->GetMaterial()->GetZ()*sigpim + (vert->GetMaterial()->GetA()*mole/g-vert->GetMaterial()->GetZ())*sigpip;
	    break;
	case kPiPlus:
	    piontypestr = G4String("pi+");
	    thisxs = vert->GetMaterial()->GetZ()*sigpip + (vert->GetMaterial()->GetA()*mole/g-vert->GetMaterial()->GetZ())*sigpim;
	    break;
	case kPi0:
	    piontypestr = G4String("pi0");
	    thisxs = vert->GetMaterial()->GetZ()*(sigpip+sigpim)/2.0 + (vert->GetMaterial()->GetA()*mole/g-vert->GetMaterial()->GetZ())*(sigpip+sigpim)/2.0;
	    break;

	default:
	    piontypestr = G4String("oops");
	    break;
    }


    
    //thisxs is in nanobarns per GeV per str
    //to get effective cross section in nanobarns, EffCrossSection = V*E_int*thisxs where V is in str and E_int is total energy integral for a pion 
    //also see main.f rate calculation in original fortran code  (main.f lines 209 - 211)
    //rakitha  Tue Sep 24 11:06:41 EDT 2013
    evt->SetEffCrossSection(V*thisxs*E_int);
    //evt->SetEffCrossSection(V*thisxs);

    if( vert->GetMaterial()->GetNumberOfElements() != 1 ){
	G4cerr << __FILE__ << " line " << __LINE__ << 
	    ": Error!  Some lazy programmer didn't account for complex materials in the moller process!" << G4endl;
	exit(1);
    }

    evt->SetAsymmetry(0.0);


    evt->ProduceNewParticle( G4ThreeVector(0.0, 0.0, 0.0), 
	    G4ThreeVector(pf*sin(ph)*sin(th), pf*cos(ph)*sin(th), pf*cos(th)), 
	    piontypestr );
    return;

}
