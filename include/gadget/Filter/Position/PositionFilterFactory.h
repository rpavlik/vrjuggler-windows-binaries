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

#ifndef _GADGET_POSITION_FILTER_FACTORY_H_
#define _GADGET_POSITION_FILTER_FACTORY_H_

#include <gadget/gadgetConfig.h>
#include <vpr/Util/Factory.h>
#include <vpr/Util/Singleton.h>

/** Register a creator for the PositionFilter classes.
 * @pre Requires that the method std::string getElementType() be defined for
 *      class FilterClass.
 *
 * Ex: GADGET_REGISTER_POSFILTER_CREATOR( PosXformFilter )
*/
#define GADGET_REGISTER_POSFILTER_CREATOR( FilterType ) \
class FilterType; \
const bool reg_ctr_ ## FilterType = gadget::PositionFilterFactory::instance()->registerCreator( FilterType::getElementType(), \
                                             vpr::CreateProduct<PositionFilter, FilterType>);

namespace gadget
{

/** \class PositionFilterFactory PositionFilterFactory.h gadget/Filter/Position/PositionFilterFactory.h
 *
 * Position filter factory singleton.
 */
class GADGET_CLASS_API PositionFilterFactory :
   public vpr::Factory<PositionFilter, std::string> 
{
   vprSingletonHeader(PositionFilterFactory);
};

} // End of gadget namespace

#endif

