class Solution {
public:
    bool isSubsequence(string s, string t) {
        // 12min, 160929-1057, using indexes, but this one is quite slow ...
        if(s.size()==0)
            return true;
        vector<vector<int>> indexes(128); //this should be enough
        for(int i=0; i<s.size(); i++)
            indexes[s[i]].push_back(i);
        // looping on t
        int checked_place = 0;
        for(char x: t){
            // check first
            if(x == s[0] && checked_place==0)
                checked_place++;
            // maybe new one
            for(int ind: indexes[x]){
                if(ind==checked_place){
                    checked_place++;
                    break;
                }
            }
            // ok?
            if(checked_place==s.size())
                return true;
        }
        return false;
    }
};

class Solution2 {
public:
    bool isSubsequence(string s, string t) {
        // 12min, 160929-1057, using indexes 
        // 5min, 160929-1105, straightforward, but why so complex in the first place?
        if(s.size()==0)
            return true;
        // looping on t
        int checked_place = 0;
        for(char x: t){
            if(x == s[checked_place])
                checked_place++;
            // ok?
            if(checked_place==s.size())
                return true;
        }
        return false;
    }
};