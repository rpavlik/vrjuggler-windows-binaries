# -*- python -*-
#                           Package   : omniidl
# template.py               Created on: 2000/01/19
#			    Author    : David Scott (djs)
#
#    Copyright (C) 2003-2009 Apasphere Ltd
#    Copyright (C) 1999 AT&T Laboratories Cambridge
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
#   C++ templates for the SK.cc file

# $Id: template.py,v 1.6.2.15 2009/05/06 16:15:32 dgrisby Exp $
# $Log: template.py,v $
# Revision 1.6.2.15  2009/05/06 16:15:32  dgrisby
# Update lots of copyright notices.
#
# Revision 1.6.2.14  2009/01/07 12:30:33  dgrisby
# Some compilers do not like empty static arrays.
#
# Revision 1.6.2.13  2008/10/28 15:33:42  dgrisby
# Undeclared user exceptions not caught in local calls.
#
# Revision 1.6.2.12  2007/09/19 14:16:07  dgrisby
# Avoid namespace clashes if IDL defines modules named CORBA.
#
# Revision 1.6.2.11  2007/02/26 15:51:14  dgrisby
# Suppress cd parameter when it is definitely unused, to avoid compiler
# warnings.
#
# Revision 1.6.2.10  2005/11/14 11:02:16  dgrisby
# Local interface fixes.
#
# Revision 1.6.2.9  2005/11/09 12:22:17  dgrisby
# Local interfaces support.
#
# Revision 1.6.2.8  2005/09/19 15:36:35  dgrisby
# Refcount shortcut now throws INV_OBJREF when the servant is
# deactivated, rather than deactivating the shortcut, which could lead
# to a race condition.
#
# Revision 1.6.2.7  2005/09/05 17:22:09  dgrisby
# Reference counted local call shortcut.
#
# Revision 1.6.2.6  2005/03/30 23:36:11  dgrisby
# Another merge from omni4_0_develop.
#
# Revision 1.6.2.5  2005/01/06 23:10:10  dgrisby
# Big merge from omni4_0_develop.
#
# Revision 1.6.2.4  2005/01/06 16:35:18  dgrisby
# Narrowing for abstract interfaces.
#
# Revision 1.6.2.3  2004/10/13 17:58:25  dgrisby
# Abstract interfaces support; values support interfaces; value bug fixes.
#
# Revision 1.6.2.2  2003/11/06 11:56:56  dgrisby
# Yet more valuetype. Plain valuetype and abstract valuetype are now working.
#
# Revision 1.6.2.1  2003/03/23 21:02:34  dgrisby
# Start of omniORB 4.1.x development branch.
#
# Revision 1.3.2.23  2002/01/16 11:31:58  dpg1
# Race condition in use of registerNilCorbaObject/registerTrackedObject.
# (Reported by Teemu Torma).
#
# Revision 1.3.2.22  2001/11/27 14:35:09  dpg1
# Context, DII fixes.
#
# Revision 1.3.2.21  2001/11/13 14:14:45  dpg1
# Bug when no catch by base class.
#
# Revision 1.3.2.20  2001/11/12 13:46:07  dpg1
# _unchecked_narrow, improved _narrow.
#
# Revision 1.3.2.19  2001/11/09 09:56:11  dpg1
# Missed a file in yesterday's checkin.
#
# Revision 1.3.2.18  2001/11/07 15:45:53  dpg1
# Faster _ptrToInterface/_ptrToObjRef in common cases.
#
# Revision 1.3.2.17  2001/11/06 15:41:37  dpg1
# Reimplement Context. Remove CORBA::Status. Tidying up.
#
# Revision 1.3.2.16  2001/10/29 17:42:42  dpg1
# Support forward-declared structs/unions, ORB::create_recursive_tc().
#
# Revision 1.3.2.15  2001/10/18 12:45:29  dpg1
# IDL compiler tweaks.
#
# Revision 1.3.2.14  2001/10/17 16:44:06  dpg1
# Update DynAny to CORBA 2.5 spec, const Any exception extraction.
#
# Revision 1.3.2.13  2001/09/19 17:26:47  dpg1
# Full clean-up after orb->destroy().
#
# Revision 1.3.2.12  2001/08/15 10:26:11  dpg1
# New object table behaviour, correct POA semantics.
#
# Revision 1.3.2.11  2001/08/03 17:41:17  sll
# System exception minor code overhaul. When a system exeception is raised,
# a meaning minor code is provided.
#
# Revision 1.3.2.10  2001/07/25 13:40:53  dpg1
# Suppress compiler warning about unused variable in _dispatch() for
# empty interfaces.
#
# Revision 1.3.2.9  2001/06/08 17:12:20  dpg1
# Merge all the bug fixes from omni3_develop.
#
# Revision 1.3.2.8  2001/05/31 16:18:12  dpg1
# inline string matching functions, re-ordered string matching in
# _ptrToInterface/_ptrToObjRef
#
# Revision 1.3.2.7  2001/05/29 17:03:50  dpg1
# In process identity.
#
# Revision 1.3.2.6  2001/05/02 14:20:15  sll
# Make sure that getStream() is used instead of casting to get a cdrStream
# from a IOP_C and IOP_S.
#
# Revision 1.3.2.5  2001/04/19 09:30:11  sll
#  Big checkin with the brand new internal APIs.
# Scoped where appropriate with the omni namespace.
#
# Revision 1.3.2.4  2000/11/09 12:27:56  dpg1
# Huge merge from omni3_develop, plus full long long from omni3_1_develop.
#
# Revision 1.3.2.3  2000/11/03 19:23:53  sll
# Replace the old set of marshalling operators in the generated code with
# a couple of unified operators for cdrStream. Changed template to correspond
# to the new callDescriptor structure and the new way to dispatch a call on
# the server side.
#
# Revision 1.3.2.2  2000/10/12 15:37:53  sll
# Updated from omni3_1_develop.
#
# Revision 1.4.2.2  2000/08/21 11:35:34  djs
# Lots of tidying
#
# Revision 1.4.2.1  2000/08/02 10:52:01  dpg1
# New omni3_1_develop branch, merged from omni3_develop.
#
# Revision 1.4  2000/07/13 15:25:59  dpg1
# Merge from omni3_develop for 3.0 release.
#
# Revision 1.1.2.8  2000/07/24 16:32:19  djs
# Fixed typo in previous BOA skeleton bugfix.
# Suppressed compiler warning (from gcc -Wall) when encountering a call with
# no arguments and no return value.
#
# Revision 1.1.2.7  2000/07/24 10:17:34  djs
# Added missing BOA skeleton constructor
#
# Revision 1.1.2.6  2000/06/05 13:04:20  djs
# Removed union member name clash (x & pd_x, pd__default, pd__d)
# Removed name clash when a sequence is called "pd_seq"
#
# Revision 1.1.2.5  2000/05/31 18:03:40  djs
# Better output indenting (and preprocessor directives now correctly output at
# the beginning of lines)
# Calling an exception "e" resulted in a name clash (and resultant C++
# compile failure)
#
# Revision 1.1.2.4  2000/05/05 16:50:53  djs
# Existing workaround for MSVC5 scoping problems extended to help with
# base class initialisers. Instead of using the fully qualified or unambiguous
# name, a flat typedef is generated at global scope and that is used instead.
# This was a solution to a previous bug wrt operation dispatch()ing.
# This does not affect the OMNI_BASE_CTOR powerpc/aix workaround.
#
# Revision 1.1.2.3  2000/04/26 18:22:57  djs
# Rewrote type mapping code (now in types.py)
# Rewrote identifier handling code (now in id.py)
# Removed superfluous externs in front of function definitions
#
# Revision 1.1.2.2  2000/04/20 15:11:28  djr
# Fixed bug when duplicating a nil object reference.
#
# Revision 1.1.2.1  2000/03/20 11:50:28  djs
# Removed excess buffering- output templates have code attached which is
# lazily evaluated when required.
#
# Revision 1.1  2000/01/19 17:05:16  djs
# Modified to use an externally stored C++ output template.
#

