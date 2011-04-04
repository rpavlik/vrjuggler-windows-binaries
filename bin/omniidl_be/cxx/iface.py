# -*- python -*-
#                           Package   : omniidl
# iface.py                  Created on: 2000/8/10
#			    Author    : David Scott (djs)
#
#    Copyright (C) 2002-2008 Apasphere Ltd
#    Copyright (C) 2000 AT&T Laboratories Cambridge
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
#   Code associated with IDL interfaces

# $Id: iface.py,v 1.1.6.18 2009/05/06 16:15:52 dgrisby Exp $
# $Log: iface.py,v $
# Revision 1.1.6.18  2009/05/06 16:15:52  dgrisby
# Update lots of copyright notices.
#
# Revision 1.1.6.17  2008/12/30 15:38:27  dgrisby
# Scope change broke structs defined in interfaces that use them.
#
# Revision 1.1.6.16  2008/12/29 18:03:34  dgrisby
# More C++ backend scope errors. Thanks Gellule Xg.
#
# Revision 1.1.6.15  2007/12/05 11:15:58  dgrisby
# Incorrect generated code involving ::CORBA::AbstractBase.
#
# Revision 1.1.6.14  2007/09/19 14:16:08  dgrisby
# Avoid namespace clashes if IDL defines modules named CORBA.
#
# Revision 1.1.6.13  2006/01/24 11:46:03  dgrisby
# Interfaces inheriting from a typedef caused an omniidl compiler error.
# Thanks Renzo Tomaselli.
#
# Revision 1.1.6.12  2005/11/18 18:23:06  dgrisby
# New -Wbimpl_mapping option.
#
# Revision 1.1.6.11  2005/11/14 11:02:16  dgrisby
# Local interface fixes.
#
# Revision 1.1.6.10  2005/11/09 12:22:17  dgrisby
# Local interfaces support.
#
# Revision 1.1.6.9  2005/09/19 15:36:35  dgrisby
# Refcount shortcut now throws INV_OBJREF when the servant is
# deactivated, rather than deactivating the shortcut, which could lead
# to a race condition.
#
# Revision 1.1.6.8  2005/09/05 17:22:09  dgrisby
# Reference counted local call shortcut.
#
# Revision 1.1.6.7  2005/08/16 13:51:21  dgrisby
# Problems with valuetype / abstract interface C++ mapping.
#
# Revision 1.1.6.6  2005/01/06 23:09:50  dgrisby
# Big merge from omni4_0_develop.
#
# Revision 1.1.6.5  2005/01/06 16:35:18  dgrisby
# Narrowing for abstract interfaces.
#
# Revision 1.1.6.4  2004/10/13 17:58:22  dgrisby
# Abstract interfaces support; values support interfaces; value bug fixes.
#
# Revision 1.1.6.3  2003/11/06 11:56:56  dgrisby
# Yet more valuetype. Plain valuetype and abstract valuetype are now working.
#
# Revision 1.1.6.2  2003/10/23 11:25:54  dgrisby
# More valuetype support.
#
# Revision 1.1.6.1  2003/03/23 21:02:41  dgrisby
# Start of omniORB 4.1.x development branch.
#
# Revision 1.1.4.12  2003/03/03 15:02:30  dgrisby
# -Wbvirtual_objref option went astray. Thanks Malge Nishant.
#
# Revision 1.1.4.11  2002/08/16 15:56:27  dgrisby
# Bug in generated code with evil IDL that uses the same parameter
# names as type names.
#
# Revision 1.1.4.10  2001/11/08 16:33:51  dpg1
# Local servant POA shortcut policy.
#
# Revision 1.1.4.9  2001/11/07 15:45:53  dpg1
# Faster _ptrToInterface/_ptrToObjRef in common cases.
#
# Revision 1.1.4.8  2001/08/15 10:26:10  dpg1
# New object table behaviour, correct POA semantics.
#
# Revision 1.1.4.7  2001/07/25 13:40:52  dpg1
# Suppress compiler warning about unused variable in _dispatch() for
# empty interfaces.
#
# Revision 1.1.4.6  2001/07/25 11:42:15  dpg1
# Generate correct code for operation parameters whose names clash with
# C++ keywords.
#
# Revision 1.1.4.5  2001/06/08 17:12:13  dpg1
# Merge all the bug fixes from omni3_develop.
#
# Revision 1.1.4.4  2001/01/25 13:09:11  sll
# Fixed up cxx backend to stop it from dying when a relative
# path name is given to the -p option of omniidl.
#
# Revision 1.1.4.3  2000/11/07 18:27:51  sll
# Pass environment to out_objrefcall.
#
# Revision 1.1.4.2  2000/11/03 19:30:21  sll
# Rationalise code generation. Consolidate all code that use call descriptors
# into the CallDescriptor class.
#
# Revision 1.1.4.1  2000/10/12 15:37:47  sll
# Updated from omni3_1_develop.
#
# Revision 1.1.2.2  2000/09/14 16:03:02  djs
# Remodularised C++ descriptor name generator
# Bug in listing all inherited interfaces if one is a forward
# repoID munging function now handles #pragma ID in bootstrap.idl
# Naming environments generating code now copes with new IDL AST types
# Modified type utility functions
# Minor tidying
#
# Revision 1.1.2.1  2000/08/21 11:34:34  djs
# Lots of omniidl/C++ backend changes
#

