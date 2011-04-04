# -*- python -*-
#                           Package   : omniidl
# template.py               Created on: 2000/01/18
#			    Author    : David Scott (djs)
#
#    Copyright (C) 2003-2008 Apasphere Ltd
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
#   C++ templates for the .hh file

# $Id: template.py,v 1.8.2.21 2009/05/06 16:15:40 dgrisby Exp $
# $Log: template.py,v $
# Revision 1.8.2.21  2009/05/06 16:15:40  dgrisby
# Update lots of copyright notices.
#
# Revision 1.8.2.20  2008/12/29 18:44:38  dgrisby
# Globally scope array functions to avoid ambiguities.
#
# Revision 1.8.2.19  2008/12/03 10:53:58  dgrisby
# Tweaks leading to Python 3 support; other minor clean-ups.
#
# Revision 1.8.2.18  2007/09/19 14:16:07  dgrisby
# Avoid namespace clashes if IDL defines modules named CORBA.
#
# Revision 1.8.2.17  2007/05/11 09:52:27  dgrisby
# New -Wbguard_prefix option. Thanks Austin Bingham.
#
# Revision 1.8.2.16  2006/10/23 15:36:25  dgrisby
# Undefine USE_stub_in_nt_dll at the end of header if it was not defined
# at the start.
#
# Revision 1.8.2.15  2006/09/04 11:40:06  dgrisby
# Remove crazy switch code in enum marshalling.
#
# Revision 1.8.2.14  2006/01/10 12:24:03  dgrisby
# Merge from omni4_0_develop pre 4.0.7 release.
#
# Revision 1.8.2.13  2005/11/14 11:02:16  dgrisby
# Local interface fixes.
#
# Revision 1.8.2.12  2005/11/09 12:22:17  dgrisby
# Local interfaces support.
#
# Revision 1.8.2.11  2005/08/16 13:51:21  dgrisby
# Problems with valuetype / abstract interface C++ mapping.
#
# Revision 1.8.2.10  2005/07/22 17:18:37  dgrisby
# Another merge from omni4_0_develop.
#
# Revision 1.8.2.9  2005/01/06 23:10:06  dgrisby
# Big merge from omni4_0_develop.
#
# Revision 1.8.2.8  2005/01/06 16:35:18  dgrisby
# Narrowing for abstract interfaces.
#
# Revision 1.8.2.7  2004/10/13 17:58:24  dgrisby
# Abstract interfaces support; values support interfaces; value bug fixes.
#
# Revision 1.8.2.6  2004/07/31 23:46:27  dgrisby
# Correct constness of exception Any insertion operator.
#
# Revision 1.8.2.5  2004/07/23 10:29:59  dgrisby
# Completely new, much simpler Any implementation.
#
# Revision 1.8.2.4  2004/07/04 23:53:39  dgrisby
# More ValueType TypeCode and Any support.
#
# Revision 1.8.2.3  2004/02/16 10:10:32  dgrisby
# More valuetype, including value boxes. C++ mapping updates.
#
# Revision 1.8.2.2  2003/10/23 11:25:55  dgrisby
# More valuetype support.
#
# Revision 1.8.2.1  2003/03/23 21:02:36  dgrisby
# Start of omniORB 4.1.x development branch.
#
# Revision 1.5.2.19  2001/11/12 13:46:07  dpg1
# _unchecked_narrow, improved _narrow.
#
# Revision 1.5.2.18  2001/11/08 16:33:51  dpg1
# Local servant POA shortcut policy.
#
# Revision 1.5.2.17  2001/10/29 17:42:41  dpg1
# Support forward-declared structs/unions, ORB::create_recursive_tc().
#
# Revision 1.5.2.16  2001/10/18 12:45:28  dpg1
# IDL compiler tweaks.
#
# Revision 1.5.2.15  2001/10/17 16:44:05  dpg1
# Update DynAny to CORBA 2.5 spec, const Any exception extraction.
#
# Revision 1.5.2.14  2001/09/19 17:29:04  dpg1
# Cosmetic changes.
#
# Revision 1.5.2.13  2001/08/17 13:45:56  dpg1
# C++ mapping fixes.
#
# Revision 1.5.2.12  2001/08/15 10:26:10  dpg1
# New object table behaviour, correct POA semantics.
#
# Revision 1.5.2.11  2001/08/03 17:41:17  sll
# System exception minor code overhaul. When a system exeception is raised,
# a meaning minor code is provided.
#
# Revision 1.5.2.10  2001/07/31 19:25:11  sll
#  Array _var should be separated into fixed and variable size ones.
#
# Revision 1.5.2.9  2001/06/18 20:30:51  sll
# Only define 1 conversion operator from T_var to T* if the compiler is
# gcc. Previously, this is only done for gcc 2.7.2. It seems that gcc 3.0
# requires this to be the case. This is the default for all versions of
# gcc.
#
# Revision 1.5.2.8  2001/05/29 17:03:50  dpg1
# In process identity.
#
# Revision 1.5.2.7  2001/04/19 09:30:12  sll
#  Big checkin with the brand new internal APIs.
# Scoped where appropriate with the omni namespace.
#
# Revision 1.5.2.6  2001/03/13 10:32:09  dpg1
# Fixed point support.
#
# Revision 1.5.2.5  2000/11/20 14:43:25  sll
# Added support for wchar and wstring.
#
# Revision 1.5.2.4  2000/11/09 12:27:55  dpg1
# Huge merge from omni3_develop, plus full long long from omni3_1_develop.
#
# Revision 1.5.2.3  2000/11/03 19:20:41  sll
# Replaced old marshal operators with a unified operator for cdrStream.
#
# Revision 1.5.2.2  2000/10/12 15:37:51  sll
# Updated from omni3_1_develop.
#
# Revision 1.6.2.2  2000/08/21 11:35:18  djs
# Lots of tidying
#
# Revision 1.6.2.1  2000/08/02 10:52:02  dpg1
# New omni3_1_develop branch, merged from omni3_develop.
#
# Revision 1.6  2000/07/13 15:26:00  dpg1
# Merge from omni3_develop for 3.0 release.
#
# Revision 1.3.2.15  2000/07/26 15:29:11  djs
# Missing typedef and forward when generating BOA skeletons
#
# Revision 1.3.2.14  2000/07/24 09:35:20  dpg1
# Adding the missing constructor meant that there was no longer a
# default constructor.
#
# Revision 1.3.2.13  2000/07/24 10:17:31  djs
# Added missing BOA skeleton constructor
#
# Revision 1.3.2.12  2000/07/04 12:57:55  djs
# Fixed Any insertion/extraction operators for unions and exceptions
#
# Revision 1.3.2.11  2000/06/26 16:24:00  djs
# Better handling of #include'd files (via new commandline options)
# Refactoring of configuration state mechanism.
#
# Revision 1.3.2.10  2000/06/19 18:19:50  djs
# Implemented union discriminant setting function _d(_value) with checks for
# illegal uses (setting to a label corresponding to a non-current member and
# setting before initialisation)
#
# Revision 1.3.2.9  2000/06/05 13:03:57  djs
# Removed union member name clash (x & pd_x, pd__default, pd__d)
# Removed name clash when a sequence is called "pd_seq"
# Nested union within union fix
# Actually generates BOA non-flattened tie templates
#
# Revision 1.3.2.8  2000/05/31 18:02:58  djs
# Better output indenting (and preprocessor directives now correctly output at
# the beginning of lines)
#
# Revision 1.3.2.7  2000/05/30 15:59:25  djs
# Removed inheritance ambiguity in generated BOA _sk_ and POA_ classes
#
# Revision 1.3.2.6  2000/05/18 15:57:33  djs
# Added missing T* data constructor for bounded sequence types
#
# Revision 1.3.2.5  2000/03/20 11:50:20  djs
# Removed excess buffering- output templates have code attached which is
# lazily evaluated when required.
#
# Revision 1.3.2.4  2000/03/10 12:01:03  djr
# Re-fixed omniidl (make exception _NP_duplicate() public).
#
# Revision 1.3.2.3  2000/03/09 15:22:42  djs
# Changing the protection status of an exception method, mirroring a change
# in omniidl3
#
# Revision 1.3.2.2  2000/03/07 18:07:33  djr
# Fixed user-exceptions when can't catch by base class.
#
# Revision 1.3.2.1  2000/03/03 14:29:17  djr
# Improvement to BOA skeletons (less generated code).
#
# Revision 1.3  2000/02/01 09:26:45  djs
# Tracking fixes in old compiler: powerpc-aix scoped identifier workarounds
#
# Revision 1.2  2000/01/19 11:23:29  djs
# Moved most C++ code to template file
#
# Revision 1.1  2000/01/18 18:05:53  djs
# Extracted most C++ from header/defs and put in a template file.
# General refactoring.
#

