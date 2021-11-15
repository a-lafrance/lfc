# Roadmap

## Collections
- [x] Vectors (array lists)
- [x] Owned strings (think Rust's `String` type, as an alternative to bare `char*` for string literals)
- [x] Hash maps
- [ ] Slicing
- [ ] Ranges
- [ ] Iterators

## Error Handling
- [x] Conditional panicking ("panic if"/guard)
- [x] Null pointer unwrapping (panic if null)
- [ ] A true panic system for unrecoverable errors, with stack unwinding

## I/O Utilities
- [ ] Something like `println`/`eprintln`/`fprintln` (print a line to different outstreams)
- [ ] Logging

## Process Management
- [ ] "Spawn-style" forking: create a child process, configure it, and then spawn it

## Other Ideas (may or may not ever materialize)
* Even more collections (tree-based sets/maps, more linked lists, stacks/queues, heaps, etc)
* Other I/O stuff (some kind of structured input parsing maybe?)
* A basic dynamic dispatch/"trait" system (basically stitching function pointers into embedded vtables)
* Graphs and graph-related data structures & algorithms
* Concurrency primitives (e.g. mutexes, read-write locks, channels)
* Smart pointers (e.g. owned, reference-counted)
