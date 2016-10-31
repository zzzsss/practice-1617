class Solution {
public:
    int r_find(string& s, int start, int end, int k){
        // recursively find all spans [start, end)
        // if nope
        if(end-start < k)
            return 0;
        // firstly scan and count
        unordered_map<char, int> count;
        for(int i=start; i<end; i++){   //bug2 - for:s
            char x = s[i];
            if(count.find(x) == count.end())
                count[x] = 1;
            else
                count[x] += 1;
        }
        // scan another time
        int max = 0;
        int temp_start = start;
        while(1){
            // find a new start
            while(temp_start<end && count[s[temp_start]]<k)
                temp_start ++;
            // find a end
            int temp_end = temp_start;
            while(temp_end<end && count[s[temp_end]]>=k)
                temp_end ++;
            // if all
            if(temp_start==start && temp_end==end)
                return end-start;
            // recursive find
            int this_one = r_find(s, temp_start, temp_end, k);
            if(this_one > max)
                max = this_one;
            // skip -- bug1: forget this
            temp_start = temp_end + 1;
            if(temp_start >= end)
                break;
        }
        return max;
    }
    int longestSubstring(string s, int k) {
        // 20min, 160927, recursive search (not efficient enough, with repetitions)
        // 10min, bug2
        // if no requirements
        if(k<=1)
            return s.size();
        // else scan
        return r_find(s, 0, s.size(), k);
    }
};