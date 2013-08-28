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

//-----------------------------------------------------
// Sample application for using the GL procedural API
//
// main.cpp
//-----------------------------------------------------

// --- Lib Stuff --- //
#include <vrj/vrjConfig.h>

#include <math.h>

#if defined(__APPLE__)
#  include <OpenGL/gl.h>
#else
#  include <GL/gl.h>
#endif

#include <iostream>
#include <iomanip>
#include <cstdlib>

#include <gmtl/Matrix.h>
#include <gmtl/Generate.h>
#include <gmtl/Vec.h>

#include <gadget/Type/PositionInterface.h>
#include <gadget/Type/DigitalInterface.h>

// --- Extensions for procedural apps --- //
#include <vrj/Draw/OpenGL/ProcApp.h>


// Callback methods
void init();
void preFrame();
void initGLState();
void bufferPreDraw();
void draw();
void drawCube();
void drawbox( GLdouble x0, GLdouble x1, GLdouble y0, GLdouble y1,
              GLdouble z0, GLdouble z1, GLenum type );


using namespace vrj;
using namespace vrj::opengl;
using namespace gmtl;

// Global variables //
gadget::PositionInterface  gWand;    /**< Positional interface for Wand position */
gadget::PositionInterface  gHead;    /**< Positional interface for Head position */
gadget::DigitalInterface   gButton0; /**< Digital interface for button 0 */
gadget::DigitalInterface   gButton1; /**< Digital interface for button 1 */

#define USE_BLOCKING_METHOD 1

int main(int argc, char* argv[])
{
   VRJConfigure(argc, argv);        // Configure the system

   init();                          // Initialize app vars

   // NOTE: The function pointers are passed using the address-of operator
   // so that this will compile with Visual C++.  With other compilers, this
   // is not necessary.
   VRJSetGLDrawMethod(&draw);                 // Set draw method
   VRJSetGLContextInitMethod(&initGLState);   // Set init for GL state
   VRJSetBufferPreDrawMethod(&bufferPreDraw); // Set method for clearing the buffers
   VRJSetPreFrameMethod(&preFrame);           // Set preframe callback

#ifdef USE_BLOCKING_METHOD
   VRJProcRunSystem();                       // Start app running, blocks until done
#else
#endif

   return EXIT_SUCCESS;
}

// --- Implementation methods ----- //


void init()
{
   std::cout << "---------- App:init() ---------------" << std::endl;
   // Initialize devices
   gWand.init("VJWand");
   gHead.init("VJHead");
   gButton0.init("VJButton0");
   gButton1.init("VJButton1");
}

void preFrame()
{
   if (gButton0->getData())
   {
      std::cout << "Button 0 pressed" << std::endl;
   }

   if (gButton1->getData())
   {
      std::cout << "Button 1 pressed" << std::endl;
   }
}


void drawCube()
{
   drawbox(-0.5, 0.5, -0.5, 0.5, -0.5, 0.5, GL_QUADS);
}


// Clears the viewport.  Put the call to glClear() in this
// method so that this application will work with configurations
// using two or more viewports per display window.
void bufferPreDraw()
{
   glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
   glClear(GL_COLOR_BUFFER_BIT);
}

//----------------------------------------------
//  Draw the scene.
//
// - Draws a box and a coordinate axis set on the box
// - Offset and rotate the box by a matrix that we create
//----------------------------------------------
void draw()
{
   glClear(GL_DEPTH_BUFFER_BIT);

   // --- Setup for drawing --- //
   glMatrixMode(GL_MODELVIEW);

   // -- Get Wand matrix --- //
   Matrix44f wand_matrix;
   wand_matrix = gWand->getData();

   // -- Create box offset matrix -- //
   Matrix44f box_offset;
   const EulerAngleXYZf euler_ang(Math::deg2Rad(-90.0f), Math::deg2Rad(0.0f),
                                  Math::deg2Rad(0.0f));
   box_offset = makeRot<Matrix44f>(euler_ang);
   setTrans(box_offset, Vec3f(0.0f, 1.0f, 0.0f));

   box_offset = wand_matrix;

   // --- Create a color for the wand --- //
   float wand_color[3];
   wand_color[0] = wand_color[1] = wand_color[2] = 0.7f;

   glPushMatrix();

      // --- Draw the box --- //
      glPushMatrix();
         glMultMatrixf(box_offset.mData);    // Push the wand offset matrix on the stack
         glColor3fv(wand_color);
         glScalef(0.5f, 0.5f, 0.5f);
         drawCube();
      glPopMatrix();

      // Draw a coordinate axis "on" the box
      glLineWidth(5.0f);
      glDisable(GL_LIGHTING);
      glPushMatrix();
         glMultMatrixf(box_offset.mData);    // Goto wand position

         Vec3f x_axis(7.0f,0.0f,0.0f);
         Vec3f y_axis(0.0f, 7.0f, 0.0f);
         Vec3f z_axis(0.0f, 0.0f, 7.0f);
         Vec3f origin(0.0f, 0.0f, 0.0f);

         glBegin(GL_LINES);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3fv(origin.mData);
            glVertex3fv(x_axis.mData);

            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3fv(origin.mData);
            glVertex3fv(y_axis.mData);

            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3fv(origin.mData);
            glVertex3fv(z_axis.mData);
         glEnd();
      glPopMatrix();
      glEnable(GL_LIGHTING);
   glPopMatrix();
}

