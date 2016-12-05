class Solution {
    vector<string> split_str(const string &s, const char x)
    {
    	vector<string> ret;
    	if(s.empty())	// first check
    		return ret;
    	string before;
    	for(char one : s){
    		if(one == x){	// again NEGATIVE trick
    			ret.emplace_back(before);
    			before = "";
    		}
    		else
    			before += one;
    	}
    	ret.emplace_back(before);
    	return ret;
    }
public:
    bool isValidSerialization(string preorder) {
        // 161111, # always <= n and equals to n+1 at last
        auto l = split_str(preorder, ',');
        int nNum = 0;
        int nNull = 0;
        for(string& one: l){
            if(nNum < nNull)
                return false;
            if(one=="#")
                nNull ++;
            else
                nNum ++;
        }
        return nNull == (nNum+1);
    }
};