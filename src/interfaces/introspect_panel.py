#!/usr/bin/env python

import ibus
import dbus

bus = dbus.SessionBus()
e = ibus.interface.IPanel()
print e.Introspect("/", bus)

