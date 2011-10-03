/****************** <VPR heading BEGIN do not edit this line> *****************
 *
 * VR Juggler Portable Runtime
 *
 * Original Authors:
 *   Allen Bierbaum, Patrick Hartling, Kevin Meinert, Carolina Cruz-Neira
 *
 ****************** <VPR heading END do not edit this line> ******************/

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

#ifndef _VPR_SOCKET_DATAGRAM_BRIDGE_H_
#define _VPR_SOCKET_DATAGRAM_BRIDGE_H_
// NOTE: this is the bridge class for use with SocketDatagram.h

#include <vpr/vprConfig.h>

#include <cstring>
#include <boost/smart_ptr.hpp>

#include <vpr/IO/Socket/Socket_t.h>


namespace vpr
{

/** \class SocketDatagram_t SocketDatagram_t.h vpr/IO/Socket/SocketDatagram_t.h
 *
 * Datagram socket interface.  Given a SocketConfiguration declaration, this
 * class is typedef'd to vpr::SocketDatagram.
 *
 * @param SocketConfig_ The SocketConfiguration type that matches the
 *                      platform-specific socket implementation to use.
 *
 * @see vpr::SocketDatagramImplNSPR, vpr::SocketDatagramImplBSD
 *
 * @note vpr::SocketDatagramOpt was folded into this class in version 2.1.10.
 *       User-level code will most likely not be affected by this difference.
 */
template<class SocketConfig_>
class SocketDatagram_t
   : public Socket_t<SocketConfig_>
{
public:
   typedef SocketConfig_ Config;
   typedef typename Config::SocketDatagramImpl SocketDatagramImpl;

   /**
    * Default constructor.
    */
   SocketDatagram_t()
      : Socket_t<Config>()
      , mSocketDgramImpl()
   {
      mSocketDgramImpl =
         boost::shared_ptr<SocketDatagramImpl>(new SocketDatagramImpl);
      Socket_t<SocketConfig_>::mSocketImpl = mSocketDgramImpl;
   }

   /**
    * Constructor.  This takes a reference to a vpr::InetAddr object giving
    * the local socket address and a reference to a vpr::InetAddr object
    * giving the remote address.
    *
    * @pre \p localAddr and \p remoteAddr are references to valid vpr::InetAddr
    *      objects.
    * @post A socket is created using \p localAddr and \p remoteAddr.
    *
    * @param localAddr  Our local address.
    * @param remoteAddr The remote address with which we will communicate.
    */
   SocketDatagram_t(const vpr::InetAddr& localAddr,
                    const vpr::InetAddr& remoteAddr)
      : Socket_t<Config>()
   {
      mSocketDgramImpl =
         boost::shared_ptr<SocketDatagramImpl>(new SocketDatagramImpl(localAddr,
                                                                      remoteAddr));
      Socket_t<SocketConfig_>::mSocketImpl = mSocketDgramImpl;
   }

   /**
    * Copy constructor.
    *
    * @param sock The source socket object to be copied.
    */
   SocketDatagram_t(const SocketDatagram_t& sock)
      : Socket_t<Config>()
      , mSocketDgramImpl(sock.mSocketDgramImpl)
   {
      Socket_t<SocketConfig_>::mSocketImpl = mSocketDgramImpl;
   }

   /**
    * Destructor.  This currently does nothing.
    */
   virtual ~SocketDatagram_t()
   {
      /* nothing */ ;
   }

   /**
    * Receives a message from some source.  The source's address is writen
    * into the by-reference parameter \p from.
    *
    * @throw vpr::IOException Thrown if the operation failed.
    */
   vpr::Uint32 recvfrom(void* msg, const vpr::Uint32 len,
                        vpr::InetAddr& from,
                        const vpr::Interval& timeout = vpr::Interval::NoTimeout)
   {
      return mSocketDgramImpl->recvfrom(msg, len, from, timeout);
   }

   /**
    * Receives a message from some source.  The source's address is writen
    * into the by-reference parameter \p from.
    *
    * @throw vpr::IOException Thrown if the operation failed.
    */
   vpr::Uint32 recvfrom(std::string& msg, const vpr::Uint32 len,
                        vpr::InetAddr& from,
                        const vpr::Interval& timeout = vpr::Interval::NoTimeout)
   {
      msg.resize(len);
      std::memset(&msg[0], '\0', msg.size());

      return recvfrom((void*) &msg[0], msg.size(), from, timeout);
   }

   /**
    * Receives a message from some source.  The source's address is writen
    * into the by-reference parameter \p from.
    *
    * @throw vpr::IOException Thrown if the operation failed.
    */
   vpr::Uint32 recvfrom(std::vector<vpr::Uint8>& msg,
                        const vpr::Uint32 len, vpr::InetAddr& from,
                        const vpr::Interval& timeout = vpr::Interval::NoTimeout)
   {
      msg.resize(len);

      std::memset(&msg[0], '\0', msg.size());
      const vpr::Uint32 bytes = recvfrom((void*) &msg[0], msg.size(), from,
                                         timeout);

      // Size it down if needed, if (bytes == len), then resize does nothing.
      msg.resize(bytes);

      return bytes;
   }

   /**
    * Sends a message to the designated recipient.
    *
    * @throw vpr::IOException Thrown if the operation failed.
    */
   vpr::Uint32 sendto(const void* msg, const vpr::Uint32 len,
                      const vpr::InetAddr& to,
                      const vpr::Interval& timeout = vpr::Interval::NoTimeout)
   {
      return mSocketDgramImpl->sendto(msg, len, to, timeout);
   }

   /**
    * Sends a message to the designated recipient.
    *
    * @throw vpr::IOException Thrown if the operation failed.
    */
   vpr::Uint32 sendto(const std::string& msg, const vpr::Uint32 len,
                      const vpr::InetAddr& to,
                      const vpr::Interval& timeout = vpr::Interval::NoTimeout)
   {
      vprASSERT(len <= msg.size() && "Length is bigger than data given");
      return sendto(msg.c_str(), len, to, timeout);
   }

   /**
    * Sends a message to the designated recipient.
    *
    * @throw vpr::IOException Thrown if the operation failed.
    */
   vpr::Uint32 sendto(const std::vector<vpr::Uint8>& msg,
                      const vpr::Uint32 len, const vpr::InetAddr& to,
                      const vpr::Interval& timeout = vpr::Interval::NoTimeout)
   {
      vprASSERT(len <= msg.size() && "Length is bigger than data given");
      return sendto((const void*) &msg[0], len, to, timeout);
   }

   /** @name Socket Options */
   //@{
   /**
    * Gets the multicast interface for this datagram socket.
    *
    * @throw vpr::SocketException Thrown if the operation failed.
    */
   const vpr::InetAddr getMcastInterface() const
   {
      vpr::SocketOptions::Data option;

      this->getOption(SocketOptions::McastInterface, option);
      return option.mcast_if;
   }

   /**
    * Sets the multicast interface for this datagram socket.
    *
    * @throw vpr::SocketException Thrown if the operation failed.
    */
   void setMcastInterface(const vpr::InetAddr& mcastIf)
   {
      vpr::SocketOptions::Data option;
      option.mcast_if = mcastIf;
      this->setOption(SocketOptions::McastInterface, option);
   }

   /**
    * Gets the multicast time-to-live parameter for packets sent on this
    * socket.
    *
    * @throw vpr::SocketException Thrown if the operation failed.
    */
   vpr::Uint8 getMcastTimeToLive() const
   {
      vpr::SocketOptions::Data option;

      this->getOption(SocketOptions::McastTimeToLive, option);
      return option.mcast_ttl;
   }

   /**
    * Sets the multicast time-to-live parameter for packets sent on this
    * socket.
    *
    * @throw vpr::SocketException Thrown if the operation failed.
    */
   void setMcastTimeToLive(const vpr::Uint8 ttl)
   {
      vpr::SocketOptions::Data option;
      option.mcast_ttl = ttl;
      this->setOption(SocketOptions::McastTimeToLive, option);
   }

   /**
    * @throw vpr::SocketException Thrown if the operation failed.
    */
   vpr::Uint8 getMcastLoopback() const
   {
      vpr::SocketOptions::Data option;

      this->getOption(SocketOptions::McastLoopback, option);
      return option.mcast_loopback;
   }

   /**
    * @throw vpr::SocketException Thrown if the operation failed.
    */
   void setMcastLoopback(const vpr::Uint8 loop)
   {
      vpr::SocketOptions::Data option;
      option.mcast_loopback = loop;
      this->setOption(SocketOptions::McastLoopback, option);
   }

   /**
    * @throw vpr::IOException Thrown if the operation failed.
    */
   void addMcastMember(const vpr::McastReq& request)
   {
      vpr::SocketOptions::Data option;
      option.mcast_add_member = request;
      this->setOption(SocketOptions::AddMember, option);
   }

   /**
    * @throw vpr::IOException Thrown if the operation failed.
    */
   void dropMcastMember(const vpr::McastReq& request)
   {
      vpr::SocketOptions::Data option;
      option.mcast_drop_member = request;
      this->setOption(SocketOptions::DropMember, option);
   }

   /**
    * @throw vpr::IOException Thrown if the operation failed.
    * @since 1.1.17
    */
   void setBroadcast(const bool val)
   {
      vpr::SocketOptions::Data option;
      option.broadcast = val;
      this->setOption(SocketOptions::Broadcast, option);
   }
   //@}

// Put in back door for simulator
#if VPR_IO_DOMAIN_INCLUDE == VPR_DOMAIN_SIMULATOR
public:
#endif
   /// Platform-specific datagram socket implementation object
   boost::shared_ptr<SocketDatagramImpl> mSocketDgramImpl;
};

} // End of vpr namespace


#endif  /* _VJ_SOCKET_DATAGRAM_BRIDGE_H_ */
