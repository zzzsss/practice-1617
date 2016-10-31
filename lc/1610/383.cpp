class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        // 161005-1025
        int alln = 256;
        int r[alln] = {0,};
        int m[alln] = {0,};
        for(char x: ransomNote)
            r[x]++;
        for(char x: magazine)
            m[x]++;
        for(int i=0;i<alln;i++)
            if(r[i]>m[i])
                return false;
        return true;
    }
};