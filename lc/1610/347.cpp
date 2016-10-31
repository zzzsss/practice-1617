struct Elem{
    int num;
    int freq;
};
bool operator<(const Elem& x, const Elem& y){return x.freq < y.freq;}

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // 161026, ...
        unordered_map<int, int> maps;   // int -> index
        for(auto x: nums){
            if(maps.find(x) == maps.end())
                maps[x] = 1;
            else
                maps[x] ++;
        }
        priority_queue<Elem> q;
        for(auto x: maps)
            q.emplace(Elem{x.first, x.second});
        vector<int> ret;
        for(int i=0; i<k; i++){
            ret.emplace_back(q.top().num);
            q.pop();
        }
        return ret;
    }
};