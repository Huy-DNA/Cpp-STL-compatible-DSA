class Solution {
public:
    int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
        const int nrounds = minutesToTest / minutesToDie;
        return ceil(log2(buckets) / log2(nrounds + 1));
    }
};