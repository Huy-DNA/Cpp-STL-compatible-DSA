# Data Structures ⚒️🧱🏠

Data Structures are wonderful and exciting! They're essentially ways of organizing data so that you can perform interested actions (**queries**, **modifying operations**) efficiently on your data. We, human have been doing this for centuries - just that now we're automating the process on a computer!!!

My goal is to:
* Implement data structures as generic as possible. But at the same time just as safe - that's why you can see I mostly support [TriviallyCopyableType](https://cplusplus.com/reference/type_traits/is_trivially_copyable/) only (which is a C++ term). Essentially I can treat data as plain data itself, mindlessly moving, copying, swapping them in memory efficiently without too much fuss: with NonTriviallyCopyableType, I have to consider the side effects of default constructors, copy constructors, copy assignments and destructors, whether the copy constructor is deleted, etc.

Things I want to improve:
* Provide constant version of various class methods where possible. For example: `LinkedList::search`, `ChainTable::search`, .etc.