"""C++ templates for the SK.cc file"""


##
## Includes
##

boilerplate = """\
// This file is generated by @program@- @library@. Do not edit.

#include "@basename@@hh@"
#include <omniORB4/IOP_S.h>
#include <omniORB4/IOP_C.h>
#include <omniORB4/callDescriptor.h>
#include <omniORB4/callHandle.h>
#include <omniORB4/objTracker.h>
@include_omniAMICallDescriptor@

OMNI_USING_NAMESPACE(omni)

static const char* @prefix@_library_version = @library@;


"""


##
## Interface
##
interface_POA = """\
POA_@fqname@::~@POA_prefix@@name@() {}
"""

interface_Helper = """\
@name@_ptr @name@_Helper::_nil() {
  return ::@name@::_nil();
}

::CORBA::Boolean @name@_Helper::is_nil(::@name@_ptr p) {
  return ::CORBA::is_nil(p);\n
}

void @name@_Helper::release(::@name@_ptr p) {
  ::CORBA::release(p);
}

void @name@_Helper::marshalObjRef(::@name@_ptr obj, cdrStream& s) {
  ::@name@::_marshalObjRef(obj, s);
}

@name@_ptr @name@_Helper::unmarshalObjRef(cdrStream& s) {
  return ::@name@::_unmarshalObjRef(s);
}
"""

