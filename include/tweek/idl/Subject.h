// This file is generated by omniidl (C++ backend)- omniORB_4_1. Do not edit.
#ifndef __Subject_hh__
#define __Subject_hh__

#ifndef __CORBA_H_EXTERNAL_GUARD__
#include <omniORB4/CORBA.h>
#endif

#ifndef  USE_stub_in_nt_dll
# define USE_stub_in_nt_dll_NOT_DEFINED_Subject
#endif
#ifndef  USE_core_stub_in_nt_dll
# define USE_core_stub_in_nt_dll_NOT_DEFINED_Subject
#endif
#ifndef  USE_dyn_stub_in_nt_dll
# define USE_dyn_stub_in_nt_dll_NOT_DEFINED_Subject
#endif



#ifndef __Observer_hh_EXTERNAL_GUARD__
#define __Observer_hh_EXTERNAL_GUARD__
#include <Observer.h>
#endif



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





_CORBA_MODULE tweek

_CORBA_MODULE_BEG

#ifndef __tweek_mSubject__
#define __tweek_mSubject__

  class Subject;
  class _objref_Subject;
  class _impl_Subject;
  
  typedef _objref_Subject* Subject_ptr;
  typedef Subject_ptr SubjectRef;

  class Subject_Helper {
  public:
    typedef Subject_ptr _ptr_type;

    static _ptr_type _nil();
    static _CORBA_Boolean is_nil(_ptr_type);
    static void release(_ptr_type);
    static void duplicate(_ptr_type);
    static void marshalObjRef(_ptr_type, cdrStream&);
    static _ptr_type unmarshalObjRef(cdrStream&);
  };

  typedef _CORBA_ObjRef_Var<_objref_Subject, Subject_Helper> Subject_var;
  typedef _CORBA_ObjRef_OUT_arg<_objref_Subject,Subject_Helper > Subject_out;

#endif

  // interface Subject
  class Subject {
  public:
    // Declarations for this interface type.
    typedef Subject_ptr _ptr_type;
    typedef Subject_var _var_type;

    static _ptr_type _duplicate(_ptr_type);
    static _ptr_type _narrow(::CORBA::Object_ptr);
    static _ptr_type _unchecked_narrow(::CORBA::Object_ptr);
    
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
    
  };

  class _objref_Subject :
    public virtual ::CORBA::Object,
    public virtual omniObjRef
  {
  public:
    void attach(::tweek::Observer_ptr o);
    void detach(::tweek::Observer_ptr o);
    void notify();

    inline _objref_Subject()  { _PR_setobj(0); }  // nil
    _objref_Subject(omniIOR*, omniIdentity*);

  protected:
    virtual ~_objref_Subject();

    
  private:
    virtual void* _ptrToObjRef(const char*);

    _objref_Subject(const _objref_Subject&);
    _objref_Subject& operator = (const _objref_Subject&);
    // not implemented

    friend class Subject;
  };

  class _pof_Subject : public _OMNI_NS(proxyObjectFactory) {
  public:
    inline _pof_Subject() : _OMNI_NS(proxyObjectFactory)(Subject::_PD_repoId) {}
    virtual ~_pof_Subject();

    virtual omniObjRef* newObjRef(omniIOR*,omniIdentity*);
    virtual _CORBA_Boolean is_a(const char*) const;
  };

  class _impl_Subject :
    public virtual omniServant
  {
  public:
    virtual ~_impl_Subject();

    virtual void attach(::tweek::Observer_ptr o) = 0;
    virtual void detach(::tweek::Observer_ptr o) = 0;
    virtual void notify() = 0;
    
  public:  // Really protected, workaround for xlC
    virtual _CORBA_Boolean _dispatch(omniCallHandle&);

  private:
    virtual void* _ptrToInterface(const char*);
    virtual const char* _mostDerivedRepoId();
    
  };


_CORBA_MODULE_END



_CORBA_MODULE POA_tweek
_CORBA_MODULE_BEG

  class Subject :
    public virtual tweek::_impl_Subject,
    public virtual ::PortableServer::ServantBase
  {
  public:
    virtual ~Subject();

    inline ::tweek::Subject_ptr _this() {
      return (::tweek::Subject_ptr) _do_this(::tweek::Subject::_PD_repoId);
    }
  };

_CORBA_MODULE_END



_CORBA_MODULE OBV_tweek
_CORBA_MODULE_BEG

_CORBA_MODULE_END





#undef _core_attr
#undef _dyn_attr



inline void
tweek::Subject::_marshalObjRef(::tweek::Subject_ptr obj, cdrStream& s) {
  omniObjRef::_marshal(obj->_PR_getobj(),s);
}




#ifdef   USE_stub_in_nt_dll_NOT_DEFINED_Subject
# undef  USE_stub_in_nt_dll
# undef  USE_stub_in_nt_dll_NOT_DEFINED_Subject
#endif
#ifdef   USE_core_stub_in_nt_dll_NOT_DEFINED_Subject
# undef  USE_core_stub_in_nt_dll
# undef  USE_core_stub_in_nt_dll_NOT_DEFINED_Subject
#endif
#ifdef   USE_dyn_stub_in_nt_dll_NOT_DEFINED_Subject
# undef  USE_dyn_stub_in_nt_dll
# undef  USE_dyn_stub_in_nt_dll_NOT_DEFINED_Subject
#endif

#endif  // __Subject_hh__

