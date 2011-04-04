// -*- Mode: C++; -*-
//                            Package   : omniORB
// giopServer.h                 Created on: 20 Dec 2000
//                            Author    : Sai Lai Lo (sll)
//
//    Copyright (C) 2003-2006 Apasphere Ltd
//    Copyright (C) 2000      AT&T Laboratories Cambridge
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
  $Log: giopServer.h,v $
  Revision 1.1.6.6  2009/05/06 16:16:08  dgrisby
  Update lots of copyright notices.

  Revision 1.1.6.5  2006/10/09 09:47:12  dgrisby
  Only delete giopServer if all threads are successfully shut down.

  Revision 1.1.6.4  2006/06/22 13:53:49  dgrisby
  Add flags to strand.

  Revision 1.1.6.3  2006/04/09 19:52:31  dgrisby
  More IPv6, endPointPublish parameter.

  Revision 1.1.6.2  2005/11/17 17:03:26  dgrisby
  Merge from omni4_0_develop.

  Revision 1.1.6.1  2003/03/23 21:03:47  dgrisby
  Start of omniORB 4.1.x development branch.

  Revision 1.1.4.8  2002/02/13 16:02:38  dpg1
  Stability fixes thanks to Bastiaan Bakker, plus threading
  optimisations inspired by investigating Bastiaan's bug reports.

  Revision 1.1.4.7  2001/12/03 18:48:14  dpg1
  Clean up strange indentation.

  Revision 1.1.4.6  2001/09/20 13:26:13  dpg1
  Allow ORB_init() after orb->destroy().

  Revision 1.1.4.5  2001/08/17 15:00:47  dpg1
  Fixes for pre-historic compilers.

  Revision 1.1.4.4  2001/07/31 16:28:01  sll
  Added GIOP BiDir support.

  Revision 1.1.4.3  2001/07/13 15:19:30  sll
  Manage the state of each connection internally. Added new callback
  functions.

  Revision 1.1.4.2  2001/06/13 20:11:37  sll
  Minor update to make the ORB compiles with MSVC++.

  Revision 1.1.4.1  2001/04/18 17:19:00  sll
  Big checkin with the brand new internal APIs.

  Revision 1.1.2.1  2001/02/23 16:47:04  sll
  Added new files.

*/

#ifndef __GIOPSERVER_H__
#define __GIOPSERVER_H__

#include <omniORB4/omniServer.h>
#include <omniORB4/omniutilities.h>
#include <omniORB4/giopEndpoint.h>

OMNI_NAMESPACE_BEGIN(omni)

class giopRendezvouser;
class giopWorker;
class giopMonitor;
class giopStrand;

class giopServer : public orbServer {
public:

  static giopServer*& singleton();

protected:
  ~giopServer();

public:
  CORBA::Boolean instantiate(const char*    endpoint_uri,
			     CORBA::Boolean no_publish,
			     EndpointList&  listening_endpoints);
  // Implement orbServer::instantiate().

  CORBA::Boolean publish(const PublishSpecs& publish_specs,
			 CORBA::Boolean      all_specs,
			 CORBA::Boolean      all_eps,
			 EndpointList&       published_endpoints);
  // Implement orbServer::publish().

  void start();
  // Implement orbServer::start().

  void stop();
  // Implement orbServer::stop().

  void remove();
  // Implement orbServer::remove().


  CORBA::Boolean addBiDirStrand(giopStrand*,giopActiveCollection* watcher);
  // Add a connection to be managed by the server. The connection is
  // an active connection used for bidirectional calls. In contrast,
  // instantiate() registers an endpoint from which passive connections
  // are created. 
  // This call returns TRUE(1) if successful. Otherwise it returns FALSE(0).
  // If the latter happens, the caller should not continue to use the
  // connection to make a call. The state of the connection is not changed
  // however.
  // When this function is called, the server must already be in the ACTIVE
  // state. Otherwise, it always returns FALSE(0).

  friend class giopRendezvouser;
  friend class giopWorker;
  friend class giopMonitor;

  class Link {
  public:
    Link* next;
    Link* prev;

    Link() {
      next = this;
      prev = this;
    }

    void insert(Link& head);
    void remove();
    static CORBA::Boolean is_empty(Link& head);

  private:
    Link(const Link&);
    Link& operator=(const Link&);
  };

private:
  enum { IDLE, ACTIVE, ZOMBIE, INFLUX, TIMEDOUT }
                                         pd_state;
  giopEndpointList                       pd_endpoints;
  Link                                   pd_rendezvousers;
  CORBA::ULong                           pd_nconnections;
  omni_tracedmutex                       pd_lock;
  omni_tracedcondition                   pd_cond;
  CORBA::Boolean                         pd_thread_per_connection;
  CORBA::ULong                           pd_n_temporary_workers;
  CORBA::ULong                           pd_n_dedicated_workers;

  omnivector<giopStrand*>                pd_bidir_strands;
  // Strands to start serving on activate().

  omnivector<giopActiveCollection*>      pd_bidir_collections;
  // Collections to start monitoring on activate().

  Link                                   pd_bidir_monitors;
  // Activated monitors.

  void activate();
  // Activate all endpoints in pd_endpoints. This involves instantiating a
  // giopRendezvouser for each of the endpoints.
  //
  // This function does not raise an exception.
  //
  // Thread Safety preconditions:
  //    Caller must hold pd_lock.

