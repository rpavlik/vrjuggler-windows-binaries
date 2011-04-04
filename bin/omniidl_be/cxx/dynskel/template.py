# -*- python -*-
#                           Package   : omniidl
# template.py               Created on: 2000/01/20
#			    Author1   : David Scott (djs)
#                           Author2   : Duncan Grisby (dgrisby)
#
#  Copyright (C) 2004-2007 Apasphere Ltd.
#  Copyright (C) 1999 AT&T Laboratories Cambridge
#
#  This file is part of omniidl.
#
#  omniidl is free software; you can redistribute it and/or modify it
#  under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#  General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
#  02111-1307, USA.
#
# Description:
#   
#   C++ templates for the DynSK.cc file

# $Id: template.py,v 1.5.2.8 2009/05/06 16:15:49 dgrisby Exp $
# $Log: template.py,v $
# Revision 1.5.2.8  2009/05/06 16:15:49  dgrisby
# Update lots of copyright notices.
#
# Revision 1.5.2.7  2007/09/19 14:16:07  dgrisby
# Avoid namespace clashes if IDL defines modules named CORBA.
#
# Revision 1.5.2.6  2004/10/13 17:58:23  dgrisby
# Abstract interfaces support; values support interfaces; value bug fixes.
#
# Revision 1.5.2.5  2004/07/31 23:44:55  dgrisby
# Properly handle null and void Anys; store omniObjRef pointer for
# objrefs in Anys.
#
# Revision 1.5.2.4  2004/07/23 10:29:58  dgrisby
# Completely new, much simpler Any implementation.
#
# Revision 1.5.2.3  2004/07/04 23:53:38  dgrisby
# More ValueType TypeCode and Any support.
#
# Revision 1.5.2.2  2004/04/02 13:26:22  dgrisby
# Start refactoring TypeCode to support value TypeCodes, start of
# abstract interfaces support.
#
# Revision 1.5.2.1  2003/03/23 21:02:39  dgrisby
# Start of omniORB 4.1.x development branch.
#
# Revision 1.3.2.12  2001/10/29 17:42:39  dpg1
# Support forward-declared structs/unions, ORB::create_recursive_tc().
#
# Revision 1.3.2.11  2001/08/29 13:41:04  dpg1
# jnw's fix for compilers with variable sizeof(enum)
#
# Revision 1.3.2.10  2001/08/22 13:29:48  dpg1
# Re-entrant Any marshalling.
#
# Revision 1.3.2.9  2001/08/15 10:29:53  dpg1
# Update DSI to use Current, inProcessIdentity.
#
# Revision 1.3.2.8  2001/06/13 17:26:41  sll
# Remove '+' from 'namespace' in the generated code.
#
# Revision 1.3.2.7  2001/06/08 17:12:15  dpg1
# Merge all the bug fixes from omni3_develop.
#
# Revision 1.3.2.6  2001/04/19 09:30:12  sll
#  Big checkin with the brand new internal APIs.
# Scoped where appropriate with the omni namespace.
#
# Revision 1.3.2.5  2001/03/13 10:32:08  dpg1
# Fixed point support.
#
# Revision 1.3.2.4  2000/11/20 14:43:24  sll
# Added support for wchar and wstring.
#
# Revision 1.3.2.3  2000/11/03 19:21:55  sll
# Use include omniORB4 in the generated code.
#
# Revision 1.3.2.2  2000/10/12 15:37:50  sll
# Updated from omni3_1_develop.
#
# Revision 1.4  2000/07/13 15:26:00  dpg1
# Merge from omni3_develop for 3.0 release.
#
# Revision 1.1.2.10  2000/07/04 12:57:52  djs
# Fixed Any insertion/extraction operators for unions and exceptions
#
# Revision 1.1.2.9  2000/06/30 09:33:05  djs
# Removed more possible nameclashes with user supplied names.
#
# Revision 1.1.2.8  2000/06/27 16:15:10  sll
# New classes: _CORBA_String_element, _CORBA_ObjRef_Element,
# _CORBA_ObjRef_tcDesc_arg to support assignment to an element of a
# sequence of string and a sequence of object reference.
#
# Revision 1.1.2.7  2000/06/26 16:23:27  djs
# Refactoring of configuration state mechanism.
#
# Revision 1.1.2.6  2000/06/05 13:03:05  djs
# Removed union member name clash (x & pd_x, pd__default, pd__d)
# Removed name clash when a sequence is called "pd_seq"
#
# Revision 1.1.2.5  2000/05/31 18:02:51  djs
# Better output indenting (and preprocessor directives now correctly output at
# the beginning of lines)
#
# Revision 1.1.2.4  2000/03/28 18:28:23  djs
# Sequence deletion function used unescaped name "data" which could clash with a
# user identifier
#   eg typedef sequence<char> data
# produces output that could not be parsed.
#
# Revision 1.1.2.3  2000/03/24 16:18:25  djs
# Added missing prefix to CORBA::Any extraction operators used for
#   typedef sequence<X> Y
# (typedef sequence<long> a; would not produce C++ which gcc could parse)
#
# Revision 1.1.2.2  2000/02/16 18:34:49  djs
# Fixed problem generating fragments in DynSK.cc file
#
# Revision 1.1.2.1  2000/02/15 15:36:25  djs
# djr's and jnw's "Super-Hacky Optimisation" patched and added
#
# Revision 1.1  2000/01/20 18:26:45  djs
# Moved large C++ output strings into an external template file
#

