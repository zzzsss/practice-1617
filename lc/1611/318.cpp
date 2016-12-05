class Solution {
public:
    int maxProduct(vector<string>& words) {
        // 161120, transformed to bits
        vector<int> onesBRepr;
        int curBRepr = 0x1;
        // construct repr
        for(int i='a'; i<='z'; i++){
            onesBRepr.push_back(curBRepr);
            curBRepr = (curBRepr << 1);
        }
        // transform to bits
        vector<pair<int, int>> wordsBRepr;
        for(const string& s: words){
            int one = 0;
            for(char x: s)
                one |= onesBRepr[x-'a'];
            wordsBRepr.push_back(make_pair(one, s.size()));
        }
        // calculate them
        int maxVal = 0;
        for(int i=0; i<wordsBRepr.size(); i++)
            for(int j=i+1; j<wordsBRepr.size(); j++)
                if(!(wordsBRepr[i].first&wordsBRepr[j].first))
                    maxVal = std::max(maxVal, wordsBRepr[i].second*wordsBRepr[j].second);
        return maxVal;
    }
};