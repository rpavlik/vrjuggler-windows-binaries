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

#include <iostream>
#include <cstdlib>
#include <sonixApp.h>

      // --- Lib Stuff --- //
#include <vrj/Kernel/Kernel.h>


int main(int argc, char* argv[])
{
   vrj::Kernel* kernel = vrj::Kernel::instance();           // Get the kernel
   vrjTest::sonixApp* application = new vrjTest::sonixApp(kernel);       // Instantiate an instance of the app

#if ! defined(VRJ_USE_COCOA)
   if (argc <= 1)
   {
      // display some usage info (holding the user by the hand stuff)
      //  this will probably go away once the kernel becomes separate
      //  and can load application plugins.
      std::cout << "\n\n" << std::flush;
      std::cout << "Usage: " << argv[0]
                << " vjconfigfile[0] vjconfigfile[1] ... vjconfigfile[n]\n"
                << std::flush;
      std::cout << "\n\n" << std::flush;
      std::exit(EXIT_FAILURE);
   }
#endif

   kernel->init(argc, argv);

   // Load any config files specified on the command line
   for ( int i = 1; i < argc; ++i )
   {
      kernel->loadConfigFile(argv[i]);
   }

   kernel->start();
   kernel->setApplication(application);
   kernel->waitForKernelStop();

   delete application;

   return EXIT_SUCCESS;
}
