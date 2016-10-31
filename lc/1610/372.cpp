class Solution {
public:
    int superPow(int a, vector<int>& b) {
        // 161017, math ...
        // a^1mod1337, a^10mod1337, ...
        int magic = 1337;
        vector<int> mods;
        mods.push_back(a%magic);
        while(mods.size() < b.size()){
            int one = mods.back();
            int cur = one;
            for(int i=0; i<9; i++)
                cur = (cur*one)%magic;
            mods.push_back(cur);
        }
        // calculate b
        int ret = 1;
        for(int i=b.size()-1; i>=0; i--){
            int digit = b[i];
            int one = mods[b.size()-1-i];
            for(int j=0; j<digit; j++)
                ret = (ret*one)%magic;
        }
        return ret;
    }
};