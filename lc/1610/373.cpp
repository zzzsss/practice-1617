struct Elem{
    int i1;
    int i2;
    int score;
};
bool operator<(const Elem& a, const Elem& b){return a.score>b.score;}

class Solution {
public:
    vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        // 161016, same as the sorted matrix, merge those lists ...
        vector<pair<int, int>> ret;
        if(nums1.empty() || nums2.empty())
            return ret;
        priority_queue<Elem> queue;
        for(int i=0;i<nums1.size();i++){
            queue.emplace(Elem{i, 0, nums1[i]+nums2[0]});
        }
        while(ret.size()<k && !queue.empty()){
            auto x = queue.top();
            queue.pop();
            ret.emplace_back(make_pair(nums1[x.i1], nums2[x.i2]));
            if(x.i2+1 < nums2.size())
                queue.emplace(Elem{x.i1, x.i2+1, nums1[x.i1]+nums2[x.i2+1]});
        }
        return ret;
    }
};