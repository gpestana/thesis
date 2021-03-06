//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: G4PolyconeSide.hh 67973 2013-03-13 10:16:25Z gcosmo $
//
// 
// --------------------------------------------------------------------
// GEANT 4 class header file
//
//
// G4PolyconeSide
//
// Class description:
//
//   Class implmenting a face that represents one conical side
//   of a polycone:
//
//   G4PolyconeSide( const G4PolyconeSideRZ *prevRZ,
//                   const G4PolyconeSideRZ *tail,
//                   const G4PolyconeSideRZ *head,
//                   const G4PolyconeSideRZ *nextRZ,
//                         G4double phiStart, G4double deltaPhi, 
//                         G4bool phiIsOpen, G4bool isAllBehind=false )
//
//   Values for r1,z1 and r2,z2 should be specified in clockwise
//   order in (r,z).

// Author: 
//   David C. Williams (davidw@scipp.ucsc.edu)
// --------------------------------------------------------------------

#ifndef G4PolyconeSide_hh
#define G4PolyconeSide_hh

#include "G4VCSGface.hh"

class G4IntersectingCone;

struct G4PolyconeSideRZ
{
  G4double r, z;  // start of vector
};

// ----------------------------------------------------------------------------
// MT-specific utility code 

#include "G4GeomSplitter.hh"

// The class G4PlSideData is introduced to encapsulate the
// fields of the class G4PolyconeSide that may not be read-only.
//
class G4PlSideData
{
  public:

    void initialize()
    {
      fPhi.first = G4ThreeVector(0,0,0);
      fPhi.second= 0.0;
    }

    std::pair<G4ThreeVector, G4double> fPhi;  // Cached value for phi
};

// The type G4PlSideManager is introduced to 
// encapsulate the methods used by both the master thread and 
// worker threads to allocate memory space for the fields encapsulated
// by the class G4PlSideData.
//
typedef G4GeomSplitter<G4PlSideData> G4PlSideManager;

// This macro changes the references to fields that are now encapsulated
// in the class G4PlSideData.
//
#define G4MT_pcphi ((subInstanceManager.offset[instanceID]).fPhi)
//
// ----------------------------------------------------------------------------

class G4PolyconeSide : public G4VCSGface
{
  public:

    G4PolyconeSide( const G4PolyconeSideRZ *prevRZ,
                    const G4PolyconeSideRZ *tail,
                    const G4PolyconeSideRZ *head,
                    const G4PolyconeSideRZ *nextRZ,
                          G4double phiStart, G4double deltaPhi, 
                          G4bool phiIsOpen, G4bool isAllBehind=false );
    virtual ~G4PolyconeSide();
  
    G4PolyconeSide( const G4PolyconeSide &source );
    G4PolyconeSide& operator=( const G4PolyconeSide &source );
  
    G4bool Intersect( const G4ThreeVector &p, const G4ThreeVector &v,  
                            G4bool outgoing, G4double surfTolerance,
                            G4double &distance, G4double &distFromSurface,
                            G4ThreeVector &normal, G4bool &isAllBehind );

    G4double Distance( const G4ThreeVector &p, G4bool outgoing );
  
    EInside Inside( const G4ThreeVector &p, G4double tolerance, 
                          G4double *bestDistance );
  
    G4ThreeVector Normal( const G4ThreeVector &p,  G4double *bestDistance );

    G4double Extent( const G4ThreeVector axis );

    void CalculateExtent( const EAxis axis, 
                          const G4VoxelLimits &voxelLimit,
                          const G4AffineTransform &tranform,
                                G4SolidExtentList &extentList       );

    G4VCSGface *Clone() { return new G4PolyconeSide( *this ); }

    G4double SurfaceArea();
    G4ThreeVector GetPointOnFace();
  
  public:  // without description

    G4PolyconeSide(__void__&);
      // Fake default constructor for usage restricted to direct object
      // persistency for clients requiring preallocation of memory for
      // persistifiable objects.

    inline G4int GetInstanceID() const  { return instanceID; }
      // Returns the instance ID.

    static const G4PlSideManager& GetSubInstanceManager();
      // Returns the private data instance manager.

  protected:

    G4double DistanceAway( const G4ThreeVector &p, G4bool opposite,
                                 G4double &distOutside2, G4double *rzNorm=0 );
      
    G4bool PointOnCone( const G4ThreeVector &hit, G4double normSign,
                        const G4ThreeVector &p,
                        const G4ThreeVector &v, G4ThreeVector &normal );

    void CopyStuff( const G4PolyconeSide &source );
  
    static void FindLineIntersect( G4double x1, G4double y1,
                                   G4double tx1, G4double ty1,
                                   G4double x2, G4double y2,
                                 G4double tx2, G4double ty2,
                                 G4double &x, G4double &y );

    G4double GetPhi( const G4ThreeVector& p );

  protected:

    G4double r[2], z[2]; // r, z parameters, in specified order
    G4double startPhi,   // Start phi (0 to 2pi), if phiIsOpen
             deltaPhi;   // Delta phi (0 to 2pi), if phiIsOpen
    G4bool   phiIsOpen;  // True if there is a phi slice
    G4bool   allBehind;  // True if the entire solid is "behind" this face
  
    G4IntersectingCone *cone;  // Our intersecting utility class
  
    G4double rNorm, zNorm;  // Normal to surface in r,z space
    G4double rS, zS;        // Unit vector along surface in r,z space
    G4double length;        // Length of face in r,z space
    G4double prevRS,
             prevZS;        // Unit vector along previous polyconeSide
    G4double nextRS,
             nextZS;        // Unit vector along next polyconeSide
  
    G4double rNormEdge[2],
             zNormEdge[2];  // Normal to edges

    G4int ncorners;
    G4ThreeVector *corners; // The coordinates of the corners (if phiIsOpen)

  private:

    G4double kCarTolerance; // Geometrical surface thickness
    G4double fSurfaceArea;  // Used for surface calculation 

    G4int instanceID;
      // This field is used as instance ID.
    G4GEOM_DLL static G4PlSideManager subInstanceManager;
      // This field helps to use the class G4PlSideManager introduced above.
};

#endif