void initGLState()
{
   GLfloat light0_ambient[]  = { 0.1f,  0.1f,  0.1f, 1.0f };
   GLfloat light0_diffuse[]  = { 0.8f,  0.8f,  0.8f, 1.0f };
   GLfloat light0_specular[] = { 1.0f,  1.0f,  1.0f, 1.0f };
   GLfloat light0_position[] = { 0.0f, 0.75f, 0.75f, 0.0f };

   GLfloat mat_ambient[]   = { 0.7f, 0.7f, 0.7f, 1.0f };
   GLfloat mat_diffuse[]   = { 1.0f, 0.5f, 0.8f, 1.0f };
   GLfloat mat_specular[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
   GLfloat mat_shininess[] = { 50.0f };
//   GLfloat mat_emission[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
   GLfloat no_mat[]        = { 0.0f, 0.0f, 0.0f, 1.0f };

   glLightfv(GL_LIGHT0, GL_AMBIENT,  light0_ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE,  light0_diffuse);
   glLightfv(GL_LIGHT0, GL_SPECULAR,  light0_specular);
   glLightfv(GL_LIGHT0, GL_POSITION,  light0_position);

   glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient );
   glMaterialfv( GL_FRONT,  GL_DIFFUSE, mat_diffuse );
   glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
   glMaterialfv( GL_FRONT,  GL_SHININESS, mat_shininess );
   glMaterialfv( GL_FRONT,  GL_EMISSION, no_mat);

   glEnable(GL_DEPTH_TEST);
   glEnable(GL_NORMALIZE);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_COLOR_MATERIAL);
   glShadeModel(GL_SMOOTH);
}

/// Utility function for drawing a cube
void drawbox(GLdouble x0, GLdouble x1, GLdouble y0, GLdouble y1,
             GLdouble z0, GLdouble z1, GLenum type)
{
   static GLdouble n[6][3] = {
      {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
      {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0}
   };
   static GLint faces[6][4] = {
      { 0, 1, 2, 3}, { 3, 2, 6, 7}, { 7, 6, 5, 4},
      { 4, 5, 1, 0}, { 5, 6, 2, 1}, { 7, 4, 0, 3}
   };
   GLdouble v[8][3], tmp;
   GLint i;

   if (x0 > x1)
   {
      tmp = x0; x0 = x1; x1 = tmp;
   }
   if (y0 > y1)
   {
      tmp = y0; y0 = y1; y1 = tmp;
   }
   if (z0 > z1)
   {
      tmp = z0; z0 = z1; z1 = tmp;
   }
   v[0][0] = v[1][0] = v[2][0] = v[3][0] = x0;
   v[4][0] = v[5][0] = v[6][0] = v[7][0] = x1;
   v[0][1] = v[1][1] = v[4][1] = v[5][1] = y0;
   v[2][1] = v[3][1] = v[6][1] = v[7][1] = y1;
   v[0][2] = v[3][2] = v[4][2] = v[7][2] = z0;
   v[1][2] = v[2][2] = v[5][2] = v[6][2] = z1;

   for (i = 0; i < 6; i++)
   {
      glBegin(type);
         glNormal3dv(&n[i][0]);
         glVertex3dv(&v[faces[i][0]][0]);
         glNormal3dv(&n[i][0]);
         glVertex3dv(&v[faces[i][1]][0]);
         glNormal3dv(&n[i][0]);
         glVertex3dv(&v[faces[i][2]][0]);
         glNormal3dv(&n[i][0]);
         glVertex3dv(&v[faces[i][3]][0]);
      glEnd();
   }
}

