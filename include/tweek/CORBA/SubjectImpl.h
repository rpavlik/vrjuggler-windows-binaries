/*************** <auto-copyright.pl BEGIN do not edit this line> **************
 *
 * VR Juggler is (C) Copyright 1998-2010 by Iowa State University
 *
 * Original Authors:
 *   Allen Bierbaum, Christopher Just,
 *   Patrick Hartling, Kevin Meinert,
 *   Carolina Cruz-Neira, Albert Baker
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 *************** <auto-copyright.pl END do not edit this line> ***************/

#ifndef _TWEEK_CORBA_SUBJECT_IMPL_H_
#define _TWEEK_CORBA_SUBJECT_IMPL_H_

#include <tweek/tweekConfig.h>

#include <vector>
#include <vpr/Sync/Mutex.h>

#include <tweek/idl/Subject.h>
#include <tweek/idl/Observer.h>


namespace tweek
{

/** \class SubjectImpl SubjectImpl.h tweek/CORBA/SubjectImpl.h
 *
 * CORBA servant for the tweek::Subject interface (the implementation of the
 * interface).  Methods here should be invoked only via a reference to an
 * Subject object (Subject_ptr, Subject_var).
 */
class TWEEK_CLASS_API SubjectImpl : virtual public POA_tweek::Subject,
                                    public PortableServer::RefCountServantBase
{
public:
   SubjectImpl()
   {
   }

   virtual ~SubjectImpl()
   {
   }

   virtual void attach(Observer_ptr o) throw(CORBA::SystemException);

   virtual void detach(Observer_ptr o) throw(CORBA::SystemException);

   virtual void notify() throw(CORBA::SystemException);

protected:
   SubjectImpl(const SubjectImpl& s);

   SubjectImpl& operator=(const SubjectImpl&)
   {
      return *this;
   }

private:
   typedef std::vector<Observer_var> observer_vec_t;
   observer_vec_t m_observers;
   vpr::Mutex m_observers_mutex;
};

} // End of tweek namespace


#endif /* _TWEEK_CORBA_SUBJECT_IMPL_H_ */