"""C++ templates for the DynSK.cc file"""

header_comment = """\
// This file is generated by @program@ - @library@. Do not edit.
"""

header = """\
#include "@basename@@hh@"

OMNI_USING_NAMESPACE(omni)

static const char* @prefix@_dyn_library_version = @library@_dyn;

static ::CORBA::TypeCode::_Tracker @prefix@_tcTrack(__FILE__);
"""

fragment_header = """\
static ::CORBA::TypeCode::_Tracker @prefix@_tcTrack(__FILE__);
"""


interface = """\
static void @private_prefix@_@guard_name@_marshal_fn(cdrStream& _s, void* _v)
{
  omniObjRef* _o = (omniObjRef*)_v;
  omniObjRef::_marshal(_o, _s);
}
static void @private_prefix@_@guard_name@_unmarshal_fn(cdrStream& _s, void*& _v)
{
  omniObjRef* _o = omniObjRef::_unMarshal(@fqname@::_PD_repoId, _s);
  _v = _o;
}
static void @private_prefix@_@guard_name@_destructor_fn(void* _v)
{
  omniObjRef* _o = (omniObjRef*)_v;
  if (_o)
    omni::releaseObjRef(_o);
}

void operator<<=(::CORBA::Any& _a, @fqname@_ptr _o)
{
  @fqname@_ptr _no = @fqname@::_duplicate(_o);
  _a.PR_insert(@tc_name@,
               @private_prefix@_@guard_name@_marshal_fn,
               @private_prefix@_@guard_name@_destructor_fn,
               _no->_PR_getobj());
}
void operator<<=(::CORBA::Any& _a, @fqname@_ptr* _op)
{
  _a.PR_insert(@tc_name@,
               @private_prefix@_@guard_name@_marshal_fn,
               @private_prefix@_@guard_name@_destructor_fn,
               (*_op)->_PR_getobj());
  *_op = @fqname@::_nil();
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, @fqname@_ptr& _o)
{
  void* _v;
  if (_a.PR_extract(@tc_name@,
                    @private_prefix@_@guard_name@_unmarshal_fn,
                    @private_prefix@_@guard_name@_marshal_fn,
                    @private_prefix@_@guard_name@_destructor_fn,
                    _v)) {
    omniObjRef* _r = (omniObjRef*)_v;
    if (_r)
      _o = (@fqname@_ptr)_r->_ptrToObjRef(@fqname@::_PD_repoId);
    else
      _o = @fqname@::_nil();
    return 1;
  }
  return 0;
}
"""