# o Keep related code in one place
# o Expose internals at a finer granularity than before (useful for
#   overriding one aspect (eg _objref class for AMI))

import string

from omniidl import idlast, idltype
from omniidl_be.cxx import types, id, call, ast, cxx, output, config, descriptor
# from omniidl_be.cxx import header
# from omniidl_be.cxx import skel
# XXX it seems that the above import fails when this file is import by
#     cxx.header.defs AND a relative patch -p argument is given to omniidl
#     Use the following import works.
import omniidl_be.cxx.skel
import omniidl_be.cxx.header


# Interface is a wrapper around an IDL interface
#  .callables():   get a list of Callable objects representing the operations
#                  and attributes
#  .inherits():    get a list of all directly inherited interfaces
#  .allInherits(): get all inherited interfaces (using a breadth first search)
#  .name():        return the IDL fully scoped name (as an id.Name)
#  .environment(): returns the IDL environment where this interface was
#                  declared
class Interface:
  """Wrapper around an IDL interface"""
  def __init__(self, node):
    self._node = node
    self._environment = id.lookup(node)
    self._node_name = id.Name(node.scopedName())

  def callables(self):
    """Return a list of Callable objects representing the combined operations
       and attributes for this interface"""
    
    if hasattr(self, "_callables"):
      return self._callables
    
    # build a list of all the Callable objects
    # The old backend processed all operations first
    # (FIXME: duplicate for the sake of easy checking)
    self._callables = []

    for c in self._node.callables():
      if isinstance(c, idlast.Operation):
        self._callables.append(call.operation(self, c))
        
    for c in self._node.callables():
      if isinstance(c, idlast.Attribute):
        self._callables = self._callables + call.read_attributes(self, c)
        if c.readonly(): continue
        self._callables = self._callables + call.write_attributes(self, c)
      
    return self._callables

  def inherits(self):
    return map(lambda x:Interface(x), self._node.fullDecl().inherits())

  def allInherits(self):
    return map(lambda x:Interface(x), ast.allInherits(self._node))

  def local(self):
    return self._node.fullDecl().local()

  def abstract(self):
    return self._node.fullDecl().abstract()

  def name(self):
    return self._node_name
    
  def environment(self):
    return self._environment
  
  
_classes = {}
_proxy_call_descriptors = {}

def instance(name):
  if _classes.has_key(name):
    return _classes[name]

  instance = eval(name)
  _classes[name] = instance
  return instance

def register_class(name, cl):
  _classes[name] = cl


