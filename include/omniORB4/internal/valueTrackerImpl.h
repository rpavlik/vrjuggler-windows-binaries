// -*- Mode: C++; -*-
//                            Package   : omniORB
// valueTrackerImpl.h         Created on: 2003/08/05
//                            Author    : Duncan Grisby (dgrisby)
//
//    Copyright (C) 2003-2005 Apasphere Ltd.
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
//    Value tracker implementation classes for C++
//

// $Log: valueTrackerImpl.h,v $
// Revision 1.1.2.6  2009/05/06 16:16:00  dgrisby
// Update lots of copyright notices.
//
// Revision 1.1.2.5  2005/01/17 14:44:46  dgrisby
// Surprisingly few changes to compile on Windows.
//
// Revision 1.1.2.4  2004/07/04 23:53:35  dgrisby
// More ValueType TypeCode and Any support.
//
// Revision 1.1.2.3  2004/04/02 13:26:24  dgrisby
// Start refactoring TypeCode to support value TypeCodes, start of
// abstract interfaces support.
//
// Revision 1.1.2.2  2003/11/06 11:56:55  dgrisby
// Yet more valuetype. Plain valuetype and abstract valuetype are now working.
//
// Revision 1.1.2.1  2003/09/26 16:12:54  dgrisby
// Start of valuetype support.
//

#ifndef __VALUETRACKERIMPL_H__
#define __VALUETRACKERIMPL_H__

#include <omniORB4/CORBA.h>

#ifdef _dyn_attr
# error "A local CPP macro _dyn_attr has already been defined."
#endif

#if defined(_OMNIORB_DYNAMIC_LIBRARY)
#  define _dyn_attr
#else
#  define _dyn_attr _OMNIORB_NTDLL_IMPORT
#endif


OMNI_NAMESPACE_BEGIN(omni)

struct OutputTableEntry;
struct InputTableEntry;


class OutputValueTracker : public ValueIndirectionTracker {
public:
  OutputValueTracker();
  virtual ~OutputValueTracker();

  inline CORBA::Boolean valid()
  {
    return pd_magic == PD_MAGIC;
  }

  CORBA::Long addValue(const CORBA::ValueBase* val,
		       CORBA::Long             current);
  // Look to see if the value has been marshalled before. If so,
  // return its offset; if not, add it to the table and return -1.

  CORBA::Long addRepoId(const char*  repoId,
			CORBA::ULong hashval,
			CORBA::Long  current);
  // As above, for a single repository id.

  CORBA::Long addRepoIds(const _omni_ValueIds* repoIds,
			 CORBA::Long           current);
  // As above, for a list of repository ids.

  inline void startTruncatable() {
    pd_in_truncatable++;
  }
  inline void endTruncatable() {
    pd_in_truncatable--;
  }
  inline CORBA::Boolean inTruncatable() {
    return (pd_in_truncatable > 0);
  }
  // Inside a truncatable value, repoIds of nested values must always
  // be sent, in case the receiver truncates the first instance of the
  // nested value away, but later receives an indirection to it.

private:
  static _dyn_attr const CORBA::ULong PD_MAGIC; // "C+OV"
  CORBA::ULong pd_magic;

  CORBA::ULong       pd_in_truncatable;
  OutputTableEntry** pd_table;
  CORBA::ULong       pd_table_size;
};

class InputValueTracker : public ValueIndirectionTracker {
public:
  InputValueTracker();
  virtual ~InputValueTracker();

  inline CORBA::Boolean valid()
  {
    return pd_magic == PD_MAGIC;
  }

  void addValue(CORBA::ValueBase* val, CORBA::Long current);
  // Add record of unmarshalled value. Takes ownership of the reference.

  void addRepoId(char* repoId, CORBA::Long current);
  // Add record of unmarshalled repoId. Takes ownership of the string.

  void addRepoIds(_omni_ValueIds* repoIds, CORBA::Long current);
  // Add record of list of unmarshalled repoIds. Takes ownership of
  // the list structure. The strings stored in the list are _not_
  // owned, since they are separately registered with addRepoId.

  CORBA::ValueBase* lookupValue(CORBA::Long pos,
				CORBA::Long current,
				CORBA::CompletionStatus comp);
  // Lookup value at specified position, from the current position.
  // Throw MARSHAL_InvalidIndirection if not found. Caller must
  // add_ref if it needs to keep the value.

  const char* lookupRepoId(CORBA::Long pos,
			   CORBA::Long current,
			   CORBA::CompletionStatus comp);
  // As above for single repoId.

  const _omni_ValueIds* lookupRepoIds(CORBA::Long pos,
				      CORBA::Long current,
				      CORBA::CompletionStatus comp);
  // As above for list of repoIds.

private:
  static _dyn_attr const CORBA::ULong PD_MAGIC; // "C+IV"
  CORBA::ULong pd_magic;

  CORBA::ULong      pd_in_truncatable;
  InputTableEntry** pd_table;
  CORBA::ULong      pd_table_size;
};


OMNI_NAMESPACE_END(omni)


#undef _dyn_attr

#endif // __VALUETRACKERIMPL_H__
