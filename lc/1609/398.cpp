class Solution {
public:
	// 160920:12, the index method seems out of memory, thus ...
    vector<int> ns;
    Solution(vector<int> nums): ns(nums) {
    }
    
    int pick(int target) {
        vector<int> inds{};
        for(int i=0; i<ns.size(); i++){
            if(ns[i]==target)
                inds.push_back(i);
        }
        return inds[rand()%inds.size()];
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(nums);
 * int param_1 = obj.pick(target);
 */