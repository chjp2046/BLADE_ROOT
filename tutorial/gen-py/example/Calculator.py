#
# Autogenerated by Thrift
#
# DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
#  @generated
#

from __future__ import absolute_import
import six
from thrift.util.Recursive import fix_spec
from thrift.Thrift import *
from thrift.protocol.TProtocol import TProtocolException


from .ttypes import *
from thrift.Thrift import TProcessor
import pprint
import warnings
from thrift import Thrift
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol
from thrift.protocol import TCompactProtocol
from thrift.protocol import THeaderProtocol
try:
  from thrift.protocol import fastbinary
  if fastbinary.version < 2:
    fastbinary = None
    warnings.warn("Disabling fastbinary, need at least version 2")
except:
  fastbinary = None
try:
  from thrift.protocol import fastproto
except:
  fastproto = None

all_structs = []
UTF8STRINGS = bool(0) or sys.version_info.major >= 3
from thrift.util.Decorators import *

class Iface:
  def add(self, num1=None, num2=None):
    """
    Parameters:
     - num1
     - num2
    """
    pass


class ContextIface:
  def add(self, handler_ctx, num1=None, num2=None):
    """
    Parameters:
     - num1
     - num2
    """
    pass


class Client(Iface):
  def __init__(self, iprot, oprot=None):
    self._iprot = self._oprot = iprot
    if oprot != None:
      self._oprot = oprot
    self._seqid = 0

  def add(self, num1=None, num2=None):
    """
    Parameters:
     - num1
     - num2
    """
    self.send_add(num1, num2)
    return self.recv_add()

  def send_add(self, num1=None, num2=None):
    self._oprot.writeMessageBegin('add', TMessageType.CALL, self._seqid)
    args = add_args()
    args.num1 = num1
    args.num2 = num2
    args.write(self._oprot)
    self._oprot.writeMessageEnd()
    self._oprot.trans.flush()

  def recv_add(self, ):
    (fname, mtype, rseqid) = self._iprot.readMessageBegin()
    if mtype == TMessageType.EXCEPTION:
      x = TApplicationException()
      x.read(self._iprot)
      self._iprot.readMessageEnd()
      raise x
    result = add_result()
    result.read(self._iprot)
    self._iprot.readMessageEnd()
    if result.success != None:
      return result.success
    raise TApplicationException(TApplicationException.MISSING_RESULT, "add failed: unknown result");


class Processor(Iface, TProcessor):
  def __init__(self, handler):
    TProcessor.__init__(self)
    self._handler = handler
    self._processMap = {}
    self._processMap["add"] = Processor.process_add

  @process_main()
  def process(self,): pass

  @process_method(oneway=False)
  def process_add(self, args, handler_ctx):
    result = add_result()
    try:
      result.success = self._handler.add(args.num1, args.num2)
    except:
      ex = sys.exc_info()[1]
      self._event_handler.handlerError(handler_ctx, 'add', ex)
      result = Thrift.TApplicationException(message=str(ex))
    return result

Iface._processor_type = Processor

class ContextProcessor(ContextIface, TProcessor):
  def __init__(self, handler):
    TProcessor.__init__(self)
    self._handler = handler
    self._processMap = {}
    self._processMap["add"] = ContextProcessor.process_add

  @process_main()
  def process(self,): pass

  @process_method(oneway=False)
  def process_add(self, args, handler_ctx):
    result = add_result()
    try:
      result.success = self._handler.add(handler_ctx, args.num1, args.num2)
    except:
      ex = sys.exc_info()[1]
      self._event_handler.handlerError(handler_ctx, 'add', ex)
      result = Thrift.TApplicationException(message=str(ex))
    return result

ContextIface._processor_type = ContextProcessor

# HELPER FUNCTIONS AND STRUCTURES

