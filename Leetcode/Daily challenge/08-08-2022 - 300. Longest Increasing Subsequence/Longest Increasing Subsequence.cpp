//For a subsequence, we only care about the largest (also the last) number of that subsequence
//in order to decide if we can enlarge the subsequence - we call it the `header` of the subsequence.
class Solution {
public:
    //O(nlgn)
    int lengthOfLIS(vector<int>& nums) {
    
        std::vector<int> header_list;           //A list of subsequence
                                                //header_list[i] is the smallest possible header
                                                //of all subsequences of length i + 1
                                                //As we iterate over `nums`, header_list is always in sorted order!
    
        for (int i = 0; i < nums.size(); ++i) {
            int id = greatest_smaller_id(header_list, nums[i]);
            
            if (id == header_list.size() - 1)   //if nums[i] is greater than all of the headers
                header_list.push_back(nums[i]); //header_list grows in size! which means we have found a longer subsequence
            else 
                header_list[id + 1] = nums[i];  //because header_list[id + 1] > nums[i]
                                                //and we can build a subsequence of length id + 2 with header nums[i]
        }
        return header_list.size();
    }
    
    //O(lgn)
    //Returns the greatest number in the sequence that is smaller than val.
    static int greatest_smaller_id(vector<int>& nums, int val) {
        int left = 0;
        int right = nums.size() - 1;
        while (left <= right) {
            int mid = (left + right) >> 1;
            
            if (nums[mid] < val) left = mid + 1;
            else right = mid - 1;
        }
        return right;
    }
    
};