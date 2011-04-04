// -*- Mode: C++; -*-
//                            Package   : omniORB2
// CORBA_basetypes.h          Created on: 30/1/96
//                            Author    : Sai Lai Lo (sll)
//
//    Copyright (C) 1996-1999 AT&T Laboratories - Cambridge Ltd
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
//	*** PROPRIETORY INTERFACE ***

/*
 $Log: CORBA_basetypes.h,v $
 Revision 1.5.2.2  2005/01/06 23:08:07  dgrisby
 Big merge from omni4_0_develop.

 Revision 1.5.2.1  2003/03/23 21:04:22  dgrisby
 Start of omniORB 4.1.x development branch.

 Revision 1.2.2.7  2002/02/18 11:59:12  dpg1
 Full autoconf support.

 Revision 1.2.2.6  2002/01/15 16:38:09  dpg1
 On the road to autoconf. Dependencies refactored, configure.ac
 written. No makefiles yet.

 Revision 1.2.2.5  2001/08/03 17:46:39  sll
 Replace _CORBA_marshal_error with _CORBA_marshal_sequence_range_check_error.

 Revision 1.2.2.4  2001/03/13 10:32:05  dpg1
 Fixed point support.

 Revision 1.2.2.3  2000/11/15 19:16:30  sll
 Added provision to override default mapping of CORBA::WChar to C++ wchar_t.

 Revision 1.2.2.2  2000/10/27 15:42:02  dpg1
 Initial code set conversion support. Not yet enabled or fully tested.

 Revision 1.2.2.1  2000/07/17 10:35:33  sll
 Merged from omni3_develop the diff between omni3_0_0_pre3 and omni3_0_0.

 Revision 1.3  2000/07/13 15:26:06  dpg1
 Merge from omni3_develop for 3.0 release.

 Revision 1.1.2.1  1999/09/24 09:51:37  djr
 Moved from omniORB2 + some new files.

 Revision 1.12  1999/08/15 13:52:17  sll
 New VMS float implementation.

 Revision 1.11  1999/06/18 21:11:24  sll
 Updated copyright notice.

 Revision 1.10  1999/06/18 20:34:22  sll
 New function _CORBA_bad_param_freebuf().

 Revision 1.9  1999/01/07 18:11:58  djr
 New functions: _CORBA_invoked_nil_pseudo_ref()
 and            _CORBA_use_nil_ptr_as_nil_pseudo_objref()

 Revision 1.8  1998/08/11 16:34:47  sll
 Changed Float and Double representation on VMS.

 Revision 1.7  1998/03/02 14:05:02  ewc
 Patch to fix IDL unions containing structs which contain floats or doubles
 (was broken on OpenVMS).

 * Revision 1.6  1998/01/21  12:12:17  sll
 * New function _CORBA_null_string_ptr.
 *
 * Revision 1.5  1998/01/20  16:45:45  sll
 * Added support for OpenVMS.
 *
 Revision 1.4  1997/08/21 22:21:38  sll
 New extern function _CORBA_use_nil_ptr_as_nil_objref().

 * Revision 1.3  1997/05/06  16:05:20  sll
 * Public release.
 *
 */

#ifndef __CORBA_BASETYPES_H__
#define __CORBA_BASETYPES_H__

#ifdef HAS_Cplusplus_Bool
typedef bool                      _CORBA_Boolean;
#else
typedef unsigned char             _CORBA_Boolean;
#endif

typedef unsigned char             _CORBA_Char;

typedef unsigned char             _CORBA_Octet;

typedef short                     _CORBA_Short;

typedef unsigned short            _CORBA_UShort;

#if SIZEOF_LONG == 4
typedef long                      _CORBA_Long;

typedef unsigned long             _CORBA_ULong;

#elif SIZEOF_INT == 4
#  ifndef OMNI_LONG_IS_INT
#    define OMNI_LONG_IS_INT
#  endif

typedef int                       _CORBA_Long;

typedef unsigned int              _CORBA_ULong;
#else
# error "Can't map Long (32 bits) to a native type."
#endif

typedef _CORBA_WCHAR_DECL         _CORBA_WChar;

#ifdef HAS_LongLong
typedef _CORBA_LONGLONG_DECL      _CORBA_LongLong;
typedef _CORBA_ULONGLONG_DECL     _CORBA_ULongLong;
#endif


#ifndef NO_FLOAT

#ifndef __VMS

// This platform uses IEEE float
typedef float                     _CORBA_Float;
typedef double                    _CORBA_Double;