interface_duplicate_narrow = """\
void @name@_Helper::duplicate(::@name@_ptr obj) {
  if( obj && !obj->_NP_is_nil() )  omni::duplicateObjRef(obj);
}

@name@_ptr
@name@::_duplicate(::@name@_ptr obj)
{
  if( obj && !obj->_NP_is_nil() )  omni::duplicateObjRef(obj);
  return obj;
}

@name@_ptr
@name@::_narrow(::CORBA::Object_ptr obj)
{
  if( !obj || obj->_NP_is_nil() || obj->_NP_is_pseudo() ) return _nil();
  _ptr_type e = (_ptr_type) obj->_PR_getobj()->_realNarrow(_PD_repoId);
  return e ? e : _nil();
}


@name@_ptr
@name@::_unchecked_narrow(::CORBA::Object_ptr obj)
{
  if( !obj || obj->_NP_is_nil() || obj->_NP_is_pseudo() ) return _nil();
  _ptr_type e = (_ptr_type) obj->_PR_getobj()->_uncheckedNarrow(_PD_repoId);
  return e ? e : _nil();
}
"""

interface_narrow_abstract = """\
@name@_ptr
@name@::_narrow(::CORBA::AbstractBase_ptr obj)
{
  return _narrow(obj->_NP_to_object());
}

@name@_ptr
@name@::_unchecked_narrow(::CORBA::AbstractBase_ptr obj)
{
  return _unchecked_narrow(obj->_NP_to_object());
}
"""


abstract_interface_duplicate_narrow = """\
void @name@_Helper::duplicate(::@name@_ptr obj) {
  if (obj) {
    if (!obj->_to_value())
      obj->_to_object();
  }
}

@name@_ptr
@name@::_duplicate(::@name@_ptr obj)
{
  if (obj) {
    if (!obj->_to_value())
      obj->_to_object();
  }
  return obj;
}

@name@_ptr
@name@::_narrow(::CORBA::AbstractBase_ptr obj)
{
  if( !obj || obj->_NP_is_nil() ) return _nil();
  _ptr_type e = 0;
  
  ::CORBA::ValueBase* v = obj->_to_value();
  if (v) {
    e = (_ptr_type) v->_ptrToValue(_PD_repoId);
  }
  else {
    ::CORBA::Object_ptr o = obj->_NP_to_object();
    if (o && !o->_NP_is_nil()) {
      e = (_ptr_type) o->_PR_getobj()->_realNarrow(_PD_repoId);
    }
  }  
  return e ? e : _nil();
}

@name@_ptr
@name@::_unchecked_narrow(::CORBA::AbstractBase_ptr obj)
{
  if( !obj || obj->_NP_is_nil() ) return _nil();
  _ptr_type e = 0;
  
  ::CORBA::ValueBase* v = obj->_to_value();
  if (v) {
    e = (_ptr_type) v->_ptrToValue(_PD_repoId);
  }
  else {
    ::CORBA::Object_ptr o = obj->_NP_to_object();
    if (o && !o->_NP_is_nil()) {
      e = (_ptr_type) o->_PR_getobj()->_uncheckedNarrow(_PD_repoId);
    }
  }  
  return e ? e : _nil();
}
"""

