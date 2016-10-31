class Solution {
    vector<int> one;
    vector<int> s;
public:
    Solution(vector<int> nums) {
        one = nums;
        s = nums;
    }
    
    /** Resets the array to its original configuration and return it. */
    vector<int> reset() {
        s = one;
        return s;
    }
    
    /** Returns a random shuffling of the array. */
    vector<int> shuffle() {
		// 151005-1022, prob = 1/n
        for(int i=0;i<s.size();i++){
            int next = rand()%(s.size()-i);
            int tmp = s[i];
            s[i] = s[i+next];
            s[i+next] = tmp;
        }
        return s;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(nums);
 * vector<int> param_1 = obj.reset();
 * vector<int> param_2 = obj.shuffle();
 */