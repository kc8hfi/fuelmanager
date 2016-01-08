Name:		fuelmanager
Version:		0.4.2
Release:		5%{?dist}
Summary:		Manage fuel mileage

Group:		Applications/Productivity
License:		GPLv3+

URL:			https://github.com/kc8hfi/fuelmanager
Source0:		https://github.com/kc8hfi/fuelmanager/fuelmanager-%{version}.tar.bz2

BuildRequires:	qt-devel
BuildRequires:	desktop-file-utils

Requires:	hicolor-icon-theme
Requires:	qt-assistant

%description
Application that keeps track of four things, miles, gallons, cost, and 
the date of each fill-up.  It generates monthly and yearly summaries of 
miles driven, cost of fuel,how many gallons, and fuel mileage.

%prep
%setup -q

%build

qmake-qt4 %{name}.pro PREFIX=%{_prefix}
make %{?_smp_mflags}

%install

make install INSTALL_ROOT=%{buildroot} 

desktop-file-install --dir=%{buildroot}%{_datadir}/applications %{name}.desktop

for s in 16 22 24 32 48 256; do
     %{__mkdir_p} %{buildroot}%{_datadir}/icons/hicolor/${s}x${s}/apps
     %{__cp} icons/${s}x${s}/%{name}.png %{buildroot}%{_datadir}/icons/hicolor/${s}x${s}/apps/%{name}.png
done

%{__mkdir_p} %{buildroot}%{_datadir}/icons/hicolor/scalable/apps/
%{__cp} %{name}.svg %{buildroot}%{_datadir}/icons/hicolor/scalable/apps/

# install the AppData file
%__mkdir_p %{buildroot}%{_datadir}/appdata
cp fuelmanager.appdata.xml %{buildroot}%{_datadir}/appdata/

%post
update-desktop-database &> /dev/null || :

/bin/touch --no-create %{_datadir}/icons/hicolor &>/dev/null || :

%postun
update-desktop-database &> /dev/null || :
if [ $1 -eq 0 ] ; then
    /bin/touch --no-create %{_datadir}/icons/hicolor &>/dev/null
    /usr/bin/gtk-update-icon-cache %{_datadir}/icons/hicolor &>/dev/null || :
fi

%posttrans
/usr/bin/gtk-update-icon-cache %{_datadir}/icons/hicolor &>/dev/null || :

%files
%doc COPYING
%doc documentation/fuelmanager.qhc
%{_bindir}/%{name}
%{_datadir}/appdata/*.*
%{_datadir}/applications/*.*
%{_datadir}/icons/hicolor/scalable/apps/*
%{_datadir}/icons/hicolor/16x16/apps/*
%{_datadir}/icons/hicolor/22x22/apps/*
%{_datadir}/icons/hicolor/24x24/apps/*
%{_datadir}/icons/hicolor/256x256/apps/*
%{_datadir}/icons/hicolor/32x32/apps/*
%{_datadir}/icons/hicolor/48x48/apps/*


%changelog
* Sat May 02 2015 Kalev Lember <kalevlember@gmail.com> - 0.4.1-5
- Rebuilt for GCC 5 C++11 ABI change

* Sat Aug 16 2014 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 0.4.1-4
- Rebuilt for https://fedoraproject.org/wiki/Fedora_21_22_Mass_Rebuild

* Thu Jun 19 2014 Richard Hughes <richard@hughsie.com> - 0.4.1-3
- Install the upstream AppData file

* Fri Jun 13 2014 kc8hfi <kc8hfi@gmail.com> - 0.4.1-2
- Build for release 0.4.1

* Sat Jun 07 2014 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 0.4.0-2
- Rebuilt for https://fedoraproject.org/wiki/Fedora_21_Mass_Rebuild

* Mon Jan 13 2014 Charles Amey <kc8hfi@gmail.com> - 0.4.0-1
- Build for release 0.4.0

* Sat Aug 03 2013 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 0.3.9.1-3
- Rebuilt for https://fedoraproject.org/wiki/Fedora_20_Mass_Rebuild

* Wed Feb 13 2013 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 0.3.9.1-2
- Rebuilt for https://fedoraproject.org/wiki/Fedora_19_Mass_Rebuild

* Wed Jan 02 2013 Charles Amey <kc8hfi@gmail.com> - 0.3.9.1-1
- built for release 0.3.9.1

* Wed Dec 19 2012 Charles Amey <kc8hfi@gmail.com> - 0.3.9
- built for release 0.3.9

* Fri Aug 31 2012 Charles Amey <kc8hfi@gmail.com> - 0.3.8.1-1
- added the documentation file to the files macro

* Sun Jul 22 2012 Charles Amey <kc8hfi@gmail.com> - 0.3.8-1
- added qt assistant in Requires section

* Thu Jun 21 2012 Charles Amey <kc8hfi@gmail.com> - 0.3.7-2
- removed the gcc-c++ from the build requirement

* Thu Jun 21 2012 Charles Amey <kc8hfi@gmail.com> - 0.3.7-1
- built for latest version
  using buildroot macro instead of a variable
  added hicolor-icon-theme for build requirement

* Thu May 31 2012 Charles Amey kc8hfi@gmail.com - 0.3.6-6
- removed unnecessary sections
  fixed spelling errors in the description
 
* Thu Jun 23 2011 Charles Amey kc8hfi@gmail.com - 0.3.6-5
- Built for Release 0.3.6-5

* Sat Jun 11 2011 Charles Amey kc8hfi@gmail.com - 0.3.4-3
- Built for Release 0.3.4

* Thu Jun 09 2011 Charles Amey kc8hfi@gmail.com - 0.3.3-1
- Built for Release 0.3.3

