hext
====

hext is a markup language and tool for describing binary files, that is easier to
read and write than a continuous stream of hexadecimal characters.


The following characters are supported:

| Character     | Description                                              |
|---------------|----------------------------------------------------------|
| 0-9 and a-f   | A byte as hexadecimal. Must be two characters long.      |
| Whitespace    | Ignored                                                  |
| Colon or Dash | Ignored - useful for improving readability               |
| ""            | A string of ASCII characters                             |
| #             | The start of a comment - the rest of the line is ignored |


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