"""C++ templates for the .hh file"""

##
## File header
##
header = """\
// This file is generated by @program@- @library@. Do not edit.
#ifndef @guard_prefix@__@guard@_hh__
#define @guard_prefix@__@guard@_hh__
"""

footer = """\
#endif
"""

##
## Main file
##
main = """\
#ifndef __CORBA_H_EXTERNAL_GUARD__
#include <omniORB4/CORBA.h>
#endif

#ifndef  USE_stub_in_nt_dll
# define USE_stub_in_nt_dll_NOT_DEFINED_@guard@
#endif
#ifndef  USE_core_stub_in_nt_dll
# define USE_core_stub_in_nt_dll_NOT_DEFINED_@guard@
#endif
#ifndef  USE_dyn_stub_in_nt_dll
# define USE_dyn_stub_in_nt_dll_NOT_DEFINED_@guard@
#endif

@sub_include_pre@
@cxx_direct_include@
@includes@
@sub_include_post@

#ifdef USE_stub_in_nt_dll
# ifndef USE_core_stub_in_nt_dll
#  define USE_core_stub_in_nt_dll
# endif
# ifndef USE_dyn_stub_in_nt_dll
#  define USE_dyn_stub_in_nt_dll
# endif
#endif

#ifdef _core_attr
# error "A local CPP macro _core_attr has already been defined."
#else
# ifdef  USE_core_stub_in_nt_dll
#  define _core_attr _OMNIORB_NTDLL_IMPORT
# else
#  define _core_attr
# endif
#endif

#ifdef _dyn_attr
# error "A local CPP macro _dyn_attr has already been defined."
#else
# ifdef  USE_dyn_stub_in_nt_dll
#  define _dyn_attr _OMNIORB_NTDLL_IMPORT
# else
#  define _dyn_attr
# endif
#endif

@forward_declarations@

@string_tcParser_declarations@

@defs@

@poa@

@obv@

@other_tie@

#undef _core_attr
#undef _dyn_attr

@operators@

@marshalling@

#ifdef   USE_stub_in_nt_dll_NOT_DEFINED_@guard@
# undef  USE_stub_in_nt_dll
# undef  USE_stub_in_nt_dll_NOT_DEFINED_@guard@
#endif
#ifdef   USE_core_stub_in_nt_dll_NOT_DEFINED_@guard@
# undef  USE_core_stub_in_nt_dll
# undef  USE_core_stub_in_nt_dll_NOT_DEFINED_@guard@
#endif
#ifdef   USE_dyn_stub_in_nt_dll_NOT_DEFINED_@guard@
# undef  USE_dyn_stub_in_nt_dll
# undef  USE_dyn_stub_in_nt_dll_NOT_DEFINED_@guard@
#endif

#endif  // __@guard@_hh__
"""


sub_include_pre = """\
#ifdef INCLUDED_stub_in_nt_dll
# ifdef USE_stub_in_nt_dll
#  error "cannot use both INCLUDED_stub_in_nt_dll and USE_stub_in_nt_dll."
# else
#  define USE_stub_in_nt_dll
# endif
# define INCLUDED_stub_in_nt_dll_DEFINED_@guard@
# undef INCLUDED_stub_in_nt_dll
#endif
"""

sub_include_post = """\
#ifdef INCLUDED_stub_in_nt_dll_DEFINED_@guard@
# undef USE_stub_in_nt_dll
# define INCLUDED_stub_in_nt_dll 
# undef INCLUDED_stub_in_nt_dll_DEFINED_@guard@
#endif
"""

