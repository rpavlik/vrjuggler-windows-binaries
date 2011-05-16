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

#ifndef _VJ_PARAM_H_
#define _VJ_PARAM_H_

/**
 * The 9-digit VR Juggler version integer. This form provides three digits for
 * each of the major, minor, and patch numbers with no leading zeros. The
 * number is a compile-time constant and is suitable (and intended) for use
 * with preprocessor integer comparisons.
 */
#define __VJ_version 3000000

/**
 * The VR Juggler version \em string. Instead of referencing this symbol, use
 * vrj::VJ_VERSION or vrj::getVersionString().
 */
#define __VJ_VERSION_STRING__ "v3.0.0-1 'The Joker' (BOOST) trunk May 16, 2011 15:54:45"

/**
 * The individual VR Juggler version numbers.
 */
#define __VJ_MAJOR__ 3
#define __VJ_MINOR__ 0
#define __VJ_PATCH__ 0

#endif	/* _VJ_PARAM_H_ */
