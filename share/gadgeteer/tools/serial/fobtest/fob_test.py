#!/bin/env python
#
#
# Test program for flock of birds.
#
# Relies upon pySerial: pyserial.sf.net
#
import serial
import sys
import getopt
import Command
import FOB

def scan():
    """scan for available ports. return a list of tuples (num, name)"""
    available = []
    for i in range(256):
        try:
            s = serial.Serial(i)
            available.append( (i, s.portstr))
            s.close()   #explicit close 'cause of delayed GC in java
        except serial.serialutil.SerialException:
            pass
    return available

def usage():
    print """Program Usage:
   --test=output - Just print the data read from the bird for fob test output
          echo - Take line of input, send to bird and then read it back
          host_data_read - Perform the host data read bird test.
   --set_rts=<new val>
   --info=basic - Print basic information about the flock
   --scan - Scan for what birds are connected.
    """

def scanFbb():
    print "Scanning bird bus:"
    fob = FOB.Flock()
    fob.open()
    
    for i in range(14):
       print "bird: ", i,
       fob.setCmdAddr(i)
       bstatus = fob.getBirdStatus()
       print bstatus
       
def printBasicFlockInfo():
    " Print basic flock information "
    print "Getting basic flock info:"
    
    fob = FOB.Flock()
    fob.open()
    
    sw_ver = fob.getSoftwareRevision()
    cur_error_code = fob.getCurrentError()
    addr_mode = fob.getAddressingMode()
    bird_status = fob.getBirdStatus()
    bird_addr = fob.getBirdAddress()
    
        
    print "  Software revision: ", sw_ver
    print "  Current error code: ", cur_error_code
    print "  Addr mode: ", addr_mode
    print "  Bird addr: ", bird_addr
    print "  bird status: ", bird_status
    fob.printFlockSystemStatus()
    
    if(0 == bird_addr):
        print "Standalone mode.  Can't autoconfig"
    else:
        print "Auto-configing the flock...."
        fob.autoConfig(3)
    
    fob.printFlockSystemStatus()
    
   

def test_output():
    print "---- Testing output -----"
    fob = FOB.Flock()    
    fob.open();
    
    print "\nReading 10 OK samples"
    port = fob.port
    
    port.flushInput()
    port.flushOutput()
    
    for i in xrange(10):
        rstr = port.read(4)
        print "%s: %s"%(i,rstr)
    
    port.close()
    
def test_echo():
    print """---- Testing echo -----
Read and echo data. 'q' to quit."""
    
    fob = FOB.Flock()    
    port = fob.port
    port.flushInput()
    port.flushOutput()
    
    raw_str = raw_input("> ")
    while(raw_str != 'q'):
        port.write(raw_str)
        rstr = port.read(len(raw_str))
        print rstr
        raw_str = raw_input("> ")
        
    port.close()
    
    
def test_host_data_read():
    """ Each time data goes to the birt it will respond with 0-255 decimal.
        This is as a response in sequence.
        """
    fob = openBirdConnection()
    vals = []
    
    for i in xrange(255):
        fob.write('a')
        val = ord(fob.read(1))
        print val
        vals.append(val)
        
    good_vals = range(256)
    if(good_vals == vals):
        print "Test passed."
    else:
        print "Test failed."
        
    fob.close()
    
    
def set_rts(arg):
    ser = serial.Serial(0)
    print "Port: ", ser
    print "  Setting rts: ", arg
    ser.setRTS(arg)
    ser.close()    

def main():
    try:
        opts, args = getopt.getopt(sys.argv[1:], "h", 
                                   ["test=", "help", "set_rts=", "info=", "scan"])
    except getopt.GetoptError:
        # print help information and exit:
        usage()
        sys.exit(2)
    if not len(opts):
        usage()
        sys.exit()
    for o, a in opts:
        if o in ("-h", "--help"):
            usage()
            sys.exit()
        if o in ("--test",):
            if "output" == a:
                test_output()
            elif "echo" == a:
                test_echo()
            elif "host_data_read" == a:
                test_host_data_read()
        if o in ("--set_rts",):
            if "0" == a:
                set_rts(0)
            else:
                set_rts(1)
        if o in ("--info",):
            if "basic" == a:
                printBasicFlockInfo()
            else:
                printBasicFlockInfo()
        if o in ("--scan",):
            scanFbb()

if __name__=='__main__':
    #print "Found ports:"
    #for n,s in scan():
    #    print "(%d) %s" % (n,s)
    
    main()
    
   
    
                        