# Class associated with an IDL interface.
#  .interface():   return the associated Interface object
#  .methods():     return a list of Method objects
#  .environment(): return the IDL environment associated with the interface
class Class(cxx.Class):
  def __init__(self, interface):
    assert isinstance(interface, Interface)
    cxx.Class.__init__(self, interface.name())
    
    self._interface = interface
    self._environment = interface.environment()
    self._methods = []
    self._callables = {}

  def interface(self):   return self._interface
  def methods(self):     return self._methods
  def environment(self): return self._environment


class _objref_Method(cxx.Method):
  def __init__(self, callable, parent_class):
    assert isinstance(callable, call.Callable)
    self._callable = callable
    self._parent_class = parent_class
    self.from_Callable()

  def callable(self): return self._callable

  def from_Callable(self):
    use_out = not config.state["Impl Mapping"]
    self._from_Callable(use_out = use_out)

  def _from_Callable(self, use_out):
    # Grab the IDL environment
    ifc = self.callable().interface()
    environment = ifc.environment().enter("_objref_" + ifc.name().simple())

    # Kept as a type object because in .cc part the _return_ type
    # must be fully qualified.
    self._return_type = types.Type(self.callable().returnType())

    # Parameters are always relative, both in .hh and .cc
    (param_types, param_names) = ([], [])
    for p in self.callable().parameters():
      pType = types.Type(p.paramType())
      direction = types.direction(p)
      param_types.append(pType.op(direction, environment,
                                  use_out = use_out))

      # Special ugly case. If the IDL says something like (in foo::bar
      # bar), the parameter name may be the same as the relative type
      # name. We mangle the parameter name if this happens.

      typeBase = pType.base(environment)
      ident    = id.mapID(p.identifier())

      if typeBase == ident:
        ident = "_" + ident

      param_names.append(ident)
      
    # an operation has optional context
    if self.callable().contexts() != []:
      param_types.append("::CORBA::Context_ptr")
      param_names.append("_ctxt")

    self._arg_types = param_types
    self._arg_names = param_names
    self._name = self.callable().method_name()


class _impl_Method(_objref_Method):
  def __init__(self, callable, parent_class):
    _objref_Method.__init__(self, callable, parent_class)

  def from_Callable(self):
    self._from_Callable(use_out = 0)


class I_Helper(Class):
  def __init__(self, I):
    Class.__init__(self, I)
    self._name = self._name.suffix("_Helper")

  def hh(self, stream):
    class_sk_name = ""
    if config.state['BOA Skeletons']:
      class_sk_name = "class " + \
                      self.interface().name().prefix("_sk_").simple() + ";"

    if self.interface().abstract():
      helper_tpl = omniidl_be.cxx.header.template.abstract_interface_Helper
    elif self.interface().local():
      helper_tpl = omniidl_be.cxx.header.template.local_interface_Helper
    else:
      helper_tpl = omniidl_be.cxx.header.template.interface_Helper

    stream.out(helper_tpl,
               class_sk_name = class_sk_name,
               name = self.interface().name().simple(),
               guard = self.interface().name().guard())

  def cc(self, stream):
    stream.out(omniidl_be.cxx.skel.template.interface_Helper,
               name = self.interface().name().fullyQualify())