abstract_interface = """\
static void @private_prefix@_@guard_name@_marshal_fn(cdrStream& _s, void* _v)
{
  ::CORBA::AbstractBase* _a = (::CORBA::AbstractBase*)_v;
  if (_v) {
    ::CORBA::ValueBase* _b = _a->_NP_to_value();
    if (_b) {
      _s.marshalBoolean(0);
      ::CORBA::ValueBase::_NP_marshal(_b,_s);
      return;
    }
    ::CORBA::Object_ptr _o = _a->_NP_to_object();
    if (_o) {
      _s.marshalBoolean(1);
      omniObjRef::_marshal(_o->_PR_getobj(),_s);
      return;
    }
  }
  _s.marshalBoolean(0);
  ::CORBA::ValueBase::_NP_marshal(0,_s);
}
static void @private_prefix@_@guard_name@_unmarshal_fn(cdrStream& _s, void*& _v)
{
  ::CORBA::AbstractBase* _a;
  ::CORBA::Boolean _c = _s.unmarshalBoolean();
  if (_c) {
    omniObjRef* _o = omniObjRef::_unMarshal(@fqname@::_PD_repoId,_s);
    if (_o)
      _a = (@fqname@_ptr)_o->_ptrToObjRef(@fqname@::_PD_repoId);
    else
      _a = @fqname@::_nil();
  }
  else {
    ::CORBA::ValueBase* _b = ::CORBA::ValueBase::_NP_unmarshal(_s);
    if (_b)
      _a = (@fqname@_ptr)_b->_ptrToValue(@fqname@::_PD_repoId);
    else
      _a = 0;
  }
  _v = _a;
}
static void @private_prefix@_@guard_name@_destructor_fn(void* _v)
{
  ::CORBA::AbstractBase* _a = (::CORBA::AbstractBase*)_v;
  ::CORBA::release(_a);
}

void operator<<=(::CORBA::Any& _a, @fqname@_ptr _o)
{
  @fqname@_ptr _no = @fqname@::_duplicate(_o);
  _a.PR_insert(@tc_name@,
               @private_prefix@_@guard_name@_marshal_fn,
               @private_prefix@_@guard_name@_destructor_fn,
               (::CORBA::AbstractBase*)_no);
}
void operator<<=(::CORBA::Any& _a, @fqname@_ptr* _op)
{
  _a.PR_insert(@tc_name@,
               @private_prefix@_@guard_name@_marshal_fn,
               @private_prefix@_@guard_name@_destructor_fn,
               (::CORBA::AbstractBase*)*_op);
  *_op = @fqname@::_nil();
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, @fqname@_ptr& _o)
{
  void* _v;
  if (_a.PR_extract(@tc_name@,
                    @private_prefix@_@guard_name@_unmarshal_fn,
                    @private_prefix@_@guard_name@_marshal_fn,
                    @private_prefix@_@guard_name@_destructor_fn,
                    _v)) {
    ::CORBA::AbstractBase* _a = (::CORBA::AbstractBase*)_v;
    if (_a) {
      ::CORBA::ValueBase* _b = _a->_NP_to_value();
      if (_b) {
        _o = (@fqname@_ptr)_b->_ptrToValue(@fqname@::_PD_repoId);
        return 1;
      }
      ::CORBA::Object_ptr _p = _a->_NP_to_object();
      if (_p) {
        _o = (@fqname@_ptr)_p->_ptrToObjRef(@fqname@::_PD_repoId);
        return 1;
      }
    }
    _o = 0;
    return 1;
  }
  return 0;
}
"""


enum = """\
static void @private_prefix@_@guard_name@_marshal_fn(cdrStream& _s, void* _v)
{
  @fqname@* _p = (@fqname@*)_v;
  *_p >>= _s;
}
static void @private_prefix@_@guard_name@_unmarshal_fn(cdrStream& _s, void*& _v)
{
  @fqname@* _p = (@fqname@*)_v;
  *_p <<= _s;
}

void operator<<=(::CORBA::Any& _a, @fqname@ _s)
{
  _a.PR_insert(@private_prefix@_tc_@guard_name@,
               @private_prefix@_@guard_name@_marshal_fn,
               &_s);
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, @fqname@& _s)
{
  return _a.PR_extract(@private_prefix@_tc_@guard_name@,
                       @private_prefix@_@guard_name@_unmarshal_fn,
                       &_s);
}
"""

struct = """\
static void @private_prefix@_@guard_name@_marshal_fn(cdrStream& _s, void* _v)
{
  @fqname@* _p = (@fqname@*)_v;
  *_p >>= _s;
}
static void @private_prefix@_@guard_name@_unmarshal_fn(cdrStream& _s, void*& _v)
{
  @fqname@* _p = new @fqname@;
  *_p <<= _s;
  _v = _p;
}
static void @private_prefix@_@guard_name@_destructor_fn(void* _v)
{
  @fqname@* _p = (@fqname@*)_v;
  delete _p;
}

void operator<<=(::CORBA::Any& _a, const @fqname@& _s)
{
  @fqname@* _p = new @fqname@(_s);
  _a.PR_insert(@private_prefix@_tc_@guard_name@,
               @private_prefix@_@guard_name@_marshal_fn,
               @private_prefix@_@guard_name@_destructor_fn,
               _p);
}
void operator<<=(::CORBA::Any& _a, @fqname@* _sp)
{
  _a.PR_insert(@private_prefix@_tc_@guard_name@,
               @private_prefix@_@guard_name@_marshal_fn,
               @private_prefix@_@guard_name@_destructor_fn,
               _sp);
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, @fqname@*& _sp)
{
  return _a >>= (const @fqname@*&) _sp;
}
::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, const @fqname@*& _sp)
{
  void* _v;
  if (_a.PR_extract(@private_prefix@_tc_@guard_name@,
                    @private_prefix@_@guard_name@_unmarshal_fn,
                    @private_prefix@_@guard_name@_marshal_fn,
                    @private_prefix@_@guard_name@_destructor_fn,
                    _v)) {
    _sp = (const @fqname@*)_v;
    return 1;
  }
  return 0;
}
"""

