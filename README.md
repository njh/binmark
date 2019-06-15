hext
====

[![Build Status](https://travis-ci.org/njh/hext.svg?branch=master)](https://travis-ci.org/njh/hext)

_hext_ is a markup language and tool for describing binary files, that is easier to
read and write than a continuous stream of hexadecimal characters.


The following characters are supported:

| Character     | Description                                              |
|---------------|----------------------------------------------------------|
| 0-9 and a-f   | A byte as hexadecimal. Must be two characters long.      |
| Whitespace    | Ignored                                                  |
| Colon or Dash | Ignored - useful for improving readability               |
| ""            | A string of ASCII characters                             |
| #             | The start of a comment - the rest of the line is ignored |
| \             | Escape sequences (\0 \a \b \f \n \r \t \v)               |


Example
-------

Given the following sample input file, which is reasonably easy read:

    30             # Packet Type 3: Publish
    11             # Remaining length (17 bytes)
    0004           # Topic name length
    "test"         # Topic name
    "hello world"  # Payload

The default is to output as a binary stream - visualised here using the hexdump command:

    ./hext -b tests/mqtt_publish.hext | hexdump -C
    00000000  30 11 00 04 74 65 73 74  68 65 6c 6c 6f 20 77 6f  |0...testhello wo|
    00000010  72 6c 64                                          |rld|
    00000013

It is also possible to output as C data structure:

    ./hext -c tests/mqtt_publish.hext
    uint8_t buffer[] = {
        0x30, 0x11, 0x00, 0x04, 0x74, 0x65, 0x73, 0x74, 
        0x68, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x77, 0x6f, 
        0x72, 0x6c, 0x64
    };

Or as a stream of hexadecimal text:

    ./hext -x tests/mqtt_publish.hext
    301100047465737468656c6c6f20776f726c64


But why?
--------

I created _hext_ after my test cases, when writing test cases for my Arduino IPv6 Library,
EtherSia, started resulting in long strings of hexadecimal characters in my code. I 
decided that these would be better in seperate external files and realised that I had the 
freedom to decide on the file format, to make them easier to read and write.

A long stream of hexadecimal is difficult to both read and write - particularly picking 
out the different fields and sections. By adding some whitespace, punctuation and 
comments, it is much easier.

Possible uses:

* Describing expected data for automated tests
* Creating new file formats before tools to generate them exist
* Documenting a data structure in a human readable way
* Alternative to a using a hex editor


Design Decisions
----------------

This was my thought process while designing _hext_:

* Readable and concise to write for humans
* Simple for a machine to parse and convert
* Streamable - don't require input to be loaded into a buffer more parsing
* ASCII input - try and avoid potential weird character-set problems
* Not so complex that there wouldn't be other implementations in other languages

