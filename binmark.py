#!/usr/bin/env python3

import struct

def isxdigit(c):
    return c in [b'0', b'1', b'2', b'3', b'4', b'5', b'6', b'7', b'8', b'9', b'a', b'b', b'c', b'd', b'e', b'f', b'A', b'B', b'C', b'D', b'E', b'F']

def ascii_to_hex(c):
    if c == b'0': return 0
    elif c == b'1': return 1
    elif c == b'2': return 2
    elif c == b'3': return 3
    elif c == b'4': return 4
    elif c == b'5': return 5
    elif c == b'6': return 6
    elif c == b'7': return 7
    elif c == b'8': return 8
    elif c == b'9': return 9
    elif c == b'a' or c == b'A': return 10
    elif c == b'b' or c == b'B': return 11
    elif c == b'c' or c == b'C': return 12
    elif c == b'd' or c == b'D': return 13
    elif c == b'e' or c == b'E': return 14
    elif c == b'f' or c == b'F': return 15
    else: return -1

# Based on: https://en.wikipedia.org/wiki/Escape_sequences_in_C
def escape_to_hex(c):
    if c == b'0': return 0x00
    elif c == b'a': return 0x07
    elif c == b'b': return 0x08
    elif c == b'f': return 0x0C
    elif c == b'n': return 0x0A
    elif c == b'r': return 0x0D
    elif c == b't': return 0x09
    elif c == b'v': return 0x0B
    elif c == b'\\': return 0x5C
    elif c == b'\'': return 0x27
    elif c == b'"': return 0x22
    elif c == b'?': return 0x3F
    else: return -1

def binmark_to_binary(input_buffer):
    output_buffer = bytearray(b"")

    i = 0
    while i < len(input_buffer):
        char = struct.pack("B", input_buffer[i])
        i += 1

        if char.isspace() or char == b':' or char == b'-':
            # Ignore
            continue

        elif char == b'#':
            # Ignore the rest of the line
            while True:
                char2 = struct.pack("B", input_buffer[i])
                i += 1
                if char2 == b'' or char2 == b'\n' or char2 == b'\r':
                    break

        elif isxdigit(char):
            char2 = struct.pack("B", input_buffer[i])
            i += 1
            if not isxdigit(char2):
                raise ValueError(f"Got non-hex digit after hex digit: '{char2}'")

            val = (ascii_to_hex(char) << 4) + ascii_to_hex(char2)
            output_buffer += struct.pack("B", val)

        elif char == b'.':
            # 8-bit Integer
            chars = b""

            while len(chars) < 4:
                char2 = struct.pack("B", input_buffer[i])
                i += 1
                if char2.isdigit() or char2 == b'-':
                    chars += char2
                else:
                    i -= 1
                    break

            if len(chars) < 1 or len(chars) > 4:
                raise ValueError(f"Invalid integer {chars}")
            else:
                num = int(chars) & 0xFF
                output_buffer += struct.pack("B", num)

        elif char == b'"':
            while True:
                char2 = struct.pack("B", input_buffer[i])
                i += 1
                if char2 == b'' or char2 == char:
                    break
                elif char2 == b'\\':
                    char3 = struct.pack("B", input_buffer[i])
                    i += 1
                    escaped = escape_to_hex(char3)
                    if escaped < 0:
                        raise ValueError(f"Invalid escape sequence '{char3}'")
                    else:
                        output_buffer += struct.pack("B", escaped)
                else:
                    output_buffer += char2

        elif char == b'\\':
            char2 = struct.pack("B", input_buffer[i])
            i += 1
            if char2 == b'':
                break
            else:
                escaped = escape_to_hex(char2)
                if escaped < 0:
                    raise ValueError(f"Invalid escape sequence '{char2}'")
                else:
                    output_buffer += struct.pack("B", escaped)

        else:
            raise ValueError(f"Unrecognised character in input: '{char}'")

    return output_buffer
