
%define name surfit
%define version 3.0
%define group Applications/Engineering

Summary: Gridding software
Name: %{name}
Version: %{version}
Release: 0%{?dist}
Epoch: 1
Source: %{_sourcedir}/%{name}-%{version}.tar.gz
Group: %{group}
License: GPL
Url: http://surfit.sourceforge.net
BuildRoot: %{_builddir}/%{name}-%{version}-buildroot
Requires: netcdf >= 3.6.2-5
BuildRequires: zlib-devel, libpng-devel, tcl-devel
#BuildRequires: netcdf-devel
Requires: desktop-file-utils
Packager: Mikhail Dmitrievsky <mishadm@mail.ru>

%description
surfit is a computer program which enables to recalculate scattered data 
to regular grid (gridding). surfit implements the original gridding method 
CMOFS, which can deal with various data of different extent of truth.

%package devel
Summary: Development files for %{name}
Group: %{group}

%description devel
Development files for %{name}

%package html
Summary: Documentation in html format for %{name}
Group: %{group}

%package examples
Summary: Examples for %{name}
Group: %{group}

%description examples
Examples data and scripts for %{name}

%description html
Documentation in html format for %{name}

%prep
%setup -q

%build
./configure --prefix=%{_prefix}
make 

%install
rm -rf ${RPM_BUILD_ROOT}
make DESTDIR=${RPM_BUILD_ROOT} install

desktop-file-install surfit.desktop


%post 
/sbin/ldconfig
if test -x /usr/bin/chcon; then
  /usr/bin/chcon system_u:object_r:texrel_shlib_t %{_libdir}/libsurfit_io.so*
fi

%postun -p /sbin/ldconfig

%clean
rm -rf ${RPM_BUILD_ROOT}

%files
%defattr(-,root,root)
%{_bindir}/surfit
%{_libdir}/libsstuff.so*
%{_libdir}/libsurfit.so*
%{_libdir}/libsurfit_io.so*
%{_libdir}/libfreeflow.so*
%{_libdir}/libglobe.so*
%doc %{_docdir}/%{name}-%{version}/README
%doc %{_docdir}/%{name}-%{version}/COPYING
%{_datadir}/applications/surfit.desktop

%files devel
%defattr(-,root,root)
%{_includedir}/*
%{_libdir}/*.a
#%{_libdir}/*.la
%{_libdir}/*.so

%files html
%defattr(-,root,root)
%doc %{_docdir}/%{name}-%{version}/*.h*
%doc %{_docdir}/%{name}-%{version}/*.css
%doc %{_docdir}/%{name}-%{version}/*.gif
%doc %{_docdir}/%{name}-%{version}/*.jpg
%doc %{_docdir}/%{name}-%{version}/*.png
%doc %{_docdir}/%{name}-%{version}/*.r*


%files examples
%defattr(-,root,root)
%{_datadir}/%{name}-%{version}/*

%changelog
* Mon Jul 23 2007 Mikhail Dmitrievsky <mishadm@mail.ru> 3.0-0
- first packaging for Fedora 7

