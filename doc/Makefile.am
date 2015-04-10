if HAVE_DOXYGEN

directory = $(top_srcdir)/doc

dist_doc_DATA = $(directory)/html
$(directory)/html: doxyfile.stamp

doxyfile.stamp:
	$(DOXYGEN) Doxyfile
	echo Timestamp > doxyfile.stamp

CLEANFILES = doxyfile.stamp

all-local: doxyfile.stamp
clean-local:
	rm -rf $(top_srcdir)/doc/html

.PHONY: $(directory)/html

endif
