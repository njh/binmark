all: hext

hext: hext.c hext.h
	$(CC) -Wall -DHEXT_TOOL -o hext hext.c

clean:
	rm -f hext

.PHONY: all clean
