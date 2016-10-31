bool operator<(const pair<int, int>& a, const pair<int, int>& b)
{
    return a.first*a.second < b.first*b.second;
}
bool less_size(const pair<int, int>& a, const pair<int, int>& b)
{
    return a.first<b.first && a.second<b.second;
}

class Solution {
public:
    int maxEnvelopes(vector<pair<int, int>>& envelopes) {
        // 161023
        if(envelopes.empty())
            return 0;
        // 1. sort them
        std::sort(envelopes.begin(), envelopes.end());
        // 2. scan O(n^2)
        vector<int> s(envelopes.size(), 1);
        int max_one = 1;
        for(int i=1; i<envelopes.size(); i++){
            int max_jvalue = 0;
            for(int j=i-1; j>=0; j--){
                if(less_size(envelopes[j], envelopes[i]))
                    max_jvalue = std::max(max_jvalue, s[j]);
            }
            s[i] = 1 + max_jvalue;
            max_one = std::max(max_one, s[i]);
        }
        return max_one;
    }
};