main_include = """\
#ifndef @guard_prefix@__@guardname@_EXTERNAL_GUARD__
#define @guard_prefix@__@guardname@_EXTERNAL_GUARD__
#include @filename@
#endif"""

##
## Modules
##
# name => C++ form of the module identifier
module_begin = """\
_CORBA_MODULE @name@

_CORBA_MODULE_BEG
"""
module_end = """\
_CORBA_MODULE_END
"""

POA_module_begin = """\
_CORBA_MODULE @POA_prefix@@name@
_CORBA_MODULE_BEG
"""

POA_module_end = """\
_CORBA_MODULE_END
"""

OBV_module_begin = """\
_CORBA_MODULE @OBV_prefix@@name@
_CORBA_MODULE_BEG
"""

OBV_module_end = """\
_CORBA_MODULE_END
"""


POA_interface = """\
class @POA_name@ :
  public virtual @impl_scopedID@,
  @inherits@
{
public:
  virtual ~@POA_name@();

  inline ::@scopedID@_ptr _this() {
    return (::@scopedID@_ptr) _do_this(::@scopedID@::_PD_repoId);
  }
};
"""


##
## Interfaces
##

interface_Helper = """\
#ifndef __@guard@__
#define __@guard@__

class @name@;
class _objref_@name@;
class _impl_@name@;
@class_sk_name@
typedef _objref_@name@* @name@_ptr;
typedef @name@_ptr @name@Ref;

class @name@_Helper {
public:
  typedef @name@_ptr _ptr_type;

  static _ptr_type _nil();
  static _CORBA_Boolean is_nil(_ptr_type);
  static void release(_ptr_type);
  static void duplicate(_ptr_type);
  static void marshalObjRef(_ptr_type, cdrStream&);
  static _ptr_type unmarshalObjRef(cdrStream&);
};

typedef _CORBA_ObjRef_Var<_objref_@name@, @name@_Helper> @name@_var;
typedef _CORBA_ObjRef_OUT_arg<_objref_@name@,@name@_Helper > @name@_out;

#endif
"""

interface_type = """\
// interface @name@
class @name@ {
public:
  // Declarations for this interface type.
  typedef @name@_ptr _ptr_type;
  typedef @name@_var _var_type;

  static _ptr_type _duplicate(_ptr_type);
  static _ptr_type _narrow(::CORBA::Object_ptr);
  static _ptr_type _unchecked_narrow(::CORBA::Object_ptr);
  @abstract_narrows@
  static _ptr_type _nil();

  static inline void _marshalObjRef(_ptr_type, cdrStream&);

  static inline _ptr_type _unmarshalObjRef(cdrStream& s) {
    omniObjRef* o = omniObjRef::_unMarshal(_PD_repoId,s);
    if (o)
      return (_ptr_type) o->_ptrToObjRef(_PD_repoId);
    else
      return _nil();
  }

  static _core_attr const char* _PD_repoId;

  // Other IDL defined within this scope.
  @Other_IDL@
};
"""

interface_abstract_narrows = """\
static _ptr_type _narrow(::CORBA::AbstractBase_ptr);
static _ptr_type _unchecked_narrow(::CORBA::AbstractBase_ptr);
"""


##
## Abstract Interfaces
##

abstract_interface_Helper = """\
#ifndef __@guard@__
#define __@guard@__

class @name@;
class _objref_@name@;
typedef @name@* @name@_ptr;
typedef @name@_ptr @name@Ref;

class @name@_Helper {
public:
  typedef @name@_ptr _ptr_type;

  static _ptr_type _nil();
  static _CORBA_Boolean is_nil(_ptr_type);
  static void release(_ptr_type);
  static void duplicate(_ptr_type);
  static void marshalObjRef(_ptr_type, cdrStream&);
  static _ptr_type unmarshalObjRef(cdrStream&);
};

typedef _CORBA_ObjRef_Var<@name@, @name@_Helper> @name@_var;
typedef _CORBA_ObjRef_OUT_arg<@name@,@name@_Helper > @name@_out;

#endif
"""

abstract_interface_type = """\
// abstract interface @name@
class @name@ :
  @inherits@
{
public:
  // Declarations for this interface type.
  typedef @name@_ptr _ptr_type;
  typedef @name@_var _var_type;

  static _ptr_type _duplicate(_ptr_type);
  static _ptr_type _narrow(::CORBA::AbstractBase_ptr);
  static _ptr_type _unchecked_narrow(::CORBA::AbstractBase_ptr);
  static _ptr_type _nil();

  static inline void _marshalObjRef(_ptr_type, cdrStream&);

  static inline _ptr_type _unmarshalObjRef(cdrStream& s) {
    _CORBA_Boolean b = s.unmarshalBoolean();
    if (b) {
      omniObjRef* o = omniObjRef::_unMarshal(_PD_repoId,s);
      if (o)
        return (_ptr_type) o->_ptrToObjRef(_PD_repoId);
      else
        return _nil();
    }
    else {
      ::CORBA::ValueBase* v = ::CORBA::ValueBase::_NP_unmarshal(s);
      if (v)
        return (_ptr_type) v->_ptrToValue(_PD_repoId);
      else
        return 0;
    }
  }

  static _core_attr const char* _PD_repoId;

  // Other IDL defined within this scope.
  @Other_IDL@

  // Operations declared in this abstract interface
  @operations@  
};
"""

##
## Local Interfaces
##

local_interface_Helper = """\
#ifndef __@guard@__
#define __@guard@__

class @name@;
typedef @name@* @name@_ptr;
typedef @name@_ptr @name@Ref;

class @name@_Helper {
public:
  typedef @name@_ptr _ptr_type;

  static _ptr_type _nil();
  static _CORBA_Boolean is_nil(_ptr_type);
  static void release(_ptr_type);
  static void duplicate(_ptr_type);
  static void marshalObjRef(_ptr_type, cdrStream&);
  static _ptr_type unmarshalObjRef(cdrStream&);
};

typedef _CORBA_ObjRef_Var<@name@, @name@_Helper> @name@_var;
typedef _CORBA_ObjRef_OUT_arg<@name@,@name@_Helper > @name@_out;

#endif
"""

