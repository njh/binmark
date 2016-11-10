all: hext

hext: hext.c hext.h
	$(CC) -Wall -DHEXT_TOOL -o hext hext.c

test: hext
	@./run-tests.sh

clean:
	rm -f hext
	rm -f tests/*.result

.PHONY: all test clean
