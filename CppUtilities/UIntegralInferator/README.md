# Unsigned Integral Type Inferator
Used to infer the smallest unsigned integral type that can hold the value of a specified unsigned integer.
## How to use
```C++
#include "<path>/UIntInfer"

template <std::size_t n, typename T = UIntInfer_T<n>>
class ...

//Demonstration
UIntInfer_T<10> n;      //uint_8
UIntInfer_T<256> n;     //uint_16
```
## Consideration
* I recall reading something about `uint_8` being unsafe. Might need to reinvestigate that.