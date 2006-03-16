AUTOMAKE_OPTIONS = foreign

$(OBJECTS): libtool
libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status --recheck

INCLUDES = $(TCLINCLUDE) $(SSTUFFINCLUDE) $(SURFITINCLUDE) $(ACMLINCLUDE)
EXTRA_DIST = vc6/acmlbooster*
EXTRA_DIST += src/interface/*.i
EXTRA_DIST += examples/*
EXTRA_DIST += doc/*
EXTRA_DIST += make_release.bat
EXTRA_DIST += make_debug.bat

#CXXFLAGS = -ggdb  -mwindows -DWIN32
#CXXFLAGS = -O2

lib_LTLIBRARIES = libacmlbooster.la 

libacmlbooster_ladir = $(prefix)/include/acmlbooster
libacmlbooster_la_SOURCES =  src/acmlbooster.cpp     
libacmlbooster_la_SOURCES += src/acmlbooster_wrap.cxx
libacmlbooster_la_SOURCES += src/acml_cg.cpp         
libacmlbooster_la_SOURCES += src/acml_threads.cpp    

libacmlbooster_la_HEADERS =  src/acmlbooster.h
libacmlbooster_la_HEADERS += src/acmlbooster_ie.h       

libacmlbooster_la_LIBADD = $(TCLLIB) $(SSTUFFLIB) $(SURFITLIB) $(ACMLLIB)
libacmlbooster_la_LDFLAGS = -version-info 1:0:0 -no-undefined --dllname libacmlbooster.dll

dist-hook:

	rm -rf `find $(distdir) -name CVS`

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
	cp -r doc/ $(DESTDIR)$(prefix)/share/$(PACKAGE)-$(VERSION)/doc ; \
	if test -d "$(DESTDIR)$(prefix)/share/$(PACKAGE)-$(VERSION)/examples"; then \
		rm -rf $(DESTDIR)$(prefix)/share/$(PACKAGE)-$(VERSION)/examples; \
	fi; \
	mkdir $(DESTDIR)$(prefix)/share/$(PACKAGE)-$(VERSION)/examples
	cp -r examples/ $(DESTDIR)$(prefix)/share/$(PACKAGE)-$(VERSION)/examples; \
	rm -rf `find $(DESTDIR)$(prefix)/share/$(PACKAGE)-$(VERSION) -name CVS`

install-exec-hook:

	if test -f $(DESTDIR)$(bindir)/cygacmlbooster-1.dll; then \
		rm -f $(DESTDIR)$(bindir)/libacmlbooster.dll; \
		ln $(DESTDIR)$(bindir)/cygacmlbooster-1.dll $(DESTDIR)$(bindir)/libacmlbooster.dll; \
	fi


