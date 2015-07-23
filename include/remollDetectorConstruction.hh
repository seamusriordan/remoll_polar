#ifndef __MOLLERDETECTORCONSTRUCTION_HH
#define __MOLLERDETECTORCONSTRUCTION_HH

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "remollGlobalField.hh"
#include <vector>

class remollIO;
class G4Tubs;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4VSensitiveDetector;


class remollDetectorConstruction : public G4VUserDetectorConstruction
{
	public:
		remollDetectorConstruction();
		virtual ~remollDetectorConstruction();

	public:
		G4VPhysicalVolume* Construct();

		void CreateGlobalMagneticField();

		void SetDetectorGeomFile(const G4String&);

		remollGlobalField* GetGlobalField(){ return fGlobalField; }

		void SetIO( remollIO *io ){ fIO = io; }

		G4double meas_loc_x,meas_loc_y,meas_loc_z;
	private:

		G4FieldManager*		fGlobalFieldManager;
		remollGlobalField* 	fGlobalField;
		G4String 		fDetFileName;

		remollIO *fIO;

		void DumpGeometricalTree(G4VPhysicalVolume* aVolume,G4int depth=0);
		G4int UpdateCopyNo(G4VPhysicalVolume* aVolume,G4int index=0);

};
#endif
