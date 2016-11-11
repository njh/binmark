PREFIX:=/usr/local
PACKAGE=hext
VERSION=0.1.0
CFLAGS+=-Wall -DVERSION=$(VERSION)

all: hext

hext: hext.c hext.h
	$(CC) $(CFLAGS) -DHEXT_TOOL -o hext hext.c

test: hext
	@./run-tests.sh

install: hext
	install -d $(PREFIX)/bin
	install -c hext $(PREFIX)/bin

clean:
	rm -f hext
	rm -f tests/*.result

dist:
	distdir='$(PACKAGE)-$(VERSION)'; mkdir $$distdir || exit 1; \
	list=`git ls-files`; for file in $$list; do \
		cp -pR $$file $$distdir || exit 1; \
	done; \
	tar -zcf $$distdir.tar.gz $$distdir; \
	rm -fr $$distdir

.PHONY: all test install clean
