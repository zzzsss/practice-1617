class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        // 15min, 161011, simple scan (wrong comprehension of the problem)
        // 30min, O(n^2)
        // 1. delete repetation and prepare vectors
        if(nums.size()<=1)
            return nums.size();
        vector<int> n2;
        for(int i=0;i<nums.size();i++){
            if(i==0 || nums[i]!=nums[i-1])
                n2.push_back(nums[i]);
        }
        vector<int> ups(n2.size(),1);
        vector<int> downs(n2.size(),1);
        // 2. scan them
        int max_len = 1;
        for(int i=1;i<n2.size();i++){
            int j = i-1;
            while(j>=0){
                if(n2[j]<n2[i]){
                    ups[i] = std::max(ups[i], downs[j]+1);
                }
                else if(n2[j]>n2[i]){
                    downs[i] = std::max(downs[i],ups[j]+1);
                }
                j--;
            }
            max_len = std::max(max_len, ups[i]);
            max_len = std::max(max_len, downs[i]);
        }
        return max_len;
    }
};