local_interface_duplicate_narrow = """\
void @name@_Helper::duplicate(::@name@_ptr obj) {
  if( obj && !obj->_NP_is_nil() )  obj->_NP_incrRefCount();
}

@name@_ptr
@name@::_duplicate(::@name@_ptr obj)
{
  if( obj && !obj->_NP_is_nil() )  obj->_NP_incrRefCount();
  return obj;
}

@name@_ptr
@name@::_narrow(::CORBA::Object_ptr obj)
{
  if( !obj || obj->_NP_is_nil() ) return _nil();
  _ptr_type e = (_ptr_type) obj->_ptrToObjRef(_PD_repoId);
  if (e) {
    e->_NP_incrRefCount();
    return e;
  }
  return _nil();
}

@name@_ptr
@name@::_unchecked_narrow(::CORBA::Object_ptr obj)
{
  return _narrow(obj);
}
"""


interface_nil = """\
@name@_ptr
@name@::_nil()
{
#ifdef OMNI_UNLOADABLE_STUBS
  static @objref_name@ _the_nil_obj;
  return &_the_nil_obj;
#else
  static @objref_name@* _the_nil_ptr = 0;
  if( !_the_nil_ptr ) {
    omni::nilRefLock().lock();
    if( !_the_nil_ptr ) {
      _the_nil_ptr = new @objref_name@;
      registerNilCorbaObject(_the_nil_ptr);
    }
    omni::nilRefLock().unlock();
  }
  return _the_nil_ptr;
#endif
}

const char* @name@::_PD_repoId = "@repoID@";

"""


interface_objref = """\
@fq_objref_name@::~@objref_name@() {
  @release_shortcut@
}


@fq_objref_name@::@objref_name@(omniIOR* ior, omniIdentity* id) :
   omniObjRef(::@name@::_PD_repoId, ior, id, 1)@comma@
   @inherits_str@
   @init_shortcut@
{
  _PR_setobj(this);
}

void*
@fq_objref_name@::_ptrToObjRef(const char* id)
{
  if( id == ::@name@::_PD_repoId )
    return (::@name@_ptr) this;
  @_ptrToObjRef_ptr@
  if( id == ::CORBA::Object::_PD_repoId )
    return (::CORBA::Object_ptr) this;

  if( omni::strMatch(id, ::@name@::_PD_repoId) )
    return (::@name@_ptr) this;
  @_ptrToObjRef_str@
  if( omni::strMatch(id, ::CORBA::Object::_PD_repoId) )
    return (::CORBA::Object_ptr) this;

  return 0;
}
"""

interface_release_refcount_shortcut = """\
if (_shortcut) {
  _shortcut->_remove_ref();
  _shortcut = 0;
}
"""

interface_objref_repoID_ptr = """\
if( id == ::@inherits_fqname@::_PD_repoId )
  return (::@inherits_fqname@_ptr) this;
"""

interface_objref_repoID_str = """\
if( omni::strMatch(id, ::@inherits_fqname@::_PD_repoId) )
  return (::@inherits_fqname@_ptr) this;
"""

interface_shortcut = """\
void
@fq_objref_name@::_enableShortcut(omniServant* _svt, const _CORBA_Boolean* _inv)
{
  if (_svt)
    _shortcut = (_impl_@basename@*)_svt->_ptrToInterface(::@name@::_PD_repoId);
  else
    _shortcut = 0;
  _invalid  = _inv;
  @inherited@
}
"""

interface_shortcut_refcount = """\
void
@fq_objref_name@::_enableShortcut(omniServant* _svt, const _CORBA_Boolean* _inv)
{
  if (_shortcut)
    _shortcut->_remove_ref();

  if (_svt) {
    _svt->_add_ref();
    _shortcut = (_impl_@basename@*)_svt->_ptrToInterface(::@name@::_PD_repoId);
  }
  else {
    _shortcut = 0;
  }
  _invalid = _inv;
  @inherited@
}
"""

interface_shortcut_inh = """\
@parent@::_enableShortcut(_svt, _inv);"""


