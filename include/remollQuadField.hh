#ifndef __REMOLLQUADFIELD_HH
#define __REMOLLQUADFIELD_HH

#include <vector>
#include "remollMagneticField.hh"
#include "G4ThreeVector.hh"

class remollQuadField : public remollMagneticField {

    public:
        remollQuadField(G4ThreeVector orig, G4ThreeVector s, G4double ap, G4double B);
        ~remollQuadField();

        void GetFieldValue(const G4double Point[4], G4double *Bfield) const;
        
        void SetOrigin(G4ThreeVector o){origin = o;}
        void SetSize(G4ThreeVector s);
        void SetAperture(G4double a);
        void SetField(G4double B){BQuad = B;}

    private:
        bool pointInRange(const G4double Point[4]) const;
        //Origin
        G4ThreeVector origin;
        //Size
        G4ThreeVector size;
        //Aperture size
        G4double aperture;
        //Maximum magnetic field value (at aperture edge)
        G4double BQuad;
};

#endif//__REMOLLQUADFIELD_HH
