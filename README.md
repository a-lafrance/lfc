# lfc
A C utility library

## Overview
Consider `lfc` something like an external "standard library" for C, implementing modern conveniences like common data structures, error-checked memory allocation, and generally more well-defined error handling. C doesn't come with a lot of those things out-of-the-box, so I decided to implement them myself in case I'd ever need them.

## Installation & Use
To build `lfc`, start by cloning the repository wherever you'd like. Then, from the root project directory, run `make` or `make liblfc`, which will build the library and place a `liblfc.a` archive in `target/` (relative to the root of the project). From there, you can take the archive from the target directory and use it however you'd like.

### Static Linking
To statically link with `lfc` (the archive produced previously), use the `-l` flag with `clang` or `gcc`, e.g. `clang -llfc <other args>`. Note that you must place the archive somewhere that the linker will look for libraries (see the `-L` flag on `clang` or `gcc`). Also, make sure `lfc`'s headers are discoverable by the compiler (see the `-I` flag on `clang` or `gcc`), which you may achieve by moving/copying the headers from the repository to the desired location. If done correctly, `lfc` should statically link against your library, and you should be able to include and use anything found in `lfc` headers.

### Running Tests
`lfc` has its own unit testing system set up, and provides runnable unit tests integrated with the rest of its build infrastructure. After cloning the repository, run `make lfc_tests` from the root project directory, and an executable unit test file will be built at `target/tests`. Running this file without arguments will run all unit tests, but you can isolate any number of test suites by passing one or more test suite names to the executable (a test suite's name is the prefix found before `_tests` in its filename, e.g. `array_tests.c` is the `array` test suite). You should then see unit test results printed to the screen for any test suites that were directed to run.

**NOTE:** If any build fails (either library or test), you _must_ run `make undo_proper_include` before doing anything else, to shift header files back into the correct place; failing to do so could result in confusion & mild inconvenience at best, and at worst loss of all header files altogether. This is due to an unfortunate consequence of how the build infrastructure is set up, which will hopefully be resolved in future releases. Even though this should never happen in an official (stable) release, it's worth mentioning in case you're working with a modified local copy or fork of the repository.

## Future
From a broad perspective, `lfc` will gain support for more collections & more utilities in the near future -- see the [roadmap](https://github.com/arthurlafrance/lfc/blob/master/ROADMAP.md) for more information about what specifically is planned on being implemented. See the [issues log](https://github.com/arthurlafrance/lfc/issues) for a list of known issues with the current codebase, ranging from actual bugs to potential opportunities for refactoring.