class add_args:
  """
  Attributes:
   - num1
   - num2
  """

  thrift_spec = None
  __init__ = None
  @staticmethod
  def isUnion():
    return False

  def read(self, iprot):
    if (iprot.__class__ == TBinaryProtocol.TBinaryProtocolAccelerated or (iprot.__class__ == THeaderProtocol.THeaderProtocol and iprot.get_protocol_id() == THeaderProtocol.THeaderProtocol.T_BINARY_PROTOCOL)) and isinstance(iprot.trans, TTransport.CReadableTransport) and self.thrift_spec is not None and fastbinary is not None:
      fastbinary.decode_binary(self, iprot.trans, [self.__class__, self.thrift_spec, False], utf8strings=UTF8STRINGS)
      return
    if (iprot.__class__ == TBinaryProtocol.TBinaryProtocolAccelerated or (iprot.__class__ == THeaderProtocol.THeaderProtocol and iprot.get_protocol_id() == THeaderProtocol.THeaderProtocol.T_BINARY_PROTOCOL)) and isinstance(iprot.trans, TTransport.CReadableTransport) and self.thrift_spec is not None and fastproto is not None:
      fastproto.decode(self, iprot.trans, [self.__class__, self.thrift_spec, False], utf8strings=UTF8STRINGS, protoid=0)
      return
    if (iprot.__class__ == TCompactProtocol.TCompactProtocolAccelerated or (iprot.__class__ == THeaderProtocol.THeaderProtocol and iprot.get_protocol_id() == THeaderProtocol.THeaderProtocol.T_COMPACT_PROTOCOL)) and isinstance(iprot.trans, TTransport.CReadableTransport) and self.thrift_spec is not None and fastproto is not None:
      fastproto.decode(self, iprot.trans, [self.__class__, self.thrift_spec, False], utf8strings=UTF8STRINGS, protoid=2)
      return
    iprot.readStructBegin()
    while True:
      (fname, ftype, fid) = iprot.readFieldBegin()
      if ftype == TType.STOP:
        break
      if fid == 1:
        if ftype == TType.I32:
          self.num1 = iprot.readI32()
        else:
          iprot.skip(ftype)
      elif fid == 2:
        if ftype == TType.I32:
          self.num2 = iprot.readI32()
        else:
          iprot.skip(ftype)
      else:
        iprot.skip(ftype)
      iprot.readFieldEnd()
    iprot.readStructEnd()

  def write(self, oprot):
    if (oprot.__class__ == TBinaryProtocol.TBinaryProtocolAccelerated or (oprot.__class__ == THeaderProtocol.THeaderProtocol and oprot.get_protocol_id() == THeaderProtocol.THeaderProtocol.T_BINARY_PROTOCOL)) and self.thrift_spec is not None and fastbinary is not None:
      oprot.trans.write(fastbinary.encode_binary(self, [self.__class__, self.thrift_spec, False], utf8strings=UTF8STRINGS))
      return
    if (oprot.__class__ == TBinaryProtocol.TBinaryProtocolAccelerated or (oprot.__class__ == THeaderProtocol.THeaderProtocol and oprot.get_protocol_id() == THeaderProtocol.THeaderProtocol.T_BINARY_PROTOCOL)) and self.thrift_spec is not None and fastproto is not None:
      oprot.trans.write(fastproto.encode(self, [self.__class__, self.thrift_spec, False], utf8strings=UTF8STRINGS, protoid=0))
      return
    if (oprot.__class__ == TCompactProtocol.TCompactProtocolAccelerated or (oprot.__class__ == THeaderProtocol.THeaderProtocol and oprot.get_protocol_id() == THeaderProtocol.THeaderProtocol.T_COMPACT_PROTOCOL)) and self.thrift_spec is not None and fastproto is not None:
      oprot.trans.write(fastproto.encode(self, [self.__class__, self.thrift_spec, False], utf8strings=UTF8STRINGS, protoid=2))
      return
    oprot.writeStructBegin('add_args')
    if self.num1 != None:
      oprot.writeFieldBegin('num1', TType.I32, 1)
      oprot.writeI32(self.num1)
      oprot.writeFieldEnd()
    if self.num2 != None:
      oprot.writeFieldBegin('num2', TType.I32, 2)
      oprot.writeI32(self.num2)
      oprot.writeFieldEnd()
    oprot.writeFieldStop()
    oprot.writeStructEnd()

  def __repr__(self):
    L = []
    for key, value in six.iteritems(self.__dict__):
      padding = ' ' * (len(key) + 1)
      value = pprint.pformat(value)
      value = padding.join(value.splitlines(True))
      L.append('    %s=%s' % (key, value))
    return "%s(\n%s)" % (self.__class__.__name__, ",\n".join(L))

  def __eq__(self, other):
    return isinstance(other, self.__class__) and self.__dict__ == other.__dict__

  def __ne__(self, other):
    return not (self == other)

all_structs.append(add_args)
add_args.thrift_spec = (
  None, # 0
  (1, TType.I32, 'num1', None, None, 2, ), # 1
  (2, TType.I32, 'num2', None, None, 2, ), # 2
)

def add_args__init__(self, num1=None, num2=None,):
  self.num1 = num1
  self.num2 = num2

add_args.__init__ = add_args__init__

