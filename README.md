# lfc
A C utility library

## Overview
`lfc` is basically a collection of things I thought (or found out) I'd need when writing significant amounts of C code, e.g. common data structures, automatically error-checked dynamic memory allocation, and other utilities. It's mostly meant to reduce small amounts of boilerplate, provide cleaner APIs for certain functionality, and save the hassle of having to write the same thing a bunch of times. 

With respect to the contents of this repo, as a user/consumer of the library all that really matters is the header files under `include/lfc`. Those define the public interface of the library, however they're consumed.

Briefly for those curious, the `lfc` subproject (i.e. subfolder of `include` and `src`) is the public contents of the library, i.e. that's what the library exports for use by third parties. The `internals` subproject supplements `lfc` with internal utilities, which are grouped separately because they're explicitly unstable and should never be depended on at all. Finally, the `tests` subproject is a simple test runner for the tests defined throughout the other subprojects.

## Use
To build `lfc`, start by cloning the repo wherever you'd like. Then, from the root project directory, run `make` or `make liblfc.a`, which will build the library and place a `liblfc.a` archive in `target/`. From there, you can take the archive from the target directory and use it however you'd like.

### Static Linking
The static archive produced by the above steps is, of course, meant to be consumed via static linking. In addition to setting up static linking however you choose, make sure `lfc`'s headers are discoverable by the compiler, so that you can include and use the library's public interface. 

If you're curious about the compiler flags required to make all of this happen, look into the `-L` and `-l` flags for linking, and `-I`/`-i` for includes (for `clang` and `gcc`).

### Running Tests
As mentioned previously, `lfc` has a simple unit test runner system set up. To run these tests, run `make tests` after cloning the repo, which will produce a test executable at `target/tests`. Running it with no arguments runs all test suites; you can choose to run one or more specific test suites by passing their names as arguments. Each test suite is defined in a file `*_tests.c` somewhere in a `tests` subfolder of a subproject; its name is the part that comes before `_tests`.

## Future
From a broad perspective, `lfc` will gain support for more collections & more utilities in the near future -- see the [roadmap](https://github.com/arthurlafrance/lfc/blob/master/ROADMAP.md) for more information about what specifically is planned on being implemented. See [issues](https://github.com/arthurlafrance/lfc/issues) for a list of known issues with the current codebase, ranging from actual bugs to potential opportunities for refactoring.
