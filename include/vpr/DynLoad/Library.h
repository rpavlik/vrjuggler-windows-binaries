/****************** <VPR heading BEGIN do not edit this line> *****************
 *
 * VR Juggler Portable Runtime
 *
 * Original Authors:
 *   Allen Bierbaum, Patrick Hartling, Kevin Meinert, Carolina Cruz-Neira
 *
 ****************** <VPR heading END do not edit this line> ******************/

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

#ifndef _VPR_LIBRARY_H_
#define _VPR_LIBRARY_H_

/**
 * \file
 *
 * Include this file to get the full declaration of the platform-specific
 * class that is typedef'd to vpr::Library.
 *
 * @see vpr::LibraryDYLD, vpr::LibraryNSPR, vpr::LibraryUNIX
 */

#include <vpr/vprConfig.h>

#include <boost/shared_ptr.hpp>

#if defined(VPR_OS_Windows)
#include <vpr/md/WIN32/DynLoad/LibraryWin32.h>

namespace vpr
{
   typedef LibraryWin32 Library;
}

#elif defined(VPR_USE_NSPR)
#include <vpr/md/NSPR/DynLoad/LibraryNSPR.h>

namespace vpr
{
   typedef LibraryNSPR Library;
}

#elif defined(VPR_OS_Darwin) && VPR_OS_RELEASE_MAJOR < 8
#include <vpr/md/DARWIN/DynLoad/LibraryDYLD.h>

namespace vpr
{
   typedef LibraryDYLD Library;
}

#else
#include <vpr/md/POSIX/DynLoad/LibraryUNIX.h>

namespace vpr
{
   typedef LibraryUNIX Library;
}

#endif

namespace vpr
{
   typedef boost::shared_ptr<Library> LibraryPtr;
}

#endif /* _VPR_LIBRARY_H_ */