local_interface_objref = """\
@name@::@sname@()
{
  _PR_setobj((omniObjRef*)1);
}

@name@::~@sname@() { }

@fq_nil_name@::~@nil_name@() { }

void*
@name@::_ptrToObjRef(const char* id)
{
  if( id == ::@name@::_PD_repoId )
    return (::@name@_ptr) this;
  @_ptrToObjRef_ptr@
  if( id == ::CORBA::Object::_PD_repoId )
    return (::CORBA::Object_ptr) this;

  if( omni::strMatch(id, ::@name@::_PD_repoId) )
    return (::@name@_ptr) this;
  @_ptrToObjRef_str@
  if( omni::strMatch(id, ::CORBA::Object::_PD_repoId) )
    return (::CORBA::Object_ptr) this;

  return 0;
}
"""

local_interface_nil_operation = """\
OMNIORB_THROW(INV_OBJREF, INV_OBJREF_InvokeOnNilObjRef, ::CORBA::COMPLETED_NO);"""

local_interface_nil_dummy_return = """
#ifdef NEED_DUMMY_RETURN
// Pretend recursive call to silence warnings about no return value
return @method@(@args@);
#endif"""


interface_callback = """\
// Local call call-back function.
static void
@local_call_descriptor@(omniCallDescriptor*@cd_arg@, omniServant* svnt)
{
  @get_call_descriptor@
  @impl_fqname@* impl = (@impl_fqname@*) svnt->_ptrToInterface(@name@::_PD_repoId);
@impl_call@
}
"""

interface_callback_context = """\
  ::CORBA::Context_var ctxt;
  if (cd->is_upcall())
    ctxt = ::CORBA::Context::_duplicate(tcd->ctxt);
  else
    ctxt = ::CORBA::Context::filterContext(tcd->ctxt, @cname@, @count@);
"""

interface_callback_invoke = """\
  @result@impl->@cxx_operation_name@(@operation_arguments@);
"""

interface_callback_tryblock = """\
#ifdef HAS_Cplusplus_catch_exception_by_base
  @result@impl->@cxx_operation_name@(@operation_arguments@);
#else
  if (!cd->is_upcall())
    @result@impl->@cxx_operation_name@(@operation_arguments@);
  else {
    try {
      @result@impl->@cxx_operation_name@(@operation_arguments@);
    }
    @catch@
  }
#endif
"""

interface_proxy_class = """\
// Proxy call descriptor class. Mangled signature:
//  @signature@
class @call_descriptor@
  : public omniCallDescriptor
{
public:
  inline @call_descriptor@(@ctor_args@):
     @base_ctor@
  {
    @contains_values@
  }
  
  @in_arguments_decl@
  @out_arguments_decl@  
  @user_exceptions_decl@
  static const char* const _user_exns[];

  @member_data@
};
"""

interface_context_array = """\
static const char*const @context_descriptor@[] = {
  @contexts@
  0
};
"""

interface_proxy_marshal_arguments = """\
void @call_descriptor@::marshalArguments(cdrStream& _n)
{
  @marshal_block@
}
"""

interface_proxy_marshal_context = """\
::CORBA::Context::marshalContext(ctxt, @name@, @count@, _n);"""

interface_proxy_unmarshal_arguments = """\
void @call_descriptor@::unmarshalArguments(cdrStream& _n)
{
  @marshal_block@
}
"""

interface_proxy_unmarshal_context = """\
ctxt = ::CORBA::Context::unmarshalContext(_n);"""

interface_proxy_marshal_returnedvalues = """\
void @call_descriptor@::marshalReturnedValues(cdrStream& _n)
{
  @marshal_block@
}
"""

interface_proxy_unmarshal_returnedvalues = """\
void @call_descriptor@::unmarshalReturnedValues(cdrStream& _n)
{
  @marshal_block@
}
"""


interface_proxy_empty_exn = """\
const char* const @call_descriptor@::_user_exns[] = {
  0
};
"""

