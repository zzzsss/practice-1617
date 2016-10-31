class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        // 161018, 
        if(nums.empty())
            return nums;
        // 1. sort them
        std::sort(nums.begin(), nums.end());
        // 2. find the longest line will be ok, simple O(n^2) scan
        vector<int> times;
        vector<int> backp;
        int max_end = 0;
        for(int i=0; i<nums.size(); i++){
            int one = 1;
            int back_ref = -1;
            {
                int tmp_max = 0;
                for(int j=i-1; j>=0; j--){  // find max
                    if(nums[i]%nums[j]==0 && times[j]>tmp_max){
                        one = 1 + times[j];
                        tmp_max = times[j];
                        back_ref = j;
                    }
                }
            }
            times.push_back(one);
            backp.push_back(back_ref);
            if(one>times[max_end])
                max_end = i;
        }
        // 3. return them
        unordered_set<int> them;
        int end = max_end;
        while(end>=0){
            them.insert(nums[end]);
            end = backp[end];
        }
        vector<int> ret;
        for(int x: nums){
            if(them.find(x) != them.end())
                ret.push_back(x);
        }
        return ret;
    }
};