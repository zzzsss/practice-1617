class Solution {
public:
    int firstUniqChar(string s) {
        // 161004, ...
        int count[128] = {0,};
        for(char x:s)
            count[x] ++;
        int i=0;
        for(i=0;i<s.size();i++)
            if(count[s[i]]<=1)
                return i;
        return -1;
    }
};