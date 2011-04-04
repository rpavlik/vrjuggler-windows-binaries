# Python stubs generated by omniidl from /home/vrjuggler/patrick/juggler/modules/tweek/python/../tweek/idl/Observer.idl

import omniORB, _omnipy
from omniORB import CORBA, PortableServer
_0_CORBA = CORBA

_omnipy.checkVersion(2,0, __file__)


#
# Start of module "tweek"
#
__name__ = "tweek"
_0_tweek = omniORB.openModule("tweek", r"/home/vrjuggler/patrick/juggler/modules/tweek/python/../tweek/idl/Observer.idl")
_0_tweek__POA = omniORB.openModule("tweek__POA", r"/home/vrjuggler/patrick/juggler/modules/tweek/python/../tweek/idl/Observer.idl")


# interface Observer
_0_tweek._d_Observer = (omniORB.tcInternal.tv_objref, "IDL:tweek/Observer:1.0", "Observer")
omniORB.typeMapping["IDL:tweek/Observer:1.0"] = _0_tweek._d_Observer
_0_tweek.Observer = omniORB.newEmptyClass()
class Observer :
    _NP_RepositoryId = _0_tweek._d_Observer[1]

    def __init__(self, *args, **kw):
        raise RuntimeError("Cannot construct objects of this type.")

    _nil = CORBA.Object._nil


_0_tweek.Observer = Observer
_0_tweek._tc_Observer = omniORB.tcInternal.createTypeCode(_0_tweek._d_Observer)
omniORB.registerType(Observer._NP_RepositoryId, _0_tweek._d_Observer, _0_tweek._tc_Observer)

# Observer operations and attributes
Observer._d_update = ((), None, None)

# Observer object reference
class _objref_Observer (CORBA.Object):
    _NP_RepositoryId = Observer._NP_RepositoryId

    def __init__(self):
        CORBA.Object.__init__(self)

    def update(self, *args):
        return _omnipy.invoke(self, "update", _0_tweek.Observer._d_update, args)

    __methods__ = ["update"] + CORBA.Object.__methods__

omniORB.registerObjref(Observer._NP_RepositoryId, _objref_Observer)
_0_tweek._objref_Observer = _objref_Observer
del Observer, _objref_Observer

# Observer skeleton
__name__ = "tweek__POA"
class Observer (PortableServer.Servant):
    _NP_RepositoryId = _0_tweek.Observer._NP_RepositoryId


    _omni_op_d = {"update": _0_tweek.Observer._d_update}

Observer._omni_skeleton = Observer
_0_tweek__POA.Observer = Observer
del Observer
__name__ = "tweek"

#
# End of module "tweek"
#
__name__ = "Observer_idl"

_exported_modules = ( "tweek", )

# The end.
