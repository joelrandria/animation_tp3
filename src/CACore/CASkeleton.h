
#ifndef __CASkeleton_H__
#define __CASkeleton_H__

#include <string>
#include <vector>
#include <cassert>
#include <fstream>
#include <iostream>

#include <BVH.h>

namespace chara {


/*
	
class CAJoint
{
public:
   int m_fatherId;        // Le num�ro du p�re dans le tableau de CAJoint de CASkeleton
   Mat4f m_local2world;   // La matrice passant du rep�re de l'articulation vers le monde. On peut aussi stocker un quaternion + une translation
   //Mat4f m_world2local;   // Si besoin : La matrice passant du rep�re du monde vers l'articulation
};


class CASkeleton
{
public:
   //! Cr�er un squelette ayant la m�me structure que d�finit dans le BVH
   CASkeleton(const BVH& );

   //! Positionne ce squelette dans la position n du BVH
   void setPose(const BVH& bvh, const int frameNumber);

   //! Calcule la distance entre deux postures
   //! precond: les deux squelettes doivent avoir le 
   //! m�me nombre d'articulations (m�me structure d'arbre)
   float distance(const CASkeleton& skel) const;

   //! Affiche en OpenGL le squelette, les liens entre les articulations
   //! sont donn�s par le champ m_fatherId de CAJoint
   void drawGL() const;

private:
   //! L'ensemble des articulations.
   //! Remarque : la notion de hi�rarchie (arbre) n'est plus n�cessaire ici,
   //! pour tracer les os on utilise l'information "fatherID" de la class CAJoint
   std::vector<CAJoint> m_joint;
};

*/

} // namespace

#endif //