union = struct

exception = """
static void @private_prefix@_@guard_name@_marshal_fn(cdrStream& _s, void* _v)
{
  const @fqname@* _p = (const @fqname@*)_v;
  *_p >>= _s;
}
static void @private_prefix@_@guard_name@_unmarshal_fn(cdrStream& _s, void*& _v)
{
  @fqname@* _p = new @fqname@;
  *_p <<= _s;
  _v = _p;
}
static void @private_prefix@_@guard_name@_destructor_fn(void* _v)
{
  @fqname@* _p = (@fqname@*)_v;
  delete _p;
}

void operator<<=(::CORBA::Any& _a, const @fqname@& _s)
{
  @fqname@* _p = new @fqname@(_s);
  _a.PR_insert(@private_prefix@_tc_@guard_name@,
               @private_prefix@_@guard_name@_marshal_fn,
               @private_prefix@_@guard_name@_destructor_fn,
               _p);
}
void operator<<=(::CORBA::Any& _a, const @fqname@* _sp)
{
  _a.PR_insert(@private_prefix@_tc_@guard_name@,
               @private_prefix@_@guard_name@_marshal_fn,
               @private_prefix@_@guard_name@_destructor_fn,
               (@fqname@*)_sp);
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, const @fqname@*& _sp)
{
  void* _v;
  if (_a.PR_extract(@private_prefix@_tc_@guard_name@,
                    @private_prefix@_@guard_name@_unmarshal_fn,
                    @private_prefix@_@guard_name@_marshal_fn,
                    @private_prefix@_@guard_name@_destructor_fn,
                    _v)) {
    _sp = (const @fqname@*)_v;
    return 1;
  }
  return 0;
}

static void @private_prefix@_insertToAny__c@guard_name@(::CORBA::Any& _a, const ::CORBA::Exception& _e) {
  const @fqname@ & _ex = (const @fqname@ &) _e;
  operator<<=(_a,_ex);
}

static void @private_prefix@_insertToAnyNCP__c@guard_name@ (::CORBA::Any& _a, const ::CORBA::Exception* _e) {
  const @fqname@* _ex = (const @fqname@*) _e;
  operator<<=(_a,_ex);
}

class @private_prefix@_insertToAny_Singleton__c@guard_name@ {
public:
  @private_prefix@_insertToAny_Singleton__c@guard_name@() {
    @fqname@::insertToAnyFn = @private_prefix@_insertToAny__c@guard_name@;
    @fqname@::insertToAnyFnNCP = @private_prefix@_insertToAnyNCP__c@guard_name@;
  }
};
static @private_prefix@_insertToAny_Singleton__c@guard_name@ @private_prefix@_insertToAny_Singleton__c@guard_name@_;
"""


value = """\
static void @private_prefix@_@guard_name@_marshal_fn(cdrStream& _s, void* _v)
{
  @fqname@* _p = (@fqname@*)_v;
  @fqname@::_NP_marshal(_p, _s);
}
static void @private_prefix@_@guard_name@_unmarshal_fn(cdrStream& _s, void*& _v)
{
  @fqname@* _p = @fqname@::_NP_unmarshal(_s);
  _v = _p;
}
static void @private_prefix@_@guard_name@_destructor_fn(void* _v)
{
  @fqname@* _p = (@fqname@*)_v;
  ::CORBA::remove_ref(_p);
}

void operator<<=(::CORBA::Any& _a, @fqname@* _v)
{
  ::CORBA::add_ref(_v);
  _a.PR_insert(@private_prefix@_tc_@guard_name@,
               @private_prefix@_@guard_name@_marshal_fn,
               @private_prefix@_@guard_name@_destructor_fn,
               _v);
}
void operator<<=(::CORBA::Any& _a, @fqname@** _vp)
{
  _a.PR_insert(@private_prefix@_tc_@guard_name@,
               @private_prefix@_@guard_name@_marshal_fn,
               @private_prefix@_@guard_name@_destructor_fn,
               *_vp);
  *_vp = 0;
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, @fqname@*& _sp)
{
  void* _v;
  if (_a.PR_extract(@private_prefix@_tc_@guard_name@,
                    @private_prefix@_@guard_name@_unmarshal_fn,
                    @private_prefix@_@guard_name@_marshal_fn,
                    @private_prefix@_@guard_name@_destructor_fn,
                    _v)) {
    _sp = (@fqname@*)_v;
    return 1;
  }
  return 0;
}
"""

