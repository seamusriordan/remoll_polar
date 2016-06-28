#ifndef __REMOLLDIPOLEFIELD_HH
#define __REMOLLDIPOLEFIELD_HH

#include <vector>
#include "remollMagneticField.hh"
#include "G4ThreeVector.hh"

class remollDipoleField : public remollMagneticField {

    public:
        remollDipoleField(G4ThreeVector orig, G4ThreeVector s, G4double B);
        ~remollDipoleField();

        void GetFieldValue(const G4double Point[4], G4double *Bfield) const;

        void SetOrigin(G4ThreeVector o){origin = o;}
        void SetSize(G4ThreeVector s);
        void SetField(G4double B){BDip = B;}

    private:
        bool pointInRange(const G4double Point[4]) const;
        G4ThreeVector origin;
        G4ThreeVector size;
        G4double BDip;
};

#endif//__REMOLLDIPOLEFIELD_HH

