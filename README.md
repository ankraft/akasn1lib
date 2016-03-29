# AKASN1Lib

ASN.1 Encoding / Decoding library in C

## Introduction
This C library offers encoding and decoding functions for ASN.1 data types. 

ASN.1 was originally specified in the CCITT recommendation X.208. This library
support the Basic Encoding Rules (BER), which is a format for encoding ASN.1
structures, and that was originally specified in X.209.


### BER Encoding / Decoding
The library supports the following ASN.1 (BER) data types and structures. 
Missing types could easily be added by writing the necessary encoders and 
decoders for those types.

All the necessary support functions for encoding/decoding of tags and length
values are available in the library.

### Types

- INTEGER
- OCTETSTRING
- NULLVALUE
- OBJECTID
- EXTERNAL
- ENUMERATED
- SEQUENCE
- SET
- NUMERICSTRING
- PRINTABLESTRING
- TELETEXSTRING
- VIDEOTEXSTRING
- IA5STRING
- GRAPHICSTRING
- VISIBLESTRING
- GENERALSTRING

###  Classes
- UNIVERSAL
- APPLICATION
- CONTEXT
- PRIVATE

### Coding
- PRIMITIVE
- CONSTRUCTED

### Length
- DEFINITIVE
- INDEFINITE


## Installation
Just check out the repository and make necessary adjustments to the Makefile. It
should compile on common 32- and 64-bit systems without problems.

## Documentation
Doxygen - generated documentation is [available](doc/html/index.html)
.

## Limitations
- Most values are limited to 32 bit integers.
- The build-in file handling is very primitive and currently only supports reading from and writing to a single file.


## History
This library was written in the early 1990's and was used in a couple of 
projects and products, namely X.400 mail clients and converters (which somehow
indicates the age of the library quite well), and encoders, decoders and engines
for the MHEG-5 multimedia presentation standard.

## License
The MIT License (MIT)

Copyright (c) 1993 - 2016 Andreas Kraft

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
