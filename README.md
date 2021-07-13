# lfc
A library of miscellaneous C utilities

## Overview
Consider `lfc` an extension of the C standard library to include the conveniences one might expect from a more modern language, like common data structures or more well-defined error handling, because that's pretty much what it feels like to write it. If you find yourself thinking that certain parts of the library look Rust-inspired (looking at you, panicking system), that's because they probably are.

## Installation & Use
`lfc` is built using a pretty simple `Makefile` routine right now. To build the library, run `make` or `make liblfc` from the root project directory, which will place a `liblfc.a` archive file in `target/`.

To use the library, link with it as a static library when compiling any source code, for example: `clang -Iinclude -Llib -llfc file.c`, which will look for headers in `./include`, external libraries in `./lib`, and link with `liblfc`. When doing this, make sure to copy all headers from `include/` in the root project directory into the appropriate place in your project, and place `liblfc.a` wherever it needs to be as well.

## Future
i'll do this later
