#ifndef _VPRTEST_SOCKET_SIMULATOR_TEST_H_
#define _VPRTEST_SOCKET_SIMULATOR_TEST_H_

#include <string>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <vpr/vpr.h>
#include <vpr/Sync/CondVar.h>


namespace vprTest
{

class SocketSimulatorTest : public CppUnit::TestCase
{
CPPUNIT_TEST_SUITE(SocketSimulatorTest);
CPPUNIT_TEST( graphConstructionTest );
CPPUNIT_TEST( singleThreadTest );
CPPUNIT_TEST( networkCommTestTCP );
CPPUNIT_TEST( networkCommTestUDP );
CPPUNIT_TEST( networkFlushTest );
CPPUNIT_TEST_SUITE_END();

public:
   SocketSimulatorTest (std::string name)
      : CppUnit::TestCase(name)
   {
      /* Do nothing. */ ;
   }

   SocketSimulatorTest ()
      : CppUnit::TestCase()
   {
      /* Do nothing. */ ;
   }

   virtual ~SocketSimulatorTest (void) {
      /* Do nothing. */ ;
   }

   void graphConstructionTest(void);

   void singleThreadTest(void);

   void networkCommTestTCP();

   void networkCommTestUDP();

   void networkFlushTest(void);

   void multiThreadTest(void);

   void multiThreadTest_acceptor();

   void multiThreadTest_connector();

protected:
   vpr::ReturnStatus constructGraph(void);

   enum State {
      ACCEPTOR_READY,
      NOT_READY,
      CONNECTOR_CLOSED,
      CONNECTOR_READY,
      DATA_SENT,
      DONE_READING
   };

   State        mState;
   vpr::CondVar mCondVar;
   vpr::Uint16  mAcceptorPort;
   std::string  mMessage;
   vpr::Uint16  mMessageLen;
};

}

#endif