class add_result:
  """
  Attributes:
   - success
  """

  thrift_spec = None
  __init__ = None
  @staticmethod
  def isUnion():
    return False

  def read(self, iprot):
    if (iprot.__class__ == TBinaryProtocol.TBinaryProtocolAccelerated or (iprot.__class__ == THeaderProtocol.THeaderProtocol and iprot.get_protocol_id() == THeaderProtocol.THeaderProtocol.T_BINARY_PROTOCOL)) and isinstance(iprot.trans, TTransport.CReadableTransport) and self.thrift_spec is not None and fastbinary is not None:
      fastbinary.decode_binary(self, iprot.trans, [self.__class__, self.thrift_spec, False], utf8strings=UTF8STRINGS)
      return
    if (iprot.__class__ == TBinaryProtocol.TBinaryProtocolAccelerated or (iprot.__class__ == THeaderProtocol.THeaderProtocol and iprot.get_protocol_id() == THeaderProtocol.THeaderProtocol.T_BINARY_PROTOCOL)) and isinstance(iprot.trans, TTransport.CReadableTransport) and self.thrift_spec is not None and fastproto is not None:
      fastproto.decode(self, iprot.trans, [self.__class__, self.thrift_spec, False], utf8strings=UTF8STRINGS, protoid=0)
      return
    if (iprot.__class__ == TCompactProtocol.TCompactProtocolAccelerated or (iprot.__class__ == THeaderProtocol.THeaderProtocol and iprot.get_protocol_id() == THeaderProtocol.THeaderProtocol.T_COMPACT_PROTOCOL)) and isinstance(iprot.trans, TTransport.CReadableTransport) and self.thrift_spec is not None and fastproto is not None:
      fastproto.decode(self, iprot.trans, [self.__class__, self.thrift_spec, False], utf8strings=UTF8STRINGS, protoid=2)
      return
    iprot.readStructBegin()
    while True:
      (fname, ftype, fid) = iprot.readFieldBegin()
      if ftype == TType.STOP:
        break
      if fid == 0:
        if ftype == TType.I64:
          self.success = iprot.readI64()
        else:
          iprot.skip(ftype)
      else:
        iprot.skip(ftype)
      iprot.readFieldEnd()
    iprot.readStructEnd()

  def write(self, oprot):
    if (oprot.__class__ == TBinaryProtocol.TBinaryProtocolAccelerated or (oprot.__class__ == THeaderProtocol.THeaderProtocol and oprot.get_protocol_id() == THeaderProtocol.THeaderProtocol.T_BINARY_PROTOCOL)) and self.thrift_spec is not None and fastbinary is not None:
      oprot.trans.write(fastbinary.encode_binary(self, [self.__class__, self.thrift_spec, False], utf8strings=UTF8STRINGS))
      return
    if (oprot.__class__ == TBinaryProtocol.TBinaryProtocolAccelerated or (oprot.__class__ == THeaderProtocol.THeaderProtocol and oprot.get_protocol_id() == THeaderProtocol.THeaderProtocol.T_BINARY_PROTOCOL)) and self.thrift_spec is not None and fastproto is not None:
      oprot.trans.write(fastproto.encode(self, [self.__class__, self.thrift_spec, False], utf8strings=UTF8STRINGS, protoid=0))
      return
    if (oprot.__class__ == TCompactProtocol.TCompactProtocolAccelerated or (oprot.__class__ == THeaderProtocol.THeaderProtocol and oprot.get_protocol_id() == THeaderProtocol.THeaderProtocol.T_COMPACT_PROTOCOL)) and self.thrift_spec is not None and fastproto is not None:
      oprot.trans.write(fastproto.encode(self, [self.__class__, self.thrift_spec, False], utf8strings=UTF8STRINGS, protoid=2))
      return
    oprot.writeStructBegin('add_result')
    if self.success != None:
      oprot.writeFieldBegin('success', TType.I64, 0)
      oprot.writeI64(self.success)
      oprot.writeFieldEnd()
    oprot.writeFieldStop()
    oprot.writeStructEnd()

  def __repr__(self):
    L = []
    for key, value in six.iteritems(self.__dict__):
      padding = ' ' * (len(key) + 1)
      value = pprint.pformat(value)
      value = padding.join(value.splitlines(True))
      L.append('    %s=%s' % (key, value))
    return "%s(\n%s)" % (self.__class__.__name__, ",\n".join(L))

  def __eq__(self, other):
    return isinstance(other, self.__class__) and self.__dict__ == other.__dict__

  def __ne__(self, other):
    return not (self == other)

all_structs.append(add_result)
add_result.thrift_spec = (
  (0, TType.I64, 'success', None, None, 2, ), # 0
)

def add_result__init__(self, success=None,):
  self.success = success

add_result.__init__ = add_result__init__

fix_spec(all_structs)
del all_structs