interface_proxy_exn = """\
const char* const @call_descriptor@::_user_exns[] = {
  @exception_namelist@
};

void @call_descriptor@::userException(cdrStream& s, _OMNI_NS(IOP_C)* iop_client, const char* repoId)
{
  @exception_block@
  else {
    if (iop_client) iop_client->RequestCompleted(1);
    OMNIORB_THROW(UNKNOWN,UNKNOWN_UserException,
                  (::CORBA::CompletionStatus)s.completion());
  }
}
"""

interface_proxy_exn_handle = """\
if ( omni::strMatch(repoId, @repoID_str@) ) {
  @exname@ _ex;
  _ex <<= s;
  if (iop_client) iop_client->RequestCompleted();
  throw _ex;
}
"""


interface_operation = """\
@call_descriptor@ _call_desc(@call_desc_args@);
@assign_args@
@assign_context@
_invoke(_call_desc);
@assign_res@
"""

interface_operation_shortcut = """\
@impl_type@* _s = _shortcut;
if (_s) {
  if (!*_invalid) {
    @callreturn@_s->@name@(@args@);@voidreturn@
  }
  else {
    _enableShortcut(0,0);
    // drop through to normal invoke
  }
}\
"""

interface_operation_shortcut_refcount = """\
@impl_type@* _s = _shortcut;
if (_s) {
  if (!*_invalid) {
    @callreturn@_s->@name@(@args@);@voidreturn@
  }
  else {
    OMNIORB_THROW(INV_OBJREF, INV_OBJREF_ShortcutServantDeactivated,
                  ::CORBA::COMPLETED_NO);
  }
}\
"""


interface_pof = """\
@pof_name@::~@uname@() {}


omniObjRef*
@pof_name@::newObjRef(omniIOR* ior, omniIdentity* id)
{
  return new ::@objref_fqname@(ior, id);
}


::CORBA::Boolean
@pof_name@::is_a(const char* id) const
{
  if( omni::ptrStrMatch(id, ::@name@::_PD_repoId) )
    return 1;
  @Other_repoIDs@
  return 0;
}

const @pof_name@ _the_pof_@idname@;
"""

interface_pof_repoID = """\
if( omni::ptrStrMatch(id, @inherited@::_PD_repoId) )
  return 1;
"""

interface_ALIAS = """\
typedef @fqname@ @flat_fqname@;
typedef @impl_fqname@ @impl_flat_fqname@;
typedef @objref_fqname@ @objref_flat_fqname@;
"""

local_interface_ALIAS = """\
typedef @fqname@ @flat_fqname@;
typedef @nil_fqname@ @nil_flat_fqname@;
"""

interface_impl = """\
@impl_fqname@::~_impl_@uname@() {}


::CORBA::Boolean
@impl_fqname@::_dispatch(omniCallHandle& _handle)
{
  @getopname@

  @dispatch@
  return 0;
}

void*
@impl_fqname@::_ptrToInterface(const char* id)
{
  if( id == ::@name@::_PD_repoId )
    return (::@impl_fqname@*) this;
  @_ptrToInterface_ptr@
  if( id == ::CORBA::Object::_PD_repoId )
    return (void*) 1;

  if( omni::strMatch(id, ::@name@::_PD_repoId) )
    return (::@impl_fqname@*) this;
  @_ptrToInterface_str@
  if( omni::strMatch(id, ::CORBA::Object::_PD_repoId) )
    return (void*) 1;
  return 0;
}

const char*
@impl_fqname@::_mostDerivedRepoId()
{
  return ::@name@::_PD_repoId;
}
"""

interface_impl_inherit_dispatch = """\

#ifndef _MSC_VER
if( @impl_inherited_name@::_dispatch(_handle) ) {
  return 1;
}
#else
// Work-around for incorrect MSVC code generation.
if( ((@impl_inherited_name@*)this)->
    @impl_inherited_name@::_dispatch(_handle) ) {
  return 1;
}
#endif
"""

interface_impl_not_abstract = """\
void @impl_fqname@::_interface_is_abstract() {}
"""

interface_impl_repoID_ptr = """\
if( id == ::@inherited_name@::_PD_repoId )
  return (::@impl_inherited_name@*) this;
"""

interface_impl_repoID_str = """\
if( omni::strMatch(id, ::@inherited_name@::_PD_repoId) )
  return (::@impl_inherited_name@*) this;
"""

