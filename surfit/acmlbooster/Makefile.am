AUTOMAKE_OPTIONS = foreign

$(OBJECTS): libtool
libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status --recheck

INCLUDES = $(TCLINCLUDE) $(SSTUFFINCLUDE) $(SURFITINCLUDE) $(ACMLINCLUDE)
EXTRA_DIST = vc6/acmlbooster*
EXTRA_DIST += src/interface/*.i
EXTRA_DIST += readme.txt
EXTRA_DIST += make_release.bat
EXTRA_DIST += make_debug.bat
EXTRA_DIST += rpmmacros
EXTRA_DIST += make_rpm_fc4
EXTRA_DIST += make_rpm_rh73
EXTRA_DIST += acmlbooster.spec.fc4
EXTRA_DIST += acmlbooster.spec.rh73
EXTRA_DIST += examples/acmlbooster/*.tcl
EXTRA_DIST += examples/acmlbooster/*.txt

lib_LTLIBRARIES = libacmlbooster.la 

libacmlbooster_ladir = $(prefix)/include/acmlbooster
libacmlbooster_la_SOURCES =  src/acmlbooster.cpp     
libacmlbooster_la_SOURCES += src/acmlbooster_wrap.cxx
libacmlbooster_la_SOURCES += src/acml_cg.cpp         
libacmlbooster_la_SOURCES += src/acml_threads.cpp    

libacmlbooster_la_HEADERS =  src/acmlbooster.h
libacmlbooster_la_HEADERS += src/acmlbooster_ie.h       

libacmlbooster_la_LIBADD = $(ACMLLIB) $(TCLLIB) $(SSTUFFLIB) $(SURFITLIB) 
libacmlbooster_la_LDFLAGS = -version-info 1:0:0 -no-undefined --dllname libacmlbooster.dll

dist-hook:

	rm -rf `find $(distdir) -name CVS`; \
	rm -rf `find $(distdir) -name "core*"`; \
	rm -rf `find $(distdir) -name "*.log"`; \
	rm -rf `find $(distdir) -name "*.dat"`

install-data-hook:

	if ! test -d "$(DESTDIR)$(prefix)/share"; then \
		mkdir $(DESTDIR)$(prefix)/share; \
	fi; \
	if ! test -d "$(DESTDIR)$(prefix)/share/$(PACKAGE)-$(VERSION)"; then \
		mkdir $(DESTDIR)$(prefix)/share/$(PACKAGE)-$(VERSION); \
	fi; \
	if test -d "$(DESTDIR)$(prefix)/share/$(PACKAGE)-$(VERSION)/doc"; then \
		rm -rf $(DESTDIR)$(prefix)/share/$(PACKAGE)-$(VERSION)/doc; \
	fi; \
	cp -r doc/html $(DESTDIR)$(prefix)/share/$(PACKAGE)-$(VERSION)/doc ; \
	if test -d "$(DESTDIR)$(prefix)/share/$(PACKAGE)-$(VERSION)/examples"; then \
		rm -rf $(DESTDIR)$(prefix)/share/$(PACKAGE)-$(VERSION)/examples; \
	fi; \
	mkdir $(DESTDIR)$(prefix)/share/$(PACKAGE)-$(VERSION)/examples
	cp -r examples/acmlbooster/ $(DESTDIR)$(prefix)/share/$(PACKAGE)-$(VERSION)/examples; \
	rm -rf `find $(DESTDIR)$(prefix)/share/$(PACKAGE)-$(VERSION) -name CVS`; \
	rm -rf `find $(DESTDIR)$(prefix)/share/$(PACKAGE)-$(VERSION) -name "core*"`; \
	rm -rf `find $(DESTDIR)$(prefix)/share/$(PACKAGE)-$(VERSION) -name ".log"`; \
	rm -rf `find $(DESTDIR)$(prefix)/share/$(PACKAGE)-$(VERSION) -name ".dat"` 

install-exec-hook:

	if test -f $(DESTDIR)$(bindir)/cygacmlbooster-1.dll; then \
		rm -f $(DESTDIR)$(bindir)/libacmlbooster.dll; \
		ln $(DESTDIR)$(bindir)/cygacmlbooster-1.dll $(DESTDIR)$(bindir)/libacmlbooster.dll; \
	fi

uninstall-hook:

	if test -d "$(DESTDIR)$(prefix)/share/$(PACKAGE)-$(VERSION)"; then \
		rm $(DESTDIR)$(prefix)/share/$(PACKAGE)-$(VERSION)/ -rf; \
	fi; \
	if test -f "$(DESTDIR)$(bindir)/cygacmlbooster-1.dll"; then \
		rm -f $(DESTDIR)$(bindir)/libacmlbooster.dll; \
	fi


