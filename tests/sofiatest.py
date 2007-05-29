"""
SofiaSIP testing framework
"""

import servicetest

from twisted.protocols import sip
from twisted.internet import reactor

import dbus
import dbus.glib

class SipProxy(sip.RegisterProxy):
    registry = sip.InMemoryRegistry("127.0.0.1")

    def __init__(self, *args, **kw):
        sip.RegisterProxy.__init__(self, *args, **kw)

    def register(self, message, host, port):
        if hasattr(self, 'registrar_handler'):
            if self.registrar_handler(message, host, port):
                sip.RegisterProxy.register(self, message, host, port)
            else:
                self.unauthorized(message, host, port)



def go(register_cb):
    params = {
        'account': 'sip:testacc@127.0.0.1',
        'password': 'testpwd',
        'port': dbus.UInt32(9090),
    }

    test = servicetest.create_test('sofiasip', 'sip', params)
    test.data['sip'] = SipProxy()
    reactor.listenUDP(9090, test.data['sip'])
    test.data['sip'].registrar_handler = register_cb
    servicetest.run_test(test)

