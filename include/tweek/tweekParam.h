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

#ifndef _TWEEK_PARAM_H_
#define _TWEEK_PARAM_H_

/**
 * The 9-digit Tweek version integer. This form provides three digits for each
 * of the major, minor, and patch numbers with no leading zeros. The number
 * is a compile-time constant and is suitable (and intended) for use with
 * preprocessor integer comparisons.
 */
#define __TWEEK_version 1004000

/**
 * The Tweek version \em string. Instead of referencing this symbol, use
 * tweek::TWEEK_VERSION or tweek::getVersionString().
 */
#define __TWEEK_VERSION_STRING__ "v1.4.0-1 'Two-Face' (BOOST) trunk Feb 17, 2011 12:09:08"

/**
 * The individual TWEEK version numbers
 */
#define __TWEEK_MAJOR__ 1
#define __TWEEK_MINOR__ 4
#define __TWEEK_PATCH__ 0

#endif	/* _TWEEK_PARAM_H_ */