local_interface_type = """\
// local interface @name@
class @name@ :
  @inherits@
{
public:
  // Declarations for this interface type.
  typedef @name@_ptr _ptr_type;
  typedef @name@_var _var_type;

  static _ptr_type _duplicate(_ptr_type);
  static _ptr_type _narrow(::CORBA::Object_ptr);
  static _ptr_type _unchecked_narrow(::CORBA::Object_ptr);
  @abstract_narrows@
  static _ptr_type _nil();

  static inline void _marshalObjRef(_ptr_type, cdrStream& s) {
    OMNIORB_THROW(MARSHAL, _OMNI_NS(MARSHAL_LocalObject),
                  (::CORBA::CompletionStatus)s.completion());
  }
  static inline _ptr_type _unmarshalObjRef(cdrStream& s) {
    OMNIORB_THROW(MARSHAL, _OMNI_NS(MARSHAL_LocalObject),
                  (::CORBA::CompletionStatus)s.completion());
#ifdef NEED_DUMMY_RETURN
    return 0;
#endif
  }

  static _core_attr const char* _PD_repoId;

  // Other IDL defined within this scope.
  @Other_IDL@

  // Operations declared in this local interface
  @operations@  

private:
  virtual void* _ptrToObjRef(const char*);

protected:
  @name@();
  virtual ~@name@();
};

class _nil_@name@ :
  @nil_inherits@
  public virtual @name@
{
  public:
    @nil_operations@

    inline _nil_@name@() { _PR_setobj(0); }

  protected:
    virtual ~_nil_@name@();
};
"""



##
## Object reference
##

interface_objref = """\
class _objref_@name@ :
  @inherits@
{
public:
  @operations@

  inline _objref_@name@() @init_shortcut@ { _PR_setobj(0); }  // nil
  _objref_@name@(omniIOR*, omniIdentity*);

protected:
  virtual ~_objref_@name@();

  @shortcut@
private:
  virtual void* _ptrToObjRef(const char*);

  _objref_@name@(const _objref_@name@&);
  _objref_@name@& operator = (const _objref_@name@&);
  // not implemented

  friend class @name@;
};
"""

interface_shortcut = """\
virtual void _enableShortcut(omniServant*, const _CORBA_Boolean*);
_impl_@name@* _shortcut;
const _CORBA_Boolean* _invalid;\
"""

##
## Proxy Object Factory
##

interface_pof = """\
class _pof_@name@ : public _OMNI_NS(proxyObjectFactory) {
public:
  inline _pof_@name@() : _OMNI_NS(proxyObjectFactory)(@name@::_PD_repoId) {}
  virtual ~_pof_@name@();

  virtual omniObjRef* newObjRef(omniIOR*,omniIdentity*);
  virtual _CORBA_Boolean is_a(const char*) const;
};
"""

##
## Interface Impl class
##

interface_impl = """\
class _impl_@name@ :
  @inherits@
{
public:
  virtual ~_impl_@name@();

  @operations@
  
public:  // Really protected, workaround for xlC
  virtual _CORBA_Boolean _dispatch(omniCallHandle&);

private:
  virtual void* _ptrToInterface(const char*);
  virtual const char* _mostDerivedRepoId();
  @abstract@
};

"""

interface_impl_abstract = """\
virtual void _interface_is_abstract() = 0;"""

interface_impl_not_abstract = """\
virtual void _interface_is_abstract();"""


##
## Old BOA skeleton class
##

interface_sk = """\
class _sk_@name@ :
  public virtual _impl_@name@,
  @inherits@
{
public:
  _sk_@name@() {}
  _sk_@name@(const omniOrbBoaKey&);
  virtual ~_sk_@name@();
  inline @name@::_ptr_type _this() {
    return (@name@::_ptr_type) omniOrbBoaServant::_this(@name@::_PD_repoId);
  }

};
"""

##
## Objref marshal function
##

interface_marshal_forward = """\
inline void
@name@::_marshalObjRef(::@name@_ptr obj, cdrStream& s) {
  omniObjRef::_marshal(obj->_PR_getobj(),s);
}

"""

abstract_interface_marshal_forward = """\
inline void
@name@::_marshalObjRef(::@name@_ptr obj, cdrStream& s) {
  if (obj) {
    ::CORBA::ValueBase* v = obj->_NP_to_value();
    if (v) {
      s.marshalBoolean(0);
      ::CORBA::ValueBase::_NP_marshal(v,s);
      return;
    }
    ::CORBA::Object_ptr o = obj->_NP_to_object();
    if (o) {
      s.marshalBoolean(1);
      omniObjRef::_marshal(o->_PR_getobj(),s);
      return;
    }
  }
  s.marshalBoolean(0);
  ::CORBA::ValueBase::_NP_marshal(0, s);
}
"""



##
## Typedefs
##
typedef_simple_to_array = """\
typedef @base@ @derived@;
typedef @base@_slice @derived@_slice;
typedef @base@_copyHelper @derived@_copyHelper;
typedef @base@_var @derived@_var;
typedef @base@_out @derived@_out;
typedef @base@_forany @derived@_forany;

@inline_qualifier@ @derived@_slice* @derived@_alloc() { return @base@_alloc(); }
@inline_qualifier@ @derived@_slice* @derived@_dup(const @derived@_slice* p) { return @base@_dup(p); }
@inline_qualifier@ void @derived@_copy( @derived@_slice* _to, const @derived@_slice* _from ) { @base@_copy(_to, _from); }
@inline_qualifier@ void @derived@_free( @derived@_slice* p) { @base@_free(p); }
"""

typedef_simple_string = """\
typedef char* @name@;
typedef ::CORBA::String_var @name@_var;
typedef ::CORBA::String_out @name@_out;
"""

typedef_simple_wstring = """\
typedef ::CORBA::WChar* @name@;
typedef ::CORBA::WString_var @name@_var;
typedef ::CORBA::WString_out @name@_out;
"""

typedef_simple_typecode = """\
typedef ::CORBA::TypeCode_ptr @name@_ptr;
typedef ::CORBA::TypeCode_var @name@_var;
"""

typedef_simple_any = """\
typedef ::CORBA::Any @name@;
typedef ::CORBA::Any_var @name@_var;
typedef ::CORBA::Any_out @name@_out;
"""

typedef_simple_fixed = """\
typedef _omni_Fixed<@digits@,@scale@> @name@;
typedef @name@& @name@_out;
"""

