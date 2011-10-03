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

#include <vrj/Display/DisplayManager.h>
#include <vrj/Display/Display.h>
#include <vrj/Display/Projection.h>
#include <vrj/Draw/OpenGL/DrawManager.h>

#include <WallTestHelpers.h>
#include <StereoEyeTestMode.h>


void StereoEyeTestMode::draw(WallTest*)
{
   vrj::DisplayManager* displayManager =
      vrj::opengl::DrawManager::instance()->getDisplayManager();
   std::vector<vrj::DisplayPtr> disps = displayManager->getAllDisplays();

   for ( unsigned int i = 0; i < disps.size(); ++i )
   {
      for ( unsigned int v = 0; v < disps[i]->getNumViewports(); ++v )
      {
         vrj::ViewportPtr viewport = disps[i]->getViewport(v);

         if ( viewport->isSurface())
         {
            // Get a pointer to the surface
            vrj::SurfaceViewportPtr surface =
               boost::dynamic_pointer_cast<vrj::SurfaceViewport>(viewport);
            vprASSERT(surface != NULL);

            gmtl::Matrix44f rotate;
            gmtl::Vec3f center;
            float wall_width, wall_height;

            calcSurfaceParameters(surface, rotate, center, wall_width,
                                  wall_height);

            glPushMatrix();
            {
               // Translate to center of wall and rotate to looking down wall
               glTranslatef(center[0],center[1],center[2]);
               glMultMatrixf(rotate.getData());

               drawCubeOrTriangle();
            }
            glPopMatrix();
         }
      }
   }
}

void StereoEyeTestMode::drawCubeOrTriangle()
{
   vrj::ProjectionPtr currentProjection =
      vrj::opengl::DrawManager::instance()->currentUserData()->getProjection();
   int currentEye = currentProjection->getEye();

   glPushMatrix();

   if ( currentEye == vrj::Projection::LEFT )
   {
      mText->drawTextBlock("Left Eye", 0.1f, 0.1f);
      glTranslatef(-1.5f, 0.0f, 0.0f);
      glColor3f(0.0f, 1.0f, 0.0f);
      drawCube();
   }
   else
   {
      mText->drawTextBlock("Right Eye", 0.7f, 0.1f);
      glTranslatef(1.5f, 0.0f, 0.0f);
      glColor3f(1.0f, 0.0f, 0.0f);
      drawPyramid();
   }

   glPopMatrix();
}
