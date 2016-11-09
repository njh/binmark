hext
====

hext is a markup language and tool for describing binary files.


The following characters are supported:

| Character     | Description                                              |
|---------------|----------------------------------------------------------|
| 0-9 and a-f   | A byte as hexadecimal. Must be two characters long.      |
| Whitespace    | Ignored                                                  |
| Colon or Dash | Ignored - useful for improving readability               |
| ""            | A string of ASCII characters                             |
| .             | A NULL byte                                              |
| #             | The start of a comment - the rest of the line is ignored |


Example
-------

The default is to output as a binary stream - visualised here using the hexdump command:

    ./hext -b tests/ipv6_udp_packet.hext | hexdump -C
    00000000  00 04 a3 2c 2b b9 a4 5e  60 da 58 9d 86 dd 60 03  |...,+..^`.X...`.|
    00000010  b1 b7 00 0d 11 40 20 01  08 b0 ff d5 00 03 a6 5e  |.....@ ........^|
    00000020  60 ff fe da 58 9d 20 01  08 b0 ff d5 00 03 02 04  |`...X. .........|
    00000030  a3 ff fe 2c 2b b9 fa 06  03 f0 00 0d 5e 37 48 65  |...,+.......^7He|
    00000040  6c 6c 6f 20 57 6f 72 6c  64                       |llo World|
    00000049

It is also possible to output as C data structure:

    ./hext -c tests/ipv6_udp_packet.hext
    uint8_t buffer[] = {
        0x00, 0x04, 0xa3, 0x2c, 0x2b, 0xb9, 0xa4, 0x5e, 
        0x60, 0xda, 0x58, 0x9d, 0x86, 0xdd, 0x60, 0x03, 
        0xb1, 0xb7, 0x00, 0x0d, 0x11, 0x40, 0x20, 0x01, 
        0x08, 0xb0, 0xff, 0xd5, 0x00, 0x03, 0xa6, 0x5e, 
        0x60, 0xff, 0xfe, 0xda, 0x58, 0x9d, 0x20, 0x01, 
        0x08, 0xb0, 0xff, 0xd5, 0x00, 0x03, 0x02, 0x04, 
        0xa3, 0xff, 0xfe, 0x2c, 0x2b, 0xb9, 0xfa, 0x06, 
        0x03, 0xf0, 0x00, 0x0d, 0x5e, 0x37, 0x48, 0x65, 
        0x6c, 0x6c, 0x6f, 0x20, 0x57, 0x6f, 0x72, 0x6c, 
        0x64
    };

Or as a stream of hexadecimal text:

    ./hext -x tests/ipv6_udp_packet.hext
    0004a32c2bb9a45e60da589d86dd6003b1b7000d1140200108b0ffd50003a65e60fffeda589d200108b0ffd500030204a3fffe2c2bb9fa0603f0000d5e3748656c6c6f20576f726c64