typedef_simple_basic = """\
typedef @base@ @derived@;
typedef @base@_out @derived@_out;
"""

typedef_simple_constructed = """\
typedef @base@ @name@;
typedef @base@_var @name@_var;
typedef @base@_out @name@_out;
"""

typedef_simple_objref = """\
typedef @base@ @name@;
typedef @base@_ptr @name@_ptr;
typedef @base@Ref @name@Ref;
@impl_base@
typedef @base@_Helper @name@_Helper;
@objref_base@
typedef @base@_var @name@_var;
typedef @base@_out @name@_out;
"""

typedef_enum_oper_friend = """\
// Need to declare <<= for elem type, as GCC expands templates early
#if defined(__GNUG__) && __GNUG__ == 2 && __GNUC_MINOR__ == 7
 @friend@ inline void operator >>= (@element@, cdrStream&);
 @friend@ inline void operator <<= (@element@&, cdrStream&);
#endif
"""

# Arrays

typedef_array = """\
typedef @type@ @name@@dims@;
typedef @type@ @name@_slice@taildims@;

@inline_qualifier@ @name@_slice* @name@_alloc() {
  return new @name@_slice[@firstdim@];
}

@inline_qualifier@ @name@_slice* @name@_dup(const @name@_slice* _s) {
  if (!_s) return 0;
  @name@_slice* _data = @name@_alloc();
  if (_data) {
    @dup_loop@
  }
  return _data;
}

@inline_qualifier@ void @name@_copy(@name@_slice* _to, const @name@_slice* _from){
  @copy_loop@
}

@inline_qualifier@ void @name@_free(@name@_slice* _s) {
  delete [] _s;
}
"""

typedef_array_copyHelper = """\
class @name@_copyHelper {
public:
  static inline @name@_slice* alloc() { return ::@fqname@_alloc(); }
  static inline @name@_slice* dup(const @name@_slice* p) { return ::@fqname@_dup(p); }
  static inline void free(@name@_slice* p) { ::@fqname@_free(p); }
};

typedef _CORBA_Array_@var_or_fix@_Var<@name@_copyHelper,@name@_slice> @name@_var;
typedef _CORBA_Array_@var_or_fix@_Forany<@name@_copyHelper,@name@_slice> @name@_forany;
"""

typedef_array_fix_out_type = """\
typedef @name@_slice* @name@_out;
"""

typedef_array_variable_out_type = """\
typedef _CORBA_Array_Variable_OUT_arg<@name@_slice,@name@_var > @name@_out;
"""

##
## Sequences
##
sequence_type = """\
class @name@_var;

class @name@ : public @derived@ {
public:
  typedef @name@_var _var_type;
  inline @name@() {}
  inline @name@(const @name@& _s)
    : @derived@(_s) {}

  @bounds@

  inline @name@& operator = (const @name@& _s) {
    @derived@::operator=(_s);
    return *this;
  }
};
"""

sequence_forward_type = """\
class @name@_var;

class @name@ : public @derived@ {
public:
  typedef @name@_var _var_type;

  inline @name@() {}
  @name@(const @name@& _s);
  @name@& operator=(const @name@& _s);

  @bounds@

  virtual ~@name@();

  @element@& operator[] (_CORBA_ULong _index);
  const @element@& operator[] (_CORBA_ULong _index) const;
  static @element@* allocbuf(_CORBA_ULong _nelems);
  static void freebuf(@element@* _b);

  void operator>>= (cdrStream &_s) const;
  void operator<<= (cdrStream &_s);

protected:
  void NP_copybuffer(_CORBA_ULong _newmax);
  void NP_freebuf();
};
"""

sequence_unbounded_ctors = """\
inline @name@(_CORBA_ULong _max)
  : @derived@(_max) {}
inline @name@(_CORBA_ULong _max, _CORBA_ULong _len, @element@* _val, _CORBA_Boolean _rel=0)
  : @derived@(_max, _len, _val, _rel) {}
"""

sequence_bounded_ctors = """\
inline @name@(_CORBA_ULong _len, @element@* _val, _CORBA_Boolean _rel=0)
  : @derived@(_len, _val, _rel) {}
"""

sequence_var_array_subscript = """\
inline @element@_slice* operator [] (_CORBA_ULong _s) {
  return (@element@_slice*) ((_pd_seq->NP_data())[_s]);
}
"""

sequence_var_subscript = """\
inline @element@ operator [] (_CORBA_ULong _s) {
  return (*_pd_seq)[_s];
}
"""

sequence_var = """\
class @name@_out;

class @name@_var {
public:
  inline @name@_var() : _pd_seq(0) {}
  inline @name@_var(@name@* _s) : _pd_seq(_s) {}
  inline @name@_var(const @name@_var& _s) {
    if( _s._pd_seq )  _pd_seq = new @name@(*_s._pd_seq);
    else              _pd_seq = 0;
  }
  inline ~@name@_var() { if( _pd_seq )  delete _pd_seq; }
    
  inline @name@_var& operator = (@name@* _s) {
    if( _pd_seq )  delete _pd_seq;
    _pd_seq = _s;
    return *this;
  }
  inline @name@_var& operator = (const @name@_var& _s) {
    if( _s._pd_seq ) {
      if( !_pd_seq )  _pd_seq = new @name@;
      *_pd_seq = *_s._pd_seq;
    } else if( _pd_seq ) {
      delete _pd_seq;
      _pd_seq = 0;
    }
    return *this;
  }
  @subscript_operator@

  inline @name@* operator -> () { return _pd_seq; }
  inline const @name@* operator -> () const { return _pd_seq; }
#if defined(__GNUG__)
  inline operator @name@& () const { return *_pd_seq; }
#else
  inline operator const @name@& () const { return *_pd_seq; }
  inline operator @name@& () { return *_pd_seq; }
#endif
    
  inline const @name@& in() const { return *_pd_seq; }
  inline @name@&       inout()    { return *_pd_seq; }
  inline @name@*&      out() {
    if( _pd_seq ) { delete _pd_seq; _pd_seq = 0; }
    return _pd_seq;
  }
  inline @name@* _retn() { @name@* tmp = _pd_seq; _pd_seq = 0; return tmp; }
    
  friend class @name@_out;
  
private:
  @name@* _pd_seq;
};
"""

