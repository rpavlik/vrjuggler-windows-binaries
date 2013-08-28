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
#ifndef _GADGET_EVENT_FACTORY_H_
#define _GADGET_EVENT_FACTORY_H_

#include <gadget/gadgetConfig.h>
#include <vpr/Util/Factory.h>
#include <vpr/Util/Singleton.h>

/** Register a creator for the Event classes
 *
 * Ex: GADGET_REGISTER_EVENT_CREATOR( EventType, event_id )
 */
#define GADGET_REGISTER_EVENT_CREATOR( EventType, id ) \
class EventType; \
const bool reg_ctr_ ## id = gadget::EventFactory::instance()->registerCreator( id, \
                                             vpr::CreateProduct<Event, EventType>);

namespace gadget
{

/** \class EventFactory EventFactory.h gadget/Type/KeyboardMouse/EventFactory.h
 *
 * Event factory.
 */
class EventFactory
   : public vpr::Factory<Event, EventType>
   , public vpr::Singleton<EventFactory>
{};

} // End of gadget namespace

#endif


