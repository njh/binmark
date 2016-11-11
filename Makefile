PREFIX:=/usr/local

all: hext

hext: hext.c hext.h
	$(CC) -Wall -DHEXT_TOOL -o hext hext.c

test: hext
	@./run-tests.sh

install: hext
	install -d $(PREFIX)/bin
	install -c hext $(PREFIX)/bin

clean:
	rm -f hext
	rm -f tests/*.result

.PHONY: all test install clean
