// -*- Mode: C++; -*-
//                            Package   : omniORB2
// initialiser.h              Created on: 16/8/99
//                            Author    : Sai-Lai Lo (sll)
//
//    Copyright (C) 1999 AT&T Research Cambridge
//
//    This file is part of the omniORB library.
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
//

/*
  $Log: initialiser.h,v $
  Revision 1.1.6.1  2003/03/23 21:03:46  dgrisby
  Start of omniORB 4.1.x development branch.

  Revision 1.1.4.2  2001/06/11 17:57:14  sll
   External libraries can now hook-up to the orb initialiser list irrespective
   of whether the global variables in the external libraries are initialised
   before the core library.

  Revision 1.1.4.1  2001/04/18 17:18:16  sll
  Big checkin with the brand new internal APIs.
  These files were relocated and scoped with the omni namespace.

  Revision 1.2.2.1  2000/07/17 10:35:40  sll
  Merged from omni3_develop the diff between omni3_0_0_pre3 and omni3_0_0.

  Revision 1.3  2000/07/13 15:26:03  dpg1
  Merge from omni3_develop for 3.0 release.

  Revision 1.1.2.2  2000/06/02 14:17:05  dpg1
  Add static install() method to initialiser so extra initialisers /
  deinitialisers can be added at run time (needed by omniORBpy).

  Revision 1.1.2.1  1999/09/24 15:01:32  djr
  Added module initialisers, and sll's new scavenger implementation.

*/

#ifndef __INITIALISER_H__
#define __INITIALISER_H__

OMNI_NAMESPACE_BEGIN(omni)

// Singletons created per compilation unit. The attach method is called
// when the ORB is initialised. The detach method is called when the ORB
// is destroyed.
class omniInitialiser {
public:
  virtual void attach() = 0;
  virtual void detach() = 0;

  static void install(omniInitialiser* init);
  // Hook to allow modules to add initialisers dynamically. These
  // initialisers are run after all statically declared ones. Not
  // thread safe.

  class init_t {
    static int count;
  public:
    init_t(void);
  };
};

OMNI_NAMESPACE_END(omni)

#endif  // __INITIALISER_H__
