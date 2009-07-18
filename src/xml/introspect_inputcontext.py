import ibus
bus = ibus.Bus()
ic = bus.create_input_context ("aa")
context = ibus.InputContext (bus, ic)
print context.introspect()
