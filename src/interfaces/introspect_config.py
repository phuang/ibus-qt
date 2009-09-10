#!/usr/bin/env python

import ibus
import dbus

bus = dbus.SessionBus()
e = ibus.interface.IConfig()
print e.Introspect("/", bus)

