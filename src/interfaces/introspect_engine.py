#!/usr/bin/env python

import ibus
import dbus

bus = dbus.SessionBus()
e = ibus.interface.IEngine()
print e.Introspect("/", bus)

