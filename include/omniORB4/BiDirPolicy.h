// -*- Mode: C++; -*-
//                            Package   : omniORB
// BiDirPolicy.h              Created on: 30/7/2001
//                            Author    : Sai Lai Lo (sll)
//
//    Copyright (C) 2001 AT&T Laboratories Cambridge
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
//

/*
  $Log: BiDirPolicy.h,v $
  Revision 1.1.4.1  2003/03/23 21:04:26  dgrisby
  Start of omniORB 4.1.x development branch.

  Revision 1.1.2.3  2001/08/17 15:00:47  dpg1
  Fixes for pre-historic compilers.

  Revision 1.1.2.2  2001/08/16 09:54:44  sll
  Hardwired the policy number instead of using the constant in the
  declaration of BidirectionalPolicy because the latter does not work for
  compilers without namespace support.

  Revision 1.1.2.1  2001/07/31 16:10:39  sll
  Added GIOP BiDir support.

  */


#ifndef __BIDIRPOLICY_H__
#define __BIDIRPOLICY_H__

_CORBA_MODULE BiDirPolicy

_CORBA_MODULE_BEG

typedef CORBA::UShort BidirectionalPolicyValue;

_CORBA_MODULE_VARINT
const BidirectionalPolicyValue NORMAL             _init_in_decl_( = 0 );

_CORBA_MODULE_VARINT
const BidirectionalPolicyValue BOTH               _init_in_decl_( = 1 );

_CORBA_MODULE_VARINT
const CORBA::PolicyType BIDIRECTIONAL_POLICY_TYPE _init_in_decl_( = 37 );

OMNIORB_DECLARE_POLICY_OBJECT(BidirectionalPolicy, 37)

_CORBA_MODULE_END



#endif // __BIDIRPOLICY_H__
