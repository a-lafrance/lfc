# Unit Tests

For now, tests will look like a subproject of the main `lfc` library project -- they get their own `include` and `src` directories, and operate mostly independently of the main library project. Aside from the test suites themselves (anything with the suffix `_tests`), the assert & setup files are probably the most interesting, because they provide the tools for tests to look nice & work correctly. See the [global README](https://github.com/arthurlafrance/lfc/blob/master/README.md) for information about how to run these unit tests.
