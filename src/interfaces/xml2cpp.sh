#!/bin/sh

qdbusxml2cpp -p qibusibusproxy -c IBusProxy -v org.freedesktop.IBus.xml org.freedesktop.IBus
qdbusxml2cpp -p qibusdbusproxy -c DBusProxy -v org.freedesktop.DBus.xml org.freedesktop.DBus
qdbusxml2cpp -p qibusinputcontextproxy -c IBusInputContextProxy -v org.freedesktop.IBus.InputContext.xml org.freedesktop.IBus.InputContext
qdbusxml2cpp -a qibusengineadaptor -c IBusEngineAdaptor -v org.freedesktop.IBus.Engine.xml org.freedesktop.IBus.Engine

qdbusxml2cpp -a qibusconfigadaptor -c IBusConfigAdaptor -v org.freedesktop.IBus.Config.xml org.freedesktop.IBus.Config
qdbusxml2cpp -p qibusconfigproxy -c IBusConfigProxy -v org.freedesktop.IBus.Config.xml org.freedesktop.IBus.Config

qdbusxml2cpp -a qibuspaneladaptor -c IBusPanelAdaptor -v org.freedesktop.IBus.Panel.xml org.freedesktop.IBus.Panel
