# lfc
A C utility library

## Overview
Consider `lfc` something like an external "standard library" for C, implementing modern conveniences like common data structures, error-checked memory allocation, and generally more well-defined error handling. C doesn't come with a lot of those things out-of-the-box, so I decided to implement them myself in case I'd ever need them.

### Contents
The contents of this repository are organized mostly the same as a typical C project: headers in `include/`, source files in `src/`, & build files in `target/`. The project is split into 3 subprojects:
* The main `lfc` project: this is where the public interface of the library is implemented. For third-party users, this is what you interact with & have direct access to.
* The `internals` companion project that implements any internal-use only functionality. The point of this project is to make explicit the public and private API of the library, without needing to resort entirely to something like a naming convention. Anything in this subproject is not guaranteed to be stable, because it's intended for internal use only, so third-party users should _never_ rely on the stability of this interface. It may (and likely will) change significantly between versions.
* The `tests` project that provides a general framework for running unit tests. Note, however, that tests are actually implemented in the `lfc` subproject (see any `tests` directory for the corresponding test suites). There's a certain amount of natural coupling between the `lfc` and `tests` projects, and there's really no good way to solve it -- no matter how you implement it, `tests` will have to have intimate knowledge of `lfc` to know what to test.

## Installation & Use
To build `lfc`, start by cloning the repository wherever you'd like. Then, from the root project directory, run `make` or `make liblfc.a`, which will build the library and place a `liblfc.a` archive in `target/` (relative to the root of the project). From there, you can take the archive from the target directory and use it however you'd like.

### Static Linking
To statically link with `lfc`, use the `-l` flag with `clang` or `gcc`, e.g. `clang -llfc <other args>`. Note that you must place the archive somewhere that the linker will look for libraries (see the `-L` flag on `clang` or `gcc`). Also, make sure `lfc`'s headers are discoverable by the compiler (see the `-I` flag on `clang` or `gcc`), which you may achieve by moving/copying the headers from the repository to the desired location. If done correctly, `lfc` should statically link against your library, and you should be able to include and use anything found in `lfc` headers.

### Running Tests
`lfc` has its own unit testing system set up, and provides runnable unit tests integrated with the rest of its build infrastructure. After cloning the repository, run `make tests` from the root project directory, and an executable unit test file will be built at `target/tests`. Running this file without arguments will run all unit tests, but you can isolate any number of test suites by passing one or more test suite names to the executable (a test suite's name is the prefix found before `_tests` in its filename, e.g. `array_tests.c` is the `array` test suite). You should then see unit test results printed to the screen for any test suites that were directed to run.

## Future
From a broad perspective, `lfc` will gain support for more collections & more utilities in the near future -- see the [roadmap](https://github.com/arthurlafrance/lfc/blob/master/ROADMAP.md) for more information about what specifically is planned on being implemented. See [issues](https://github.com/arthurlafrance/lfc/issues) for a list of known issues with the current codebase, ranging from actual bugs to potential opportunities for refactoring.
