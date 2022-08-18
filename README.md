# Data structure and Algorithm
This is where I store my C++ implementations of data structures and solutions to some algorithmic problems. Hopefully I'll get all of this right. &#128563; &#128563; &#128563; 

* My aim is to code as generic as possible, so I'll utilize template and SFINAE in this. I'm pretty much interested in this so-called metaprogramming thing though &#128541; It often goes like "woaahhh!? Did I just write those awfully beautiful SFINAE???" &#129325;
* I'll try to provide as much information as possible in a README file for each implementation here. It's a way that I revise things and might turn out useful in the future!? &#129488;

## What I've learnt from this
* Always include self-written libraries first before any other standard libraries.
* Consider adding constant version of any methods you're writing if it's possible. See my notes at [Direct-addressing table - No Null Marking](https://github.com/HuyDNA/DSA/tree/main/Data%20structures/Direct-addressing%20table).
* My project organization and documentation skills are bad lol.

## Some works done
* [Compact List and Fast probabilistic search on Linked List](https://github.com/HuyDNA/DSA/tree/main/Data%20structures/Linked%20list/Compact%20list)
* [Smallest Unsigned Integral Type Inferator for a given number](https://github.com/HuyDNA/DSA/tree/main/CppUtilities/Unsigned%20Integral%20Inferator)

## My plan
1. Implements anything I've learned, in a style that is consistent with the already done work. At the time I write this (19/08/2022), I've implemented `DynamicTable`, `Queue`, `Stack`, `LinkedList`, `CompactList`, `DirectAddressingTable`, many sorting algorithms, a select algorithm, here and there some variants of the aforementions.
2. Spotting anything that I can improve. For example, I've just read about `placement new` that allows to me to decouple object storage and object lifetime -- with this, I can extend my `DynamicTable` class to support `NonTriviallyCopyableType` too! Before I could do that, I may prepare myself by digging into more stuffs about lower-level features of C++. I hope I wouldn't cause chaos and gain some experience in low-level management myself!!! 

## Books that I read
* [Introduction to Algorithm, 3rd edition](https://www.amazon.com/Introduction-Algorithms-3rd-MIT-Press/dp/0262033844) 
