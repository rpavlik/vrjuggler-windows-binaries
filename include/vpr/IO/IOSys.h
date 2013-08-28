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

#ifndef _VPR_IOSYS_FAKE_H_
#define _VPR_IOSYS_FAKE_H_

/**
 * \file
 *
 * Include this file to get the full declaration of the platform-specific class
 * that is typedef'd to vpr::IOSys.
 */

#include <vpr/vprConfig.h>

// determine which implementation of vpr::IOSys to include.
#if VPR_IO_DOMAIN_INCLUDE == VPR_DOMAIN_NSPR
#   include <vpr/md/NSPR/IO/IOSysNSPR.h>
#elif VPR_IO_DOMAIN_INCLUDE == VPR_DOMAIN_POSIX
#   include <vpr/md/POSIX/IO/IOSysUnix.h>
#elif VPR_IO_DOMAIN_INCLUDE == VPR_DOMAIN_SIMULATOR
#   include <vpr/md/SIM/IO/IOSysSIM.h>
#elif VPR_IO_DOMAIN_INCLUDE == VPR_DOMAIN_BOOST
#   include <vpr/md/BOOST/IO/IOSysBOOST.h>
#endif

#endif   /* _VPR_IOSYS_FAKE_H_ */
