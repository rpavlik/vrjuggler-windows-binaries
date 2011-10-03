/*************** <auto-copyright.pl BEGIN do not edit this line> **************
 *
 * VR Juggler is (C) Copyright 1998-2010 by Iowa State University
 *
 * Original Authors:
 *   Allen Bierbaum, Christopher Just,
 *   Patrick Hartling, Kevin Meinert,
 *   Carolina Cruz-Neira, Albert Baker
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 *************** <auto-copyright.pl END do not edit this line> ***************/

#ifndef JUGGLER_PFRAY_COLLIDER
#define JUGGLER_PFRAY_COLLIDER

#include <collider.h>

//: Collider class for testing collisions in Performer
//
// This class will test collisions against a given world model
//
// NOTE: Remember that the navigation system is dealing
//     in Juggler (OpenGL) coordinates, not in Performer coords.
//     So there is some coord system conversion that will be
//     going on here.
class pfRayCollider : public collider
{
public:
   // ARGS: world - The node to start collision with
   //       it should be the one under the one being used for navigation ( ie. pfNaver)
   pfRayCollider( pfNode* world )
   {
      mWorldNode = world;
   }

   //: test a movement
   //!ARGS: whereYouAre - The current position we are at
   //!ARGS: delta - The amount we want to move
   //!ARGS: correction - The amount to correct the movement so that we do not collide
   //!RETURNS: true - There was a hit.
   virtual bool testMove( gmtl::Vec3f whereYouAre, gmtl::Vec3f delta, gmtl::Vec3f& correction, bool whereYouAreWithDelta = false );

   // general ray collision routine with a scene.
   // correctionVector - should be added to whereYouWantToBe after calling this function
   bool testRayCollision( pfVec3& intersectionPt,
                        pfVec3& whereYouReallyAre,
                        pfNode *objNode, int mask,
                        pfVec3 whereYouAre,
                        pfVec3 whereYouWantToBe );

   // data structure to get intersection result back from pfHit::mQuery
   class pfHitQueryResult
   {
   public:
       int     flags;
       int     whichseg;
       pfVec3  point;
       pfVec3  normal;
   };


protected:
   pfNode* mWorldNode;        // The world to collide with
};

#endif
