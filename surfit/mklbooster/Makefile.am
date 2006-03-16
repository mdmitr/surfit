AUTOMAKE_OPTIONS = foreign

$(OBJECTS): libtool
libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status --recheck

INCLUDES = $(TCLINCLUDE) $(SSTUFFINCLUDE) $(SURFITINCLUDE) $(MKLINCLUDE)
EXTRA_DIST = vc6/mklbooster*
EXTRA_DIST += src/interface/*.i
EXTRA_DIST += make_release.bat
EXTRA_DIST += make_debug.bat

#CXXFLAGS = -ggdb  -mwindows -DWIN32
#CXXFLAGS = -O2

lib_LTLIBRARIES = libmklbooster.la 

libmklbooster_ladir = $(prefix)/include/mklbooster
libmklbooster_la_SOURCES =  src/mklbooster.cpp     
libmklbooster_la_SOURCES += src/mklbooster_wrap.cxx
libmklbooster_la_SOURCES += src/mkl_cg.cpp         
libmklbooster_la_SOURCES += src/mkl_threads.cpp    

libmklbooster_la_HEADERS =  src/mklbooster.h
libmklbooster_la_HEADERS += src/mklbooster_ie.h       

libmklbooster_la_LIBADD = $(TCLLIB) $(SSTUFFLIB) $(SURFITLIB) $(MKLLIB)
libmklbooster_la_LDFLAGS = -version-info 1:0:0 -no-undefined --dllname libmklbooster.dll

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

	if test -f $(DESTDIR)$(bindir)/cygmklbooster-1.dll; then \
		rm -f $(DESTDIR)$(bindir)/libmklbooster.dll; \
		ln $(DESTDIR)$(bindir)/cygmklbooster-1.dll $(DESTDIR)$(bindir)/libmklbooster.dll; \
	fi


