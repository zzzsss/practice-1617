class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        // 161026, ...
        vector<int> ret;
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        for(int i1=0, i2=0; i1<nums1.size()&&i2<nums2.size();){
            if(nums1[i1]<nums2[i2])
                i1++;
            else if(nums1[i1]>nums2[i2])
                i2++;
            else{
                if(!ret.empty() && ret.back()==nums1[i1]);
                else
                    ret.push_back(nums1[i1]);
                i1++;
                i2++;
            }
        }
        return ret;
    }
};