#include <string>

#include <vpr/vpr.h>
#include <vpr/IO/Selector.h>
#include <vpr/IO/Socket/SocketStream.h>
#include <vpr/Util/ReturnStatus.h>

#include <vpr/md/SIM/Controller.h>

#include <TestCases/Simulator/SimSelectorTest.h>


namespace vprTest
{
#ifdef VPR_SIMULATOR
CPPUNIT_TEST_SUITE_REGISTRATION( SimSelectorTest );
#endif

void SimSelectorTest::singleThreadTest ()
{
   vpr::SocketStream sender, acceptor, receiver;
   vpr::Selector selector;
   vpr::ReturnStatus status;

   vpr::InetAddr temp_addr;
   temp_addr.setPort(5556);
   status = acceptor.setLocalAddr(temp_addr);
   CPPUNIT_ASSERT(status.success() && "Acceptor failed to set local address");

   status = acceptor.open();
   CPPUNIT_ASSERT(status.success() && "Failed to open acceptor");

   status = acceptor.bind();
   CPPUNIT_ASSERT(status.success() &&
                  "Acceptor failed to bind to local address");

   status = acceptor.listen();
   CPPUNIT_ASSERT(status.success() &&
                  "Failed to set listening state for acceptor");

   selector.addHandle(acceptor.getHandle(), vpr::Selector::Accept);
   vpr::Uint16 num_events;
   status = selector.select(num_events,
                            vpr::Interval(1, vpr::Interval::Msec));
   CPPUNIT_ASSERT(status == vpr::ReturnStatus::Timeout &&
                  "Selector should not have found any pending connections");

   status = acceptor.accept(receiver);
   CPPUNIT_ASSERT(status == vpr::ReturnStatus::WouldBlock &&
                  "Acceptor should not have accepted");

   status = sender.setRemoteAddr(acceptor.getLocalAddr());
   CPPUNIT_ASSERT(status.success() && "Sender failed to set remote address");

   status = sender.open();
   CPPUNIT_ASSERT(status.success() && "Failed to open sender");

   status = sender.connect();
   CPPUNIT_ASSERT(status == vpr::ReturnStatus::InProgress &&
                  "Connection to acceptor should be in progress");

   status = selector.select(num_events);
   CPPUNIT_ASSERT(status.success() &&
                  "Selector should have found one pending connection");

   status = acceptor.accept(receiver);
   CPPUNIT_ASSERT(status.success() && "Failed to accept waiting connection");

   CPPUNIT_ASSERT(selector.removeHandle(acceptor.getHandle()) &&
                  "Failed to remove acceptor handle from selector");

   selector.addHandle(sender.getHandle(), vpr::Selector::Write);
   status = selector.select(num_events);
   CPPUNIT_ASSERT(status.success() && "Sender should always be able to send");
   CPPUNIT_ASSERT(selector.removeHandle(sender.getHandle()) &&
                  "Failed to remove sender handle from selector");

   // From this point on, we need the simulator to move messages around...
   std::string buffer("This is a message");
   vpr::Uint32 bytes_written;
   status = sender.write(buffer, buffer.length(), bytes_written);
   CPPUNIT_ASSERT(status.success() && "Failed to send buffer to receiver");

   vpr::Uint32 bytes_read;
   char buffer2[20];
   selector.addHandle(receiver.getHandle(), vpr::Selector::Read);

   do
   {
      status = selector.select(num_events);
   }
   while (status == vpr::ReturnStatus::Timeout);

   status = receiver.read(buffer2, sizeof(buffer2), bytes_read);

   CPPUNIT_ASSERT(status.success() && "Failed to receive buffer");
   CPPUNIT_ASSERT(bytes_read == buffer.length() && "Received message wrong size");

   status = receiver.close();
   CPPUNIT_ASSERT(status.success() && "Failed to close receiver");

   status = sender.close();
   CPPUNIT_ASSERT(status.success() && "Failed to close sender");

   status = acceptor.close();
   CPPUNIT_ASSERT(status.success() && "Failed to close acceptor");
}

} // End of vprTest namespace
