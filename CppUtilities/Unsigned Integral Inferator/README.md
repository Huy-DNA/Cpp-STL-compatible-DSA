# Unsigned Integral Type Inferator
Used to deduce the smallest unsigned integral type that can hold the value of a specified unsigned integer.
## How to use
```C++
#include "<path>/UIntInfer"

//Demonstration
UIntInfer_T<10> n;      //n is of type uint_8
UIntInfer_T<256> n;     //n is of type uint_16
```
## Consideration
* I recall reading something about `uint_8` being unsafe. Might need to reinvestigate that.
