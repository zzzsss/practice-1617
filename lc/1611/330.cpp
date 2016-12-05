class Solution {
public:
    int minPatches(const vector<int>& nums, int n) {
        // 161111, greedy
        int curSum = 0;
        int numP = 0;
        int index = 0;
        for(int i=1; i<=n && i > 0;){
            if(index<nums.size() && nums[index] <= i){
                curSum += nums[index];
                i = curSum + 1;
                index ++;
            }
            else{
                numP ++;
                curSum += i;
                i = curSum + 1;
            }
        }
        return numP;
    }
};