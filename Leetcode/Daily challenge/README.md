# 458. Poor Pigs
> Problem link: https://leetcode.com/problems/poor-pigs/

I manage to kinda work out (but still haven't proven rigorously) that if $n$ is the number of buckets, $k$ is the number of pigs, $d$ is the minimum number of rounds required so that for a pair of given $k$ and $n$, we could figure out which is the bucket with poisonous liquid, then $(d+1)^k \ge n \iff k \ge \lceil \lg n / \lg (d+1)\rceil $.

I was so happy I decided to create a seperate folder for Leetcode.

Can't wait to work out a  rigorous proof for this (and of course, share it here!!!!).