valuebox = value



array = """\
static void @private_prefix@_@guard_name@_marshal_fn(cdrStream& _s, void* _v)
{
  @fqname@_slice* _a = (@fqname@_slice*)_v;
  @marshal@
}
static void @private_prefix@_@guard_name@_unmarshal_fn(cdrStream& _s, void*& _v)
{
  @fqname@_slice* _a = @fqname@_alloc();
  @unmarshal@
  _v = _a;
}
static void @private_prefix@_@guard_name@_destructor_fn(void* _v)
{
  @fqname@_slice* _a = (@fqname@_slice*)_v;
  @fqname@_free(_a);
}

void operator<<=(::CORBA::Any& _a, const @fqname@_forany& _s)
{
  @fqname@_slice* _v;
  if (!_s.NP_nocopy())
    _v = @fqname@_dup(_s);
  else
    _v = _s.NP_getSlice();

  _a.PR_insert(@private_prefix@_tc_@guard_name@,
               @private_prefix@_@guard_name@_marshal_fn,
               @private_prefix@_@guard_name@_destructor_fn,
               _v);
}
::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, @fqname@_forany& _s)
{
  void* _v;
  if (_a.PR_extract(@private_prefix@_tc_@guard_name@,
                    @private_prefix@_@guard_name@_unmarshal_fn,
                    @private_prefix@_@guard_name@_marshal_fn,
                    @private_prefix@_@guard_name@_destructor_fn,
                    _v)) {
    _s = (@fqname@_slice*)_v;
    return 1;
  }
  return 0;
}
"""

sequence = """\
static void @private_prefix@_@guard_name@_marshal_fn(cdrStream& _s, void* _v)
{
  @fqname@* _p = (@fqname@*)_v;
  *_p >>= _s;
}
static void @private_prefix@_@guard_name@_unmarshal_fn(cdrStream& _s, void*& _v)
{
  @fqname@* _p = new @fqname@;
  *_p <<= _s;
  _v = _p;
}
static void @private_prefix@_@guard_name@_destructor_fn(void* _v)
{
  @fqname@* _p = (@fqname@*)_v;
  delete _p;
}

void operator<<=(::CORBA::Any& _a, const @fqname@& _s)
{
  @fqname@* _p = new @fqname@(_s);
  _a.PR_insert(@private_prefix@_tc_@guard_name@,
               @private_prefix@_@guard_name@_marshal_fn,
               @private_prefix@_@guard_name@_destructor_fn,
               _p);
}
void operator<<=(::CORBA::Any& _a, @fqname@* _sp)
{
  _a.PR_insert(@private_prefix@_tc_@guard_name@,
               @private_prefix@_@guard_name@_marshal_fn,
               @private_prefix@_@guard_name@_destructor_fn,
               _sp);
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, @fqname@*& _sp)
{
  return _a >>= (const @fqname@*&) _sp;
}
::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, const @fqname@*& _sp)
{
  void* _v;
  if (_a.PR_extract(@private_prefix@_tc_@guard_name@,
                    @private_prefix@_@guard_name@_unmarshal_fn,
                    @private_prefix@_@guard_name@_marshal_fn,
                    @private_prefix@_@guard_name@_destructor_fn,
                    _v)) {
    _sp = (const @fqname@*)_v;
    return 1;
  }
  return 0;
}
"""



## TypeCode generation
##
tc_string = """\
#if !defined(___tc_string_@n@_value__) && !defined(DISABLE_Unnamed_Bounded_String_TC)
#define ___tc_string_@n@_value__
const ::CORBA::TypeCode_ptr _tc_string_@n@ = ::CORBA::TypeCode::PR_string_tc(@n@, &@prefix@_tcTrack);
#endif
"""

tc_wstring = """\
#if !defined(___tc_wstring_@n@_value__) && !defined(DISABLE_Unnamed_Bounded_WString_TC)
#define ___tc_wstring_@n@_value__
const ::CORBA::TypeCode_ptr _tc_wstring_@n@ = ::CORBA::TypeCode::PR_wstring_tc(@n@, &@prefix@_tcTrack);
#endif
"""

external_linkage = """\
#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage otherwise.
@open_namespace@
  const ::CORBA::TypeCode_ptr @tc_unscoped_name@ = @mangled_name@;
@close_namespace@
#else
const ::CORBA::TypeCode_ptr @tc_name@ = @mangled_name@;
#endif
"""
