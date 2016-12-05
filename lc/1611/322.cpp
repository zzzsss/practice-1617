class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // 16118, dp
        vector<int> nums;
        nums.push_back(0);
        for(int i=1; i<=amount; i++){
            int minNum = -1;
            for(int one: coins){
                int next = i-one;
                if(next>=0 && nums[next]>=0){
                    int newNum = nums[next]+1;
                    if(minNum<0 || newNum<minNum)
                        minNum = newNum;
                }
            }
            nums.push_back(minNum);
        }
        return nums[amount];
    }
};