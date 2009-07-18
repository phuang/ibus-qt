#!/bin/sh

qdbusxml2cpp -p qibusibusproxy -c IBusProxy -v org.freedesktop.IBus.xml org.freedesktop.IBus
qdbusxml2cpp -p qibusdbusproxy -c DBusProxy -v org.freedesktop.DBus.xml org.freedesktop.DBus
qdbusxml2cpp -p qibusinputcontextproxy -c IBusInputContextProxy -v org.freedesktop.IBus.InputContext.xml org.freedesktop.IBus.InputContext
