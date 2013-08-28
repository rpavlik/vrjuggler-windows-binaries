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

#ifndef _VPR_SYSTEM_H_
#define _VPR_SYSTEM_H_

/**
 * \file
 *
 * Include this file to get the platform-specific declaration of the class
 * that is typedef'd to vpr::System.
 */

#include <vpr/vprConfig.h>

// determine which implementation of vpr::System to include.
#if VPR_THREAD_DOMAIN_INCLUDE == VPR_DOMAIN_NSPR
#  include <vpr/md/NSPR/SystemNSPR.h>
#elif VPR_THREAD_DOMAIN_INCLUDE == VPR_DOMAIN_WIN32
#  include <vpr/md/WIN32/SystemWin32.h>
#elif VPR_THREAD_DOMAIN_INCLUDE == VPR_DOMAIN_POSIX
#  include <vpr/md/POSIX/SystemPosix.h>
#endif

#endif /* _VPR_SYSTEM_FAKE_H_ */