  void deactivate();
  // deactivate all endpoints in pd_endpoints. This involves terminating
  // all giopRendezvousers and giopWorkers. For each giopRendezvouser,
  // its endpoint is reentered into pd_endpoints.
  //
  // This function does not raise an exception.
  //
  // Thread Safety preconditions:
  //    Caller must hold pd_lock.

  void ensureNotInFlux();
  // ensure that the state of the server is not INFLUX.
  // If pd_state == INFLUX, block waiting until it changes out of that state.
  //
  // This function does not raise an exception.
  //
  // Thread Safety preconditions:
  //    Caller must hold pd_lock.

  /////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////
  //
  // Callback functions used by giopRendezvouser
  //
  void notifyRzNewConnection(giopRendezvouser*,giopConnection*);
  // Callback by giopRendezvouser when a new connection is accepted.
  // If no exception or outOfResource is raised by the call, the connection 
  // is consumed.
  // Otherwise the caller must free the connection.
  //
  // notifyRzNewConnection could throw:
  //    outOfResource to indicate it cannot accept the new strand.
  //    Terminate     to indicate that the caller should stop serving
  //                     this connection immediately
  //
  // Thread Safety preconditions:
  //    Caller MUST NOT hold pd_lock. The lock is acquired by this method.
  //
  class outOfResource {};
  class Terminate {};

  void notifyRzDone(giopRendezvouser*,CORBA::Boolean exit_on_error);
  // Callback by giopRendezvouser when the task is about to end.
  // The flag exit_on_error indicates whether the task ends because it
  // was told or trigged by an error.
  //
  // Thread Safety preconditions:
  //    Caller MUST NOT hold pd_lock. The lock is acquired by this method.
  //


  void notifyRzReadable(giopConnection*,
			CORBA::Boolean force_create = 0);
  // Callback by giopRendezvouser when a connection is readable.
  // If <force_create> is true(1), the server must dispatch a giopWorker
  // to the connection immediately. Otherwise, it may delay the dispatch
  // if the no. of giopWorkers for the connection has already reach the
  // limit set in omniORB::maxServerThreadPerConnection.
  //
  // Thread Safety preconditions:
  //    Caller MUST NOT hold pd_lock. The lock is acquired by this method.

  /////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////
  //
  // Callback functions used by giopWorker
  //
  CORBA::Boolean notifyWkDone(giopWorker*,CORBA::Boolean exit_on_error);
  // Callback by giopWorker when it finishes one upcall.
  //
  // The flag exit_on_error indicates whether the task ends because it
  // was told or trigged by an error.
  //
  // Returns true if the worker should continue processing another
  // upcall; false if it should finish.
  //
  // Thread Safety preconditions:
  //    Caller MUST NOT hold pd_lock. The lock is acquired by this method.
  //

public:
  static void peekCallBack(void*, giopConnection*);

  void notifyWkPreUpCall(giopWorker*,
			 CORBA::Boolean data_in_buffer);
  // Callback by the thread performing the giopWorker task when it
  // is about to perform an upcall to the applicaton level code.
  // This is an indication that from this point onwards, the thread will not
  // be reading from the strand. The server may want to start watching the
  // strand for any new request coming in.
  // If <data_in_buffer> == 1, there are data pending already. The server
  // should treat this case as if there are new data to be read from the 
  // strand.
  //
  // Thread Safety preconditions:
  //    Caller MUST NOT hold pd_lock. The lock may be acquired by this method.
  //

  /////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////
  //
  // Callback functions used by giopMonitor
  //
  void notifyMrDone(giopMonitor*,CORBA::Boolean exit_on_error);
  // Callback by giopMonitor when it finishes one upcall.
  //
  // The flag exit_on_error indicates whether the task ends because it
  // was told or trigged by an error.
  //
  // Thread Safety preconditions:
  //    Caller MUST NOT hold pd_lock. The lock is acquired by this method.
  //

  /////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////
  //
  // Callback functions used by giopImpl12
  //
  void notifyCallFullyBuffered(giopConnection*);
  // GIOP 1.2 and above allows fragments of different requests to interleave
  // on a connection. It may happens that while a giopWorker is processing
  // one request, it encounters fragments for another request. These fragments
  // are set aside. If these set-aside fragments actually constitute a 
  // complete request, this callback function is invoked. The server should
  // dispatch a giopWorker task to deal with this callback. 

  /////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////
  //
  // Callback functions used by getBiDirServiceContext.
  // Indicate that the connection is now bidirectional. There should
  // be a dedicate thread serving the connection. Normally the return
  // value is 1, if it returns 0 the server fails to arrange the connection
  // to be served as bidirectional.
  //
  CORBA::Boolean notifySwitchToBiDirectional(giopConnection*);

  struct connectionState {
    giopConnection*  connection;
    giopStrand*      strand;
    Link             workers;
    connectionState* next;

    connectionState(giopConnection* c,giopStrand* s);
    ~connectionState();

    static CORBA::ULong hashsize;
  };

private:
  connectionState** pd_connectionState;

  connectionState* csLocate(giopConnection*);
  connectionState* csRemove(giopConnection*);
  connectionState* csInsert(giopConnection*);
  connectionState* csInsert(giopStrand*);

  void removeConnectionAndWorker(giopWorker* conn);
  // Thread Safety preconditions:
  //    Caller MUST NOT hold pd_lock. The lock is acquired by this method.

  giopServer();
};

OMNI_NAMESPACE_END(omni)

#endif // __GIOPSERVER_H__
