// -*- Mode: C++; -*-
//                            Package   : omniORB
// corbaOrb.h                 Created on: 22/6/99
//                            Author    : David Riddoch (djr)
//
//    Copyright (C) 1996-1999 AT&T Research Cambridge
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
//    Implementation of the ORB interface.
//

/*
  $Log: corbaOrb.h,v $
  Revision 1.1.6.1  2003/03/23 21:03:51  dgrisby
  Start of omniORB 4.1.x development branch.

  Revision 1.1.4.5  2001/11/13 14:11:44  dpg1
  Tweaks for CORBA 2.5 compliance.

  Revision 1.1.4.4  2001/11/06 15:41:37  dpg1
  Reimplement Context. Remove CORBA::Status. Tidying up.

  Revision 1.1.4.3  2001/09/19 17:26:46  dpg1
  Full clean-up after orb->destroy().

  Revision 1.1.4.2  2001/08/01 10:08:20  dpg1
  Main thread policy.

  Revision 1.1.4.1  2001/04/18 17:18:18  sll
  Big checkin with the brand new internal APIs.
  These files were relocated and scoped with the omni namespace.

  Revision 1.2.2.1  2000/07/17 10:35:52  sll
  Merged from omni3_develop the diff between omni3_0_0_pre3 and omni3_0_0.

  Revision 1.3  2000/07/13 15:25:58  dpg1
  Merge from omni3_develop for 3.0 release.

  Revision 1.1.2.3  2000/02/04 18:11:02  djr
  Minor mods for IRIX (casting pointers to ulong instead of int).

  Revision 1.1.2.2  2000/01/20 11:51:34  djr
  (Most) Pseudo objects now used omni::poRcLock for ref counting.
  New assertion check OMNI_USER_CHECK.

  Revision 1.1.2.1  1999/09/22 14:26:46  djr
  Major rewrite of orbcore to support POA.

*/

#ifndef __CORBAORB_H__
#define __CORBAORB_H__


class omniOrbORB : public CORBA::ORB {
public:
  virtual ~omniOrbORB();
  omniOrbORB(int nil);

  virtual char* id();

  virtual char* object_to_string(CORBA::Object_ptr);
  virtual CORBA::Object_ptr string_to_object(const char*);

  virtual CORBA::ORB::ObjectIdList* list_initial_services();
  virtual CORBA::Object_ptr resolve_initial_references(const char* id);

  virtual CORBA::Boolean work_pending();
  virtual void perform_work();
  virtual void run();
  virtual void shutdown(CORBA::Boolean);
  virtual void destroy();

  virtual void register_initial_reference(const char* id,
					  CORBA::Object_ptr obj);

  virtual CORBA::Boolean _non_existent();
  virtual void* _ptrToObjRef(const char*);
  virtual void _NP_incrRefCount();
  virtual void _NP_decrRefCount();
  // Override CORBA::Object.

  void actual_shutdown();

  CORBA::Boolean run_timeout(unsigned long secs, unsigned long nanosecs);
  // Same as run(), but stopping when the absolute timeout is reached.
  // Returns true if shutdown, false if timed out. Note the potential
  // for race conditions if shutdown coincides with timeout: only
  // treat a timed-out indication as a hint.

  static CORBA::Boolean all_destroyed();
  // True if all ORBs have been destroyed (although there's only ever
  // one at present).
  //  NO CONCURRENCY CONTROL. This is intended to be used in the final
  //  clean-up by a static destructor.

private:
  void do_shutdown(CORBA::Boolean wait_for_completion);

  int pd_refCount;
  // Protected by <omni::poRcLock>.

  int pd_destroyed;
  int pd_shutdown;
  int pd_shutdown_in_progress;
  // All protected by <orb_lock>.
};


#endif  // __CORBAORB_H__
