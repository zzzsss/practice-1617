class Solution {
public:
    char findTheDifference(string s, string t) {
        // ...
        int rec[128] = {0,};
        for(char x: s)
            rec[x] ++;
        for(char x: t){
            rec[x] --;
            if(rec[x] < 0)
                return x;
        }
        return 0;
    }
};