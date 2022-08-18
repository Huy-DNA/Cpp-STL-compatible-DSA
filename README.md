# Data structure and Algorithm
This is where I store my C++ implementations of data structures and solutions to some algorithmic problems. Hopefully I'll get all of this right. &#128563; &#128563; &#128563; 

* My aim is to code as generic as possible, so I'll utilize template and SFINAE in this. I'm pretty much interested in this so-called metaprogramming thing though &#128541; It often goes like "woaahhh!? Did I just write those awfully beautiful SFINAE???" &#129325;
* I'll try to provide as much information as possible in a README file for each implementation here. It's a way that I revise things and might turn out useful in the future!? &#129488;

Things I've learnt from this:
* When testing written C++ libraries, always include it first before any other standard library. This way, you can figure out what standard library you forget to include in your written libraries.
* Consider adding constant version of any methods you're writing if it's possible. There are some cases in which it's necessary but hard to see why. Look at the README file of "Direct-addressing table - No Null Marking".