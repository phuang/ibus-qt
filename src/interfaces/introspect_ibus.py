#!/usr/bin/env python

import ibus
bus = ibus.Bus()
print bus.introspect_ibus()