class I(Class):
  def __init__(self, i, other_idl):
    Class.__init__(self, i)
    self._other_idl = other_idl

  def hh(self, stream):
    if self.interface().abstract():

      for callable in self.interface().callables():
        method = _impl_Method(callable, self)
        self._methods.append(method)
        self._callables[method] = callable

      methodl = []
      for method in self.methods():
          methodl.append(method.hh(virtual = 1, pure = 1))

      inh = self.interface().inherits()
      if inh:
        inheritl = []
        for i in inh:
          iname = i.name().unambiguous(self._environment)
          inheritl.append("public virtual " + iname)
      else:
        inheritl = [ "public virtual ::CORBA::AbstractBase" ]

      stream.out(omniidl_be.cxx.header.template.abstract_interface_type,
                 name=self.interface().name().simple(),
                 Other_IDL = self._other_idl,
                 inherits = string.join(inheritl, ",\n"),
                 operations = string.join(methodl, "\n"))

    elif self.interface().local():
      abstract_base = 0
      for i in self.interface().allInherits():
        if i.abstract():
          abstract_base = 1
          break

      if abstract_base:
        abstract_narrows = omniidl_be.cxx.header.template.\
                           interface_abstract_narrows
      else:
        abstract_narrows = ""

      for callable in self.interface().callables():
        method = _impl_Method(callable, self)
        self._methods.append(method)
        self._callables[method] = callable

      # Override methods from inherited non-local interfaces
      for i in self.interface().allInherits():
        if not i.local():
          for c in i.callables():
            # Make new callable with ref to this interface instead of
            # inherited interface
            callable = call.Callable(self.interface(),
                                     c.operation_name(),
                                     c.method_name(),
                                     c.returnType(),
                                     c.parameters(),
                                     c.oneway(),
                                     c.raises(),
                                     c.contexts())

            method = _impl_Method(callable, self)
            self._methods.append(method)
            self._callables[method] = callable

      bmethodl = []
      nmethodl = []
      for method in self.methods():
          bmethodl.append(method.hh(virtual = 1, pure = 1))
          nmethodl.append(method.hh(virtual = 1, pure = 0))

      local_base = 0
      inheritl   = []
      ninheritl  = []

      for i in self.interface().inherits():
        if i.local():
          local_base = 1
          iname = i.name().unambiguous(self._environment)
          niname = i.name().prefix("_nil_").unambiguous(self._environment)
          ninheritl.append(niname)
        else:
          iname = i.name().prefix("_objref_").unambiguous(self._environment)

        inheritl.append("public virtual " + iname)

      if not local_base:
        inheritl.append("public virtual ::CORBA::LocalObject")

      if ninheritl:
        nil_inherits = string.join(ninheritl, ",\n") + ","
      else:
        nil_inherits = ""

      stream.out(omniidl_be.cxx.header.template.local_interface_type,
                 name=self.interface().name().simple(),
                 abstract_narrows = abstract_narrows,
                 Other_IDL = self._other_idl,
                 inherits = string.join(inheritl, ",\n"),
                 operations = string.join(bmethodl, "\n"),
                 nil_operations = string.join(nmethodl, "\n"),
                 nil_inherits = nil_inherits)

    else:
      abstract_base = 0
      for i in self.interface().allInherits():
        if i.abstract():
          abstract_base = 1
          break

      if abstract_base:
        abstract_narrows = omniidl_be.cxx.header.template.\
                           interface_abstract_narrows
      else:
        abstract_narrows = ""

      stream.out(omniidl_be.cxx.header.template.interface_type,
                 name=self.interface().name().simple(),
                 abstract_narrows = abstract_narrows,
                 Other_IDL = self._other_idl)



