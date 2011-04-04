// -*- Mode: C++; -*-
//                            Package   : omniORB
// valueFactoryManager.h      Created on: 2003/09/03
//                            Author    : Duncan Grisby (dgrisby)
//
//    Copyright (C) 2003-2004 Apasphere Ltd.
//
//    This file is part of the omniORB library
//
//    The omniORB library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU Library General Public
//    License as published by the Free Software Foundation; either
//    version 2 of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Library General Public License for more details.
//
//    You should have received a copy of the GNU Library General Public
//    License along with this library; if not, write to the Free
//    Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
//    02111-1307, USA
//
//
// Description:
//    Manager for ValueFactories
//

// $Log: valueFactoryManager.h,v $
// Revision 1.1.2.3  2009/05/06 16:16:10  dgrisby
// Update lots of copyright notices.
//
// Revision 1.1.2.2  2004/02/16 10:10:29  dgrisby
// More valuetype, including value boxes. C++ mapping updates.
//
// Revision 1.1.2.1  2003/09/26 16:12:53  dgrisby
// Start of valuetype support.
//

#include <omniORB4/CORBA.h>


class _omni_ValueFactoryManager {
public:
  
  static CORBA::ValueFactory
  register_factory(const char* id, CORBA::ULong hashval,
		   CORBA::ValueFactory factory, CORBA::Boolean internal);
  // Register factory, replacing existing one if there is one. Returns
  // the old one if there was one, zero otherwise.

  static void unregister_factory(const char* id, CORBA::ULong hashval);
  // Unregister, or raise BAD_PARAM on lookup failure.

  static CORBA::ValueFactory lookup(const char* id, CORBA::ULong hashval);
  // Lookup. Raises BAD_PARAM on failure.

  static CORBA::ValueBase* create_for_unmarshal(const char* id,
						CORBA::ULong hashval);
  // Lookup and call create_for_unmarshal on factory. Return zero if
  // no factory registered. Raise UNKNOWN_UserException if unknown
  // exception from factory.
};
