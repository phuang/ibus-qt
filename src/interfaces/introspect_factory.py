#!/usr/bin/env python

import ibus
import dbus

bus = dbus.SessionBus()
e = ibus.interface.IEngineFactory()
print e.Introspect("/", bus)

