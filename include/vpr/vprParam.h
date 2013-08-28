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

#ifndef _VPR_PARAM_H_
#define _VPR_PARAM_H_

/**
 * The 9-digit VPR version integer. This form provides three digits for each of
 * the major, minor, and patch numbers with no leading zeros. The number is a
 * compile-time constant and is suitable (and intended) for use with
 * preprocessor integer comparisons.
 */
#define __VPR_version 2002001

/**
 * The VPR version \em string. Instead of referencing this symbol, use
 * vpr::VPR_VERSION or vpr::getVersionString().
 */
#define __VPR_VERSION_STRING__ "2.2.1"

/**
 * The individual VPR version numbers.
 */
#define __VPR_MAJOR__ 2
#define __VPR_MINOR__ 2
#define __VPR_PATCH__ 1

#endif	/* _VPR_PARAM_H_ */
