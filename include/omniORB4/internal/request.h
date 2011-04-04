// -*- Mode: C++; -*-
//                            Package   : omniORB2
// request.h                  Created on: 9/1998
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
//

#ifndef __REQUEST_H__
#define __REQUEST_H__

#ifndef __PSEUDO_H__
#include <pseudo.h>
#endif

OMNI_NAMESPACE_BEGIN(omni)

class DeferredRequest;

class RequestImpl : public CORBA::Request, public PseudoObjBase {
public:
  RequestImpl(CORBA::Object_ptr target, const char* operation);

  RequestImpl(CORBA::Object_ptr target, const char* operation,
	      CORBA::Context_ptr context, CORBA::NVList_ptr arguments,
	      CORBA::NamedValue_ptr result);

  RequestImpl(CORBA::Object_ptr target, const char* operation,
	      CORBA::Context_ptr context, CORBA::NVList_ptr arguments,
	      CORBA::NamedValue_ptr result,
	      CORBA::ExceptionList_ptr exceptions,
	      CORBA::ContextList_ptr contexts);

  virtual ~RequestImpl();

  virtual CORBA::Object_ptr        target() const;
  virtual const char*              operation() const;
  virtual CORBA::NVList_ptr        arguments();
  virtual CORBA::NamedValue_ptr    result();
  virtual CORBA::Environment_ptr   env();
  virtual CORBA::ExceptionList_ptr exceptions();
  virtual CORBA::ContextList_ptr   contexts();
  virtual CORBA::Context_ptr       ctx() const;
  virtual void                     ctx(CORBA::Context_ptr);
  virtual CORBA::Any& add_in_arg();
  virtual CORBA::Any& add_in_arg(const char* name);
  virtual CORBA::Any& add_inout_arg();
  virtual CORBA::Any& add_inout_arg(const char* name);
  virtual CORBA::Any& add_out_arg();
  virtual CORBA::Any& add_out_arg(const char* name);
  virtual void        set_return_type(CORBA::TypeCode_ptr tc);
  virtual CORBA::Any& return_value();
  virtual void 	      invoke();
  virtual void 	      send_oneway();
  virtual void 	      send_deferred();
  virtual void 	      get_response();
  virtual CORBA::Boolean poll_response();
  virtual CORBA::Boolean NP_is_nil() const;
  virtual CORBA::Request_ptr NP_duplicate();

  inline void storeExceptionInEnv() {
    pd_environment->exception(pd_sysExceptionToThrow);
    pd_sysExceptionToThrow = 0;
  }

  void marshalArgs(cdrStream&);
  void unmarshalResults(cdrStream&);
  CORBA::Boolean unmarshalUserException(cdrStream&, const char* repoId);

  void deferred_invoke();

private:
  enum State {
    RS_READY,       // Not used yet
    RS_DONE,        // Result got
    RS_DEFERRED,    // Sent deferred
    RS_POLLED_DONE  // Found to be done by poll_response() but not yet got
  };

  CORBA::Object_var        pd_target;
  CORBA::String_var        pd_operation;
  CORBA::NVList_var        pd_arguments;
  CORBA::Boolean           pd_i_own_arguments;
  CORBA::NamedValue_var    pd_result;
  CORBA::Boolean           pd_i_own_result;
  CORBA::Environment_var   pd_environment;
  CORBA::ExceptionList_var pd_exceptions;  // may be nil
  CORBA::ContextList_var   pd_contexts;    // may be nil
  CORBA::Context_var       pd_context;     // may be nil
  State                    pd_state;
  DeferredRequest*         pd_deferredRequest;

  CORBA::Exception*        pd_sysExceptionToThrow;
  // If non-zero, then the exception should be thrown next
  // time one of the public methods (other than poll_response)
  // is called.

};

OMNI_NAMESPACE_END(omni)


#endif  // __REQUEST_H__