class _objref_I(Class):
  def __init__(self, I):
    Class.__init__(self, I)
    self._name = self._name.prefix("_objref_")

    # In abstract interfaces, signatures are like _impl classes, not
    # normal _objref classes.
    if self.interface().abstract():
      cls = _impl_Method
    else:
      cls = _objref_Method

    for callable in self.interface().callables():
      method = cls(callable, self)
      self._methods.append(method)
      self._callables[method] = callable


  def hh(self, stream):
    # build the inheritance list

    objref_inherits = []

    inh = self.interface().inherits()
    if inh:
      for i in inh:
        objref_inherited_name = i.name().prefix("_objref_")
        uname = objref_inherited_name.unambiguous(self._environment)
        objref_inherits.append("public virtual " + uname)
    else:
      if self.interface().abstract():
        objref_inherits = [ "public virtual ::CORBA::_omni_AbstractBaseObjref",
                            "public virtual omniObjRef" ]
      else:
        objref_inherits = [ "public virtual ::CORBA::Object",
                            "public virtual omniObjRef" ]

    if self.interface().abstract():
      objref_inherits.append("public virtual " +
                             self.interface().name().simple())

    methods = []
    for method in self.methods():
      if config.state['Virtual Objref Methods']:
        methods.append(method.hh(virtual = 1, pure = 0))
      else:
        methods.append(method.hh())

    if config.state['Shortcut']:
      shortcut = output.StringStream()
      shortcut.out(omniidl_be.cxx.header.template.interface_shortcut,
                   name = self.interface().name().simple())
      shortcut = str(shortcut)
      init_shortcut = ": _shortcut(0)"
    else:
      shortcut = ""
      init_shortcut = ""

    stream.out(omniidl_be.cxx.header.template.interface_objref,
               name = self.interface().name().simple(),
               inherits = string.join(objref_inherits, ",\n"),
               operations = string.join(methods, "\n"),
               shortcut = shortcut,
               init_shortcut = init_shortcut)

  def cc(self, stream):

    def _ptrToObjRef_ptr(self = self, stream = stream):
      has_abstract = self.interface().abstract()

      for i in self.interface().allInherits():
        if i.abstract(): has_abstract = 1

        stream.out(omniidl_be.cxx.skel.template.interface_objref_repoID_ptr,
                   inherits_fqname = i.name().fullyQualify())

      if has_abstract:
        stream.out(omniidl_be.cxx.skel.template.interface_objref_repoID_ptr,
                   inherits_fqname = "CORBA::AbstractBase")

    def _ptrToObjRef_str(self = self, stream = stream):
      has_abstract = self.interface().abstract()

      for i in self.interface().allInherits():
        if i.abstract(): has_abstract = 1

        stream.out(omniidl_be.cxx.skel.template.interface_objref_repoID_str,
                   inherits_fqname = i.name().fullyQualify())

      if has_abstract:
        stream.out(omniidl_be.cxx.skel.template.interface_objref_repoID_str,
                   inherits_fqname = "CORBA::AbstractBase")

    # build the inherits list
    
    inherits_str_list = []
    for i in self.interface().inherits():
      objref_name = i.name().prefix("_objref_")

      objref_str = objref_name.unambiguous(self._environment)

      if objref_name.needFlatName(self._environment):
        objref_str = objref_name.flatName()

      this_inherits_str = objref_str + "(ior, id)"

      # FIXME:
      # The powerpc-aix OMNIORB_BASE_CTOR workaround still works here
      # (in precendence to the flattened base name) but lacking a
      # powerpc-aix test machine I can't properly test it. It's probably
      # not required any more.
      if objref_name.relName(self._environment) != i.name().fullName():
        prefix = []
        for x in objref_name.fullName():
          if x == "_objref_" + objref_name.relName(self._environment)[0]:
            break
          prefix.append(x)
        inherits_scope_prefix = string.join(prefix, "::") + "::"
        this_inherits_str = "OMNIORB_BASE_CTOR(" + inherits_scope_prefix +\
                            ")" + this_inherits_str

      inherits_str_list.append(this_inherits_str)

    inherits_str = string.join(inherits_str_list, ",\n")
    if inherits_str:
      comma = ","
    else:
      comma = ""

    if config.state['Shortcut']:
      inherits_str  = inherits_str + ","
      init_shortcut = "_shortcut(0)"
    else:
      init_shortcut = ""

    if config.state['Shortcut'] == 2:
      release_shortcut = omniidl_be.cxx.skel.template.\
                         interface_release_refcount_shortcut
    else:
      release_shortcut = ""

    stream.out(omniidl_be.cxx.skel.template.interface_objref,
               name = self.interface().name().fullyQualify(),
               fq_objref_name = self.name().fullyQualify(),
               objref_name = self.name().simple(),
               inherits_str = inherits_str,
               comma = comma,
               _ptrToObjRef_ptr = _ptrToObjRef_ptr,
               _ptrToObjRef_str = _ptrToObjRef_str,
               init_shortcut = init_shortcut,
               release_shortcut = release_shortcut)

    shortcut_mode = config.state['Shortcut']

    if shortcut_mode:
      inherited = output.StringStream()
      for i in self.interface().inherits():
        objref_name = i.name().prefix("_objref_")

        objref_str = objref_name.unambiguous(self._environment)

        if objref_name.needFlatName(self._environment):
          objref_str = objref_name.flatName()

        inherited.out(omniidl_be.cxx.skel.template.interface_shortcut_inh,
                      parent=objref_str)

      if shortcut_mode == 1:
        tmpl = omniidl_be.cxx.skel.template.interface_shortcut
      else:
        tmpl = omniidl_be.cxx.skel.template.interface_shortcut_refcount
        
      stream.out(tmpl,
                 name = self.interface().name().fullyQualify(),
                 basename = self.interface().name().simple(),
                 fq_objref_name = self.name().fullyQualify(),
                 inherited = str(inherited))
      
    for method in self.methods():
      callable = self._callables[method]

      # signature is a text string form of the complete operation signature
      signature = callable.signature()

      # we only need one descriptor for each _signature_ (not operation)
      if _proxy_call_descriptors.has_key(signature):
        call_descriptor = _proxy_call_descriptors[signature]
      else:
        call_descriptor = call.CallDescriptor(signature,callable)
        call_descriptor.out_desc(stream)
        _proxy_call_descriptors[signature] = call_descriptor

      # produce a localcall function
      node_name = self.interface().name()
      localcall_fn = descriptor.local_callback_fn(node_name,
                                                  callable.operation_name(),
                                                  signature)
      call_descriptor.out_localcall(stream,node_name,callable.method_name(),
                                    localcall_fn)

      # produce member function for this operation/attribute.
      body = output.StringStream()

      argnames = method.arg_names()

      if config.state['Shortcut']:
        if method.return_type().kind() != idltype.tk_void:
          callreturn = "return "
          voidreturn = ""
        else:
          callreturn = ""
          voidreturn = " return;"

        objref_class = method.parent_class()
        interface = objref_class.interface()
        implname = interface.name().prefix("_impl_").unambiguous(self._environment)

        if config.state['Shortcut'] == 2:
          tmpl = omniidl_be.cxx.skel.template.\
                 interface_operation_shortcut_refcount
        else:
          tmpl = omniidl_be.cxx.skel.template.\
                 interface_operation_shortcut
        
        body.out(tmpl,
                 impl_type = implname,
                 callreturn = callreturn,
                 voidreturn = voidreturn,
                 args = string.join(argnames, ", "),
                 name = method.name())


      intf_env = self._environment.enter("_objref_" +
                                         self.interface().name().simple())

      call_descriptor.out_objrefcall(body,
                                     callable.operation_name(),
                                     argnames,
                                     localcall_fn,
                                     intf_env)
      method.cc(stream, body)


