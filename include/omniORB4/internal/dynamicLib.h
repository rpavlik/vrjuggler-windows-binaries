// -*- Mode: C++; -*-
//                            Package   : omniORB
// dynamicLib.h               Created on: 15/9/99
//                            Author    : David Riddoch (djr)
//
//    Copyright (C) 1996-1999 AT&T Laboratories Cambridge
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
//    Hook to allow orbcore to access dynamic library when linked.
//

/*
  $Log: dynamicLib.h,v $
  Revision 1.1.6.1  2003/03/23 21:03:50  dgrisby
  Start of omniORB 4.1.x development branch.

  Revision 1.1.4.3  2001/11/06 15:41:37  dpg1
  Reimplement Context. Remove CORBA::Status. Tidying up.

  Revision 1.1.4.2  2001/08/17 17:09:39  sll
  Use LinkHack.

  Revision 1.1.4.1  2001/04/18 17:18:17  sll
  Big checkin with the brand new internal APIs.
  These files were relocated and scoped with the omni namespace.

  Revision 1.2.2.2  2000/09/27 17:42:38  sll
  Updated to use the new cdrStream abstraction

  Revision 1.2.2.1  2000/07/17 10:35:39  sll
  Merged from omni3_develop the diff between omni3_0_0_pre3 and omni3_0_0.

  Revision 1.3  2000/07/13 15:26:03  dpg1
  Merge from omni3_develop for 3.0 release.

  Revision 1.1.2.2  2000/02/08 13:25:24  djr
  Added a couple of missing _core_attr.

  Revision 1.1.2.1  1999/09/22 14:26:25  djr
  Major rewrite of orbcore to support POA.

*/

#ifndef __DYNAMICLIB_H__
#define __DYNAMICLIB_H__


#if defined(_OMNIORB_LIBRARY)
# define _core_attr
#elif defined(_OMNIORB_DYNAMIC_LIBRARY)
# define _core_attr _OMNIORB_NTDLL_IMPORT
#else
# error "Neither _OMNIORB_LIBRARY nor _OMNIORB_DYNAMIC_LIBRARY defined"
#endif

class omniCallDescriptor;

OMNI_NAMESPACE_BEGIN(omni)


class omniDynamicLib {
public:

  // This points to the implementation of dynamic library functions
  // that the orbcore library should use.  If the dynamic library
  // is linked then the real functions are called.  Otherwise
  // stub versions are called which do nothing, or deal with the
  // error appropriately.
  static _core_attr omniDynamicLib* ops;

  // This points to the dynamic library's version of the functions
  // if the dynamic is linked, or is zero otherwise.
  static _core_attr omniDynamicLib* hook;

  ////////////////////////////////////////////////
  // Operations exported by the dynamic library //
  ////////////////////////////////////////////////

  // Initialisation
  void (*init)();
  void (*deinit)();

  // Local call call-back function for CORBA::Repository::lookup_id().
  // This is needed to support the server side of _get_interface(),
  // in the case that the interface repository is co-located!
  void (*lookup_id_lcfn)(omniCallDescriptor*, omniServant*);
};


#undef _core_attr

OMNI_NAMESPACE_END(omni)

#endif  // __DYNAMICLIB_H__
