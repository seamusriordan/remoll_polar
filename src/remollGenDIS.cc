#include "remollGenDIS.hh"

#include "CLHEP/Random/RandFlat.h"

#include "remollEvent.hh"
#include "remollVertex.hh"
#include "G4Material.hh"

#include "remolltypes.hh"

////////////////////////////////////////////////////////
#include "cteq/cteqpdf.h"

cteq_pdf_t *__dis_pdf;

// Use CTEQ6 parameterization
//
void initcteqpdf(){
         __dis_pdf = cteq_pdf_alloc_id(400); 
}

void freecteqpdf(){
         cteq_pdf_free(__dis_pdf); 
}

////////////////////////////////////////////////////////

remollGenDIS::remollGenDIS(){
    fTh_min =     5.0*deg;
    fTh_max =     60.0*deg;

    fApplyMultScatt = true;

    // init DIS cteq pdf
    initcteqpdf();
}

remollGenDIS::~remollGenDIS(){
    freecteqpdf();
}

void remollGenDIS::SamplePhysics(remollVertex *vert, remollEvent *evt){
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

    if( fE_min < 0.0 || fE_min > efmax ){
	G4cerr << __FILE__ << " line " << __LINE__ <<
		             ": Warning!  minimum energy specified is nonmeaninful (" << fE_min/GeV << " GeV), setting to 0" << G4endl;
	efmin = 0.0;
    } else {
	efmin = fE_min;
    }

    double ef = CLHEP::RandFlat::shoot(efmin, efmax);


    if( vert->GetMaterial()->GetNumberOfElements() != 1 ){
	G4cerr << __FILE__ << " line " << __LINE__ << 
	    ": Error!  Some lazy programmer didn't account for complex materials in the moller process!" << G4endl;
	exit(1);
    }

    double Q2 = 2.0*beamE*ef*(1.0-cos(th));
    evt->SetQ2( Q2 );

    double nu = beamE-ef;
    evt->SetW2( mp*mp + 2.0*mp*nu - Q2 );
    double x = Q2/(2.0*mp*nu);
    evt->SetXbj( x );
    double y = nu/beamE;

    double numax = beamE;

    double Ynum = 2.0*x*(1.0-y/2.0);
    double Yden = 2.0*x*y + 4.0*x*(1.0-y-x*y*mp/(2.0*numax))/y;
    double Y = Ynum/Yden;

    double eta_gZ = GF*Q2*MZ*MZ/(alpha*2.0*sqrt(2.0)*pi)/(Q2+MZ*MZ);

    double evQ2 = Q2/(GeV*GeV);
    // Force a mimimum evolution
    if( evQ2 < 1.0 ){
	evQ2 = 1.0;
    }

    double qu =    cteq_pdf_evolvepdf(__dis_pdf, 1, x, sqrt(evQ2) );
    double qd =    cteq_pdf_evolvepdf(__dis_pdf, 2, x, sqrt(evQ2) );
    double qubar = cteq_pdf_evolvepdf(__dis_pdf, -1, x, sqrt(evQ2) );
    double qdbar = cteq_pdf_evolvepdf(__dis_pdf, -2, x, sqrt(evQ2) );

    double quv = qu-qubar;
    double qdv = qd-qdbar;

    double qs = cteq_pdf_evolvepdf(__dis_pdf, 3, x, sqrt(evQ2) );


    double F2p = x*( e_u*e_u*quv + e_d*e_d*qdv );
    double F2n = x*( e_u*e_u*qdv + e_d*e_d*quv );

    double F1gZp = e_u*gV_u*quv + e_d*gV_d*qdv;
    double F1gZn = e_u*gV_u*qdv + e_d*gV_d*quv;

    double F3gZp = 2.0*(e_u*gA_u*quv + e_d*gA_d*qdv);
    double F3gZn = 2.0*(e_u*gA_u*qdv + e_d*gA_d*quv);

    // Sea quarks, 2 is to account for quarks and antiquarks
    F2p  += x*(2.0*e_u*e_u*qubar + 2.0*e_d*e_d*(qdbar + qs));
    F2n  += x*(2.0*e_u*e_u*qubar + 2.0*e_d*e_d*(qdbar + qs));

    F1gZp += 2.0*e_u*gV_u*qubar + 2.0*e_d*gV_d*(qdbar+qs);
    F1gZn += 2.0*e_u*gV_u*qubar + 2.0*e_d*gV_d*(qdbar+qs);

    // Sea quarks cancel for F3gZ

    double F1p = F2p/(2.0*x);
    double F1n = F2n/(2.0*x);


    //  PDG formulas for cross section
    double sigmap_dxdy = 4.0*pi*alpha*alpha*((1.0-y-pow(x*y*mp,2.0)/Q2)*F2p+y*y*x*F1p)/(x*y*Q2);
    double sigman_dxdy = 4.0*pi*alpha*alpha*((1.0-y-pow(x*y*mp,2.0)/Q2)*F2n+y*y*x*F1n)/(x*y*Q2);

    double sigmap_dOmega_dE = sigmap_dxdy*ef*hbarc*hbarc/(2.0*pi*mp*nu);
    double sigman_dOmega_dE = sigman_dxdy*ef*hbarc*hbarc/(2.0*pi*mp*nu);


    double pcont = sigmap_dOmega_dE*vert->GetMaterial()->GetZ();
	//  Effective neutron number...  I don't like it either  SPR 2/14/2013
    double ncont = sigman_dOmega_dE*(vert->GetMaterial()->GetA()*mole/g - vert->GetMaterial()->GetZ());

    double sigmatot = pcont + ncont;

    double V = (fPh_max - fPh_min)*(cos(fTh_min) - cos(fTh_max))*(efmax-efmin);

    evt->SetEffCrossSection(sigmatot*V);

    G4double APVp = eta_gZ*(gA*F1gZp + Y*gV*F3gZp)/F1p;
    G4double APVn = eta_gZ*(gA*F1gZn + Y*gV*F3gZn)/F1n;

    G4double APV = 0.0;

    if( pcont + ncont > 0.0 ){
	APV = (APVp*pcont + APVn*ncont)/(pcont+ncont);
    }
    
    evt->SetAsymmetry(APV);

    evt->ProduceNewParticle( G4ThreeVector(0.0, 0.0, 0.0), 
	                     G4ThreeVector(ef*sin(th)*cos(ph), ef*sin(th)*sin(ph), ef*cos(th) ), 
			     "e-" );

    return;
}