class _nil_I(Class):
  def __init__(self, I):
    Class.__init__(self, I)
    self._name = self._name.prefix("_nil_")

    for callable in self.interface().callables():
      method = _impl_Method(callable, self)
      self._methods.append(method)
      self._callables[method] = callable

    for i in self.interface().allInherits():
      if not i.local():
        for c in i.callables():
          # Make new callable with ref to this interface instead of
          # inherited interface
          callable = call.Callable(self.interface(),
                                   c.operation_name(),
                                   c.method_name(),
                                   c.returnType(),
                                   c.parameters(),
                                   c.oneway(),
                                   c.raises(),
                                   c.contexts())

          method = _impl_Method(callable, self)
          self._methods.append(method)
          self._callables[method] = callable

  def hh(self, stream):
    pass

  def cc(self, stream):

    def _ptrToObjRef_ptr(self = self, stream = stream):
      has_abstract = 0

      for i in self.interface().allInherits():
        if i.abstract(): has_abstract = 1

        stream.out(omniidl_be.cxx.skel.template.interface_objref_repoID_ptr,
                   inherits_fqname = i.name().fullyQualify())

      stream.out(omniidl_be.cxx.skel.template.interface_objref_repoID_ptr,
                 inherits_fqname = "CORBA::LocalObject")

      if has_abstract:
        stream.out(omniidl_be.cxx.skel.template.interface_objref_repoID_ptr,
                   inherits_fqname = "CORBA::AbstractBase")

    def _ptrToObjRef_str(self = self, stream = stream):
      has_abstract = 0

      for i in self.interface().allInherits():
        if i.abstract(): has_abstract = 1

        stream.out(omniidl_be.cxx.skel.template.interface_objref_repoID_str,
                   inherits_fqname = i.name().fullyQualify())

      stream.out(omniidl_be.cxx.skel.template.interface_objref_repoID_str,
                 inherits_fqname = "CORBA::LocalObject")

      if has_abstract:
        stream.out(omniidl_be.cxx.skel.template.interface_objref_repoID_str,
                   inherits_fqname = "CORBA::AbstractBase")

    stream.out(omniidl_be.cxx.skel.template.local_interface_objref,
               name = self.interface().name().fullyQualify(),
               sname = self.interface().name().simple(),
               fq_nil_name = self.name().fullyQualify(),
               nil_name = self.name().simple(),
               _ptrToObjRef_ptr = _ptrToObjRef_ptr,
               _ptrToObjRef_str = _ptrToObjRef_str)

    for method in self.methods():
      callable = self._callables[method]

      # signature is a text string form of the complete operation signature
      signature = callable.signature()

      # produce member function for this operation/attribute.
      body = output.StringStream()

      argnames = method.arg_names()

      body.out(omniidl_be.cxx.skel.template.local_interface_nil_operation)

      if not method.return_type().void():
        body.out(omniidl_be.cxx.skel.template.local_interface_nil_dummy_return,
                 method = method.name(),
                 args   = string.join(method.arg_names(),", "))
      
      method.cc(stream, body)
      stream.out("\n")



