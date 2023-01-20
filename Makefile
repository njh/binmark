PREFIX:=/usr/local
PACKAGE=binmark
VERSION=0.2.0
CFLAGS+=-std=c89 -Wall -pedantic -DVERSION=$(VERSION)
DIST_FILES=$(shell git ls-files) $(EXTRA_DIST)

all: binmark

binmark: binmark.c binmark.h
	$(CC) $(CFLAGS) -DBINMARK_TOOL -o binmark binmark.c

test: binmark
	@./run-tests.sh

install: binmark
	install -d $(PREFIX)/bin
	install -c binmark $(PREFIX)/bin

clean:
	rm -f binmark
	rm -f tests/*.result

dist:
	distdir='$(PACKAGE)-$(VERSION)'; mkdir $$distdir || exit 1; \
	for file in $(DIST_FILES); do \
		cp -pR $$file $$distdir || exit 1; \
	done; \
	tar -zcf $$distdir.tar.gz $$distdir; \
	rm -fr $$distdir

.PHONY: all test install clean
