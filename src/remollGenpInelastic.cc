#include "remollGenpInelastic.hh"

#include "christy_bosted_inelastic.h"

#include "CLHEP/Random/RandFlat.h"

#include "remollEvent.hh"
#include "remollVertex.hh"
#include "G4Material.hh"

#include "remolltypes.hh"

remollGenpInelastic::remollGenpInelastic(){
    fTh_min =     5.0*deg;
    fTh_max =     60.0*deg;

    fApplyMultScatt = true;
}

remollGenpInelastic::~remollGenpInelastic(){
}

void remollGenpInelastic::SamplePhysics(remollVertex *vert, remollEvent *evt){
    // Generate inelastic event

    double beamE = vert->GetBeamE();
    double mp    = proton_mass_c2;

    double th = acos(CLHEP::RandFlat::shoot(cos(fTh_max), cos(fTh_min)));
    double ph = CLHEP::RandFlat::shoot(fPh_min, fPh_max);
    double efmax = mp*beamE/(mp + beamE*(1.0-cos(th)));;
    double efmin = 0.0;

    if( efmax > fE_max ){
	efmax = fE_max;
    }

    if(fE_min < 0 || fE_min > efmax ){
	 G4cerr << __FILE__ << " line " << __LINE__ <<
	     ": Warning!  minimum energy specified is nonmeaninful (" << fE_min/GeV << " GeV), setting to 0" << G4endl;
	 efmin = 0.0;
    } else {
	efmin = fE_min;
    }


    double ef = CLHEP::RandFlat::shoot(efmin, efmax);

    double thissigma_p = sigma_p( beamE/GeV, th, ef/GeV )*nanobarn/GeV;
    double thissigma_n = sigma_n( beamE/GeV, th, ef/GeV )*nanobarn/GeV;

    double sigmatot = thissigma_p*vert->GetMaterial()->GetZ() +
	//  Effective neutron number...  I don't like it either  SPR 2/14/2013
	thissigma_n*(vert->GetMaterial()->GetA()*mole/g - vert->GetMaterial()->GetZ());

    double V = (fPh_max-fPh_min)*(cos(fTh_min) - cos(fTh_max))*(efmax-efmin);

    evt->SetEffCrossSection(sigmatot*V);

    if( vert->GetMaterial()->GetNumberOfElements() != 1 ){
	G4cerr << __FILE__ << " line " << __LINE__ << 
	    ": Error!  Some lazy programmer didn't account for complex materials in the moller process!" << G4endl;
	exit(1);
    }


    double Q2 = 2.0*beamE*ef*(1.0-cos(th));
    evt->SetQ2( Q2 );

    G4double APV = Q2*0.8e-4/GeV/GeV; // Empirical APV value, 
                                      // stolen from mollerClass.C in mollersim

    evt->SetAsymmetry(APV);


    evt->SetW2( mp*mp + 2.0*mp*(beamE-ef) - Q2 );
    evt->SetXbj( Q2/(2.0*mp*(vert->GetBeamE()-ef) ) );


    evt->ProduceNewParticle( G4ThreeVector(0.0, 0.0, 0.0), 
	                     G4ThreeVector(ef*sin(th)*cos(ph), ef*sin(th)*sin(ph), ef*cos(th) ), 
			     "e-" );

    return;
}
