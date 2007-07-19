
%define name surfit
%define version 2.2
%define release fc7

Summary: freeware gridding software
Name: %{name}
Version: %{version}
Release: %{release}
Epoch: 1
Source: %{_sourcedir}/%{name}-%{version}.tar.gz
Group: Applications/Math
License: GPL
Url: http://surfit.sourceforge.net
Prefix: %{_prefix}
BuildRoot: %{_builddir}/%{name}-%{version}-buildroot
requires: netcdf >= 3.6.2-5

%description
surfit is a computer program which enables to recalculate scattered data to regular grid (gridding). surfit implements the original gridding method CMOFS, which can deal with various data of different extent of truth.

%prep
%setup -q

%build
./configure --prefix %{_prefix}
make 

%install
rm -rf ${RPM_BUILD_ROOT}
make DESTDIR=${RPM_BUILD_ROOT} install

%post
if test -x /usr/bin/chcon; then
  /usr/bin/chcon system_u:object_r:texrel_shlib_t %{_prefix}/lib/libsurfit_io.so
fi

%clean
rm -rf ${RPM_BUILD_ROOT}

%files
%defattr(-,root,root)
%dir %{_prefix}/bin
%{_prefix}/bin/surfit
%dir %{_prefix}/lib
%{_prefix}/lib/libsstuff*
%{_prefix}/lib/libsurfit*
%{_prefix}/lib/libfreeflow*
%{_prefix}/lib/libglobe*
%{_prefix}/lib/libsurfit_io*
%dir %{_prefix}/include/sstuff
%{_prefix}/include/sstuff/*.h
%dir %{_prefix}/include/surfit
%{_prefix}/include/surfit/*.h
%dir %{_prefix}/include/freeflow
%{_prefix}/include/freeflow/*.h
%dir %{_prefix}/include/globe
%{_prefix}/include/globe/*.h
%dir %{_prefix}/include/surfit_io
%{_prefix}/include/surfit_io/*.h
%dir %{_prefix}/share/%{name}-%{version}
%{_prefix}/share/%{name}-%{version}/*
%dir %{_prefix}/share/applications
%{_prefix}/share/applications/surfit.desktop