class _pof_I(Class):
  def __init__(self, I):
    Class.__init__(self, I)
    self._name = self._name.prefix("_pof_")

  def hh(self, stream):
    stream.out(omniidl_be.cxx.header.template.interface_pof,
               name = self.interface().name().simple())

  def cc(self, stream):
    inherits = output.StringStream()
    for i in self.interface().allInherits():
      ancestor = i.name().fullyQualify()
      inherits.out(omniidl_be.cxx.skel.template.interface_pof_repoID, inherited = ancestor)

    node_name = self.interface().name()
    objref_name = node_name.prefix("_objref_")
    pof_name = node_name.prefix("_pof_")
    stream.out(omniidl_be.cxx.skel.template.interface_pof,
               pof_name = pof_name.fullyQualify(),
               objref_fqname = objref_name.fullyQualify(),
               name = node_name.fullyQualify(),
               uname = pof_name.simple(),
               Other_repoIDs = inherits,
               idname = node_name.guard())
    

class _impl_I(Class):
  def __init__(self, I):
    Class.__init__(self, I)
    self._name = self._name.prefix("_impl_")

    for callable in self.interface().callables():
      method = _impl_Method(callable, self)
      self._methods.append(method)
      self._callables[method] = callable

  def hh(self, stream):
    # build the inheritance list
    environment = self._environment
    impl_inherits = []
    inherit_abstract = 0
    
    for i in self.interface().inherits():
      if i.abstract():
        inherit_abstract = 1

      impl_inherited_name = i.name().prefix("_impl_")
      uname = impl_inherited_name.unambiguous(environment)
      impl_inherits.append("public virtual " + uname)

    # if already inheriting, the base class will be present
    # (transitivity of the inherits-from relation)
    if self.interface().inherits() == []:
      impl_inherits   = [ "public virtual omniServant" ]

    methods = []
    for method in self.methods():
        methods.append(method.hh(virtual = 1, pure = 1))

    if self.interface().abstract():
      abstract = omniidl_be.cxx.header.template.interface_impl_abstract
    elif inherit_abstract:
      abstract = omniidl_be.cxx.header.template.interface_impl_not_abstract
    else:
      abstract = ""
        
    stream.out(omniidl_be.cxx.header.template.interface_impl,
               name = self.interface().name().simple(),
               inherits = string.join(impl_inherits, ",\n"),
               operations = string.join(methods, "\n"),
               abstract = abstract)

  def cc(self, stream):

    # Function to write the _impl_I::dispatch method
    def dispatch(self = self, stream = stream):
      # first check if method is from this interface
      dispatched = []
      for method in self.methods():
        callable = self._callables[method]
        operation_name = callable.operation_name()
        if operation_name not in dispatched:
          signature = callable.signature()
          call_descriptor = _proxy_call_descriptors[signature]
          localcall_fn = descriptor.local_callback_fn(self.interface().name(),
                                                      operation_name,signature)
          call_descriptor.out_implcall(stream,operation_name,localcall_fn)
          dispatched.append(operation_name)

      # next call dispatch methods of superclasses
      for i in self.interface().inherits():
        inherited_name = i.name().prefix("_impl_")
        impl_inherits = inherited_name.simple()
        # The MSVC workaround might be needed here again
        if inherited_name.needFlatName(self._environment):
          impl_inherits = inherited_name.flatName()
        stream.out(omniidl_be.cxx.skel.template.interface_impl_inherit_dispatch,
                   impl_inherited_name = impl_inherits)

    # For each of the inherited interfaces, check their repoId strings
    def _ptrToInterface_ptr(self = self, stream = stream):
      for i in self.interface().allInherits():
        inherited_name = i.name()
        impl_inherited_name = inherited_name.prefix("_impl_")

        # HERE: using the fully scoped name may fail on old MSVC
        # versions, but it is required by newer MSVC versions.
        # Marvellous.
        inherited_str      = inherited_name.fullyQualify()
        impl_inherited_str = impl_inherited_name.fullyQualify()

        stream.out(omniidl_be.cxx.skel.template.interface_impl_repoID_ptr,
                   inherited_name = inherited_str,
                   impl_inherited_name = impl_inherited_str)

    def _ptrToInterface_str(self = self, stream = stream):
      for i in self.interface().allInherits():
        inherited_name = i.name()
        impl_inherited_name = inherited_name.prefix("_impl_")

        inherited_str      = inherited_name.fullyQualify()
        impl_inherited_str = impl_inherited_name.fullyQualify()

        stream.out(omniidl_be.cxx.skel.template.interface_impl_repoID_str,
                   inherited_name = inherited_str,
                   impl_inherited_name = impl_inherited_str)

    node_name = self.interface().name()
    impl_name = node_name.prefix("_impl_")
    if self.methods():
      getopname = "const char* op = _handle.operation_name();"
    else:
      getopname = ""

    stream.out(omniidl_be.cxx.skel.template.interface_impl,
               impl_fqname = impl_name.fullyQualify(),
               uname = node_name.simple(),
               getopname = getopname,
               dispatch = dispatch,
               impl_name = impl_name.unambiguous(self._environment),
               _ptrToInterface_ptr = _ptrToInterface_ptr,
               _ptrToInterface_str = _ptrToInterface_str,
               name = node_name.fullyQualify())

    if not self.interface().abstract():
      # Are we derived from an abstract interface?
      inherit_abstract = 0
      for i in self.interface().inherits():
        if i.abstract():
          inherit_abstract = 1
          break
      if inherit_abstract:
        stream.out(omniidl_be.cxx.skel.template.interface_impl_not_abstract,
                   impl_fqname = impl_name.fullyQualify())
          

class _sk_I(Class):
  def __init__(self, I):
    Class.__init__(self, I)

  def hh(self, stream):
    # build the inheritance list
    environment = self._environment
    sk_inherits = []
    for i in self.interface().inherits():
      sk_inherited_name = i.name().prefix("_sk_")
      uname = sk_inherited_name.unambiguous(environment)
      sk_inherits.append("public virtual " + uname)

    # if already inheriting, the base class will be present
    # (transitivity of the inherits-from relation)
    if self.interface().inherits() == []:
      sk_inherits   = [ "public virtual omniOrbBoaServant" ]

    stream.out(omniidl_be.cxx.header.template.interface_sk,
               name = self.interface().name().simple(),
               inherits = string.join(sk_inherits, ",\n"))






