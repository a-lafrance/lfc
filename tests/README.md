ok for now tests are gonna operate based on some pretty jank mechanisms, but that's fine cause they'll be improved later.

I know this kinda violates project structure but tests will get their own `include`/`src` dirs for now just to make things easy. They'll be compiled via the same global `Makefile` into one target that just runs all tests monolithically (i'm too lazy to come up with a way to run tests granularly because i'll literally do it for `jf` anyway). eventually once jackfruit is done, this project will be switched to it for infra, so `jftest` will cover any testing needs and i won't need this jank solution anymore.

in short: testing is gonna be jank and a little gross for now, but it's just a bare bones way to make sure everything works. once this project and jackfruit are done, `lfc` tests will be run on jackfruit and will be much more pleasant of an experience.
