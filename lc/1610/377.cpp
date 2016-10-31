class Solution {
public:
    int get_way(unordered_map<int, int>& ways, vector<int>& nums, int x){
        if(x==0)
            return 1;
        if(x<0)
            return 0;
        if(ways.find(x) != ways.end())
            return ways[x];
        int ret = 0;
        for(int z: nums){
            ret += get_way(ways, nums, x-z);
        }
        ways[x] = ret;
        return ret;
    }
    int combinationSum4(vector<int>& nums, int target) {
        // 161010-1052
        sort(nums.begin(), nums.end());
        unordered_map<int, int> ways;
        return get_way(ways, nums, target);
    }
};