sequence_out_array_subscript = """\
inline @element@_slice* operator [] (_CORBA_ULong _i) {
  return (@element@_slice*) ((_data->NP_data())[_i]);
}
"""

sequence_out_subscript = """\
inline @element@ operator [] (_CORBA_ULong _i) {
  return (*_data)[_i];
}
"""

sequence_out = """\
class @name@_out {
public:
  inline @name@_out(@name@*& _s) : _data(_s) { _data = 0; }
  inline @name@_out(@name@_var& _s)
    : _data(_s._pd_seq) { _s = (@name@*) 0; }
  inline @name@_out(const @name@_out& _s) : _data(_s._data) {}
  inline @name@_out& operator = (const @name@_out& _s) {
    _data = _s._data;
    return *this;
  }
  inline @name@_out& operator = (@name@* _s) {
    _data = _s;
    return *this;
  }
  inline operator @name@*&()  { return _data; }
  inline @name@*& ptr()       { return _data; }
  inline @name@* operator->() { return _data; }

  @subscript_operator@

  @name@*& _data;

private:
  @name@_out();
  @name@_out& operator=(const @name@_var&);
};
"""

##
## Structs
##

struct = """\
struct @name@ {
  typedef _CORBA_ConstrType_@fix_or_var@_Var<@name@> _var_type;

  @Other_IDL@
  @members@

  void operator>>= (cdrStream &) const;
  void operator<<= (cdrStream &);
};

typedef @name@::_var_type @name@_var;
"""

struct_fix_out_type = """\
typedef @name@& @name@_out;
"""

struct_variable_out_type = """\
typedef _CORBA_ConstrType_Variable_OUT_arg< @name@,@name@_var > @name@_out;
"""

struct_array_declarator = """\
typedef @memtype@ @prefix@_@cxx_id@@dims@;
typedef @memtype@ _@cxx_id@_slice@tail_dims@;
"""

struct_nonarray_sequence = """\
typedef @memtype@ _@cxx_id@_seq;
_@cxx_id@_seq @cxx_id@;
"""

struct_normal_member = """\
@memtype@ @cxx_id@@dims@;
"""

struct_forward = """\
struct @name@;
"""

##
## Exceptions
##

exception = """\
class @name@ : public ::CORBA::UserException {
public:
  @Other_IDL@
  @members@

  inline @name@() {
    pd_insertToAnyFn    = insertToAnyFn;
    pd_insertToAnyFnNCP = insertToAnyFnNCP;
  }
  @name@(const @name@&);
  @constructor@
  @name@& operator=(const @name@&);
  virtual ~@name@();
  virtual void _raise() const;
  static @name@* _downcast(::CORBA::Exception*);
  static const @name@* _downcast(const ::CORBA::Exception*);
  static inline @name@* _narrow(::CORBA::Exception* _e) {
    return _downcast(_e);
  }
  
  @inline@void operator>>=(cdrStream&) const @body@
  @inline@void operator<<=(cdrStream&) @body@

  static _core_attr insertExceptionToAny    insertToAnyFn;
  static _core_attr insertExceptionToAnyNCP insertToAnyFnNCP;

  virtual ::CORBA::Exception* _NP_duplicate() const;

  static _core_attr const char* _PD_repoId;
  static _core_attr const char* _PD_typeId;

private:
  virtual const char* _NP_typeId() const;
  virtual const char* _NP_repoId(int*) const;
  virtual void _NP_marshal(cdrStream&) const;
};
"""  


exception_array_declarator = """\
typedef @memtype@ @private_prefix@_@cxx_id@@dims@;
typedef @memtype@ _@cxx_id@_slice@tail_dims@;
"""

exception_member = """\
@memtype@ @cxx_id@@dims@;
"""

##
## Unions
##

union_ctor_nonexhaustive = """\
if ((_pd__default = _value._pd__default)) {
  @default@
}
else {
  switch(_value._pd__d) {
    @cases@
  }
}
_pd__d = _value._pd__d;
"""

union_ctor_exhaustive = """\
switch(_value._pd__d) {
  @cases@
}
_pd__d = _value._pd__d;"""

union_ctor_case = """\
case @discrimvalue@: @name@(_value._pd_@name@); break;
"""

union_ctor_bool_default = """\
#ifndef HAS_Cplusplus_Bool
  default: break;
#endif
"""

union_ctor_default = """\
  default: break;
"""

union = """\
class @unionname@ {
public:

  typedef _CORBA_ConstrType_@fixed@_Var<@unionname@> _var_type;

  @Other_IDL@

  @unionname@(): _pd__initialised(0) {
    @default_constructor@
  }
  
  @unionname@(const @unionname@& _value) {
    _pd__initialised = _value._pd__initialised;
    @copy_constructor@
  }

  ~@unionname@() {}

  @unionname@& operator=(const @unionname@& _value) {
    _pd__initialised = _value._pd__initialised;
    @copy_constructor@
    return *this;
  }

  @discrimtype@ _d() const { return _pd__d;}
  void _d(@discrimtype@ _value){
    @_d_body@
  }

  @implicit_default@

  @members@
  
  void operator>>= (cdrStream&) const;
  void operator<<= (cdrStream&);

private:
  @discrimtype@ _pd__d;
  _CORBA_Boolean _pd__default;
  _CORBA_Boolean _pd__initialised;

  @union@
  @outsideUnion@
};

typedef @unionname@::_var_type @unionname@_var;
"""

union_fix_out_type = """\
typedef @unionname@& @unionname@_out;
"""

union_variable_out_type = """\
typedef _CORBA_ConstrType_Variable_OUT_arg< @unionname@,@unionname@_var > @unionname@_out;
"""

union_union = """\
union {
  @members@
};
"""

union_d_fn_body = """\
// illegal to set discriminator before making a member active
if (!_pd__initialised)
  OMNIORB_THROW(BAD_PARAM,_OMNI_NS(BAD_PARAM_InvalidUnionDiscValue),::CORBA::COMPLETED_NO);

if (_value == _pd__d) return; // no change

@switch@

fail:
OMNIORB_THROW(BAD_PARAM,_OMNI_NS(BAD_PARAM_InvalidUnionDiscValue),::CORBA::COMPLETED_NO);

"""

