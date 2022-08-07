# Bucket sort
> Say hellllo to the dreaded **Segmentation fault**. Implementing this algorithm has taught me the lesson of properly planning anything you're going to code me up front. It was a mess patching things up!!!.

Notes about this implementation of Bucket sort:
* Assumptions:
    * All elements are of floating point type.
    * All elements lie within $[0, 1)$.
* Time complexity: With the assumptions that the elements are generated from a uniform distribution over $[0, 1)$,
    * Average-case running time: $\Theta(n)$
    * Best-case running time: $\Theta(n)$ (ex. when every bucket has exactly one element)
    * Worst-case running time: $\Theta(n^2)$ (ex. when all elements end up in one bucket)
* Space complexity: $\Theta(n)$
* Other technical:
    * NOT stable (because this specific version of Insertion sort is not stable). However, fixing this is quite trivial.
    * NOT in-place
    * Only works with random-access iterator (in C++ terminology)

Notes:
* Among the linear-time sorting algorithms I have implemented, this is the only one that works with floating point numbers and also relies on its fast average-case running time.
* Actually even if the elements are not generated from a uniform distribution but we know the continous probability distribution function $P$ that is used to yield those elements, we can modify Bucket sort to sort them in linear time as well!  
> You can view the buckets as disjoint intervals whose union is the range $[0..1)$: 
> * In the case where the $P$ is a uniform distribution, the buckets are just equal splits of the range $[0, 1)$. The idea is to spread the elements across all the buckets. With uniform distribution, any elements are equally likely to fall into any one of those buckets if we partition the range $[0, 1)$ this way. Quite intuitive right??
> * In the general case, the idea is the same - we only need to adjust the buckets' sizes according to the probability distribution $P$ so that **any elements** generated are equally likely to fall into one of the buckets. Figuring out the buckets' sizes is straightforward if you know the function $P$ - if there are $n$ elements, there should be a $1/n$ probability that an element fall into one specific bucket.