#ifdef HAS_LongDouble
typedef _CORBA_LONGDOUBLE_DECL    _CORBA_LongDouble;
#endif

#else	// VMS float test

// VMS now always uses proxies for float.
#define USING_PROXY_FLOAT

#undef cvt_
#if __D_FLOAT
#define cvt_ cvt_d_
#elif __G_FLOAT
#define cvt_ cvt_g_
#else
#define cvt_ cvt_ieee_
#endif

class _CORBA_Float {
  _CORBA_Long pd_f;
  void cvt_d_(float f);
  float cvt_d_() const;
  void cvt_g_(float f);
  float cvt_g_() const;
#ifndef __VAX
  void cvt_ieee_(float f);
  float cvt_ieee_() const;
#endif
public:
  // using compiler generated copy constructor and copy assignment
  inline _CORBA_Float() {cvt_(0.0f);}
  inline _CORBA_Float(float f) {cvt_(f);}
  inline operator float() const {return cvt_();}
  inline _CORBA_Float operator+() const {
    return *this;
  }
  inline _CORBA_Float operator-() const {
    return _CORBA_Float(-cvt_());
  }
  inline _CORBA_Float& operator+=(_CORBA_Float const& v) {
    cvt_(cvt_()+v.cvt_());
    return *this;
  }
  inline _CORBA_Float& operator-=(_CORBA_Float const& v) {
    cvt_(cvt_()-v.cvt_());
    return *this;
  }
  inline _CORBA_Float& operator*=(_CORBA_Float const& v) {
    cvt_(cvt_()*v.cvt_());
    return *this;
  }
  inline _CORBA_Float& operator/=(_CORBA_Float const& v) {
    cvt_(cvt_()/v.cvt_());
    return *this;
  }
  inline _CORBA_Float& operator+=(float v) {
    cvt_(cvt_()+v);
    return *this;
  }
  inline _CORBA_Float& operator-=(float v) {
    cvt_(cvt_()-v);
    return *this;
  }
  inline _CORBA_Float& operator*=(float v) {
    cvt_(cvt_()*v);
    return *this;
  }
  inline _CORBA_Float& operator/=(float v) {
    cvt_(cvt_()/v);
    return *this;
  }
  inline static int compare(_CORBA_Float const& lhs,
                            _CORBA_Float const& rhs) {
    float l=lhs.cvt_();
    float r=rhs.cvt_();
    if (l<r)
      return -1;
    if (l==r)
      return 0;
    return 1;
  }
};

class _CORBA_Double {
  _CORBA_Long pd_d[2];
  void cvt_d_(double d);
  double cvt_d_() const;
  void cvt_g_(double d);
  double cvt_g_() const;
#ifndef __VAX
  void cvt_ieee_(double d);
  double cvt_ieee_() const;
#endif
public:
  // using compiler generated copy constructor and copy assignment
  inline _CORBA_Double() {cvt_(0.0);}
  inline _CORBA_Double(double d) {cvt_(d);}
  inline operator double() const {return cvt_();}
  inline _CORBA_Double operator+() const {
    return *this;
  }
  inline _CORBA_Double operator-() const {
    return _CORBA_Double(-cvt_());
  }
  inline _CORBA_Double& operator+=(_CORBA_Double const& v) {
    cvt_(cvt_()+v.cvt_());
    return *this;
  }
  inline _CORBA_Double& operator-=(_CORBA_Double const& v) {
    cvt_(cvt_()-v.cvt_());
    return *this;
  }
  inline _CORBA_Double& operator*=(_CORBA_Double const& v) {
    cvt_(cvt_()*v.cvt_());
    return *this;
  }
  inline _CORBA_Double& operator/=(_CORBA_Double const& v) {
    cvt_(cvt_()/v.cvt_());
    return *this;
  }
  inline _CORBA_Double& operator+=(double v) {
    cvt_(cvt_()+v);
    return *this;
  }
  inline _CORBA_Double& operator-=(double v) {
    cvt_(cvt_()-v);
    return *this;
  }
  inline _CORBA_Double& operator*=(double v) {
    cvt_(cvt_()*v);
    return *this;
  }
  inline _CORBA_Double& operator/=(double v) {
    cvt_(cvt_()/v);
    return *this;
  }
  inline static int compare(_CORBA_Double const& lhs,
                            _CORBA_Double const& rhs) {
    double l=lhs.cvt_();
    double r=rhs.cvt_();
    if (l<r)
      return -1;
    if (l==r)
      return 0;
    return 1;
  }
};

inline _CORBA_Float operator+(_CORBA_Float const& lhs,
                              _CORBA_Float const& rhs) {
  _CORBA_Float f(lhs);
  f+=rhs;
  return f;
}

