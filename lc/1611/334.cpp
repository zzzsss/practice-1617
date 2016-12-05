class Solution {
public:
    bool increasingTriplet(const vector<int>& nums) {
        // 161109, longest increasing subsequence >= 3
        vector<int> seqs;
        seqs.push_back(INT_MIN); // seqs[0]==-inf
        // scan
        for(int x: nums){
            if(x > seqs.back()){
                // new one
                seqs.push_back(x);
                if(seqs.size()>3)
                    return true;
            }
            else{
                auto iter = std::upper_bound(seqs.begin(), seqs.end(), x);
                if(*(iter-1) != x) // update
                    *iter = x;
            }
        }
        return false;
    }
};