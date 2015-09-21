#include "remollMagneticField.hh"
#include "G4UImanager.hh"


#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

#include "G4ThreeVector.hh"

#include <iostream>
#include <fstream>

#include <assert.h>
#include <math.h>

// Boost headers
#ifdef __USE_BOOST_IOSTREAMS
// This supports gzipped iostreams as magnetic field maps.
// Compile with -D __USE_BOOST_IOSTREAMS to use.
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/device/file.hpp>
#endif

remollMagneticField::remollMagneticField( G4String filename ){ 

    fFilename = filename;

    /*!  Initialize grid variables
     */

    for( int cidx = kR; cidx < kZ; cidx++ ){
	fN[cidx] = -1;
	fMin[cidx] = -1e9;
	fMax[cidx] = -2e9;
    }

    fPhi0 = -1e9;

    fZoffset = 0.0;
    fInit = false;
    fMagCurrent0 = -1e9;

    fFieldScale = 1.0;

    ReadFieldMap();
}

remollMagneticField::~remollMagneticField(){ 
}

G4String remollMagneticField::GetName(){ 
    if( !fInit ){
	G4cerr << "WARNING " << __FILE__ << " line " << __LINE__ 
	    << ": access uninitialized field." << G4endl;
	return G4String("");
    }

    return fFilename;
}

void remollMagneticField::SetFieldScale(G4double s){ 
    fFieldScale = s;
    G4cout << fFilename << " scale set to " << s << G4endl;
    return;
}

void remollMagneticField::SetMagnetCurrent(G4double s){ 
    if( fMagCurrent0 > 0.0 ){
       	SetFieldScale(s/fMagCurrent0);
    } else {
    	G4cerr << "Warning:  " << __FILE__ << " line " << __LINE__ 
	    << ": Field current not specified in map " << fFilename << " - Ignoring and proceeding " << G4endl;
    }
    return;
}


void remollMagneticField::InitializeGrid() {
    return;
}

void remollMagneticField::ReadFieldMap(){
    const G4double eps = 1e-6;

    fInit = true;

}

void remollMagneticField::GetFieldValue(const G4double Point[4], G4double *Bfield ) const {

    // First we have to translate into polar or cylindric coordinates
    // since the field maps are given in cylindric coordinates and the 
    // interpolation will be done in cylindric coordinates as well.

    // Then we need to translate to cartesian components to give them
    // back to the field manager

    G4double r, phi, z, dxtant;
    G4double   x[__NDIM], didx[__NDIM];
    G4int    idx[__NDIM], xtant;
    G4double dphi, lphi; 


    // Point coords are ordered 0,1,2 by x,y,z

    phi = atan2(Point[1],Point[0]);
    r   = sqrt(Point[0]*Point[0] + Point[1]*Point[1]);
    z   = Point[2] - fZoffset;

    if( std::isnan(phi) || std::isinf(phi) ||
            std::isnan(r) || std::isinf(r) ||
            std::isnan(z) || std::isinf(z) ){

        G4cerr << __FILE__ << " line " << __LINE__ << ": ERROR bad conversion to cylindrical coordinates" << G4endl;
        G4cerr << "Point  ( " << Point[0]/m << ", " << Point[1]/m << ", " << Point[2]/m << " ) m" << G4endl;

        exit(1);
    }

    // Initialize fields to 0 by hand
    Bfield[0] = 0.0;
    Bfield[1] = 0.0;
    Bfield[2] = 0.0;

    //  Quad and Dipole fields by hand

    if( fabs(Point[2] - 55*cm) < 15*cm ) {
        // Add quad field, focus in x

        double B1    = 0.186*tesla;
        double q1app = 10*cm;

        Bfield[0] += (B1/q1app)*Point[1];
        Bfield[1] += (B1/q1app)*Point[0];
    }

    /*
    // Dipole


    if( fabs(Point[2] - 105*cm) < 5*cm ) {
        // Add dipole field, bend positive x for negative particles
        // bend of 45 deg over 10cm for 70 MeV
        //
        double Bdip = 1.65*tesla;

        if( Point[0] > 0 ){
            Bfield[1] -= Bdip;
        } else {
            Bfield[1] += Bdip;
        }

    }
    */

    return;
} 


