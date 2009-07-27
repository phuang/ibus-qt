Name:       ibus-qt
Version:    1.2.0.20090727
Release:    1%{?dist}
Summary:    Qt IBus library and Qt input method plugin
License:    GPLv2+
Group:      System Environment/Libraries
URL:        http://code.google.com/p/ibus/
Source0:    http://ibus.googlecode.com/files/%{name}-%{version}-Source.tar.gz

BuildRoot:  %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

BuildRequires:  qt-devel >= 4.5
BuildRequires:  dbus-devel >= 1.2
BuildRequires:  cmake
Requires:   ibus >= 1.2

%description
Qt IBus library and Qt input method plugin.

%prep
%setup -q -n %{name}-%{version}-Source

%build
%cmake -DCMAKE_INSTALL_PREFIX=%{_usr} -DLIBDIR=%{_libdir}
make VERBOSE=1 C_DEFINES="$RPM_OPT_FLAGS" CXX_DEFINES="$RPM_OPT_FLAGS" %{?_smp_mflags}

%install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT
# %find_lang %{name}

%pre

%post
/sbin/ldconfig

%preun

%postun
/sbin/ldconfig

%clean
rm -rf $RPM_BUILD_ROOT

%files
# -f %{name}.lang
%defattr(-,root,root,-)
%doc
%{_libdir}/libibus-qt.so
%{_libdir}/qt4/plugins/inputmethods/libqtim-ibus.so

%changelog
* Mon Jul 27 2009 Peng Huang <shawn.p.huang@gmail.com> - 1.2.0.20090727
- The first version.