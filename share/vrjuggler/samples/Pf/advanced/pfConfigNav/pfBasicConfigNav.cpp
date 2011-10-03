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

#include <cstdlib>

 // --- VR Juggler Stuff --- //
#include <vrj/Kernel/Kernel.h>
#include <pfBasicConfigNavApp.h>


int main(int argc, char* argv[])
{
   vrj::Kernel* kernel = vrj::Kernel::instance(); // Declare a new Kernel
   pfBasicConfigNavApp* application = new pfBasicConfigNavApp();  // Delcare an instance of my application

   // Load config information
   //kernel->loadConfigDefinitionFile(std::string("pfNavChunks.dsc"));

   kernel->init(argc, argv);

   for ( int i = 1; i < argc; i++ )
   {
      kernel->loadConfigFile(argv[i]);
   }

   kernel->start();
   kernel->setApplication( application );    // Set up the kernel
   kernel->waitForKernelStop();

   delete application;

   // Tell Performer to clean up its resources.  A side effect of this call
   // is that the standard library exit() function will be called, so nothing
   // after this call to pfExit() will be executed.
   pfExit();

   return EXIT_SUCCESS;
}
