// -*- Mode: C++; -*-
//                            Package   : omniORB
// giopWorker.h                 Created on: 20 Dec 2000
//                            Author    : Sai Lai Lo (sll)
//
//    Copyright (C) 2000 AT&T Laboratories Cambridge
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
  $Log: giopWorker.h,v $
  Revision 1.1.6.1  2003/03/23 21:03:46  dgrisby
  Start of omniORB 4.1.x development branch.

  Revision 1.1.4.3  2002/09/10 23:17:11  dgrisby
  Thread interceptors.

  Revision 1.1.4.2  2001/07/13 15:21:22  sll
  Added access functions.

  Revision 1.1.4.1  2001/04/18 17:18:59  sll
  Big checkin with the brand new internal APIs.

  Revision 1.1.2.1  2001/02/23 16:47:03  sll
  Added new files.

*/

#ifndef __GIOPWORKER_H__
#define __GIOPWORKER_H__

OMNI_NAMESPACE_BEGIN(omni)

class giopWorker : public omniTask, public giopServer::Link {
public:
  giopWorker(giopStrand* strand, giopServer* server, 
	     CORBA::Boolean singleshot=0);

  void execute();
  void real_execute();

  void terminate();
  // finish off this task, call by another thread.

  giopServer* server() const { return pd_server; }
  giopStrand* strand() const { return pd_strand; }
  CORBA::Boolean singleshot() const { return pd_singleshot; }

private:
  giopStrand*          pd_strand;
  giopServer*          pd_server;
  const CORBA::Boolean pd_singleshot;

  giopWorker();
  giopWorker(const giopWorker&);
  giopWorker& operator=(const giopWorker&);
};

OMNI_NAMESPACE_END(omni)

#endif // __GIOPWORKER_H__
