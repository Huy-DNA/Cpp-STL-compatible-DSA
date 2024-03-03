# Contribution

We're very welcome for any contribution to the repo. We love to learn and enjoy the many skills of C++ artists. As this repo aims to be somewhat elementary, we don't utilize modern C++ principles much (smart pointer, etc.). Instead, we still manage memory manually. However, some interesting compile-time features such as concepts, templates and SFINAE will be heavily utilized here for compatibility with the STL and also for learning too.

## Bug fixes
* Any kind of memory errors: leak, dangling ref, double free.
* Logic implemented incorrectly.
* Traits implemented incorrectly for a data structures.
* SFINAE header is not good enough.

## Enhancement
* We're planning to utilize `placement new` instead of constraining every data structure to work with `TriviallyCopyable` types.

## More algorithms & data structures
* Please make it as generic as possible and play nice with the STL.
* Fun little utility can be put into `CppUtilities`

Thanks for any contribution!
