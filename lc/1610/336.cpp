class Solution {
    int wsize{0};
    unordered_set<int> pairs;
    unordered_map<string, int> index;
    inline int pair_encode(int x, int y){return x*wsize+y;}
    inline vector<int> pair_decode(int z){return vector<int>{z/wsize, z%wsize};}
    void add_one(int le, int ri, const string& one, int i){
        int len = one.size();
        for(;;){
            bool flag = false;
            if(le < 0){
                // find right
                string to_find = "";
                for(int j=ri; j<len; j++)
                    to_find += one[j];
                std::reverse(to_find.begin(), to_find.end());
                auto iter = index.find(to_find);
                if(iter != index.end() && iter->second != i)
                    pairs.insert(pair_encode(iter->second, i));
                flag = true;
            }
            if(ri >= len){
                // find left
                string to_find = "";
                for(int j=0; j<=le; j++)
                    to_find += one[j];
                std::reverse(to_find.begin(), to_find.end());
                auto iter = index.find(to_find);
                if(iter != index.end() && iter->second != i)
                    pairs.insert(pair_encode(i, iter->second));
                flag = true;
            }
            // check equal
            if(flag || one[le] != one[ri])
                break;
            le--;
            ri++;
        }
    }
public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        // 161031, 
        wsize = words.size();
        for(int i=0; i<wsize; i++)
            index[words[i]] = i;
        // for each word
        for(int i=0; i<wsize; i++){
            string one = words[i];
            int len = one.size();
            for(int sp=0; sp<=len; sp++)
                add_one(sp-1, sp, one, i);
            for(int sp=0; sp<len; sp++)
                add_one(sp-1, sp+1, one, i);
        }
        // return
        vector<vector<int>> ret;
        for(int z: pairs)
            ret.emplace_back(pair_decode(z));
        return ret;
    }
};