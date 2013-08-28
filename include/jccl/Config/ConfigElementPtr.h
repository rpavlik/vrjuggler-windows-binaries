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

#ifndef _JCCL_CONFIG_ELEMENT_PTR_H_
#define _JCCL_CONFIG_ELEMENT_PTR_H_

#include <boost/smart_ptr.hpp>

/**
 * \file
 *
 * Include this file to get a forward declaration of the pointer type
 * jccl::ConfigElementPtr.  To get the full declaration of jccl::ConfigElement
 * jccl/Config/ConfigElement.h must be included, too.
 */

namespace jccl
{
   class ConfigElement;
   typedef boost::shared_ptr<ConfigElement> ConfigElementPtr;
}

#endif