union_constructor_implicit = """\
_default();
"""
union_constructor_default = """\
_pd__default = 1;
_pd__d = @default@;
"""
union_implicit_default = """\
void _default()
{
  _pd__initialised = 1;
  _pd__d = @arbitraryDefault@;
  _pd__default = 1;
}
"""

union_proxy_float = """
#ifdef USING_PROXY_FLOAT
  @type@ _pd_@name@@dims@;
#endif
"""

union_noproxy_float = """
#ifndef USING_PROXY_FLOAT
  @type@ _pd_@name@@dims@;
#endif
"""


union_array_declarator = """\
typedef @memtype@ @prefix@_@name@@dims@;
typedef @memtype@ _@name@_slice@tail_dims@;
"""

union_array = """\
const @memtype@_slice *@name@ () const { return _pd_@name@; }
void @name@ (const @const_type@ _value) {
  _pd__initialised = 1;
  _pd__d = @discrimvalue@;
  _pd__default = @isDefault@;
  @loop@
}
"""

union_any = """\
const @type@ &@name@ () const { return _pd_@name@; }
@type@ &@name@ () { return _pd_@name@; }
void @name@ (const @type@& _value) {
  _pd__initialised = 1;
  _pd__d = @discrimvalue@;
  _pd__default = @isDefault@;
  _pd_@name@ = _value;
}
"""

union_typecode = """\
::CORBA::TypeCode_ptr @name@ () const { return _pd_@name@._ptr; }
void @name@(::CORBA::TypeCode_ptr _value) {
  _pd__initialised = 1;
  _pd__d = @discrimvalue@;
  _pd__default = @isDefault@;
  _pd_@name@ = ::CORBA::TypeCode::_duplicate(_value);
}
void @name@(const ::CORBA::TypeCode_member& _value) {
  _pd__initialised = 1;
  _pd__d = @discrimvalue@;
  _pd__default = @isDefault@;
  _pd_@name@ = _value;
}
void @name@(const ::CORBA::TypeCode_var& _value) {
  _pd__initialised = 1;
  _pd__d = @discrimvalue@;
  _pd__default = @isDefault@;
  _pd_@name@ = _value;
}
"""

union_basic = """\
@type@ @name@ () const { return _pd_@name@; }
void @name@ (@type@  _value) {
  _pd__initialised = 1;
  _pd__d = @discrimvalue@;
  _pd__default = @isDefault@;
  _pd_@name@ = _value;
}
"""

union_string = """\
const char * @name@ () const { return (const char*) _pd_@name@; }
void @name@(char* _value) {
  _pd__initialised = 1;
  _pd__d = @discrimvalue@;
  _pd__default = @isDefault@;
  _pd_@name@ = _value;
}
void @name@(const char*  _value) {
  _pd__initialised = 1;
  _pd__d = @discrimvalue@;
  _pd__default = @isDefault@;
  _pd_@name@ = _value;
}
void @name@(const ::CORBA::String_var& _value) {
  _pd__initialised = 1;
  _pd__d = @discrimvalue@;
  _pd__default = @isDefault@;
  _pd_@name@ = _value;
}
void @name@(const ::CORBA::String_member& _value) {
  _pd__initialised = 1;
  _pd__d = @discrimvalue@;
  _pd__default = @isDefault@;
  _pd_@name@ = _value;
}
"""

union_wstring = """\
const ::CORBA::WChar * @name@ () const {
    return (const ::CORBA::WChar*) _pd_@name@;
}
void @name@(::CORBA::WChar* _value) {
  _pd__initialised = 1;
  _pd__d = @discrimvalue@;
  _pd__default = @isDefault@;
  _pd_@name@ = _value;
}
void @name@(const ::CORBA::WChar*  _value) {
  _pd__initialised = 1;
  _pd__d = @discrimvalue@;
  _pd__default = @isDefault@;
  _pd_@name@ = _value;
}
void @name@(const ::CORBA::WString_var& _value) {
  _pd__initialised = 1;
  _pd__d = @discrimvalue@;
  _pd__default = @isDefault@;
  _pd_@name@ = _value;
}
void @name@(const ::CORBA::WString_member& _value) {
  _pd__initialised = 1;
  _pd__d = @discrimvalue@;
  _pd__default = @isDefault@;
  _pd_@name@ = _value;
}
"""


union_objref = """\
@ptr_name@ @member@ () const { return _pd_@member@._ptr; }
void @member@(@ptr_name@ _value) {
  _pd__initialised = 1;
  _pd__d = @discrimvalue@;
  _pd__default = @isDefault@;
  @Helper_name@::duplicate(_value);
  _pd_@member@ = _value;
}
void @member@(const @memtype@& _value) {
  _pd__initialised = 1;
  _pd__d = @discrimvalue@;
  _pd__default = @isDefault@;
  _pd_@member@ = _value;
}
void @member@(const @var_name@&  _value) {
  _pd__initialised = 1;
  _pd__d = @discrimvalue@;
  _pd__default = @isDefault@;
  _pd_@member@ = _value;
}
"""

union_constructed = """\
const @type@ &@name@ () const { return _pd_@name@; }
@type@ &@name@ () { return _pd_@name@; }
void @name@ (const @type@& _value) {
  _pd__initialised = 1;
  _pd__d = @discrimvalue@;
  _pd__default = @isDefault@;
  _pd_@name@ = _value;
}
"""

union_sequence = """\
typedef @sequence_template@ _@member@_seq;
const _@member@_seq& @member@ () const { return _pd_@member@; }
_@member@_seq& @member@ () { return _pd_@member@; }
void @member@ (const _@member@_seq& _value) {
  _pd__initialised = 1;
  _pd__d = @discrimvalue@;
  _pd__default = @isDefault@;
  _pd_@member@ = _value;
}
"""

union_value = """\
@type@* @member@() const { return _pd_@member@.in(); }
void @member@(@type@* _value) {
  _pd__initialised = 1;
  _pd__d = @discrimvalue@;
  _pd__default = @isDefault@;
  ::CORBA::add_ref(_value);
  _pd_@member@ = _value;
}
"""


union_member = """\
@type@ _pd_@name@@dims@;
"""

