class Solution {
public:
    vector<int> countBits(int num) {
        // 161030, ...
        if(num==0)
            return vector<int>{0};
        vector<int> ret{0, 1};
        for(int i=2; i<=num; i++){
            if(i%2==0)
                ret.push_back(ret[i>>1]);
            else
                ret.push_back(ret[i>>1]+1);
        }
        return ret;
    }
};