inline _CORBA_Float operator-(_CORBA_Float const& lhs,
                              _CORBA_Float const& rhs) {
  _CORBA_Float f(lhs);
  f-=rhs;
  return f;
}

inline _CORBA_Float operator*(_CORBA_Float const& lhs,
                              _CORBA_Float const& rhs) {
  _CORBA_Float f(lhs);
  f*=rhs;
  return f;
}

inline _CORBA_Float operator/(_CORBA_Float const& lhs,
                              _CORBA_Float const& rhs) {
  _CORBA_Float f(lhs);
  f/=rhs;
  return f;
}

inline bool operator==(_CORBA_Float const& lhs,
                       _CORBA_Float const& rhs) {
    return _CORBA_Float::compare(lhs,rhs)==0;
}

inline bool operator!=(_CORBA_Float const& lhs,
                       _CORBA_Float const& rhs) {
    return _CORBA_Float::compare(lhs,rhs)!=0;
}

inline bool operator<=(_CORBA_Float const& lhs,
                       _CORBA_Float const& rhs) {
    return _CORBA_Float::compare(lhs,rhs)<=0;
}

inline bool operator>=(_CORBA_Float const& lhs,
                       _CORBA_Float const& rhs) {
    return _CORBA_Float::compare(lhs,rhs)>=0;
}

inline bool operator<(_CORBA_Float const& lhs,
                       _CORBA_Float const& rhs) {
    return _CORBA_Float::compare(lhs,rhs)<0;
}

inline bool operator>(_CORBA_Float const& lhs,
                       _CORBA_Float const& rhs) {
    return _CORBA_Float::compare(lhs,rhs)>0;
}

inline _CORBA_Double operator+(_CORBA_Double const& lhs,
                               _CORBA_Double const& rhs) {
  _CORBA_Double d(lhs);
  d+=rhs;
  return d;
}

inline _CORBA_Double operator-(_CORBA_Double const& lhs,
                               _CORBA_Double const& rhs) {
  _CORBA_Double d(lhs);
  d-=rhs;
  return d;
}

inline _CORBA_Double operator*(_CORBA_Double const& lhs,
                               _CORBA_Double const& rhs) {
  _CORBA_Double d(lhs);
  d*=rhs;
  return d;
}

inline _CORBA_Double operator/(_CORBA_Double const& lhs,
                               _CORBA_Double const& rhs) {
  _CORBA_Double d(lhs);
  d/=rhs;
  return d;
}

inline bool operator==(_CORBA_Double const& lhs,
                       _CORBA_Double const& rhs) {
    return _CORBA_Double::compare(lhs,rhs)==0;
}

inline bool operator!=(_CORBA_Double const& lhs,
                       _CORBA_Double const& rhs) {
    return _CORBA_Double::compare(lhs,rhs)!=0;
}

inline bool operator<=(_CORBA_Double const& lhs,
                       _CORBA_Double const& rhs) {
    return _CORBA_Double::compare(lhs,rhs)<=0;
}

inline bool operator>=(_CORBA_Double const& lhs,
                       _CORBA_Double const& rhs) {
    return _CORBA_Double::compare(lhs,rhs)>=0;
}

inline bool operator<(_CORBA_Double const& lhs,
                      _CORBA_Double const& rhs) {
    return _CORBA_Double::compare(lhs,rhs)<0;
}

inline bool operator>(_CORBA_Double const& lhs,
                      _CORBA_Double const& rhs) {
    return _CORBA_Double::compare(lhs,rhs)>0;
}

#undef cvt_

//  Assume long double type is compatible with the CORBA standard.

#ifdef HAS_LongDouble
typedef _CORBA_LONGDOUBLE_DECL    _CORBA_LongDouble;
#endif

#endif   // VMS float test
#endif   // !defined(NO_FLOAT)

class cdrStream;

extern void _CORBA_new_operator_return_null();
extern void _CORBA_bound_check_error();
extern void _CORBA_marshal_sequence_range_check_error(cdrStream&);
extern _CORBA_Boolean _CORBA_use_nil_ptr_as_nil_objref();
extern void _CORBA_null_string_ptr(_CORBA_Boolean);
extern void _CORBA_invoked_nil_pseudo_ref();
extern void _CORBA_invoked_nil_objref();
extern _CORBA_Boolean
_CORBA_use_nil_ptr_as_nil_pseudo_objref(const char* objType);
extern void _CORBA_bad_param_freebuf();


#endif // __CORBA_BASETYPES_H__