union_forward = """\
class @name@;
"""

##
## Enum
##
enum = """\
enum @name@ { @memberlist@ /*, __max_@name@=0xffffffff */ };
typedef @name@& @name@_out;
"""

##
## Const
##
const_inclass_isinteger = """\
static _core_attr const @type@ @name@ _init_in_cldecl_( = @val@ );
"""
const_inclass_notinteger = """\
static _core_attr const @type@ @name@;
"""
const_outsideclass_isinteger = """\
_CORBA_@where@_VARINT const @type@ @name@ _init_in_decl_( = @val@ );
"""
const_outsideclass_notinteger = """\
_CORBA_@where@_VAR _core_attr const @type@ @name@;
"""

##
## Typecode_ptr
##
typecode = """\
@qualifier@ _dyn_attr const ::CORBA::TypeCode_ptr _tc_@name@;
"""


##
## Operators
##
any_struct = """\
extern void operator<<=(::CORBA::Any& _a, const @fqname@& _s);
extern void operator<<=(::CORBA::Any& _a, @fqname@* _sp);
extern _CORBA_Boolean operator>>=(const ::CORBA::Any& _a, @fqname@*& _sp);
extern _CORBA_Boolean operator>>=(const ::CORBA::Any& _a, const @fqname@*& _sp);
"""

any_exception = """\
void operator<<=(::CORBA::Any& _a, const @fqname@& _s);
void operator<<=(::CORBA::Any& _a, const @fqname@* _sp);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, const @fqname@*& _sp);
"""

any_union = """\
void operator<<=(::CORBA::Any& _a, const @fqname@& _s);
void operator<<=(::CORBA::Any& _a, @fqname@* _sp);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, const @fqname@*& _sp);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, @fqname@*& _sp);
"""

any_enum = """\
void operator<<=(::CORBA::Any& _a, @name@ _s);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, @name@& _s);
"""

any_interface = """\
void operator<<=(::CORBA::Any& _a, @fqname@_ptr _s);
void operator<<=(::CORBA::Any& _a, @fqname@_ptr* _s);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, @fqname@_ptr& _s);
"""

any_array_declarator = """\
void operator<<=(::CORBA::Any& _a, const @fqname@_forany& _s);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, @fqname@_forany& _s);
"""

any_sequence = """\
void operator<<=(::CORBA::Any& _a, const @fqname@& _s);
void operator<<=(::CORBA::Any& _a, @fqname@* _sp);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, @fqname@*& _sp);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, const @fqname@*& _sp);
"""

any_value = """\
void operator<<=(::CORBA::Any& _a, @fqname@* _s);
void operator<<=(::CORBA::Any& _a, @fqname@** _s);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, @fqname@*& _s);
"""


enum_operators = """\
inline void operator >>=(@name@ _e, cdrStream& s) {
  ::operator>>=((::CORBA::ULong)_e, s);
}

inline void operator <<= (@name@& _e, cdrStream& s) {
  ::CORBA::ULong @private_prefix@_e;
  ::operator<<=(@private_prefix@_e,s);
  if (@private_prefix@_e <= @last_item@) {
    _e = (@name@) @private_prefix@_e;
  }
  else {
    OMNIORB_THROW(MARSHAL,_OMNI_NS(MARSHAL_InvalidEnumValue),
                  (::CORBA::CompletionStatus)s.completion());
  }
}
"""

  
##
## tie template
##
tie_template = """\
template <class _omniT>
class @tie_name@ : public virtual @inherits@
{
public:
  @tie_name@(_omniT& t)
    : pd_obj(&t), pd_poa(0), pd_rel(0) {}
  @tie_name@(_omniT& t, ::PortableServer::POA_ptr p)
    : pd_obj(&t), pd_poa(p), pd_rel(0) {}
  @tie_name@(_omniT* t, _CORBA_Boolean r=1)
    : pd_obj(t), pd_poa(0), pd_rel(r) {}
  @tie_name@(_omniT* t, ::PortableServer::POA_ptr p,_CORBA_Boolean r=1)
    : pd_obj(t), pd_poa(p), pd_rel(r) {}
  ~@tie_name@() {
    if( pd_poa )  ::CORBA::release(pd_poa);
    if( pd_rel )  delete pd_obj;
  }

  _omniT* _tied_object() { return pd_obj; }

  void _tied_object(_omniT& t) {
    if( pd_rel )  delete pd_obj;
    pd_obj = &t;
    pd_rel = 0;
  }

  void _tied_object(_omniT* t, _CORBA_Boolean r=1) {
    if( pd_rel )  delete pd_obj;
    pd_obj = t;
    pd_rel = r;
  }

  _CORBA_Boolean _is_owner()        { return pd_rel; }
  void _is_owner(_CORBA_Boolean io) { pd_rel = io;   }

  ::PortableServer::POA_ptr _default_POA() {
    if( !pd_poa )  return ::PortableServer::POA::_the_root_poa();
    else           return ::PortableServer::POA::_duplicate(pd_poa);
  }

  @callables@

private:
  _omniT*                   pd_obj;
  ::PortableServer::POA_ptr pd_poa;
  _CORBA_Boolean            pd_rel;
};
"""

tie_template_old = """\
template <class _omniT, _CORBA_Boolean release>
class @tie_name@ : public virtual @inherits@
{
public:
  @tie_name@(_omniT& t)
    : pd_obj(&t), pd_rel(release) {}
  @tie_name@(_omniT* t)
    : pd_obj(t),  pd_rel(release) {}
  ~@tie_name@() {
    if( pd_rel )  delete pd_obj;
  }

  @callables@

private:
  _omniT*                  pd_obj;
  _CORBA_Boolean           pd_rel;
};
"""

##
## tc_string
##
tcstring = """\
#if !defined(___tc_string_@n@__) && !defined(DISABLE_Unnamed_Bounded_String_TC)
#define ___tc_string_@n@__
_CORBA_GLOBAL_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_string_@n@;
#endif
"""

##
## tc_wstring
##
tcwstring = """\
#if !defined(___tc_wstring_@n@__) && !defined(DISABLE_Unnamed_Bounded_WString_TC)
#define ___tc_wstring_@n@__
_CORBA_GLOBAL_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_wstring_@n@;
#endif
"""