interface_sk = """\
@sk_fqname@::@sk_name@(const omniOrbBoaKey& k) { pd_key = k; }

@sk_fqname@::~@sk_name@() {}
"""

interface_operation_catch_exn = """\
catch(@exname@& ex) {
  throw omniORB::StubUserException(ex._NP_duplicate());
}
"""

interface_operation_context = """\
::CORBA::Context_var _ctxt;
_ctxt = ::CORBA::Context::unmarshalContext(iop_s);
"""

interface_operation_dispatch = """\
if( omni::strMatch(op, "@idl_operation_name@") ) {

  @call_descriptor@ _call_desc(@call_desc_args@);
  @prepare_out_args@
  _handle.upcall(this,_call_desc);
  return 1;
}
"""

##
## Struct
##
struct = """\
void
@name@::operator>>= (cdrStream &_n) const
{
  @marshall_code@
}

void
@name@::operator<<= (cdrStream &_n)
{
  @unmarshall_code@
}
"""

##
## Unions
##

union_default_bool = """\
#ifndef HAS_Cplusplus_Bool
  default: break;
#endif
"""

union_default = """\
default: break;
"""

union_operators = """\
void
@name@::operator>>= (cdrStream& _n) const
{
  @marshal_discriminator@
  @marshal_cases@
}

void
@name@::operator<<= (cdrStream& _n)
{
  @unmarshal_discriminator@
  switch(_pd__d) {
    @unmarshal_cases@
  }
  _pd__initialised = 1;
}
"""

union_operators_nonexhaustive = """\
if (_pd__default) {
  @default@
}
else {
  switch(_pd__d) {
    @cases@
  }
}
"""

union_operators_exhaustive = """\
switch(_pd__d) {
  @cases@
}
"""


##
## const
##
const_namespace = """\
#if defined(HAS_Cplusplus_Namespace) && defined(_MSC_VER)
// MSVC++ does not give the constant external linkage othewise.
@open_namespace@
  extern const @type@ @simple_name@ = @value@;
@close_namespace@
#else
const @type@ @name@ = @value@;
#endif
"""

const_simple = """\
const @type@ @name@ = @value@;
"""

const_in_interface = """\
const @type@ @name@ _init_in_cldef_( = @value@ );
"""

const_init_in_def = """\
_init_in_def_( const @type@ @name@ = @value@; )
"""

##
## Exception
##
exception = """\
::CORBA::Exception::insertExceptionToAny @scoped_name@::insertToAnyFn = 0;
::CORBA::Exception::insertExceptionToAnyNCP @scoped_name@::insertToAnyFnNCP = 0;

@scoped_name@::@name@(const @scoped_name@& _s) : ::CORBA::UserException(_s)
{
  @copy_ctor_body@
}

@default_ctor@

@scoped_name@& @scoped_name@::operator=(const @scoped_name@& _s)
{
  ((::CORBA::UserException*) this)->operator=(_s);
  @assign_op_body@
  return *this;
}

@scoped_name@::~@name@() {}

void @scoped_name@::_raise() const { throw *this; }

const char* @scoped_name@::_PD_repoId = "@repoID@";
const char* @scoped_name@::_PD_typeId = "Exception/UserException/@scoped_name@";

@scoped_name@* @scoped_name@::_downcast(::CORBA::Exception* _e) {
  return (@name@*) _NP_is_a(_e, _PD_typeId);
}

const @scoped_name@* @scoped_name@::_downcast(const ::CORBA::Exception* _e) {
  return (const @name@*) _NP_is_a(_e, _PD_typeId);
}

::CORBA::Exception* @scoped_name@::_NP_duplicate() const {
  return new @name@(*this);
}

const char* @scoped_name@::_NP_typeId() const {
  return _PD_typeId;
}

const char* @scoped_name@::_NP_repoId(int* _size) const {
  *_size = sizeof("@repoID@");
  return _PD_repoId;
}
 
void @scoped_name@::_NP_marshal(cdrStream& _s) const {
  *this >>= _s;
}
"""

