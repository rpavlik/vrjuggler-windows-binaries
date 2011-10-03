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

#ifndef _CLUSTER_CLUSTER_EXCEPTION_H_
#define _CLUSTER_CLUSTER_EXCEPTION_H_

#include <gadget/gadgetConfig.h>
#include <vpr/Util/Exception.h>

namespace cluster
{

/** \class ClusterException ClusterException.h cluster/ClusterException.h 
 *
 * Basic exception that may be thrown by the ClusterNetwork or any of the
 * Plugins.
 */
class GADGET_CLASS_API ClusterException : public vpr::Exception
{
public:
   ClusterException(const std::string& msg,
                    const std::string& location = "")
      throw ();

   virtual ~ClusterException() throw();

   virtual std::string getExceptionName() const
   {
      return "cluster::ClusterException";
   }
};

} // end namespace gadget

#endif
