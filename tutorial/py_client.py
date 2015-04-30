#!/usr/bin/env python
 
import sys
sys.path.append('gen-py')
 
from example import Calculator
from example.ttypes import *
from example.constants import *
 
from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol

try:
  # Make socket
  transport = TSocket.TSocket('127.0.0.1', 8081)
 
  # Buffering is critical. Raw sockets are very slow
  transport = TTransport.TBufferedTransport(transport)
 
  # Wrap in a protocol
  protocol = TBinaryProtocol.TBinaryProtocol(transport)
 
  # Create a client to use the protocol encoder
  client = Calculator.Client(protocol)
 
  # Connect!
  transport.open()
 
  print client.add(1, 2);
 
  transport.close()
 
except Thrift.TException, tx:
  print "%s" % (tx.message)