exception_default_ctor = """\
@scoped_name@::@name@(@ctor_args@)
{
  pd_insertToAnyFn    = @scoped_name@::insertToAnyFn;
  pd_insertToAnyFnNCP = @scoped_name@::insertToAnyFnNCP;
  @default_ctor_body@
}
"""

exception_operators = """\
void
@scoped_name@::operator>>= (cdrStream& _n) const
{
  @marshal@
}

void
@scoped_name@::operator<<= (cdrStream& _n)
{
  @unmarshal@
}
"""

##
## Sequence of forward declared struct/union
##

sequence_forward_unbounded_defns = """\
@fqname@::@name@(const ::@fqname@& _s)
  : @derived@(_s.pd_max, 0, 0, 1)
{
  length(_s.pd_len);
  for (_CORBA_ULong _i=0; _i < pd_len; _i++) {
    pd_buf[_i] = _s.pd_buf[_i];
  }
}

void
@fqname@::operator<<= (cdrStream& _s)
{
  _CORBA_ULong _l;
  _l <<= _s;
  if (!_s.checkInputOverrun(1,_l)) {
    _CORBA_marshal_sequence_range_check_error(_s);
    // never reach here
  }
  length(_l);
  for( _CORBA_ULong _i = 0; _i < _l; _i++ )
    pd_buf[_i] <<= _s;
}
"""

sequence_forward_bounded_defns = """\
@fqname@::@name@(const ::@fqname@& _s)
  : @derived@(0,0,1)
{
  length(_s.pd_len);
  for (_CORBA_ULong _i=0; _i < pd_len; _i++) {
    pd_buf[_i] = _s.pd_buf[_i];
  }
}

void
@fqname@::operator<<= (cdrStream& _s)
{
  _CORBA_ULong _l;
  _l <<= _s;
  if (!_s.checkInputOverrun(1,_l) || (_l > @bound@)) {
    _CORBA_marshal_sequence_range_check_error(_s);
    // never reach here
  }
  length(_l);
  for( _CORBA_ULong _i = 0; _i < _l; _i++ )
    pd_buf[_i] <<= _s;
}
"""

sequence_forward_defns = """\
void
@fqname@::operator>>= (cdrStream& _s) const
{
  ::operator>>=(_CORBA_ULong(pd_len), _s);
  for( _CORBA_ULong _i = 0; _i < pd_len; _i++ )
    pd_buf[_i] >>= _s;
}

@fqname@&
@fqname@::operator=(const ::@fqname@& _s)
{
  length(_s.pd_len);
  for (unsigned long _i=0; _i < pd_len; _i++) {
    pd_buf[_i] = _s.pd_buf[_i];
  }
  return *this;
}

@element@&
@fqname@::operator[](_CORBA_ULong _index)
{
  if (_index >= pd_len) _CORBA_bound_check_error();
  return pd_buf[_index];
}

const @element@&
@fqname@::operator[](_CORBA_ULong _index) const
{
  if (_index >= pd_len) _CORBA_bound_check_error();
  return pd_buf[_index];
}

@element@*
@fqname@::allocbuf(_CORBA_ULong _nelems)
{
  ::@element@* _tmp = 0;
  if (_nelems) {
    _tmp = new ::@element@[_nelems];
  }
  return _tmp;
}

void
@fqname@::freebuf(::@element@* _b)
{
  if (_b) delete [] _b;
}

void
@fqname@::NP_freebuf()
{
  if (pd_buf) delete [] pd_buf;
}

@fqname@::~@name@()
{
  if (pd_rel && pd_buf) delete [] pd_buf;
  pd_buf = 0;
}

void
@fqname@::NP_copybuffer(_CORBA_ULong _newmax)
{
  // replace pd_data with a new buffer of size newmax.
  // Invariant:  pd_len <= newmax
  //
  ::@element@* _newbuf = allocbuf(_newmax);
  if (!_newbuf) {
    _CORBA_new_operator_return_null();
    // never reach here
  }
  for (unsigned long _i=0; _i < pd_len; _i++) {
    _newbuf[_i] = pd_buf[_i];
  }
  if (pd_rel && pd_buf) {
    freebuf(pd_buf);
  }
  else {
    pd_rel = 1;
  }
  pd_buf = _newbuf;
  pd_max = _newmax;
}
"""
