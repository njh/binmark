hext
====

hext is a markup language and tool for binary files.


The following characters are supported:

    0-9 and a-f: A byte as hexadecimal 
    Whitespace: ignored
    Colon and Dash: ignored
    "": a string of ASCII characters
    #: The start of a comment - the rest of the line is ignored
    n: a 8-bit decimal number in network byte order
    N: a 16-bit decimal number in network byte order
