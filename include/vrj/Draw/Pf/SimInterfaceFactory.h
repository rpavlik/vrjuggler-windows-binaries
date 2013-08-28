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

#ifndef _VRJ_PF_SIM_INTERFACE_FACTORY_H_
#define _VRJ_PF_SIM_INTERFACE_FACTORY_H_

#include <vrj/Draw/Pf/Config.h>
#include <string>
#include <vpr/Util/Factory.h>
#include <vpr/Util/Singleton.h>
#include <vrj/Draw/DrawSimInterface.h>

/**
 * Registers a creator for the DrawSimInterface implementation classes.
 *
 * @pre Requires that the method std::string getElementType() be defined for
 *      class SimIfType.
 *
 * Ex: VRJ_REGISTER_SIM_INTERFACE_CREATOR(simulators::PySim)
 */
#define VRJ_REGISTER_PF_SIM_INTERFACE_CREATOR(SimIfType) \
class SimIfType; \
const bool reg_ctr_ ## SimIfType = \
   vrj::pf::SimInterfaceFactory::instance()-> \
      registerCreator(SimIfType::getElementType(), \
                      vpr::CreateProduct<vrj::DrawSimInterface, SimIfType>);

namespace vrj
{

namespace pf
{

/** \class vrj::pf::SimInterfaceFactory SimInterfaceFactory.h vrj/Draw/Pf/SimInterfaceFactory.h
 *
 * Simulator renderer factory.
 *
 * @note This class was renamed from vrj::PfSimInterfaceFactory in VR Juggler
 *       2.3.11.
 */
class VJ_PF_CLASS_API SimInterfaceFactory :
   public vpr::Factory<DrawSimInterface, std::string>
{
public:
   vprSingletonHeader(SimInterfaceFactory);
};

} // End of pf namespace

} // End of vrj namespace


#endif /* _VRJ_DRAW_SIM_INTERFACE_FACTORY_H_ */
